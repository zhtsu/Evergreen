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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGamePaused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameResumed);

UCLASS()
class EVERGREEN_API UEvergreenGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	static UEvergreenGameInstance* Singleton;
	static void LoadStringTablesOnRuntime();
	
	EEvergreenGameMode GameMode = EEvergreenGameMode::ThirdPerson;
	FGamePlayState GamePlayState;
	bool bTestModeEnabled = false;
	TArray<FString> CollectedItemUUIDs;
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnGameModeChanged OnGameModeChanged;

	UPROPERTY(BlueprintAssignable)
	FOnGamePlayStateChanged OnGamePlayStateChanged;

	UPROPERTY(BlueprintAssignable)
	FOnGamePaused OnGamePaused;

	UPROPERTY(BlueprintAssignable)
	FOnGameResumed OnGameResumed;

	UFUNCTION(BlueprintPure)
	static UEvergreenGameInstance* GetEvergreenGameInstance();

	UEvergreenGameInstance();
	bool IsAllowKeyboardInput();
	bool IsAllowInput();
	
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

	UFUNCTION(BlueprintCallable)
	void EndMiniGame(TSubclassOf<AMiniGameBase> MiniGameClass);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EGamePlayState GetCurrentGamePlayState() { return GamePlayState.CurrentGamePlayState; }

	UFUNCTION(BlueprintCallable)
	void CollectItem(FString UUID);

	UFUNCTION(BlueprintCallable)
	bool HasItem(FString UUID);
	
private:
	void SetCurrentGamePlayState(EGamePlayState NewGamePlayState);

	UFUNCTION()
	void ReturnPreviousGamePlayState();
};
