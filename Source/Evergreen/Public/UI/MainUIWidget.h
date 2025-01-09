// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUIWidget.generated.h"

UCLASS(Abstract)
class EVERGREEN_API UMainUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	class UCommonActivatableWidget* PushWidgetToStack(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);
	void RemoveWidgetFromStack(UCommonActivatableWidget& WidgetToRemove);
	
private:
	UPROPERTY(Transient, meta = (BindWidget))
	class UCanvasPanel* RootCanvasPanel;

	UPROPERTY(Transient, meta = (BindWidget))
	class UCommonActivatableWidgetContainerBase* WidgetStack;
};
