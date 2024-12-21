// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EvergreenPlayerController.h"

#include "Gameplay/EvergreenCharacter.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "Gameplay/EvergreenPawn.h"

AEvergreenPlayerController::AEvergreenPlayerController()
{
	UEvergreenGameInstance::SetEvergreenPlayerController(this);
}

void AEvergreenPlayerController::PossessThirdPersonPlayer()
{
	if (ThirdPersonPlayer)
	{
		Possess(ThirdPersonPlayer);
		SwitchToThirdPersonMode();
	}
}

void AEvergreenPlayerController::PossessInteractionPlayer()
{
	if (InteractionPlayer)
	{
		Possess(InteractionPlayer);
		SwitchToInteractionMode();
	}
}

void AEvergreenPlayerController::SwitchToThirdPersonMode()
{
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;
	bShowMouseCursor = false;

	if (ThirdPersonPlayer)
	{
		ThirdPersonPlayer->GetMesh()->SetHiddenInGame(false);
	}
}

void AEvergreenPlayerController::SwitchToInteractionMode()
{
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bShowMouseCursor = true;

	if (ThirdPersonPlayer && InteractionPlayer)
	{
		ThirdPersonPlayer->GetMesh()->SetHiddenInGame(true);
	}
}
