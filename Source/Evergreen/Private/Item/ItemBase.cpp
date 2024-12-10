// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"

#include "AssetPathHub.h"
#include "Evergreen/Evergreen.h"
#include "Internationalization/StringTableCore.h"
#include "Internationalization/StringTableRegistry.h"

AEvergreenItemBase::AEvergreenItemBase()
{
	ReadItemNameFromStringTable();
	ReadItemDescriptionFromStringTable();
}

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

void AEvergreenItemBase::ReadItemNameFromStringTable()
{
	FStringTableConstPtr ST_ItemName = FStringTableRegistry::Get().FindStringTable(FAssetPathHub::ST_ItemName);
	if (ST_ItemName)
	{
		FString ItemNameStr;
		if (ST_ItemName->GetSourceString(FTextKey(ItemID.ToString()), ItemNameStr))
		{
			ItemInfo.ItemName = FText::FromString(ItemNameStr);
		}
		else
		{
			FAST_WARNING(TEXT("Fail to find key '%s' from StringTable '%s'"), *ItemID.ToString(), *FAssetPathHub::ST_ItemName.ToString());
			ItemInfo = {};
		}
	}
	else
	{
		FAST_WARNING(TEXT("Fail to find StringTable '%s'"), *FAssetPathHub::ST_ItemName.ToString());
		ItemInfo = {};
	}
}

void AEvergreenItemBase::ReadItemDescriptionFromStringTable()
{
	FStringTableConstPtr ST_ItemDescription = FStringTableRegistry::Get().FindStringTable(FAssetPathHub::ST_ItemDescription);
	if (ST_ItemDescription)
	{
		FString ItemNameStr;
		if (ST_ItemDescription->GetSourceString(FTextKey(ItemID.ToString()), ItemNameStr))
		{
			ItemInfo.ItemDescription = FText::FromString(ItemNameStr);
		}
		else
		{
			FAST_WARNING(TEXT("Fail to find key '%s' from StringTable '%s'"), *ItemID.ToString(), *FAssetPathHub::ST_ItemDescription.ToString());
			ItemInfo = {};
		}
	}
	else
	{
		FAST_WARNING(TEXT("Fail to find StringTable '%s'"), *FAssetPathHub::ST_ItemDescription.ToString());
		ItemInfo = {};
	}
}
