// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGame/Watering/WateringCanBase.h"

AWateringCanBase::AWateringCanBase()
{
	CapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cap"));
	CapMesh->Mobility = EComponentMobility::Static;
	CapMesh->SetGenerateOverlapEvents(false);
	CapMesh->SetCollisionProfileName("NoCollision");
	CapMesh->SetupAttachment(RootScene);
}
