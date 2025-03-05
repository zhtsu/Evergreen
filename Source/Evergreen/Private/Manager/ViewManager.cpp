// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/ViewManager.h"

#include "LevelSequencePlayer.h"
#include "Common/CommonMacro.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "Interface/ObservableInterface.h"
#include "Config/EvergreenCameraSettings.h"
#include "Gameplay/EvergreenCharacter.h"
#include "Gameplay/EvergreenPlayerController.h"
#include "World/EvergreenCamera.h"

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
		AEvergreenCamera* TargetViewCamera = IObservableInterface::Execute_GetViewTarget(ObservableObject);
		if (!TargetViewCamera) return;
		
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

void UViewManager::SetCameraOffsetFollowMouseEnabled(bool bEnabled)
{
	bCameraOffsetFollowMouseEnabled = bEnabled;
}

void UViewManager::SetCameraOffsetScale_X(float Scale)
{
	CameraOffsetScale_X = Scale;
}

void UViewManager::SetCameraOffsetScale_Y(float Scale)
{
	CameraOffsetScale_Y = Scale;
}

bool UViewManager::GetCameraOffsetFollowMouseEnabled() const
{
	return bCameraOffsetFollowMouseEnabled;
}

float UViewManager::GetCameraOffsetScale_X() const
{
	return CameraOffsetScale_X;
}

float UViewManager::GetCameraOffsetScale_Y() const
{
	return CameraOffsetScale_Y;
}

void UViewManager::RotateCameraBoomYaw_ThirdPerson(float Yaw, bool bAllowMove)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (EGI->GetCurrentEvergreenGameMode() == EEvergreenGameMode::Interaction) return;
	
	if (ThirdPersonPlayer)
	{
		ThirdPersonPlayer->K2_RotateCameraBoomYaw(Yaw, bAllowMove);
	}
}

void UViewManager::RotateCameraBoomPitch_ThirdPerson(float Pitch, bool bAllowMove)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (EGI->GetCurrentEvergreenGameMode() == EEvergreenGameMode::Interaction) return;

	if (ThirdPersonPlayer)
	{
		ThirdPersonPlayer->K2_RotateCameraBoomPitch(Pitch, bAllowMove);
	}
}

void UViewManager::AdjustCameraBoomLength_ThirdPerson(float Length, bool bAllowMove)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (EGI->GetCurrentEvergreenGameMode() == EEvergreenGameMode::Interaction) return;

	if (ThirdPersonPlayer)
	{
		ThirdPersonPlayer->K2_AdjustCameraBoomLength(Length, bAllowMove);
	}
}

void UViewManager::ChangeCameraParams(ECameraViewType ViewType, bool bBlend, bool bAllowMove)
{
	FCameraParams TargetCameraParams;

	UEvergreenCameraSettings* ECS = UEvergreenCameraSettings::Get();
	if (!ECS || !ThirdPersonPlayer) return;
	
	if (ViewType == ECameraViewType::SuperFarView) TargetCameraParams = ECS->SuperFarView;
	else if (ViewType == ECameraViewType::FarView) TargetCameraParams = ECS->FarView;
	else if (ViewType == ECameraViewType::FullView) TargetCameraParams = ECS->FullView;
	else if (ViewType == ECameraViewType::MidView) TargetCameraParams = ECS->MidView;
	else if (ViewType == ECameraViewType::CloseView) TargetCameraParams = ECS->CloseView;
	else if (ViewType == ECameraViewType::CloseUpView) TargetCameraParams = ECS->CloseUpView;
	else if (ViewType == ECameraViewType::SuperCloseUpView) TargetCameraParams = ECS->SuperCloseUpView;
	
	if (bBlend)
	{
		ThirdPersonPlayer->K2_AdjustCameraBoomLength(TargetCameraParams.CameraBoomLength, bAllowMove);
		ThirdPersonPlayer->K2_RotateCameraBoomYaw(TargetCameraParams.CameraBoomYaw, bAllowMove);
		ThirdPersonPlayer->K2_RotateCameraBoomPitch(TargetCameraParams.CameraBoomPitch, bAllowMove);
	}
	else
	{
		ThirdPersonPlayer->SetCameraParams(
			TargetCameraParams.CameraBoomYaw, TargetCameraParams.CameraBoomPitch, TargetCameraParams.CameraBoomLength);
	}
}

void UViewManager::ChangeCamera(const FString& CameraID, bool& Success, FViewTargetTransitionParams TransitionParams)
{
	AEvergreenCamera* Camera = AEvergreenCamera::FindFirstFixedCamera(CameraID);
	if (!Camera)
	{
		Success = false;
		return;
	}

	if (AEvergreenPlayerController* PlayerController = UEvergreenGameInstance::GetEvergreenPlayerController())
	{
		PlayerController->SetViewTarget(Camera, TransitionParams);
		Success = true;
	}
}
