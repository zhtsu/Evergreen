// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\CommandButtonWidget.h"
#include "SlateOptMacros.h"
#include "Brushes/SlateColorBrush.h"
#include "Engine/GameEngine.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

const FSlateColorBrush BlueBrush = FSlateColorBrush(FColor(
	0.023529 * 255.0f,
	0.207843 * 255.0f,
	0.847059 * 255.0f,
	255.0f));

const FSlateColorBrush GreenBrush = FSlateColorBrush(FColor(
	0.135633 * 255.0f,
	0.396755 * 255.0f,
	0.0f,
	255.0f));


FReply SCommandButtonWidget::ExecCommand()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		GEngine->Exec(World, *Command);
		Enable = !Enable;
		if (Enable)
		{
			ColorStrip->SetBorderImage(&GreenBrush);
		}
		else
		{
			ColorStrip->SetBorderImage(&BlueBrush);
		}
	}
	else
	{
		GLog->Log("LogCommonCommands: Failed to access World point!");
	}
	
	return FReply::Handled();
}

void SCommandButtonWidget::Construct(const FArguments& InArgs)
{
	Command = InArgs._CommandText.Get().ToString();
	
	ChildSlot
	[
		SNew(SBox)
		.MinDesiredHeight(60.0f)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(SButton)
				.OnClicked(this, &SCommandButtonWidget::ExecCommand)
			]
			+ SOverlay::Slot()
			.Padding(4.0f)
			.HAlign(EHorizontalAlignment::HAlign_Fill)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SBox)
					[
						SAssignNew(ColorStrip, SBorder)
						.BorderImage(&BlueBrush)
					]
				]
				+ SHorizontalBox::Slot()
				.HAlign(EHorizontalAlignment::HAlign_Center)
				.VAlign(EVerticalAlignment::VAlign_Center)
				[
					SNew(STextBlock)
					.Text(InArgs._CommandText)
					.Visibility(EVisibility::HitTestInvisible)
#if ENGINE_MAJOR_VERSION == 4
					.ColorAndOpacity(FLinearColor::Black)
#endif
				]
			]
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
