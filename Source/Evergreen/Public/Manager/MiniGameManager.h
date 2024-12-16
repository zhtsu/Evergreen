// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameManager.generated.h"

UCLASS()
class UMiniGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMiniGameManager();

	UFUNCTION(BlueprintCallable)
	bool StartMiniGame(TSubclassOf<class AMiniGameBase> MiniGameClass, class UMiniGameData* MiniGameData);

	UFUNCTION(BlueprintCallable)
	bool EndMiniGame(TSubclassOf<class AMiniGameBase> MiniGameClass);

	UFUNCTION(BlueprintPure)
	bool IsMiniGameOnProcess(TSubclassOf<class AMiniGameBase> MiniGameClass);

	UFUNCTION(BlueprintPure)
	bool IsAnyMiniGameOnProcess();
	
private:
	UPROPERTY()
	TArray<AMiniGameBase*> OnProcessMiniGames;
};
