// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/LoadMapHelper.h"

#include "Blueprint/UserWidget.h"
#include "Config/EvergreenLoadingSettings.h"
#include "Gameplay/EvergreenGameInstance.h"

void ULoadMapHelper::ShowLoadingWidget()
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	
	if (TSubclassOf<UUserWidget> LoadingWidgetClass = UEvergreenLoadingSettings::Get()->LoadingWidgetClass)
	{
		if (!LoadingWidget)
		{
			LoadingWidget = CreateWidget(EGI, LoadingWidgetClass);
		}

		EGI->GetGameViewportClient()->AddViewportWidgetContent(LoadingWidget->TakeWidget(), 100);
	}
}

void ULoadMapHelper::HideLoadingWidget()
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	
	EGI->GetGameViewportClient()->RemoveViewportWidgetContent(LoadingWidget->TakeWidget());
}

bool ULoadMapHelper::IsMapEqual(TSoftObjectPtr<UWorld> A, TSoftObjectPtr<UWorld> B)
{
	if (A.ToSoftObjectPath().IsNull() && B.ToSoftObjectPath().IsValid()) return false;
	if (B.ToSoftObjectPath().IsNull() && A.ToSoftObjectPath().IsValid()) return false;
	if (A.ToSoftObjectPath().IsNull() && B.ToSoftObjectPath().IsNull()) return true;
	
	return A.ToSoftObjectPath().GetAssetFName() == B.ToSoftObjectPath().GetAssetFName();
}
