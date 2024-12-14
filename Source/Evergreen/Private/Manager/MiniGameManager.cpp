// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/MiniGameManager.h"
#include "Game/MiniGameBase.h"
#include "Game/EvergreenGameInstance.h"

UMiniGameManager::UMiniGameManager()
{
	
}

void UMiniGameManager::StartMiniGame(TSubclassOf<AMiniGameBase> MiniGameClass, UMiniGameData* MiniGameData)
{
	if (!MiniGameClass || CurrentMiniGame) return;

	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	EGI->SetCurrentGamePlayState(EGamePlayState::MiniGame);

	AMiniGameBase* MiniGame = Cast<AMiniGameBase>(GetWorld()->SpawnActor(MiniGameClass));
	if (MiniGame)
	{
		CurrentMiniGame = MiniGame;
		IMiniGameInterface::Execute_OnStartMiniGame(MiniGame, MiniGameData);
	}
}

void UMiniGameManager::EndMiniGame()
{
	if (CurrentMiniGame == nullptr) return;

	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	EGI->SetCurrentGamePlayState(EGI->GetPreviousGamePlayState());
	
	IMiniGameInterface::Execute_OnEndMiniGame(CurrentMiniGame);
	CurrentMiniGame->Destroy();
	CurrentMiniGame = nullptr;
}
