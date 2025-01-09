// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUIWidget.h"

#include "CommonActivatableWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UCommonActivatableWidget* UMainUIWidget::PushWidgetToStack(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	return WidgetStack->AddWidget(ActivatableWidgetClass);
}

void UMainUIWidget::RemoveWidgetFromStack(UCommonActivatableWidget& WidgetToRemove)
{
	WidgetStack->RemoveWidget(WidgetToRemove);
}
