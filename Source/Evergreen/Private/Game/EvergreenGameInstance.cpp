// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EvergreenGameInstance.h"

#include "Game/MiniGameBase.h"
#include "GameFramework/GameUserSettings.h"
#include "Manager/MiniGameManager.h"

UEvergreenGameInstance* UEvergreenGameInstance::Singleton = nullptr;

UEvergreenGameInstance* UEvergreenGameInstance::GetEvergreenGameInstance()
{
	return Singleton;
}

UEvergreenGameInstance::UEvergreenGameInstance()
{
	Singleton = this;
}

void UEvergreenGameInstance::OnStart()
{
	Super::OnStart();
	
}

void UEvergreenGameInstance::BeginDestroy()
{
	Super::BeginDestroy();
	
}

void UEvergreenGameInstance::SetEvergreenGameMode(EEvergreenGameMode InGameMode)
{
	GameMode = InGameMode;
	OnGameModeChanged.Broadcast(GameMode);
}

void UEvergreenGameInstance::PauseGame()
{
	SetCurrentGamePlayState(EGamePlayState::Paused);
}

void UEvergreenGameInstance::ResumeGame()
{
	ReturnPreviousGamePlayState();
}

bool UEvergreenGameInstance::IsAllowKeyboardInput() const
{
	bool bJudgeWithCurrentMiniGame = false;
	if (GamePlayState.CurrentGamePlayState == EGamePlayState::MiniGame)
	{
		if (GetSubsystem<UMiniGameManager>()->GetCurrentMiniGame()) bJudgeWithCurrentMiniGame = true;
		else bJudgeWithCurrentMiniGame = false;
	}

	if (bJudgeWithCurrentMiniGame)
	{
		return IsAllowInput() && GetSubsystem<UMiniGameManager>()->GetCurrentMiniGame()->bAllowKeyboardInput;
	}

	return GamePlayState.CurrentGamePlayState != EGamePlayState::Cutscene
		&& GamePlayState.CurrentGamePlayState != EGamePlayState::Paused
		&& GamePlayState.CurrentGamePlayState != EGamePlayState::MiniGame;
}

bool UEvergreenGameInstance::IsAllowInput() const
{
	return GamePlayState.CurrentGamePlayState != EGamePlayState::Cutscene
		&& GamePlayState.CurrentGamePlayState != EGamePlayState::Paused;
}

void UEvergreenGameInstance::SetCurrentGamePlayState(EGamePlayState NewGamePlayState)
{
	if (NewGamePlayState == GamePlayState.CurrentGamePlayState)
	{
		return;
	}

	GamePlayState.PreviousGamePlayState = GamePlayState.CurrentGamePlayState;
	GamePlayState.CurrentGamePlayState = NewGamePlayState;
	OnGamePlayStateChanged.Broadcast(GamePlayState.CurrentGamePlayState);
}

void UEvergreenGameInstance::ReturnPreviousGamePlayState()
{
	SetCurrentGamePlayState(GamePlayState.PreviousGamePlayState);
}

void UEvergreenGameInstance::SetScreenResolution(FString ScreenResolution)
{
	int32 MaxScreenWidth = 1920;
	int32 MaxScreenHeight = 1080;
	int32 TargetScreenWidth = MaxScreenWidth;
	int32 TargetScreenHeight = MaxScreenHeight;
	
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
	if (ScreenResolution == "Fullscreen")
	{
		TargetScreenWidth = MaxScreenWidth;
		TargetScreenHeight = MaxScreenHeight;
	}
	else if (ScreenResolution == "1920x1080")
	{
		TargetScreenWidth = 1920;
		TargetScreenHeight = 1080;
	}
	else if (ScreenResolution == "1280x720")
	{
		TargetScreenWidth = 1280;
		TargetScreenHeight = 720;
	}
	else if (ScreenResolution == "960x540")
	{
		TargetScreenWidth = 960;
		TargetScreenHeight = 540;
	}

	FIntPoint TargetScreenResolution = FIntPoint(TargetScreenWidth, TargetScreenHeight);
	if (CurrentScreenResolution == TargetScreenResolution) return;
	
	UserSettings->SetScreenResolution(TargetScreenResolution);
	if (TargetScreenWidth == MaxScreenWidth && TargetScreenHeight == MaxScreenHeight)
	{
		UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	}
	else
	{
		UserSettings->SetFullscreenMode(EWindowMode::Windowed);
	}
	UserSettings->ApplySettings(false);

	CurrentScreenResolution = TargetScreenResolution;
	OnScreenResolutionChanged.Broadcast(CurrentScreenResolution);
}

void UEvergreenGameInstance::SetGameLanguage(FString IetfLanguageTag)
{
	if (CurrentIetfLanguageTag == IetfLanguageTag) return;
	
	FInternationalization::Get().SetCurrentLanguageAndLocale(IetfLanguageTag);

	CurrentIetfLanguageTag = IetfLanguageTag;
	OnGameLanguageChanged.Broadcast(CurrentIetfLanguageTag);
}
