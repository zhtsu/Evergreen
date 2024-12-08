// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EvergreenPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Game/EvergreenGameInstance.h"

AEvergreenPawn::AEvergreenPawn()
{
	
}

void AEvergreenPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEvergreenPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEvergreenPawn::Move);
		EnhancedInputComponent->BindAction(UpDownAction, ETriggerEvent::Triggered, this, &AEvergreenPawn::UpDown);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AEvergreenPawn::Rotate);
	}
}

void AEvergreenPawn::Move(const FInputActionValue& InputActionValue)
{
	UEvergreenGameInstance* EGI = Cast<UEvergreenGameInstance>(GetGameInstance());
	if (EGI != nullptr && !EGI->IsDebugModeEnabled()) return;

	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator ControlRotation = Controller->GetControlRotation();
		
		const FRotator YawRotation(0, ControlRotation.Yaw, 0);
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AEvergreenPawn::UpDown(const FInputActionValue& InputActionValue)
{
	UEvergreenGameInstance* EGI = Cast<UEvergreenGameInstance>(GetGameInstance());
	if (EGI != nullptr && !EGI->IsDebugModeEnabled()) return;

	
}

void AEvergreenPawn::Rotate(const FInputActionValue& InputActionValue)
{
	UEvergreenGameInstance* EGI = Cast<UEvergreenGameInstance>(GetGameInstance());
	if (EGI != nullptr && !EGI->IsDebugModeEnabled()) return;

	
}

