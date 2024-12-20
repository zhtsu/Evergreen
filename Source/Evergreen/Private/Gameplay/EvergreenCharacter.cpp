// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EvergreenCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Common/AssetPathHub.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gameplay/EvergreenPawn.h"
#include "CineCameraComponent.h"
#include "Gameplay/EvergreenPlayerController.h"
#include "Manager/ViewManager.h"

AEvergreenCharacter::AEvergreenCharacter()
{
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 2000;
	SpringArm->SetRelativeRotation(FRotator(-25, 0, 0));
	SpringArm->SetRelativeLocation(FVector(0, 0, 40));
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritYaw = false;
	Camera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400, 0);
}

void AEvergreenCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AEvergreenPawn* InteractionPlayer = Cast<AEvergreenPawn>(GetWorld()->SpawnActor(InteractorClass));
	if (InteractionPlayer)
	{
		InteractionPlayer->SetActorTransform(GetActorTransform());

		AEvergreenPlayerController::SetGamePlayers(this, InteractionPlayer);
		UViewManager::SetGamePlayers(this, InteractionPlayer);
	}
}

void AEvergreenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	ActivateMappingContext(
		UEvergreenGameInstance::GetEvergreenPlayerController(), PlayerInputComponent);
}

void AEvergreenCharacter::K2_StartRotateCameraBoomYawIfAllowed(float Yaw, bool& AllowRotation)
{
	if (UEvergreenGameInstance::GetEvergreenGameInstance()->GetCurrentGamePlayState() == EGamePlayState::Cutscene)
	{
		AllowRotation = false;
		return;
	}
	
	StartCameraBoomRotation = SpringArm->GetRelativeRotation();
	TargetCameraBoomRotation = StartCameraBoomRotation;
	TargetCameraBoomRotation.Yaw = Yaw;
	
	if (FMath::Abs(StartCameraBoomRotation.Yaw - Yaw) < 1.f)
	{
		AllowRotation = false;
		return;
	}

	UEvergreenGameInstance::GetEvergreenGameInstance()->SetCurrentGamePlayState(EGamePlayState::Cutscene);
	
	AllowRotation = true;
}

void AEvergreenCharacter::K2_EndRotateCameraYaw()
{
	SpringArm->SetRelativeRotation(TargetCameraBoomRotation);
	UEvergreenGameInstance::GetEvergreenGameInstance()->SetCurrentGamePlayState(EGamePlayState::Exploring);
}

void AEvergreenCharacter::K2_StartAdjustCameraBoomIfAllowed(float Length, float Pitch, bool& AllowAdjust)
{
	if (UEvergreenGameInstance::GetEvergreenGameInstance()->GetCurrentGamePlayState() == EGamePlayState::Cutscene)
	{
		AllowAdjust = false;
		return;
	}
	
	StartCameraBoomRotation = SpringArm->GetRelativeRotation();
	TargetCameraBoomRotation = StartCameraBoomRotation;
	TargetCameraBoomRotation.Pitch = Pitch;

	StartCameraBoomLength = SpringArm->TargetArmLength;
	TargetCameraBoomLength = Length;
	
	if (FMath::Abs(StartCameraBoomRotation.Pitch - Pitch) < 1.f
		&& FMath::Abs(StartCameraBoomLength - TargetCameraBoomLength) < 1.f) return;

	UEvergreenGameInstance::GetEvergreenGameInstance()->SetCurrentGamePlayState(EGamePlayState::Cutscene);
	
	AllowAdjust = true;
}

void AEvergreenCharacter::K2_EndAdjustCameraBoom()
{
	SpringArm->TargetArmLength = TargetCameraBoomLength;
	SpringArm->SetRelativeRotation(TargetCameraBoomRotation);
	UEvergreenGameInstance::GetEvergreenGameInstance()->SetCurrentGamePlayState(EGamePlayState::Exploring);
}

void AEvergreenCharacter::Move(const FInputActionValue& InputActionValue)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (!EGI->IsAllowKeyboardInput()) return;
	
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator ControlRotation = SpringArm->GetRelativeRotation();
		
		const FRotator YawRotation(0, ControlRotation.Yaw, 0);
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AEvergreenCharacter::SetCameraBoom(float Length, float Pitch)
{
	SpringArm->TargetArmLength = Length;
	SpringArm->SetRelativeRotation(FRotator(Pitch, 0.f, 0.f));
}

void AEvergreenCharacter::ActivateMappingContext(AEvergreenPlayerController* PlayerController, UInputComponent* PlayerInputComponent)
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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEvergreenCharacter::Move);
	}
}

void AEvergreenCharacter::RemoveMappingContext(AEvergreenPlayerController* PlayerController)
{
	if (!PlayerController) return;
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
	}
}
