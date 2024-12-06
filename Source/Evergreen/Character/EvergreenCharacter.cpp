// Fill out your copyright notice in the Description page of Project Settings.


#include "EvergreenCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

AEvergreenCharacter::AEvergreenCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void AEvergreenCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

void AEvergreenCharacter::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		
		const FRotator RotationForRight(0, Rotation.Yaw, Rotation.Roll);
		const FVector RightDirection = UKismetMathLibrary::GetRightVector(RotationForRight);
		AddMovementInput(RightDirection, MovementVector.X);
		
		const FRotator RotationForForward(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = UKismetMathLibrary::GetForwardVector(RotationForForward);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
}
