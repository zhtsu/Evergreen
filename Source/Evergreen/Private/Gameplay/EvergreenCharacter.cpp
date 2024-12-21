// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EvergreenCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
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
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
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

	StartCameraBoomLength = SpringArm->TargetArmLength;
	StartCameraBoomYaw = SpringArm->GetRelativeRotation().Yaw;
	StartCameraBoomPitch = SpringArm->GetRelativeRotation().Pitch;
	
	TargetCameraBoomYaw = StartCameraBoomYaw;
	TargetCameraBoomPitch = StartCameraBoomPitch;
	TargetCameraBoomLength = StartCameraBoomLength;
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

void AEvergreenCharacter::K2_StartRotateCameraBoomYawIfAllowed(float Yaw, bool bAllowMove, bool& AllowRotation)
{
	if (UEvergreenGameInstance::GetEvergreenGameInstance()->GetCurrentGamePlayState() == EGamePlayState::Cutscene)
	{
		AllowRotation = false;
		return;
	}

	if (Yaw == -1.f)
	{
		AllowRotation = false;
		return;
	}
	
	TargetCameraBoomYaw = Yaw;
	
	if (FMath::Abs(StartCameraBoomYaw - TargetCameraBoomYaw) < 1.f)
	{
		AllowRotation = false;
		return;
	}

	if (!bAllowMove)
	{
		UEvergreenGameInstance::GetEvergreenGameInstance()->SetCurrentGamePlayState(EGamePlayState::Cutscene);
	}
	
	AllowRotation = true;
}

void AEvergreenCharacter::K2_EndRotateCameraYaw()
{
	StartCameraBoomYaw = TargetCameraBoomYaw;
	
	UEvergreenGameInstance::GetEvergreenGameInstance()->SetCurrentGamePlayState(EGamePlayState::Exploring);
}

void AEvergreenCharacter::K2_StartRotateCameraBoomPitchIfAllowed(float Pitch, bool bAllowMove, bool& AllowRotation)
{
	if (UEvergreenGameInstance::GetEvergreenGameInstance()->GetCurrentGamePlayState() == EGamePlayState::Cutscene)
	{
		AllowRotation = false;
		return;
	}

	if (Pitch == -1.f)
	{
		AllowRotation = false;
		return;
	}
	
	TargetCameraBoomPitch = Pitch;
	
	if (FMath::Abs(StartCameraBoomYaw - TargetCameraBoomYaw) < 1.f)
	{
		AllowRotation = false;
		return;
	}

	if (!bAllowMove)
	{
		UEvergreenGameInstance::GetEvergreenGameInstance()->SetCurrentGamePlayState(EGamePlayState::Cutscene);
	}
	
	AllowRotation = true;
}

void AEvergreenCharacter::K2_EndRotateCameraPitch()
{
	StartCameraBoomPitch = TargetCameraBoomPitch;
	
	UEvergreenGameInstance::GetEvergreenGameInstance()->SetCurrentGamePlayState(EGamePlayState::Exploring);
}

void AEvergreenCharacter::K2_StartAdjustCameraBoomLengthIfAllowed(float Length, bool bAllowMove, bool& AllowAdjust)
{
	if (UEvergreenGameInstance::GetEvergreenGameInstance()->GetCurrentGamePlayState() == EGamePlayState::Cutscene)
	{
		AllowAdjust = false;
		return;
	}

	if (Length == -1.f)
	{
		AllowAdjust = false;
		return;
	}
	
	TargetCameraBoomLength = Length;
	
	if (FMath::Abs(StartCameraBoomLength - TargetCameraBoomLength) < 1.f)
	{
		AllowAdjust = false;
		return;
	}

	if (!bAllowMove)
	{
		UEvergreenGameInstance::GetEvergreenGameInstance()->SetCurrentGamePlayState(EGamePlayState::Cutscene);
	}
	
	AllowAdjust = true;
}

void AEvergreenCharacter::K2_EndAdjustCameraBoomLength()
{
	StartCameraBoomLength = TargetCameraBoomLength;
	
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

void AEvergreenCharacter::SetCameraParams(float Yaw, float Pitch, float Length)
{
	if (Length != -1.f) SpringArm->TargetArmLength = Length;

	FRotator NewRatator = FRotator::ZeroRotator;
	if (Yaw != -1.f) NewRatator.Yaw = Yaw;
	if (Pitch != -1.f) NewRatator.Pitch = Pitch;
	SpringArm->SetRelativeRotation(NewRatator);
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
