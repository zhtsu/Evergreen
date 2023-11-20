// Copyright Epic Games, Inc. All Rights Reserved.

#include "LanguageSwitcherStyle.h"
#include "LanguageSwitcher.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

#if ENGINE_MAJOR_VERSION == 5
#include "Styling/SlateStyleMacros.h"
#endif


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


#if ENGINE_MAJOR_VERSION == 4
#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush( RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#endif


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef< FSlateStyleSet > FLanguageSwitcherStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("LanguageSwitcherStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("LanguageSwitcher")->GetBaseDir() / TEXT("Resources"));

	FVector2D IconSize = Icon20x20;

#if ENGINE_MAJOR_VERSION == 4
	IconSize = Icon40x40;
#endif
	
	Style->Set("LanguageSwitcher.PluginAction", new IMAGE_BRUSH(TEXT("LanguageSwitcherIcon"), IconSize));

	return Style;
}


#if ENGINE_MAJOR_VERSION == 4
#undef IMAGE_BRUSH 
#endif


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
