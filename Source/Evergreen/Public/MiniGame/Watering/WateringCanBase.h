// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "World/ClickableItemBase.h"
#include "WateringCanBase.generated.h"

UCLASS()
class EVERGREEN_API AWateringCanBase : public AClickableItemBase
{
	GENERATED_BODY()
	
public:
	AWateringCanBase();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetPressed(bool InPressed) { Pressed = InPressed; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsPressed() { return Pressed; }

private:
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "FlowerPot", meta = (AllowPrivateAccess))
	UStaticMeshComponent* CapMesh;

	bool Pressed = false;
};
