// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EvergreenPawn.h"

AEvergreenPawn::AEvergreenPawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEvergreenPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEvergreenPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

