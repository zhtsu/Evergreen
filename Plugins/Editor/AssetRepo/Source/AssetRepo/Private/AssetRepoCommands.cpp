// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetRepoCommands.h"

#define LOCTEXT_NAMESPACE "FAssetRepoModule"

void FAssetRepoCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "AssetRepo", "Execute AssetRepo action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
