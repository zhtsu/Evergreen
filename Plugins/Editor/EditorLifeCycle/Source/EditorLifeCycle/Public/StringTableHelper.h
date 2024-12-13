// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StringTableHelper.generated.h"

UCLASS()
class UStringTableHelper : public UObject
{
	GENERATED_BODY()

public:
	static void ImportStringTableFromCSV(FString StringTableID, FString StringTableRelativePath, FString ImportFileRelativePath);
	static void ExportStringTableToCSV(FString StringTableID, FString StringTableRelativePath, FString ExportFileRelativePath);

private:
	enum class ENotificationType
	{
		Default,
		Success,
		Error
	};
	
	static void AddNotification(ENotificationType Type, FString Msg);
	static void AddNotification(ENotificationType Type, FText Msg);
};
