// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/ViewManager.h"

#include "LevelSequencePlayer.h"
#include "Common/CommonMacro.h"
#include "Game/EvergreenGameInstance.h"
#include "Interface/ObservableInterface.h"
#include "Camera/CameraActor.h"

UViewManager::UViewManager()
{
	
}

bool UViewManager::IsObserved(UObject* ObservableObject)
{
	if (!ObservableObject) return false;
	if (!ObservableObject->Implements<UObservableInterface>()) return false;

	if (CurrentObservedObject == ObservableObject) return true;

	return false;
}

void UViewManager::Observe(UObject* ObservableObject, FViewTargetTransitionParams ViewTargetTransitionParams)
{
	if (!ObservableObject) return;
	if (!ObservableObject->Implements<UObservableInterface>()) return;

	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (APlayerController* PlayerController = EGI->GetPrimaryPlayerController())
	{
		EGI->SetCurrentGamePlayState(EGamePlayState::Observing);
		CurrentObservedObject = ObservableObject;
		ACameraActor* TargetViewCamera = IObservableInterface::Execute_GetViewTarget(ObservableObject);
		PlayerController->SetViewTarget(Cast<AActor>(TargetViewCamera), ViewTargetTransitionParams);
	}
}

void UViewManager::SetToPlayerView(FViewTargetTransitionParams ViewTargetTransitionParams)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (APlayerController* PlayerController = EGI->GetPrimaryPlayerController())
	{
		if (APawn* Player = PlayerController->GetPawn())
		{
			EGI->SetCurrentGamePlayState(EGamePlayState::Exploring);

			if (CurrentObservedObject)
			{
				CurrentObservedObject = nullptr;
			}
			
			PlayerController->SetViewTarget(Player, ViewTargetTransitionParams);
		}
	}
}

void UViewManager::PlayCutscene(ULevelSequence* LevelSequence, ALevelSequenceActor*& LevelSequenceActor, ULevelSequencePlayer*& LevelSequencePlayer)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	EGI->SetCurrentGamePlayState(EGamePlayState::Cutscene);
	
	LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
		EGI->GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);

	if (!LevelSequenceActor || !LevelSequencePlayer)
	{
		FAST_WARNING(TEXT("Unable to create level sequence player"));
		return;
	}
	
	LevelSequencePlayer->Play();
	LevelSequencePlayer->OnStop.AddDynamic(EGI, &UEvergreenGameInstance::ReturnPreviousGamePlayState);
}
