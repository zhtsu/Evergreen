// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Common/StringTableHelper.h"

#include "Common/AssetPathHub.h"
#include "Internationalization/StringTableRegistry.h"

#define IMPORT_STRING_TABLE(StringTableID)\
	FStringTableRegistry::Get().UnregisterStringTable(#StringTableID);\
	FStringTableRegistry::Get().Internal_LocTableFromFile(#StringTableID, #StringTableID,\
		UAssetPathHub::ST_##StringTableID##_CSV_Path.ToString(), FPaths::ProjectContentDir());\
	FStringTablePtr StringTableID##_StringTable = FStringTableRegistry::Get().FindMutableStringTable(#StringTableID);\
	if (!StringTableID##_StringTable)\
	{\
		UE_LOG(LogTemp, Warning, TEXT("%s"), *UAssetPathHub::ST_##StringTableID##_CSV_Path.ToString());\
	}\

void UStringTableHelper::ImportAllStringTableFromCSV()
{
	IMPORT_STRING_TABLE(ItemName)
	IMPORT_STRING_TABLE(ItemDescription)
	IMPORT_STRING_TABLE(UI)
	IMPORT_STRING_TABLE(UI_Test)
}
