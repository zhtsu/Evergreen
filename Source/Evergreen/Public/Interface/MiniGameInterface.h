// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MiniGameInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMiniGameInterface : public UInterface
{
	GENERATED_BODY()
};

class EVERGREEN_API IMiniGameInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "MiniGame")
	void OnStartMiniGame(class UMiniGameData* MiniGameData);
	virtual void OnStartMiniGame_Implementation(UMiniGameData* MiniGameData) = 0;

	UFUNCTION(BlueprintNativeEvent, Category = "MiniGame")
	void OnEndMiniGame();
	virtual void OnEndMiniGame_Implementation() = 0;
};
