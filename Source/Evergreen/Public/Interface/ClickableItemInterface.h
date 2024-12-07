// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ClickableItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClickableItemInterface : public UInterface
{
	GENERATED_BODY()
};

class EVERGREEN_API IClickableItemInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "ClickableItem")
	void OnClicked();
	virtual void OnClicked_Implementation() = 0;
	
	UFUNCTION(BlueprintNativeEvent, Category = "ClickableItem")
	void OnHovered();
	virtual void OnHovered_Implementation() = 0;

	UFUNCTION(BlueprintNativeEvent, Category = "ClickableItem")
	void OnUnhovered();
	virtual void OnUnhovered_Implementation() = 0;
};
