// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EvergreenPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
	if (!DebugModeEnabled) return;

	
}

void AEvergreenPawn::UpDown(const FInputActionValue& InputActionValue)
{
	if (!DebugModeEnabled) return;

	
}

void AEvergreenPawn::Rotate(const FInputActionValue& InputActionValue)
{
	if (!DebugModeEnabled) return;

	
}

