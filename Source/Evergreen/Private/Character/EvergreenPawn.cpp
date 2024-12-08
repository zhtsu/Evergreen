// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EvergreenPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Game/EvergreenGameInstance.h"
#include "GameFramework/FloatingPawnMovement.h"

AEvergreenPawn::AEvergreenPawn()
{
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
}

void AEvergreenPawn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}
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
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEvergreenPawn::Look);
	}
}

void AEvergreenPawn::Move(const FInputActionValue& InputActionValue)
{
	UEvergreenGameInstance* EGI = Cast<UEvergreenGameInstance>(GetGameInstance());
	if (EGI != nullptr && !EGI->IsTestModeEnabled()) return;

	const FVector MovementVector = InputActionValue.Get<FVector>();

	if (Controller != nullptr)
	{
		const FRotator ControlRotation = Controller->GetControlRotation();
		
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
	UEvergreenGameInstance* EGI = Cast<UEvergreenGameInstance>(GetGameInstance());
	if (EGI != nullptr && !EGI->IsTestModeEnabled()) return;

	const FVector LookVector = InputActionValue.Get<FVector>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
		AddControllerRollInput(LookVector.Z);
	}
}
