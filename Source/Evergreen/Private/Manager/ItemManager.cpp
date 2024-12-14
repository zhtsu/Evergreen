// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/ItemManager.h"
#include "Item/ItemBase.h"

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
