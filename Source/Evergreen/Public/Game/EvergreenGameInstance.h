// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameBase.h"
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
	MiniGame,
	Cutscene,
	Paused
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameModeChanged, EEvergreenGameMode, CurrentMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGamePaused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameResumed);

UCLASS()
class EVERGREEN_API UEvergreenGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	EEvergreenGameMode GameMode = EEvergreenGameMode::ThirdPerson;
	bool bTestModeEnabled = false;
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnGameModeChanged OnGameModeChanged;

	UPROPERTY(BlueprintAssignable)
	FOnGamePaused OnGamePaused;

	UPROPERTY(BlueprintAssignable)
	FOnGameResumed OnGameResumed;

	UPROPERTY(BlueprintReadOnly)
	EGamePlayState CurrentGamePlayState = EGamePlayState::Exploring;

	static UEvergreenGameInstance* Singleton;
	
	UFUNCTION(BlueprintPure)
	static UEvergreenGameInstance* GetEvergreenGameInstance();

	UEvergreenGameInstance();
	
	UFUNCTION(BlueprintCallable)
	void SetEvergreenGameMode(EEvergreenGameMode InGameMode);

	UFUNCTION(BlueprintPure)
	FORCEINLINE EEvergreenGameMode GetEvergreenGameMode() const { return GameMode; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetTestModeEnabled(bool Enabled) { bTestModeEnabled = Enabled; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsTestModeEnabled() const { return bTestModeEnabled; }

	UFUNCTION(BlueprintCallable)
	void PauseGame();

	UFUNCTION(Blueprintable)
	void ResumeGame();

	UFUNCTION(BlueprintCallable)
	void PlayCutscene(class ULevelSequence* LevelSequence, class ALevelSequenceActor*& LevelSequenceActor, class ULevelSequencePlayer*& LevelSequencePlayer);

	UFUNCTION(BlueprintCallable)
	void StartMiniGame(TSubclassOf<AMiniGameBase> MiniGameClass);
};
