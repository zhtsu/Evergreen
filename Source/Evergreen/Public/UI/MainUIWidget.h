// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainUIWidget.generated.h"

UCLASS(Abstract)
class EVERGREEN_API UMainUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(Transient, meta = (BindWidget))
	class UCanvasPanel* RootCanvasPanel;

	UPROPERTY(Transient, meta = (BindWidget))
	class UCharacterBubbleWidget* CharacterBubble;
};
