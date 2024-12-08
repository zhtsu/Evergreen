// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EvergreenGameInstance.h"

void UEvergreenGameInstance::SetEvergreenGameMode(EEvergreenGameMode InGameMode)
{
	GameMode = InGameMode;
	OnGameModeChanged.Broadcast(GameMode);
}
