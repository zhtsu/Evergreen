// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UStringTableHelper
{
public:
	static void ImportAllStringTableFromCSV();
	
private:
	enum class ENotificationType
	{
		Default,
		Success,
		Error
	};
	
	static void AddErrorNotification(ENotificationType Type, FString CsvPath);
};

#include "..\Private\StringTableHelper.inl"
