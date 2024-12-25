// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlowerPotBase.generated.h"

UCLASS()
class EVERGREEN_API AFlowerPotBase : public AActor
{
	GENERATED_BODY()
	
public:
	AFlowerPotBase();
	
	void WateringTick(float DeltaSeconds);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	USceneComponent* RootScene;
	
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "FlowerPot", meta = (AllowPrivateAccess))
	UStaticMeshComponent* SoilMesh;
	
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "FlowerPot", meta = (AllowPrivateAccess))
	UStaticMeshComponent* PotMesh;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "FlowerPot", meta = (AllowPrivateAccess))
	UStaticMeshComponent* PlantMesh;

	float MoisturePercentage = 0.f;
};
