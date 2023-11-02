// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonCommandsCommands.h"

#define LOCTEXT_NAMESPACE "FCommonCommandsModule"

void FCommonCommandsCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "CommonCommands", "Execute CommonCommands action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
