// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ClickableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClickableInterface : public UInterface
{
	GENERATED_BODY()
};

class EVERGREEN_API IClickableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "ClickableItem")
	void OnClick();
	
	UFUNCTION(BlueprintNativeEvent, Category = "ClickableItem")
	void OnHover();

	UFUNCTION(BlueprintNativeEvent, Category = "ClickableItem")
	void OnUnhover();
};
