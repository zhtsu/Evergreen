// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EvergreenCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AEvergreenCharacter::AEvergreenCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600;
	SpringArm->SetRelativeRotation(FRotator(-25, 0, 0));
	SpringArm->SetRelativeLocation(FVector(0, 0, 40));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
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

void AEvergreenCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bCameraRotating)
	{
		CurrentSpringArmRotator =
			FMath::RInterpTo(CurrentSpringArmRotator, TargetSpringArmRotator, DeltaSeconds, InterpSpeed);
		SpringArm->SetRelativeRotation(CurrentSpringArmRotator);

		if (CurrentSpringArmRotator == TargetSpringArmRotator)
		{
			bCameraRotating = false;
		}
	}
}

void AEvergreenCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentSpringArmRotator = SpringArm->GetRelativeRotation();
}

void AEvergreenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEvergreenCharacter::Move);
	}
}

void AEvergreenCharacter::RotateCameraYaw(float Angle)
{
	FRotator NewRotator = SpringArm->GetRelativeRotation();
	NewRotator.Yaw = Angle;
	TargetSpringArmRotator = NewRotator;
	bCameraRotating = true;
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
