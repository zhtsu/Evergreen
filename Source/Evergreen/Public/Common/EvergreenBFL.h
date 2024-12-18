// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EvergreenBFL.generated.h"

UCLASS()
class UEvergreenBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static FVector GenerateLocationFromCircle(const FVector& Center, float Radius);
};
