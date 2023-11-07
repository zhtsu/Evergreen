// Fill out your copyright notice in the Description page of Project Settings.


#include "SCommandButtonWidget.h"
#include "SlateOptMacros.h"
#include "Brushes/SlateColorBrush.h"
#include "Util/ColorConstants.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

const FSlateColorBrush BlueBrush = FSlateColorBrush(FColor(60.0f,53.0f,216.0f,255.0f));


void SCommandButtonWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SBox)
		.MinDesiredHeight(60.0f)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(SButton)
				.OnClicked(InArgs._OnClicked)
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
						SNew(SBorder)
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
				]
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
