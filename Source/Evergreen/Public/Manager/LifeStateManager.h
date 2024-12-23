// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LifeStateManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLifeStateValueUpdated, int, LatestLifeStateValue);

UCLASS()
class ULifeStateManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnLifeStateValueUpdated OnLifeStateValueUpdated;
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetLifeStateDefaultValue(int DefaultValue) { LifeStateValue = DefaultValue; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetLifeStateValue() const { return LifeStateValue; }

	UFUNCTION(BlueprintCallable)
	void AddLifeStateValue(int AddedValue);

	UFUNCTION(BlueprintCallable)
	void SubtractLifeStateValue(int SubtractedValue);
	
private:
	int LifeStateValue = 50.f;
};
