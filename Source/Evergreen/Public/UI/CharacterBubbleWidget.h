// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CharacterBubbleWidget.generated.h"

UCLASS(Abstract)
class EVERGREEN_API UCharacterBubbleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;

	UPROPERTY(Transient, meta = (BindWidget))
	UTextBlock* Text;
	
	UFUNCTION(BlueprintCallable, Category = "TypewriterText")
	void SetText(FText InText = FText());

	UFUNCTION(BlueprintCallable, Category = "TypewriterText")
	void Show();

	UFUNCTION(BlueprintCallable, Category = "TypewriterText")
	void Hide();
};
