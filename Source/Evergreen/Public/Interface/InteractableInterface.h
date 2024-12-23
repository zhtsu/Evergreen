// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class EVERGREEN_API IInteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "InteractableItem")
	void OnInteract();
	
	UFUNCTION(BlueprintNativeEvent, Category = "InteractableItem")
	void OnActorEnter();

	UFUNCTION(BlueprintNativeEvent, Category = "InteractableItem")
	void OnActorLeave();
};
