// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UIManager.generated.h"

UCLASS()
class UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UUIManager();

	UFUNCTION(BlueprintCallable)
	void ShowBubble(FText InText = FText(), float Duration = 3.f);
};
