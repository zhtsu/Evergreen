// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/LoaderManager.h"

void ULoaderManager::AsyncLoadMap(TSoftObjectPtr<UWorld> TargetMap)
{
	ULoader* Loader = NewObject<ULoader>(GetOuter(), ULoader::StaticClass());
	if (Loader)
	{
		LoaderDict.Add(TargetMap, Loader);
		FOnMapLoadFinished OnFinished;
		OnFinished.BindDynamic(this, &ULoaderManager::OnLoadMapFinished);
		Loader->AsyncLoadMap(TargetMap, OnFinished);
	}
}

float ULoaderManager::GetLoadMapProgress(TSoftObjectPtr<UWorld> LoadingMap) const
{
	if (LoaderDict.Find(LoadingMap))
	{
		return LoaderDict[LoadingMap]->GetLoadProgress();
	}

	return -1.f;
}

void ULoaderManager::OnLoadMapFinished(TSoftObjectPtr<UWorld> LoadedMap)
{
	if (LoaderDict.Find(LoadedMap))
	{
		LoaderDict.Remove(LoadedMap);
	}
}
