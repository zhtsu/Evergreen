// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CommonCommandsStyle.h"

class FCommonCommandsCommands : public TCommands<FCommonCommandsCommands>
{
public:

	FCommonCommandsCommands()
		: TCommands<FCommonCommandsCommands>(TEXT("CommonCommands"), NSLOCTEXT("Contexts", "CommonCommands", "CommonCommands Plugin"), NAME_None, FCommonCommandsStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
