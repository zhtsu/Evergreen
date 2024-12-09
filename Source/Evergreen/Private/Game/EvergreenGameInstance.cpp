// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EvergreenGameInstance.h"

#include "Evergreen/Evergreen.h"
#include "LevelSequencePlayer.h"

void UEvergreenGameInstance::SetEvergreenGameMode(EEvergreenGameMode InGameMode)
{
	GameMode = InGameMode;
	OnGameModeChanged.Broadcast(GameMode);
}

void UEvergreenGameInstance::PauseGame()
{
}

void UEvergreenGameInstance::ResumeGame()
{
}

void UEvergreenGameInstance::PlayCutscene(ULevelSequence* LevelSequence, ALevelSequenceActor*& LevelSequenceActor, ULevelSequencePlayer*& LevelSequencePlayer)
{
	LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
		GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);

	if (!LevelSequenceActor || !LevelSequencePlayer)
	{
		FAST_WARNING(TEXT("Unable to create level sequence player"))
		return;
	}
	
	LevelSequencePlayer->Play();
}

void UEvergreenGameInstance::StartMiniGame(TSubclassOf<AMiniGameBase> MiniGameClass)
{
}
