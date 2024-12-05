// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetRepo.h"
#include "AssetRepoStyle.h"
#include "AssetRepoCommands.h"
#include "Widgets/Docking/SDockTab.h"
#include "ToolMenus.h"
#include "../Public/SAssetRepoTileView.h"
#include "HAL/FileManagerGeneric.h"
#include "Misc/FileHelper.h"

static const FName AssetRepoTabName("AssetRepo");

#define LOCTEXT_NAMESPACE "FAssetRepoModule"

void FAssetRepoModule::StartupModule()
{
	FAssetRepoStyle::Initialize();
	FAssetRepoStyle::ReloadTextures();

	FAssetRepoCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAssetRepoCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FAssetRepoModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAssetRepoModule::RegisterMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AssetRepoTabName, FOnSpawnTab::CreateRaw(this, &FAssetRepoModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FAssetRepoTabTitle", "AssetRepo"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	LoadConfig();
}

void FAssetRepoModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAssetRepoStyle::Shutdown();

	FAssetRepoCommands::Unregister();
}

void FAssetRepoModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(AssetRepoTabName);
}

void FAssetRepoModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
#if ENGINE_MAJOR_VERSION == 5
		FName MenuName = "LevelEditor.LevelEditorToolBar.PlayToolBar";
#endif

#if ENGINE_MAJOR_VERSION == 4
		FName MenuName = "LevelEditor.LevelEditorToolBar";
#endif
		
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu(MenuName);
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("AssetRepo");
			{
				FToolMenuEntry& Entry = Section.AddEntry(
					FToolMenuEntry::InitToolBarButton(
						FAssetRepoCommands::Get().PluginAction,
						FText::FromString("AR"),
						FText::FromString("AssetRepo: Asset repository"),
						FSlateIcon(FAssetRepoStyle::GetStyleSetName(), "AssetRepo.PluginAction")
					)
				);
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

void FAssetRepoModule::LoadConfig()
{
	if (FFileManagerGeneric::Get().FileExists(*ConfigFilePath))
	{
		FFileHelper::LoadFileToString(AssetRepoRootPath, *ConfigFilePath);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load file: %s"), *ConfigFilePath);
	}
}

TSharedRef<class SDockTab> FAssetRepoModule::OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SAssetRepoTileView> AssetRepoTileView =
		SNew(SAssetRepoTileView)
		.AssetRepoRootPath(AssetRepoRootPath);
	
	TSharedRef<SDockTab> TabWidget = SNew(SDockTab).TabRole(ETabRole::NomadTab)
	[
		AssetRepoTileView
	];

	return TabWidget;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssetRepoModule, AssetRepo)