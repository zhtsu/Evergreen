// Copyright Epic Games, Inc. All Rights Reserved.

#include "LanguageSwitcherStyle.h"
#include "LanguageSwitcher.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FLanguageSwitcherStyle::StyleInstance = nullptr;

void FLanguageSwitcherStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FLanguageSwitcherStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FLanguageSwitcherStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("LanguageSwitcherStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FLanguageSwitcherStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("LanguageSwitcherStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("LanguageSwitcher")->GetBaseDir() / TEXT("Resources"));
	
	Style->Set("LanguageSwitcher.PluginAction", new IMAGE_BRUSH(TEXT("LanguageSwitcherIcon"), Icon20x20));

	return Style;
}

void FLanguageSwitcherStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FLanguageSwitcherStyle::Get()
{
	return *StyleInstance;
}
