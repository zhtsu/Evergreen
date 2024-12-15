// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/ItemManager.h"

#include "Common/AssetPathHub.h"
#include "World/ItemBase.h"

UItemManager::UItemManager()
{
	
}

void UItemManager::CollectItem(AEvergreenItemBase* Item)
{
	if (!Item) return;
	
	if (!CollectedItemIdArray.Contains(Item->ItemID))
	{
		CollectedItemIdArray.Add(Item->ItemID);
		OnItemCollected.Broadcast(Item->ItemID);
		Item->Destroy();
	}
}

bool UItemManager::HasItem(FString ItemID)
{
	return CollectedItemIdArray.Contains(ItemID);
}

void UItemManager::GetItemInfo(FString ItemID, FEvergreenItemInfo& OutItemInfo)
{
	OutItemInfo = {
		FText::FromStringTable(UAssetPathHub::ST_ItemName_TableID, ItemID),
		FText::FromStringTable(UAssetPathHub::ST_ItemDescription_TableID, ItemID)
	};
}
