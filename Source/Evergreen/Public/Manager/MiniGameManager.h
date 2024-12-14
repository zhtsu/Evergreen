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
	void StartMiniGame(TSubclassOf<class AMiniGameBase> MiniGameClass, class UMiniGameData* MiniGameData);

	UFUNCTION(BlueprintCallable)
	void EndMiniGame();

	UFUNCTION(BlueprintPure)
	FORCEINLINE AMiniGameBase* GetCurrentMiniGame() const { return CurrentMiniGame; }
	
private:
	UPROPERTY()
	AMiniGameBase* CurrentMiniGame = nullptr;
};
