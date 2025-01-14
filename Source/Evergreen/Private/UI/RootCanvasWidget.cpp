// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RootCanvasWidget.h"

#include "CommonActivatableWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UCommonActivatableWidget* URootCanvasWidget::PushWidgetToStack(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	return WidgetStack->AddWidget(ActivatableWidgetClass);
}

void URootCanvasWidget::RemoveWidgetFromStack(UCommonActivatableWidget& WidgetToRemove)
{
	WidgetStack->RemoveWidget(WidgetToRemove);
}
