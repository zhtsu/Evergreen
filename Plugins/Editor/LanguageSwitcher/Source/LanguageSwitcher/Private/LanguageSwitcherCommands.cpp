// Copyright Epic Games, Inc. All Rights Reserved.

#include "LanguageSwitcherCommands.h"

#define LOCTEXT_NAMESPACE "FLanguageSwitcherModule"

void FLanguageSwitcherCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "LanguageSwitcher", "Execute LanguageSwitcher action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
