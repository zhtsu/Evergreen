// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObservableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UObservableInterface : public UInterface
{
	GENERATED_BODY()
};

class EVERGREEN_API IObservableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Observable")
	class AEvergreenCamera* GetViewTarget();

	UFUNCTION(BlueprintNativeEvent, Category = "Observable")
	void OnStartObserve();

	UFUNCTION(BlueprintNativeEvent, Category = "Observable")
	void OnEndObserve();
};
