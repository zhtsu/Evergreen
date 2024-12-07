// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ClickableItem.h"

#include "Evergreen/Evergreen.h"

AClickableItem::AClickableItem()
{
	
}

void AClickableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AClickableItem::OnClicked_Implementation()
{
	FAST_PRINT("OnClicked")
}

void AClickableItem::OnHovered_Implementation()
{
	FAST_PRINT("OnHovered")
}

void AClickableItem::OnUnhovered_Implementation()
{
	FAST_PRINT("OnUnhovered")
}
