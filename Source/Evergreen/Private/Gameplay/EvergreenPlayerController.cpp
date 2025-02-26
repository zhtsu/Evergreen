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

		if (ThirdPersonPlayer)
		{
			ThirdPersonPlayer->GetMesh()->SetHiddenInGame(false);
		}
	}
}

void AEvergreenPlayerController::PossessInteractionPlayer()
{
	if (InteractionPlayer)
	{
		Possess(InteractionPlayer);

		if (ThirdPersonPlayer && InteractionPlayer)
		{
			ThirdPersonPlayer->GetMesh()->SetHiddenInGame(true);
		}
	}
}
