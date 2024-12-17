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
	SetToPreviousGamePlayState();
}

bool UEvergreenGameInstance::IsAllowKeyboardInput() const
{
	if (GetSubsystem<UMiniGameManager>()->IsAnyMiniGameOnProcess())
	{
#if WITH_EDITOR
		if (bTestModeEnabled) return true;
#endif
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

void UEvergreenGameInstance::SetToPreviousGamePlayState()
{
	SetCurrentGamePlayState(GamePlayState.PreviousGamePlayState);
}

bool UEvergreenGameInstance::SetScreenResolutionFromString(FString ScreenResolutionString)
{
	FIntPoint TargetScreenResolution;
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
	UserSettings->SetScreenResolution(TargetScreenResolution);
	UserSettings->ApplySettings(false);
	UserSettings->ApplyResolutionSettings(false);

	CurrentScreenResolution = TargetScreenResolution;
	OnScreenResolutionChanged.Broadcast(CurrentScreenResolution);

	return true;
}

void UEvergreenGameInstance::SetFullscreenEnabled(bool FullscreenEnabled)
{
	EWindowMode::Type TargetWindowMode = FullscreenEnabled ? EWindowMode::Fullscreen : EWindowMode::Windowed;
	
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
	if (UserSettings->GetFullscreenMode() == TargetWindowMode) return;

	UserSettings->SetFullscreenMode(TargetWindowMode);
	UserSettings->ApplySettings(false);
	UserSettings->ApplyResolutionSettings(false);
}

void UEvergreenGameInstance::SetGameLanguage(FString IetfLanguageTag)
{
	if (CurrentIetfLanguageTag == IetfLanguageTag) return;
	
	FInternationalization::Get().SetCurrentLanguageAndLocale(IetfLanguageTag);

	CurrentIetfLanguageTag = IetfLanguageTag;
	OnGameLanguageChanged.Broadcast(CurrentIetfLanguageTag);
}
