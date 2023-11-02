// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "LanguageSwitcherStyle.h"

class FLanguageSwitcherCommands : public TCommands<FLanguageSwitcherCommands>
{
public:

	FLanguageSwitcherCommands()
		: TCommands<FLanguageSwitcherCommands>(TEXT("LanguageSwitcher"), NSLOCTEXT("Contexts", "LanguageSwitcher", "LanguageSwitcher Plugin"), NAME_None, FLanguageSwitcherStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
