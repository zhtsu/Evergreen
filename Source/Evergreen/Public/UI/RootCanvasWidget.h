// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RootCanvasWidget.generated.h"

UCLASS(Abstract)
class EVERGREEN_API URootCanvasWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	class UCommonActivatableWidget* PushWidgetToStack(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);
	void RemoveWidgetFromStack(UCommonActivatableWidget& WidgetToRemove);
	
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UCanvasPanel* RootCanvasPanel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UCommonActivatableWidgetContainerBase* WidgetStack;
};
