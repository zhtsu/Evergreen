// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetBean.h"
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
	
	void LoadAllAsset();
	
private:
	TSharedPtr<class FUICommandList> PluginCommands;

	TSharedPtr<SVerticalBox> CommandButtonContainer;
	
	const FString AssetRepoPathFile = IPluginManager::Get().FindPlugin("CommonCommands")->GetBaseDir() / TEXT("Resources/AssetRepoPath");
	FString AssetRepoPath;
	TArray<FAssetBean> AssetList = { FAssetBean(), FAssetBean() };
};
