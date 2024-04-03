// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetRepoStyle.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

#if ENGINE_MAJOR_VERSION == 5
#include "Styling/SlateStyleMacros.h"
#endif


#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FAssetRepoStyle::StyleInstance = nullptr;

void FAssetRepoStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FAssetRepoStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FAssetRepoStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("AssetRepoStyle"));
	return StyleSetName;
}


#if ENGINE_MAJOR_VERSION == 4
#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush( RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#endif


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef< FSlateStyleSet > FAssetRepoStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("AssetRepoStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("AssetRepo")->GetBaseDir() / TEXT("Resources"));

	FVector2D IconSize = Icon20x20;

#if ENGINE_MAJOR_VERSION == 4
	IconSize = Icon40x40;
#endif
	
	Style->Set("AssetRepo.PluginAction", new IMAGE_BRUSH(TEXT("AssetRepoIcon"), IconSize));
	
	return Style;
}


#if ENGINE_MAJOR_VERSION == 4
#undef IMAGE_BRUSH 
#endif


void FAssetRepoStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FAssetRepoStyle::Get()
{
	return *StyleInstance;
}
