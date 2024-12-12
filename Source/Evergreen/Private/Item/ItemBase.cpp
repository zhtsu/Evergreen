// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"

#include "GeneralUtility.h"
#include "Internationalization/StringTable.h"
#include "Internationalization/StringTableCore.h"
#include "Internationalization/StringTableRegistry.h"

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
	UStringTable* ST_ItemName = FStringTableRegistry::Get().FindStringTableAsset(FAssetPathHub::ST_ItemName_Reference);
	if (ST_ItemName)
	{
		FString ItemNameStr;
		if (ST_ItemName->GetMutableStringTable()->GetSourceString(FTextKey(ItemID), ItemNameStr))
		{
			ItemName = FText::FromString(ItemNameStr);
		}
		else
		{
			FAST_WARNING(TEXT("Fail to find key '%s' from StringTable '%s'"), *ItemID, *FAssetPathHub::ST_ItemName_Reference.ToString());
			ItemName = {};
		}
	}
	else
	{
		FAST_WARNING(TEXT("Fail to find StringTable '%s'"), *FAssetPathHub::ST_ItemName_Reference.ToString());
		ItemName = {};
	}
}

void AEvergreenItemBase::ReadItemDescriptionFromStringTable()
{
	UStringTable* ST_ItemDescription = FStringTableRegistry::Get().FindStringTableAsset(FAssetPathHub::ST_ItemDescription_Reference);
	if (ST_ItemDescription)
	{
		FString ItemDescriptionStr;
		if (ST_ItemDescription->GetMutableStringTable()->GetSourceString(FTextKey(ItemID), ItemDescriptionStr))
		{
			ItemDescription = FText::FromString(ItemDescriptionStr);
		}
		else
		{
			FAST_WARNING(TEXT("Fail to find key '%s' from StringTable '%s'"), *ItemID, *FAssetPathHub::ST_ItemDescription_Reference.ToString());
			ItemDescription = {};
		}
	}
	else
	{
		FAST_WARNING(TEXT("Fail to find StringTable '%s'"), *FAssetPathHub::ST_ItemDescription_Reference.ToString());
		ItemDescription = {};
	}
}
