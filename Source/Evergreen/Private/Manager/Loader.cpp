// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/Loader.h"

#include "Engine/AssetManager.h"

void ULoader::AsyncLoadMap(TSoftObjectPtr<UWorld> TargetMap, const FOnMapLoadFinished& OnFinished)
{
	OnMapLoadFinished = OnFinished;
	LoadedMap = TargetMap;

	Handle = UAssetManager::GetStreamableManager().RequestAsyncLoad(
		TargetMap.ToSoftObjectPath(),
		FStreamableDelegate::CreateUObject(this, &ULoader::ExecuteOnFinished),
		FStreamableManager::AsyncLoadHighPriority);
}

float ULoader::GetLoadProgress() const
{
	if (Handle.IsValid())
	{
		return Handle->GetProgress();
	}

	return -1.f;
}

TSoftObjectPtr<UWorld> ULoader::GetLoadedMapSoftObjectPtr() const
{
	return LoadedMap;
}

void ULoader::ExecuteOnFinished()
{
	OnMapLoadFinished.ExecuteIfBound(LoadedMap);

	Handle.Reset();
}
