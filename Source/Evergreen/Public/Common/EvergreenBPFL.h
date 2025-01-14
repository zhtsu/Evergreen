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
};
