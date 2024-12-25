// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGame/Watering/WateringCanBase.h"

AWateringCanBase::AWateringCanBase()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootScene->Mobility = EComponentMobility::Static;
	RootComponent = RootScene;
	
	BottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle"));
	BottleMesh->Mobility = EComponentMobility::Static;
	BottleMesh->SetGenerateOverlapEvents(false);
	BottleMesh->SetCollisionProfileName("NoCollision");
	BottleMesh->SetupAttachment(RootScene);

	CapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cap"));
	CapMesh->Mobility = EComponentMobility::Static;
	CapMesh->SetGenerateOverlapEvents(false);
	CapMesh->SetCollisionProfileName("NoCollision");
	CapMesh->SetupAttachment(RootScene);
}
