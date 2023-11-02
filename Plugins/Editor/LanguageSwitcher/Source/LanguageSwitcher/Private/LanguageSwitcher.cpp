// Copyright Epic Games, Inc. All Rights Reserved.

#include "LanguageSwitcher.h"
#include "LanguageSwitcherStyle.h"
#include "LanguageSwitcherCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

#include "Editor/InternationalizationSettings/Classes/InternationalizationSettingsModel.h"
#include "Runtime/Core/Public/Internationalization/Internationalization.h"
#include "Editor/MainFrame/Public/Interfaces/IMainFrameModule.h"


static const FName LanguageSwitcherTabName("LanguageSwitcher");

#define LOCTEXT_NAMESPACE "FLanguageSwitcherModule"

void FLanguageSwitcherModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FLanguageSwitcherStyle::Initialize();
	FLanguageSwitcherStyle::ReloadTextures();

	FLanguageSwitcherCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FLanguageSwitcherCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FLanguageSwitcherModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FLanguageSwitcherModule::RegisterMenus));
}

void FLanguageSwitcherModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FLanguageSwitcherStyle::Shutdown();

	FLanguageSwitcherCommands::Unregister();
}

void FLanguageSwitcherModule::PluginButtonClicked()
{
	UInternationalizationSettingsModel* SettingsModel = NewObject<UInternationalizationSettingsModel>();
	SettingsModel->GetEditorLanguage(CurrentLanguage);

	if (CurrentLanguage == "en")
	{
		CurrentLanguage = "zh-Hans";
	}
	else
	{
		CurrentLanguage = "en";
	}

	SettingsModel->SetEditorLanguage(CurrentLanguage);
	FInternationalization& I18N = FInternationalization::Get();
	I18N.SetCurrentLanguage(CurrentLanguage);
}

void FLanguageSwitcherModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("LanguageSwitcher");
			{
				FToolMenuEntry& Entry = Section.AddEntry(
					FToolMenuEntry::InitToolBarButton(
						FLanguageSwitcherCommands::Get().PluginAction,
						FText::FromString("LanguageSwitcher"),
						FText::FromString("Switch editor language between Chinese and English"),
						FSlateIcon(FLanguageSwitcherStyle::GetStyleSetName(), "LanguageSwitcher.PluginAction")
					)
				);

				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLanguageSwitcherModule, LanguageSwitcher)