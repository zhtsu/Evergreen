// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"

#include "Common/AssetPathHub.h"

void AEvergreenItemBase::BeginPlay()
{
	Super::BeginPlay();

	ItemName = FText::FromStringTable(UAssetPathHub::ST_ItemName_TableID, ItemID);
	ItemDescription = FText::FromStringTable(UAssetPathHub::ST_ItemDescription_TableID, ItemID);
}
