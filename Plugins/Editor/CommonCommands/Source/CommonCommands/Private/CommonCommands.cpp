// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonCommands.h"
#include "CommonCommandsStyle.h"
#include "CommonCommandsCommands.h"
#include "Widgets/Docking/SDockTab.h"
#include "ToolMenus.h"
#include "SCommandButtonWidget.h"
#include "HAL/FileManagerGeneric.h"
#include "Misc/FileHelper.h"
#include "Widgets/Layout/SScrollBox.h"

static const FName CommonCommandsTabName("CommonCommands");

#define LOCTEXT_NAMESPACE "FCommonCommandsModule"

void FCommonCommandsModule::StartupModule()
{
	LoadCommands();
	
	FCommonCommandsStyle::Initialize();
	FCommonCommandsStyle::ReloadTextures();

	FCommonCommandsCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCommonCommandsCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FCommonCommandsModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCommonCommandsModule::RegisterMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CommonCommandsTabName, FOnSpawnTab::CreateRaw(this, &FCommonCommandsModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FCommonCommandsTabTitle", "CommonCommands"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FCommonCommandsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCommonCommandsStyle::Shutdown();

	FCommonCommandsCommands::Unregister();
}

void FCommonCommandsModule::PluginButtonClicked()
{
	LoadCommands();

	if (CommandButtonContainer)
	{
		CommandButtonContainer->ClearChildren();
		for (const FString& Command : Commands)
		{
			CommandButtonContainer->AddSlot()
			.AutoHeight()
			[
				SNew(SCommandButtonWidget)
				.CommandText(FText::FromString(Command))
			];
		}
	}

	FGlobalTabmanager::Get()->TryInvokeTab(CommonCommandsTabName);
}

void FCommonCommandsModule::RegisterMenus()
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
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("CommonCommands");
			{
				FToolMenuEntry& Entry = Section.AddEntry(
					FToolMenuEntry::InitToolBarButton(
						FCommonCommandsCommands::Get().PluginAction,
						FText::FromString("CC"),
						FText::FromString("CommonCommands: Quickly execute common console commands for debug"),
						FSlateIcon(FCommonCommandsStyle::GetStyleSetName(), "CommonCommands.PluginAction")
					)
				);
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

void FCommonCommandsModule::LoadCommands()
{
	if (FFileManagerGeneric::Get().FileExists(*CommandsFilePath))
	{
		FFileHelper::LoadFileToStringArray(Commands, *CommandsFilePath);
	}
}

TSharedRef<class SDockTab> FCommonCommandsModule::OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs)
{
	SAssignNew(CommandButtonContainer, SVerticalBox);
	for (const FString& Command : Commands)
	{
		CommandButtonContainer->AddSlot()
		.AutoHeight()
		[
			SNew(SCommandButtonWidget)
			.CommandText(FText::FromString(Command))
		];
	}
	
	TSharedRef<SDockTab> TabWidget = SNew(SDockTab).TabRole(ETabRole::NomadTab)
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		[
			CommandButtonContainer.ToSharedRef()
		]
	];

	return TabWidget;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCommonCommandsModule, CommonCommands)