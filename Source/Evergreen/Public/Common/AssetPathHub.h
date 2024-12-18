// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetPathHub.generated.h"

UENUM()
enum class EStringTableType : uint8
{
	ItemName,
	ItemDescription,
	UI,
	UI_Test
};

UCLASS()
class UAssetPathHub : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "AssetPathHub")
	static FName GetStringTableID(EStringTableType Type);
	
	inline static FString StringTableSavePath = "Localization/StringTables_DontOpenInEditor";
	
	inline static FName ST_ItemName_TableID = "/Game/Evergreen/DataTables/ST_ItemName.ST_ItemName";
	inline static FName ST_ItemDescription_TableID = "/Game/Evergreen/DataTables/ST_ItemDescription.ST_ItemDescription";
	inline static FName ST_UI_TableID = "/Game/Evergreen/DataTables/ST_UI.ST_UI";
	inline static FName ST_UI_Test_TableID = "/Game/Evergreen/DataTables/ST_UI_Test.ST_UI_Test";
	
	inline static FName ST_ItemName_CSV_Path = "Evergreen/DataTables/CSV/item_name.csv";
	inline static FName ST_ItemDescription_CSV_Path = "Evergreen/DataTables/CSV/item_description.csv";
	inline static FName ST_UI_CSV_Path = "Evergreen/DataTables/CSV/ui.csv";
	inline static FName ST_UI_Test_CSV_Path = "Evergreen/DataTables/CSV/ui_test.csv";

	inline static FName WBP_ItemDescriptionText_Path = "Blueprint'/Game/Evergreen/Blueprints/UI/WBP_ItemDescriptionText.WBP_ItemDescriptionText_C'";
	inline static FName WBP_ItemShowOnHovered_Path = "Blueprint'/Game/Evergreen/Blueprints/UI/WBP_ItemShowOnHovered.WBP_ItemShowOnHovered_C'";

	inline static FName BP_Interactor_Path = "Blueprint'/Game/Evergreen/Blueprints/Characters/BP_Interactor.BP_Interactor_C'";
};
