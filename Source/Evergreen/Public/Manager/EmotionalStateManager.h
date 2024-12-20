// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EmotionalStateManager.generated.h"

UCLASS()
class UEmotionalStateManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetEmotionalStateDefaultValue(int DefaultValue) { EmotionalStateValue = DefaultValue; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void AddEmotionalStateValue(int AddedValue) { EmotionalStateValue += AddedValue; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SubtractEmotionalStateValue(int SubtractValue) { EmotionalStateValue -= SubtractValue; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetEmotionalStateValue() const { return EmotionalStateValue; }
	
private:
	int EmotionalStateValue = 50.f;
};
