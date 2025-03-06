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
	
	Camera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AEvergreenPawn::BeginPlay()
{
	Super::BeginPlay();

	// UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	// AEvergreenPlayerController* EPC = UEvergreenGameInstance::GetEvergreenPlayerController();
	//
	// EPC->SetInteractionPlayer(this);
	//
	// if (!EPC->GetThirdPersonPlayer())
	// {
	// 	FVector Location = ThirdPersonPlayerGeneratedTransform.GetLocation();
	// 	FRotator Rotator = ThirdPersonPlayerGeneratedTransform.GetRotation().Rotator();
	//
	// 	AEvergreenCharacter* ThirdPersonPlayer = Cast<AEvergreenCharacter>(
	// 		GetWorld()->SpawnActor(ThirdPersonPlayerClass, &Location, &Rotator));
	// }
}
