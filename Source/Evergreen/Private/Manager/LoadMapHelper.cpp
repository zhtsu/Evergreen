// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/LoadMapHelper.h"

#include "Blueprint/UserWidget.h"
#include "Config/EvergreenLoadingSettings.h"
#include "Engine/AssetManager.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULoadMapHelper::AsyncLoadMap(TSoftObjectPtr<UWorld> TargetMap, bool bShowLoadingWidget)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	
	if (ULoadMapHelper* LMH = EGI->GetSubsystem<ULoadMapHelper>())
	{
		LMH->LoadedMap = TargetMap;

		if (bShowLoadingWidget) LMH->ShowLoadingWidget();

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

void ULoadMapHelper::ShowLoadingWidget()
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	
	if (TSubclassOf<UUserWidget> LoadingWidgetClass = UEvergreenLoadingSettings::Get()->LoadingWidgetClass)
	{
		if (!LoadingWidget)
		{
			LoadingWidget = CreateWidget(EGI, LoadingWidgetClass);
			EGI->GetGameViewportClient()->AddViewportWidgetContent(LoadingWidget->TakeWidget());
		}
	}
}

void ULoadMapHelper::HideLoadingWidget()
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	
	EGI->GetGameViewportClient()->RemoveViewportWidgetContent(LoadingWidget->TakeWidget());
}

// float ULoadMapHelper::GetLoadMapProgress()
// {
// 	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
// 	if (ULoadMapHelper* LMH = EGI->GetSubsystem<ULoadMapHelper>())
// 	{
// 		if (LMH->LoadHandle.IsValid())
// 		{
// 			return LMH->LoadHandle->GetProgress();
// 		}
// 	}
//
// 	return -1.f;
// }

void ULoadMapHelper::OnFinishedCallback()
{
	OnLoadMapFinished.ExecuteIfBound(LoadedMap);
}
