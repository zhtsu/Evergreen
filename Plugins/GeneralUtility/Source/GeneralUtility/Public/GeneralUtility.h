// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#define FAST_PRINT(Message) \
if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Message); }

#define FAST_LOG(Message, ...) \
UE_LOG(LogTemp, Display, Message, ##__VA_ARGS__)

#define FAST_WARNING(Message, ...) \
UE_LOG(LogTemp, Warning, Message, ##__VA_ARGS__) \
UE_LOG(LogTemp, Warning, TEXT("Please check this file: %s - Line: %d"), __FILEW__, __LINE__)

class FGeneralUtility : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

class FAssetPathHub
{
public:
	inline static FName ST_ItemName_CSV_Path = "Evergreen/DataTables/item_name.csv";
	inline static FName ST_ItemName_Reference = "/Game/Evergreen/DataTables/ST_ItemName.ST_ItemName";
	
	inline static FName ST_ItemDescription_CSV_Path = "Evergreen/DataTables/item_description.csv";
	inline static FName ST_ItemDescription_Reference = "/Game/Evergreen/DataTables/ST_ItemDescription.ST_ItemDescription";

	inline static FName WBP_ItemDescriptionText_Path = "Blueprint'/Game/Evergreen/Blueprints/UI/WBP_ItemDescriptionText.WBP_ItemDescriptionText_C'";
	inline static FName WBP_ItemShowOnHovered_Path = "Blueprint'/Game/Evergreen/Blueprints/UI/WBP_ItemShowOnHovered.WBP_ItemShowOnHovered_C'";
};

class StringTableHelper
{
public:
	UFUNCTION(BlueprintCallable, Category = "EvergreenEditorUtility")
	static void ImportStringTableFromCSV();

	UFUNCTION(BlueprintCallable, Category = "EvergreenEditorUtility")
	static void ExportStringTableToCSV();
};
