// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IPluginManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FCommonCommandsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	
	void LoadCommands();
	
private:
	TSharedPtr<class FUICommandList> PluginCommands;

	TSharedPtr<SVerticalBox> CommandButtonContainer;
	
	const FString CommandsFilePath = IPluginManager::Get().FindPlugin("CommonCommands")->GetBaseDir() / TEXT("Resources/Commands.txt");
	TArray<FString> Commands;
};
