// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AssetRepoStyle.h"

class FAssetRepoCommands : public TCommands<FAssetRepoCommands>
{
public:

	FAssetRepoCommands()
		: TCommands<FAssetRepoCommands>(TEXT("AssetRepo"), NSLOCTEXT("Contexts", "AssetRepo", "AssetRepo Plugin"), NAME_None, FAssetRepoStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
