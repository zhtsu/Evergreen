// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AssetPathHub.h"
#include "Internationalization/StringTableRegistry.h"
#if WITH_EDITOR
	#include "Framework/Notifications/NotificationManager.h"
	#include "Widgets/Notifications/SNotificationList.h"
#endif

#define CREATE_STRING_TABLE(StringTableID)\
	FStringTableRegistry::Get().UnregisterStringTable(#StringTableID);\
	FStringTableRegistry::Get().Internal_LocTableFromFile(#StringTableID, #StringTableID,\
		FAssetPathHub::ST_##StringTableID##_CSV_Path.ToString(), FPaths::ProjectContentDir());\
	FStringTableConstPtr StringTableID##_StringTable = FStringTableRegistry::Get().FindStringTable(#StringTableID);\
	if (!StringTableID##_StringTable)\
	{\
		AddErrorNotification(ENotificationType::Error, FAssetPathHub::ST_##StringTableID##_CSV_Path.ToString());\
	}

inline void UStringTableHelper::ImportAllStringTableFromCSV()
{
	CREATE_STRING_TABLE(ItemName)
	CREATE_STRING_TABLE(ItemDescription)
	CREATE_STRING_TABLE(UI)
}

inline void UStringTableHelper::AddErrorNotification(ENotificationType Type, FString CsvPath)
{
#if WITH_EDITOR
	FFormatNamedArguments Args;
	Args.Add("CSV", FText::FromString(CsvPath));
	FText Msg = FText::Format(FTextFormat::FromString("{CSV}"), Args);
	
	FNotificationInfo Info(Msg);
	Info.ExpireDuration = 3.0f;
	Info.bUseLargeFont = true;
	
	if (Type == ENotificationType::Default)
		((void)0);
	else if (Type == ENotificationType::Success)
		Info.Image = FCoreStyle::Get().GetBrush("Icons.Success");
	else if (Type == ENotificationType::Error)
		Info.Image = FCoreStyle::Get().GetBrush("Icons.Error");
	
	FSlateNotificationManager::Get().AddNotification(Info);
#endif
}
