// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EvergreenBPFL.generated.h"

UCLASS()
class UEvergreenBPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static FVector GenerateLocationFromCircle(const FVector& Center, float Radius);

	UFUNCTION(BlueprintCallable)
	static UTexture2D* GenerateTextureFromWidget(UUserWidget* Widget, const FVector2D& DrawSize);
};
