// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"

#include "CommonMacro.h"
#include "AssetPathHub.h"
#include "Internationalization/StringTableCore.h"
#include "Internationalization/StringTableRegistry.h"

AEvergreenItemBase::AEvergreenItemBase()
{
	ReadItemNameFromStringTable();
	ReadItemDescriptionFromStringTable();
}

#if WITH_EDITOR
void AEvergreenItemBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = PropertyChangedEvent.GetPropertyName();
	if (PropertyName == FName("ItemID"))
	{
		ReadItemNameFromStringTable();
		ReadItemDescriptionFromStringTable();
	}
}

#endif

void AEvergreenItemBase::ReadItemNameFromStringTable()
{
	FStringTableConstPtr ST_ItemName = FStringTableRegistry::Get().FindStringTable(FAssetPathHub::ItemName_TableID);
	if (ST_ItemName)
	{
		FString ItemNameStr;
		if (ST_ItemName->GetSourceString(FTextKey(ItemID), ItemNameStr))
		{
			ItemName = FText::FromString(ItemNameStr);
		}
		else
		{
			FAST_WARNING(TEXT("Fail to find key '%s' from StringTable '%s'"), *ItemID, *FAssetPathHub::ItemName_TableID.ToString());
			ItemName = {};
		}
	}
	else
	{
		FAST_WARNING(TEXT("Fail to find StringTable '%s'"), *FAssetPathHub::ItemName_TableID.ToString());
		ItemName = {};
	}
}

void AEvergreenItemBase::ReadItemDescriptionFromStringTable()
{
	FStringTableConstPtr ST_ItemDescription = FStringTableRegistry::Get().FindStringTable(FAssetPathHub::ItemDescription_TableID);
	if (ST_ItemDescription)
	{
		FString ItemDescriptionStr;
		if (ST_ItemDescription->GetSourceString(FTextKey(ItemID), ItemDescriptionStr))
		{
			ItemDescription = FText::FromString(ItemDescriptionStr);
		}
		else
		{
			FAST_WARNING(TEXT("Fail to find key '%s' from StringTable '%s'"), *ItemID, *FAssetPathHub::ItemDescription_TableID.ToString());
			ItemDescription = {};
		}
	}
	else
	{
		FAST_WARNING(TEXT("Fail to find StringTable '%s'"), *FAssetPathHub::ItemDescription_TableID.ToString());
		ItemDescription = {};
	}
}
