// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TypewriterTextWidget.h"

#include "Kismet/KismetSystemLibrary.h"

void UTypewriterTextWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
}

void UTypewriterTextWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bPlaying)
	{
		WriteText();
	}
}

void UTypewriterTextWidget::SetTypewriter(FText InText, float InDelay, int InCharNumPerDalay)
{
	FullString = InText.ToString();
	Delay = InDelay;
	CharNumPerDelay = InCharNumPerDalay;
}

void UTypewriterTextWidget::Show(bool bAutoPlay, bool bFadeIn)
{
	if (bPlaying) return;
	
	SetVisibility(ESlateVisibility::HitTestInvisible);
	
	if (bAutoPlay)
	{
		StartTimestamp = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
		Text->SetText(FText());
		bPlaying = true;
	}
	else
	{
		Text->SetText(FText::FromString(FullString));
	}

	if (bFadeIn)
	{
		PlayAnimation(FadeIn);
	}
}

void UTypewriterTextWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UTypewriterTextWidget::WriteText()
{
	float EllapsedTime = (UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld()) - StartTimestamp) / Delay;
	int DisplayCharCount = FMath::Clamp(FMath::Floor(EllapsedTime) * CharNumPerDelay, 0, FullString.Len());

	Text->SetText(FText::FromString(FullString.Mid(0, DisplayCharCount)));

	if (DisplayCharCount == FullString.Len())
	{
		bPlaying = false;
		FTimerHandle UnusedHandle;
		GetWorld()->GetTimerManager()
			.SetTimer(UnusedHandle, this, &UTypewriterTextWidget::BroadcastOnPlayFinished, Delay, false);
	}
}

void UTypewriterTextWidget::BroadcastOnPlayFinished()
{
	OnPlayCompleted.Broadcast();
}
