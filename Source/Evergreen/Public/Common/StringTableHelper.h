// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

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
};
