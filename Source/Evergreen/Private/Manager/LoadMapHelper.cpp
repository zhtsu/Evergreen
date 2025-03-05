// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/LoadMapHelper.h"

#include "Blueprint/UserWidget.h"
#include "Config/EvergreenLoadingSettings.h"
#include "Engine/AssetManager.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULoadMapHelper::AsyncLoadMap(TSoftObjectPtr<UWorld> TargetMap)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	
	if (ULoadMapHelper* LMH = EGI->GetSubsystem<ULoadMapHelper>())
	{
		LMH->LoadedMap = TargetMap;
		
		if (TSubclassOf<UUserWidget> LoadingWidgetClass = UEvergreenLoadingSettings::Get()->LoadingWidgetClass)
		{
			if (!LMH->LoadingWidget)
			{
				LMH->LoadingWidget = CreateWidget(EGI, LoadingWidgetClass);
				EGI->GetGameViewportClient()->AddViewportWidgetContent(LMH->LoadingWidget->TakeWidget());
			}
		}

		TSoftObjectPtr<UWorld> TransitMap = UEvergreenLoadingSettings::Get()->TransitMap;
		if (!TransitMap.ToSoftObjectPath().IsNull())
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(EGI->GetWorld(), TransitMap);
		}
	}
}

void ULoadMapHelper::StartAsyncLoadMap_CallInTransitMap(const FOnMapLoadFinished& OnFinished)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();

	if (ULoadMapHelper* LMH = EGI->GetSubsystem<ULoadMapHelper>())
	{
		if (!LMH->LoadedMap.ToSoftObjectPath().IsValid()) return;
		
		LMH->OnLoadMapFinished = OnFinished;
		
		LMH->LoadHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(
			LMH->LoadedMap.ToSoftObjectPath(),
			FStreamableDelegate::CreateUObject(LMH, &ULoadMapHelper::OnFinishedCallback),
			FStreamableManager::AsyncLoadHighPriority);
	}
}

float ULoadMapHelper::GetLoadMapProgress()
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (ULoadMapHelper* LMH = EGI->GetSubsystem<ULoadMapHelper>())
	{
		if (LMH->LoadHandle.IsValid())
		{
			return LMH->LoadHandle->GetProgress();
		}
	}

	return -1.f;
}

void ULoadMapHelper::OnFinishedCallback()
{
	OnLoadMapFinished.ExecuteIfBound(LoadedMap);
	
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	EGI->GetGameViewportClient()->RemoveViewportWidgetContent(LoadingWidget->TakeWidget());
}
