// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WateringCanBase.generated.h"

UCLASS()
class EVERGREEN_API AWateringCanBase : public AActor
{
	GENERATED_BODY()
	
public:
	AWateringCanBase();

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	USceneComponent* RootScene;
	
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "FlowerPot", meta = (AllowPrivateAccess))
	UStaticMeshComponent* BottleMesh;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "FlowerPot", meta = (AllowPrivateAccess))
	UStaticMeshComponent* CapMesh;
};
