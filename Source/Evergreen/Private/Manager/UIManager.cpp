// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/UIManager.h"

#include "CommonActivatableWidget.h"
#include "..\..\Public\UI\RootCanvasWidget.h"

UUIManager::UUIManager()
{
	WidgetMap = TMap<int32, UEvergreenWidgetBase*>();
	UniqueWidgetMap = TMap<TSubclassOf<UEvergreenWidgetBase>, UEvergreenWidgetBase*>();
}

UCommonActivatableWidget* UUIManager::OpenUI(TSubclassOf<UEvergreenWidgetBase> WidgetClass)
{
	if (RootCanvas)
	{
		UEvergreenWidgetBase* Widget = Cast<UEvergreenWidgetBase>(RootCanvas->PushWidgetToStack(WidgetClass));
		if (Widget)
		{
			WidgetMap.Add(Widget->GetUniqueID(), Widget);
		}
	}

	return nullptr;
}

UCommonActivatableWidget* UUIManager::OpenUniqueUI(TSubclassOf<UEvergreenWidgetBase> WidgetClass, bool& Success)
{
	if (RootCanvas && UniqueWidgetMap.Find(WidgetClass) == nullptr)
	{
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

void UUIManager::CloseUniqueUI(TSubclassOf<UEvergreenWidgetBase> WidgetClassToRemove, bool& Success)
{
	if (RootCanvas && UniqueWidgetMap.Find(WidgetClassToRemove) != nullptr)
	{
		Success = true;
		
		UCommonActivatableWidget* Widget = *UniqueWidgetMap.Find(WidgetClassToRemove);
		RootCanvas->RemoveWidgetFromStack(*Widget);
		
		UniqueWidgetMap.Remove(WidgetClassToRemove);
	}

	Success = false;
}
