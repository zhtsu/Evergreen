// Copyright Epic Games, Inc. All Rights Reserved.

#include "StringTableHelper.h"

#include "AssetPathHub.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Internationalization/StringTable.h"
#include "Internationalization/StringTableCore.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Internationalization/StringTableRegistry.h"
#include "Widgets/Notifications/SNotificationList.h"

void UStringTableHelper::ImportStringTableFromCSV(FString StringTableID, FString StringTableRelativePath, FString ImportFileRelativePath)
{
	IDesktopPlatform* const DesktopPlatform = FDesktopPlatformModule::Get();

	FStringTableRegistry::Get().UnregisterStringTable(FAssetPathHub::ST_ItemName_Reference);
	FStringTableRegistry::Get().Internal_LocTableFromFile(
		FAssetPathHub::ST_ItemName_Reference, TEXT("ST_ItemName"),
		FAssetPathHub::ST_ItemName_CSV_Path.ToString(), FPaths::ProjectContentDir());

	FStringTableRegistry::Get().UnregisterStringTable(FAssetPathHub::ST_ItemDescription_Reference);
	FStringTableRegistry::Get().Internal_LocTableFromFile(
		FAssetPathHub::ST_ItemDescription_Reference, TEXT("ST_ItemDescription"),
		FAssetPathHub::ST_ItemDescription_CSV_Path.ToString(), FPaths::ProjectContentDir());
	
	UStringTable* StringTable = FStringTableRegistry::Get().FindStringTableAsset(FAssetPathHub::ST_ItemName_Reference);
	if (StringTable)
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("Name"), FText::FromString(StringTable->GetFullName()));
		AddNotification(ENotificationType::Default, FText::Format(FTextFormat::FromString("{Name}"), Args));
	}
	else
	{
		AddNotification(ENotificationType::Error, TEXT("没有发现StringTable"));
	}
	
	// if (DesktopPlatform)
	// {
	// 	TArray<FString> OutFiles;
	// 	{
	// 		UStringTable* StringTable = Cast<UStringTable>(GetEditingObject());
	// 		if (StringTable)
	// 		{
	// 			StringTable->Modify();
	// 			StringTable->GetMutableStringTable()->ImportStrings(OutFiles[0]);
	// 		}
	// 	}
	// }
	// AddNotification(ENotificationType::Success, FText::FromString("Successful import all data from CSV"));
	// AddNotification(ENotificationType::Error, FText::FromString("Fail to import all data to CSV"));

	FStringTableRegistry::Get().UnregisterStringTable(FAssetPathHub::ST_ItemName_Reference);
	FStringTableRegistry::Get().UnregisterStringTable(FAssetPathHub::ST_ItemDescription_Reference);
}

void UStringTableHelper::ExportStringTableToCSV(FString StringTableID, FString StringTableRelativePath, FString ExportFileRelativePath)
{
	AddNotification(ENotificationType::Default, TEXT("这是一条通知"));
	AddNotification(ENotificationType::Success, "Successful import all data from CSV");
	AddNotification(ENotificationType::Error, "Fail to import all data to CSV");
}

void UStringTableHelper::AddNotification(ENotificationType Type, FString Msg)
{
	FNotificationInfo Info(FText::FromString(Msg));
	Info.ExpireDuration = 3.0f;
	Info.bUseLargeFont = true;
	
	if (Type == ENotificationType::Default)
		((void)0);
	else if (Type == ENotificationType::Success)
		Info.Image = FCoreStyle::Get().GetBrush("Icons.Success");
	else if (Type == ENotificationType::Error)
		Info.Image = FCoreStyle::Get().GetBrush("Icons.Error");
	
	FSlateNotificationManager::Get().AddNotification(Info);
}

void UStringTableHelper::AddNotification(ENotificationType Type, FText Msg)
{
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
}
