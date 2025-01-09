// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/UIManager.h"

#include "CommonActivatableWidget.h"
#include "UI/MainUIWidget.h"

UUIManager::UUIManager()
{
	WidgetMap = TMap<int32, TSharedPtr<UCommonActivatableWidget>>();
	UniqueWidgetMap = TMap<TSubclassOf<UCommonActivatableWidget>, TSharedPtr<UCommonActivatableWidget>>();
}

UCommonActivatableWidget* UUIManager::OpenUI(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	if (MainUI)
	{
		TSharedPtr<UCommonActivatableWidget> WidgetPtr = MakeShareable(MainUI->PushWidgetToStack(ActivatableWidgetClass));
		if (WidgetPtr)
		{
			WidgetMap.Add(WidgetPtr->GetUniqueID(), WidgetPtr);
		}
	}

	return nullptr;
}

UCommonActivatableWidget* UUIManager::OpenUniqueUI(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass, bool& Success)
{
	if (MainUI && UniqueWidgetMap.Find(ActivatableWidgetClass) == nullptr)
	{
		TSharedPtr<UCommonActivatableWidget> WidgetPtr = MakeShareable(MainUI->PushWidgetToStack(ActivatableWidgetClass));
		if (WidgetPtr)
		{
			UniqueWidgetMap.Add(ActivatableWidgetClass, WidgetPtr);
		}
		
		Success = true;
		return MainUI->PushWidgetToStack(ActivatableWidgetClass);
	}

	Success = false;
	return nullptr;
}

void UUIManager::CloseUI(UCommonActivatableWidget* WidgetToRemove)
{
	if (WidgetToRemove && WidgetMap.Find(WidgetToRemove->GetUniqueID()) != nullptr)
	{
		WidgetMap.Remove(WidgetToRemove->GetUniqueID());
	}
}

void UUIManager::CloseUniqueUI(TSubclassOf<UCommonActivatableWidget> WidgetClassToRemove, bool& Success)
{
	if (MainUI && UniqueWidgetMap.Find(WidgetClassToRemove) != nullptr)
	{
		Success = true;
		UniqueWidgetMap.Remove(WidgetClassToRemove);
	}

	Success = false;
}
