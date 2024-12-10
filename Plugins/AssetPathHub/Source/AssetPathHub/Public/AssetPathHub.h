// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FAssetPathHub : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	inline static FName ST_ItemName = "/Game/Evergreen/DataTables/ST_ItemName.ST_ItemName";
	inline static FName ST_ItemDescription = "/Game/Evergreen/DataTables/ST_ItemDescription.ST_ItemDescription";
};
