// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGame/Watering/FlowerPotBase.h"

AFlowerPotBase::AFlowerPotBase()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootScene->Mobility = EComponentMobility::Static;
	RootComponent = RootScene;

	SoilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Soil"));
	SoilMesh->Mobility = EComponentMobility::Static;
	SoilMesh->SetGenerateOverlapEvents(false);
	SoilMesh->SetCollisionProfileName("NoCollision");
	SoilMesh->SetupAttachment(RootScene);
	
	PotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pot"));
	PotMesh->Mobility = EComponentMobility::Static;
	PotMesh->SetGenerateOverlapEvents(false);
	PotMesh->SetCollisionProfileName("NoCollision");
	PotMesh->SetupAttachment(RootScene);

	PlantMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plant"));
	PlantMesh->Mobility = EComponentMobility::Static;
	PlantMesh->SetGenerateOverlapEvents(false);
	PlantMesh->SetCollisionProfileName("NoCollision");
	PlantMesh->SetupAttachment(RootScene);
}

void AFlowerPotBase::WateringTick(float DeltaSeconds)
{
}
