// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EvergreenGameInstance.h"

#include "GameFramework/GameUserSettings.h"
#include "Gameplay/EvergreenPlayerController.h"

UEvergreenGameInstance* UEvergreenGameInstance::Singleton = nullptr;
AEvergreenPlayerController* UEvergreenGameInstance::EvergreenPlayerController = nullptr;

void UEvergreenGameInstance::OnStart()
{
	SetScreenResolution({ 1920, 1080 });
}

UEvergreenGameInstance* UEvergreenGameInstance::GetEvergreenGameInstance()
{
	return Singleton;
}

UEvergreenGameInstance::UEvergreenGameInstance()
{
	Singleton = this;
	
#if WITH_EDITOR
	(void)0;
#else
	UStringTableHelper::ImportAllStringTableFromCSV();
#endif
}

AEvergreenPlayerController* UEvergreenGameInstance::GetEvergreenPlayerController()
{
	return EvergreenPlayerController;
}

void UEvergreenGameInstance::SetEvergreenPlayerController(AEvergreenPlayerController* InPlayerController)
{
	EvergreenPlayerController = InPlayerController;
}

void UEvergreenGameInstance::SwitchEvergreenGameModeTo(EEvergreenGameMode InGameMode)
{
	if (CurrentGameMode == InGameMode) return;
	
	CurrentGameMode = InGameMode;
	OnGameModeChanged.Broadcast(CurrentGameMode);

	if (InGameMode == EEvergreenGameMode::Interaction)
	{
		EvergreenPlayerController->PossessInteractionPlayer();
	}
	else if (InGameMode == EEvergreenGameMode::ThirdPerson)
	{
		EvergreenPlayerController->PossessThirdPersonPlayer();
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
	return IsAllowInput() && IsThirdPersonMode();
}

bool UEvergreenGameInstance::IsAllowMouseInput() const
{
	return IsAllowInput() && IsInteractionMode();
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
	UserSettings->SetFullscreenMode(EWindowMode::Windowed);
	UserSettings->SetScreenResolution(TargetScreenResolution);
	UserSettings->ApplySettings(false);
	
	CurrentScreenResolution = TargetScreenResolution;
	OnScreenResolutionChanged.Broadcast(CurrentScreenResolution);
	OnFullscreenModeChanged.Broadcast("Windowed");

	return true;
}

void UEvergreenGameInstance::SetFullscreenEnabled(bool FullscreenEnabled)
{
	EWindowMode::Type TargetWindowMode = FullscreenEnabled ? EWindowMode::WindowedFullscreen : EWindowMode::Windowed;
	
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
	if (UserSettings->GetFullscreenMode() == TargetWindowMode) return;

	UserSettings->SetFullscreenMode(TargetWindowMode);
	UserSettings->ApplySettings(false);

	OnFullscreenModeChanged.Broadcast(TargetWindowMode == EWindowMode::WindowedFullscreen ? "Fullscreen" : "Windowed");
}

void UEvergreenGameInstance::SetGameLanguage(FString IetfLanguageTag)
{
	if (CurrentIetfLanguageTag == IetfLanguageTag) return;
	
	FInternationalization::Get().SetCurrentLanguageAndLocale(IetfLanguageTag);

	CurrentIetfLanguageTag = IetfLanguageTag;
	OnGameLanguageChanged.Broadcast(CurrentIetfLanguageTag);
}
