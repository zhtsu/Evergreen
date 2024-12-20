// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/ViewManager.h"

#include "LevelSequencePlayer.h"
#include "Common/CommonMacro.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "Interface/ObservableInterface.h"
#include "Camera/CameraActor.h"
#include "Gameplay/EvergreenCharacter.h"
#include "Gameplay/EvergreenPawn.h"

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
	if (EGI->GetCurrentGamePlayState() == EGamePlayState::Cutscene) return;
	
	if (APlayerController* PlayerController = EGI->GetPrimaryPlayerController())
	{
		EGI->SetCurrentGamePlayState(EGamePlayState::Cutscene);
		CurrentObservedObject = ObservableObject;
		ACameraActor* TargetViewCamera = IObservableInterface::Execute_GetViewTarget(ObservableObject);
		
		PlayerController->SetViewTarget(Cast<AActor>(TargetViewCamera), ViewTargetTransitionParams);

		if (TimerHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle, this, &UViewManager::CallOnStartObserve, ViewTargetTransitionParams.BlendTime);
	}
}

void UViewManager::SetToPlayerView(FViewTargetTransitionParams ViewTargetTransitionParams)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (EGI->GetCurrentGamePlayState() == EGamePlayState::Cutscene) return;
	
	if (APlayerController* PlayerController = EGI->GetPrimaryPlayerController())
	{
		if (APawn* Player = PlayerController->GetPawn())
		{
			EGI->SetCurrentGamePlayState(EGamePlayState::Cutscene);

			if (CurrentObservedObject)
			{
				IObservableInterface::Execute_OnEndObserve(CurrentObservedObject);
				CurrentObservedObject = nullptr;
			}
			
			PlayerController->SetViewTarget(Player, ViewTargetTransitionParams);
			
			if (TimerHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			GetWorld()->GetTimerManager().SetTimer(
				TimerHandle, this, &UViewManager::CallOnAttainPlayerView, ViewTargetTransitionParams.BlendTime);
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
		FAST_WARNING("Unable to create level sequence player");
		return;
	}
	
	LevelSequencePlayer->Play();
	LevelSequencePlayer->OnStop.AddDynamic(EGI, &UEvergreenGameInstance::SetToPreviousGamePlayState);
}

void UViewManager::CallOnStartObserve()
{
	if (CurrentObservedObject)
	{
		UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
		EGI->SetCurrentGamePlayState(EGamePlayState::Observing);
		IObservableInterface::Execute_OnStartObserve(CurrentObservedObject);
	}
}

void UViewManager::CallOnAttainPlayerView()
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	EGI->SetCurrentGamePlayState(EGamePlayState::Exploring);
}

void UViewManager::SetCameraOffsetFollowCursorEnabled(bool bEnabled)
{
	if (InteractionPlayer)
	{
		InteractionPlayer->SetCameraOffsetFollowCursorEnabled(bEnabled);
	}
}

void UViewManager::SetCameraOffsetScale_X(float Scale)
{
	if (InteractionPlayer)
	{
		InteractionPlayer->SetCameraOffsetScale_X(Scale);
	}
}

void UViewManager::SetCameraOffsetScale_Y(float Scale)
{
	if (InteractionPlayer)
	{
		InteractionPlayer->SetCameraOffsetScale_Y(Scale);
	}
}

bool UViewManager::GetCameraOffsetFollowCursorEnabled() const
{
	if (InteractionPlayer)
	{
		return InteractionPlayer->GetCameraOffsetFollowCursorEnabled();
	}
	
	return false;
}

float UViewManager::GetCameraOffsetScale_X() const
{
	if (InteractionPlayer)
	{
		return InteractionPlayer->GetCameraOffsetScale_X();
	}
	
	return 0.f;
}

float UViewManager::GetCameraOffsetScale_Y() const
{
	if (InteractionPlayer)
	{
		return InteractionPlayer->GetCameraOffsetScale_Y();
	}
	
	return 0.f;
}

void UViewManager::RotateCharacterCameraBoomYaw(float Yaw, bool bAllowMove)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (EGI->GetCurrentEvergreenGameMode() == EEvergreenGameMode::Interaction) return;

	if (APlayerController* PlayerController = EGI->GetPrimaryPlayerController())
	{
		if (AEvergreenCharacter* Character = Cast<AEvergreenCharacter>(PlayerController->GetPawn()))
		{
			Character->K2_RotateCameraBoomYaw(Yaw, bAllowMove);
		}
	}
}

void UViewManager::AdjustCharacterCameraBoom(float Length, float Pitch, bool bAllowMove)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (EGI->GetCurrentEvergreenGameMode() == EEvergreenGameMode::Interaction) return;

	if (APlayerController* PlayerController = EGI->GetPrimaryPlayerController())
	{
		if (AEvergreenCharacter* Character = Cast<AEvergreenCharacter>(PlayerController->GetPawn()))
		{
			Character->K2_AdjustCameraBoom(Length, Pitch, bAllowMove);
		}
	}
}

void UViewManager::SetCharacterCameraBoom(float Length, float Pitch)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (EGI->GetCurrentEvergreenGameMode() == EEvergreenGameMode::Interaction) return;

	if (APlayerController* PlayerController = EGI->GetPrimaryPlayerController())
	{
		if (AEvergreenCharacter* Character = Cast<AEvergreenCharacter>(PlayerController->GetPawn()))
		{
			Character->SetCameraBoom(Length, Pitch);
		}
	}
}
