// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LifeStateManager.generated.h"

UCLASS()
class ULifeStateManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetLifeStateDefaultValue(int DefaultValue) { LifeStateValue = DefaultValue; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void AddLifeStateValue(int AddedValue) { LifeStateValue += AddedValue; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SubtractLifeStateValue(int SubtractedValue) { LifeStateValue -= SubtractedValue; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetEmotionalStateValue() const { return LifeStateValue; }
	
private:
	int LifeStateValue = 50.f;
};
