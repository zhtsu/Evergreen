// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EvergreenPlayerController.h"

#include "Gameplay/EvergreenCameraModifier.h"
#include "Gameplay/EvergreenCharacter.h"
#include "Gameplay/EvergreenGameInstance.h"

AEvergreenPlayerController::AEvergreenPlayerController()
{
	UEvergreenGameInstance::SetEvergreenPlayerController(this);
}

void AEvergreenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCameraManager->AddNewCameraModifier(UEvergreenCameraModifier::StaticClass());
}

void AEvergreenPlayerController::SetPlayerHiddenInGame(bool bHide)
{
	if (ThirdPersonPlayer)
	{
		if (ThirdPersonPlayer->GetMesh())
		{
			ThirdPersonPlayer->GetMesh()->SetHiddenInGame(bHide);
		}
	}
}
