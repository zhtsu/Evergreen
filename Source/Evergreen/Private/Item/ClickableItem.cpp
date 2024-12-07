// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ClickableItem.h"

// Sets default values
AClickableItem::AClickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClickableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

