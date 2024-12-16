// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EvergreenGameInstance.h"

#include "World/MiniGameBase.h"
#include "GameFramework/GameUserSettings.h"
#include "Gameplay/EvergreenPlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/MiniGameManager.h"
#include "Manager/ViewManager.h"

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

	if (APlayerController* PlayerController = Cast<APlayerController>(GetPrimaryPlayerController()))
	{
		FIntPoint ViewportSize;
		PlayerController->GetViewportSize(ViewportSize.X, ViewportSize.Y);
		if (ViewportSize != CurrentScreenResolution)
		{
			SetScreenResolution(CurrentScreenResolution);
		}
	}

	if (GameMode == EEvergreenGameMode::Interaction)
	{
		UViewManager* ViewManager = GetSubsystem<UViewManager>();
		AEvergreenPlayerCameraManager* PCM = Cast<AEvergreenPlayerCameraManager>(
			UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));

		ViewManager->SetPlayerCameraManager(PCM);
	}
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
	if (GetSubsystem<UMiniGameManager>()->IsAnyMiniGameOnProcess())
	{
		if (bTestModeEnabled) return true;
		return false;
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

bool UEvergreenGameInstance::SetScreenResolutionFromString(FString ScreenResolutionString)
{
	FIntPoint TargetScreenResolution = FIntPoint(-1, -1);
	if (ScreenResolutionString == "1920x1080") TargetScreenResolution = FIntPoint(1920, 1080);
	else if (ScreenResolutionString == "1280x720") TargetScreenResolution = FIntPoint(1280, 720);
	else if (ScreenResolutionString == "960x540") TargetScreenResolution = FIntPoint(960, 540);
	else return false;

	return SetScreenResolution(TargetScreenResolution);
}

bool UEvergreenGameInstance::SetScreenResolution(FIntPoint TargetScreenResolution)
{
	if (CurrentScreenResolution == TargetScreenResolution) return false;
	
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
	
	if (CurrentScreenResolution != TargetScreenResolution) UserSettings->SetScreenResolution(TargetScreenResolution);
	UserSettings->ApplySettings(false);

	CurrentScreenResolution = TargetScreenResolution;
	OnScreenResolutionChanged.Broadcast(CurrentScreenResolution);

	return true;
}

void UEvergreenGameInstance::SetFullscreenEnabled(bool FullscreenEnabled)
{
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
	if (FullscreenEnabled) UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	else UserSettings->SetFullscreenMode(EWindowMode::Windowed);
}

void UEvergreenGameInstance::SetGameLanguage(FString IetfLanguageTag)
{
	if (CurrentIetfLanguageTag == IetfLanguageTag) return;
	
	FInternationalization::Get().SetCurrentLanguageAndLocale(IetfLanguageTag);

	CurrentIetfLanguageTag = IetfLanguageTag;
	OnGameLanguageChanged.Broadcast(CurrentIetfLanguageTag);
}
