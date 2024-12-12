// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TypewriterTextWidget.h"

#include "Animation/UMGSequencePlayer.h"
#include "Kismet/KismetSystemLibrary.h"

void UTypewriterTextWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Hide_NoAnim_Event.BindDynamic(this, &UTypewriterTextWidget::Hide_NoAnim);
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

	StopAnimation(FadeOut);
	UnbindFromAnimationFinished(FadeOut, Hide_NoAnim_Event);
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
		CurrentUMGSequencePlayer = PlayAnimationReverse(FadeOut);
	}
}

void UTypewriterTextWidget::Hide(bool bAutoHide, bool bFadeOut)
{
	bAutoHideEnabled = bAutoHide;
	bFadeOutHideEnabled = bFadeOut;
	
	if (bPlaying)
	{
		if (!bAutoHide)
		{
			bPlaying = false;
			
			if (bFadeOut) Hide_FadeOut();
			else Hide_NoAnim();
		}
	}
	else
	{
		if (bFadeOut) Hide_FadeOut();
		else Hide_NoAnim();
	}
}

void UTypewriterTextWidget::WriteText()
{
	float EllapsedTime = (UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld()) - StartTimestamp) / Delay;
	int DisplayCharCount = FMath::Clamp(FMath::Floor(EllapsedTime) * CharNumPerDelay, 0, FullString.Len());

	Text->SetText(FText::FromString(FullString.Mid(0, DisplayCharCount)));

	if (DisplayCharCount == FullString.Len())
	{
		bPlaying = false;

		if (bAutoHideEnabled)
		{
			FTimerHandle AutoHideHandle;
			GetWorld()->GetTimerManager()
				.SetTimer(AutoHideHandle, this, &UTypewriterTextWidget::Hide_Callback, Delay, false);
		}
		
		FTimerHandle UnusedHandle;
		GetWorld()->GetTimerManager()
			.SetTimer(UnusedHandle, this, &UTypewriterTextWidget::BroadcastOnPlayFinished, Delay, false);
	}
}

void UTypewriterTextWidget::Hide_NoAnim()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UTypewriterTextWidget::Hide_FadeOut()
{
	float AnimStartTime = 0.f;
	if (CurrentUMGSequencePlayer)
	{
		AnimStartTime = CurrentUMGSequencePlayer->GetCurrentTime().AsSeconds();
	}
	
	PlayAnimation(FadeOut, AnimStartTime);
	BindToAnimationFinished(FadeOut, Hide_NoAnim_Event);
}

void UTypewriterTextWidget::Hide_Callback()
{
	if (bFadeOutHideEnabled) Hide_FadeOut();
	else Hide_NoAnim();
}

void UTypewriterTextWidget::BroadcastOnPlayFinished()
{
	OnPlayCompleted.Broadcast();
}
