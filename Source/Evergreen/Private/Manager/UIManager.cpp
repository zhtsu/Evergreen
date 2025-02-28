// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/UIManager.h"

#include "CommonActivatableWidget.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "Gameplay/EvergreenPlayerController.h"
#include "Manager/ViewManager.h"
#include "UI/RootCanvasWidget.h"

UUIManager::UUIManager()
{
	WidgetMap = TMap<int32, UEvergreenWidgetBase*>();
	UniqueWidgetMap = TMap<TSubclassOf<UEvergreenWidgetBase>, UEvergreenWidgetBase*>();
}

UEvergreenWidgetBase* UUIManager::OpenUI(TSubclassOf<UEvergreenWidgetBase> WidgetClass)
{
	if (RootCanvas)
	{
		UEvergreenWidgetBase* Widget = Cast<UEvergreenWidgetBase>(RootCanvas->PushWidgetToStack(WidgetClass));
		if (Widget)
		{
			WidgetMap.Add(Widget->GetUniqueID(), Widget);
			return Widget;
		}
	}

	return nullptr;
}

UEvergreenWidgetBase* UUIManager::OpenUniqueUI(TSubclassOf<UEvergreenWidgetBase> WidgetClass, bool& Success)
{
	if (RootCanvas && UniqueWidgetMap.Find(WidgetClass) == nullptr)
	{
		UViewManager* ViewManager = UEvergreenGameInstance::GetEvergreenGameInstance()->GetSubsystem<UViewManager>();
		if (ViewManager)
		{
			ViewManager->SetCameraOffsetFollowMouseEnabled(false);
		}
		
		Success = true;

		UEvergreenWidgetBase* Widget = Cast<UEvergreenWidgetBase>(RootCanvas->PushWidgetToStack(WidgetClass));
		UniqueWidgetMap.Add(WidgetClass, Widget);
		
		return Widget;
	}

	Success = false;
	
	return nullptr;
}

void UUIManager::CloseUI(UEvergreenWidgetBase* WidgetToRemove)
{
	if (WidgetToRemove && WidgetMap.Find(WidgetToRemove->GetUniqueID()) != nullptr)
	{
		UCommonActivatableWidget* Widget = *WidgetMap.Find(WidgetToRemove->GetUniqueID());
		RootCanvas->RemoveWidgetFromStack(*WidgetToRemove);
		
		WidgetMap.Remove(WidgetToRemove->GetUniqueID());
	}
}

void UUIManager::CloseUniqueUI(TSubclassOf<UEvergreenWidgetBase> WidgetClassToRemove, bool bResetMousePosition, bool& Success)
{
	if (RootCanvas && UniqueWidgetMap.Find(WidgetClassToRemove) != nullptr)
	{
		UViewManager* ViewManager = UEvergreenGameInstance::GetEvergreenGameInstance()->GetSubsystem<UViewManager>();
		if (ViewManager)
		{
			ViewManager->SetCameraOffsetFollowMouseEnabled(true);
		}
		
		Success = true;
		
		UCommonActivatableWidget* Widget = *UniqueWidgetMap.Find(WidgetClassToRemove);
		RootCanvas->RemoveWidgetFromStack(*Widget);
		
		UniqueWidgetMap.Remove(WidgetClassToRemove);

		if (bResetMousePosition)
		{
			AEvergreenPlayerController* EPC = UEvergreenGameInstance::GetEvergreenGameInstance()->GetEvergreenPlayerController();

			FIntPoint ViewportSize;
			EPC->GetViewportSize(ViewportSize.X, ViewportSize.Y);
	
			FVector2D ViewportCenter = FVector2D(ViewportSize) * 0.5;
			
			EPC->SetMousePosition(ViewportCenter);
		}
	}

	Success = false;
}
