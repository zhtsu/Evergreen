// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EvergreenPawn.h"

#include "CineCameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "Gameplay/EvergreenPlayerController.h"
#include <Manager/ViewManager.h>
#include <Manager/UIManager.h>

#include "Gameplay/EvergreenCharacter.h"

AEvergreenPawn::AEvergreenPawn()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootScene->Mobility = EComponentMobility::Movable;
	RootComponent = RootScene;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 2000;
	SpringArm->SetRelativeRotation(FRotator(-25, 0, 0));
	SpringArm->SetRelativeLocation(FVector(0, 0, 40));
	SpringArm->bDoCollisionTest = false;
	
	Camera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritYaw = false;
	Camera->bUsePawnControlRotation = false;
}

void AEvergreenPawn::BeginPlay()
{
	Super::BeginPlay();

	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (AEvergreenPlayerController* EPC = UEvergreenGameInstance::GetEvergreenPlayerController())
		EPC->SetInteractionPlayer(this);
	if (UViewManager* ViewManager = EGI->GetSubsystem<UViewManager>())
		ViewManager->SetInteractionPlayer(this);
	if (UUIManager* UIManager = EGI->GetSubsystem<UUIManager>())
		UIManager->SetInteractionPlayer(this);

	if (Controller && Controller->GetControlRotation() != SpringArm->GetRelativeRotation())
	{
		Controller->SetControlRotation(SpringArm->GetRelativeRotation());
	}

	AEvergreenPlayerController* EPC = UEvergreenGameInstance::GetEvergreenPlayerController();
	if (EPC && !EPC->GetThirdPersonPlayer())
	{
		if (AEvergreenCharacter* ThirdPersonPlayer = Cast<AEvergreenCharacter>(GetWorld()->SpawnActor(ThirdPersonPlayerClass)))
		{
			ThirdPersonPlayer->SetActorTransform(GetActorTransform());
			ThirdPersonPlayer->GetMesh()->SetHiddenInGame(true);
		}
	}
}

void AEvergreenPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	ActivateMappingContext(
		UEvergreenGameInstance::GetEvergreenPlayerController(), PlayerInputComponent);
}

void AEvergreenPawn::ActivateMappingContext(AEvergreenPlayerController* PlayerController, UInputComponent* PlayerInputComponent)
{
	if (!PlayerController) return;

	RemoveMappingContext(PlayerController);
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->ClearActionValueBindings();
		EnhancedInputComponent->ClearActionEventBindings();
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEvergreenPawn::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEvergreenPawn::Look);
	}
}

void AEvergreenPawn::RemoveMappingContext(AEvergreenPlayerController* PlayerController)
{
	if (!PlayerController) return;
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
	}
}

void AEvergreenPawn::Move(const FInputActionValue& InputActionValue)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (!EGI->IsTestModeEnabled()) return;

	const FVector MovementVector = InputActionValue.Get<FVector>();

	if (Controller != nullptr)
	{
		const FRotator ControlRotation = SpringArm->GetRelativeRotation();
		
		const FVector ForwardDirection = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);
		const FVector UpVector = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Z);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
		AddMovementInput(UpVector, MovementVector.Z);
	}
}

void AEvergreenPawn::Look(const FInputActionValue& InputActionValue)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (!EGI->IsTestModeEnabled()) return;

	const FVector LookVector = InputActionValue.Get<FVector>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
		AddControllerRollInput(LookVector.Z);
		SpringArm->SetRelativeRotation(Controller->GetControlRotation());
	}
}

void AEvergreenPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (!bCameraOffsetFollowCursorEnabled) return;
	if (!UEvergreenGameInstance::GetEvergreenGameInstance()->IsInteractionMode()) return;
	
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (!PlayerController) return;
	
	FVector2D MousePosition;
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	
	FIntPoint ViewportSize;
	PlayerController->GetViewportSize(ViewportSize.X, ViewportSize.Y);
	
	FVector2D ViewportCenter = FVector2D(ViewportSize) * 0.5;
	
	FVector2D MouseOffset = MousePosition - ViewportCenter;

	bool bIsMouseInViewport = (MousePosition.X > KINDA_SMALL_NUMBER && MousePosition.X < ViewportSize.X)
		&& (MousePosition.Y > KINDA_SMALL_NUMBER && MousePosition.Y < ViewportSize.Y);

	FVector TargetOffset = FVector::ZeroVector;
	if (bIsMouseInViewport)
	{
		TargetOffset += (MouseOffset.X * CameraOffsetScale_X) * FVector::RightVector;
		TargetOffset += (-MouseOffset.Y * CameraOffsetScale_Y) * FVector::UpVector;
	}
	
	SpringArm->SocketOffset = TargetOffset;
}
