// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IPluginManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FAssetRepoModule : public IModuleInterface
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
	
private:
	void LoadConfig();
	
	TSharedPtr<class FUICommandList> PluginCommands;
	
	const FString ConfigFilePath = IPluginManager::Get().FindPlugin("AssetRepo")->GetBaseDir() / TEXT("Resources/Config");

	FString AssetRepoRootPath;
};
