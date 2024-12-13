// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FAssetPathHub
{
public:
	inline static FName ItemName_TableID = "ItemName";
	inline static FName ItemDescription_TableID = "ItemDescription";
	inline static FName UI_TableID = "UI";
	
	inline static FName ST_ItemName_CSV_Path = "Evergreen/DataTables/CSV/item_name.csv";
	inline static FName ST_ItemDescription_CSV_Path = "Evergreen/DataTables/CSV/item_description.csv";
	inline static FName ST_UI_CSV_Path = "Evergreen/DataTables/CSV/ui.csv";

	inline static FName WBP_ItemDescriptionText_Path = "Blueprint'/Game/Evergreen/Blueprints/UI/WBP_ItemDescriptionText.WBP_ItemDescriptionText_C'";
	inline static FName WBP_ItemShowOnHovered_Path = "Blueprint'/Game/Evergreen/Blueprints/UI/WBP_ItemShowOnHovered.WBP_ItemShowOnHovered_C'";
};
