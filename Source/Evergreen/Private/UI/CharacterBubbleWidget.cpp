// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterBubbleWidget.h"

#include "Animation/UMGSequencePlayer.h"

void UCharacterBubbleWidget::NativeConstruct()
{
	
}

void UCharacterBubbleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	
}

void UCharacterBubbleWidget::SetText(FText InText)
{
	Text->SetText(InText);
}

void UCharacterBubbleWidget::Show()
{
	PlayAnimation(FadeIn);
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCharacterBubbleWidget::Hide()
{
	StopAnimation(FadeIn);
	SetVisibility(ESlateVisibility::Hidden);
}
