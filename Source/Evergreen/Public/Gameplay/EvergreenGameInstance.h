// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EvergreenGameInstance.generated.h"

UENUM()
enum class EEvergreenGameMode : uint8
{
	ThirdPerson,
	Interaction
};

UENUM()
enum class EGamePlayState : uint8
{
	Exploring,
	Observing,
	MiniGame,
	Cutscene,
	Paused
};

USTRUCT()
struct FGamePlayState
{
	GENERATED_BODY()

	EGamePlayState PreviousGamePlayState;
	EGamePlayState CurrentGamePlayState;

	FGamePlayState() :
		PreviousGamePlayState(EGamePlayState::Exploring),
		CurrentGamePlayState(EGamePlayState::Exploring) {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameModeChanged, EEvergreenGameMode, CurrentMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePlayStateChanged, EGamePlayState, CurrentGamePlayState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScreenResolutionChanged, FIntPoint, CurrentScreenResolution);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFullscreenModeChanged, FString, CurrentFullscreenMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameLanguageChanged, FString, CurrentIetfLanguageTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGamePaused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameResumed);

UCLASS()
class EVERGREEN_API UEvergreenGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	virtual void OnStart() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameModeChanged OnGameModeChanged;

	UPROPERTY(BlueprintAssignable)
	FOnGamePlayStateChanged OnGamePlayStateChanged;

	UPROPERTY(BlueprintAssignable)
	FOnGamePaused OnGamePaused;

	UPROPERTY(BlueprintAssignable)
	FOnGameResumed OnGameResumed;
	
	UPROPERTY(BlueprintAssignable)
	FOnScreenResolutionChanged OnScreenResolutionChanged;

	UPROPERTY(BlueprintAssignable)
	FOnGameLanguageChanged OnGameLanguageChanged;

	UPROPERTY(BlueprintAssignable)
	FOnFullscreenModeChanged OnFullscreenModeChanged;

	UFUNCTION(BlueprintPure)
	static UEvergreenGameInstance* GetEvergreenGameInstance();
	
	UFUNCTION(BlueprintPure)
	static class AEvergreenPlayerController* GetEvergreenPlayerController();

	static void SetEvergreenPlayerController(AEvergreenPlayerController* InPlayerController);
	
	UEvergreenGameInstance();
	
	bool IsAllowKeyboardInput() const;
	bool IsAllowMouseInput() const;
	bool IsAllowInput() const;
	
	UFUNCTION(BlueprintCallable)
	void ChangeEvergreenGameMode(EEvergreenGameMode InGameMode);

	UFUNCTION(BlueprintPure)
	FORCEINLINE EEvergreenGameMode GetCurrentEvergreenGameMode() const { return CurrentGameMode; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsThirdPersonMode() const { return CurrentGameMode == EEvergreenGameMode::ThirdPerson; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsInteractionMode() const { return CurrentGameMode == EEvergreenGameMode::Interaction; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetTestModeEnabled(bool bEnabled) { bTestModeEnabled = bEnabled; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsTestModeEnabled() const { return bTestModeEnabled; }

	UFUNCTION(BlueprintCallable)
	void PauseGame();

	UFUNCTION(Blueprintable)
	void ResumeGame();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EGamePlayState GetCurrentGamePlayState() const { return GamePlayState.CurrentGamePlayState; }

	void SetCurrentGamePlayState(EGamePlayState NewGamePlayState);
	EGamePlayState GetPreviousGamePlayState() const { return GamePlayState.PreviousGamePlayState; }
	
	UFUNCTION()
	void SetToPreviousGamePlayState();

	UFUNCTION(BlueprintPure)
	static void GetSupportedLanguages(TArray<FString>& OutSupportedLanguages) { OutSupportedLanguages = SupportedLanguages; }

	UFUNCTION(BlueprintPure)
	static void GetSupportedScreenResolutions(TArray<FString>& OutSupportedScreenResolutions) { OutSupportedScreenResolutions = SupportedScreenResolutions; }

	UFUNCTION(BlueprintCallable)
	bool SetScreenResolutionFromString(FString ScreenResolutionString);

	UFUNCTION(BlueprintCallable)
	bool SetScreenResolution(FIntPoint TargetScreenResolution);
	
	UFUNCTION(BlueprintCallable)
	void SetFullscreenEnabled(bool FullscreenEnabled);

	UFUNCTION(BlueprintCallable)
	void SetGameLanguage(FString IetfLanguageTag);

	UFUNCTION(BlueprintPure)
	FIntPoint GetCurrentScreenResolution() const { return CurrentScreenResolution; }

	UFUNCTION(BlueprintPure)
	FString GetCurrentScreenResolutionAsString() const;

	UFUNCTION(BlueprintPure)
	FString GetCurrentIetfLanguageTag() const { return CurrentIetfLanguageTag; }
	
private:
	static UEvergreenGameInstance* Singleton;
	static AEvergreenPlayerController* EvergreenPlayerController;
	inline static TArray<FString> SupportedLanguages = {
		"en", "zh-CN"
	};
	inline static TArray<FString> SupportedScreenResolutions = {
		"1920x1080", "1280x720", "960x540"
	};
	
	EEvergreenGameMode CurrentGameMode = EEvergreenGameMode::ThirdPerson;
	FGamePlayState GamePlayState;
	bool bTestModeEnabled = false;
	FString CurrentIetfLanguageTag = "zh-CN";
	FIntPoint CurrentScreenResolution = FIntPoint(-1, -1);
};
