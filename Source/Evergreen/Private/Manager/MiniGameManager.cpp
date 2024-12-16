// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/MiniGameManager.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "World/MiniGameBase.h"

UMiniGameManager::UMiniGameManager()
{
	
}

bool UMiniGameManager::StartMiniGame(TSubclassOf<AMiniGameBase> MiniGameClass, UMiniGameData* MiniGameData)
{
	if (!MiniGameClass || IsMiniGameOnProcess(MiniGameClass)) return false;

	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	EGI->SetCurrentGamePlayState(EGamePlayState::MiniGame);

	AMiniGameBase* MiniGame = Cast<AMiniGameBase>(GetWorld()->SpawnActor(MiniGameClass));
	OnProcessMiniGames.Add(MiniGame);
	IMiniGameInterface::Execute_OnStartMiniGame(MiniGame, MiniGameData);

	return true;
}

bool UMiniGameManager::EndMiniGame(TSubclassOf<class AMiniGameBase> MiniGameClass)
{
	if (!IsMiniGameOnProcess(MiniGameClass)) return false;

	AMiniGameBase* EndedMiniGame = nullptr;
	for (AMiniGameBase* MiniGame : OnProcessMiniGames)
	{
		if (MiniGame->GetClass() == MiniGameClass)
		{
			EndedMiniGame = MiniGame;
			break;
		}
	}

	if (EndedMiniGame)
	{
		if (OnProcessMiniGames.Num() - 1 <= 0)
		{
			UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
			EGI->SetCurrentGamePlayState(EGI->GetPreviousGamePlayState());
		}
		
		IMiniGameInterface::Execute_OnEndMiniGame(EndedMiniGame);
		OnProcessMiniGames.Remove(EndedMiniGame);
		EndedMiniGame->Destroy();
		
		return true;
	}

	return false;
}

bool UMiniGameManager::IsMiniGameOnProcess(TSubclassOf<AMiniGameBase> MiniGameClass)
{
	for (AMiniGameBase* MiniGame : OnProcessMiniGames)
	{
		if (MiniGame->GetClass() == MiniGameClass) return true;
	}

	return false;
}

bool UMiniGameManager::IsAnyMiniGameOnProcess()
{
	return OnProcessMiniGames.Num() > 0;
}
