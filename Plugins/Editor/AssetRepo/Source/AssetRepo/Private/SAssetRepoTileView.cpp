// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\SAssetRepoTileView.h"
#include "SlateOptMacros.h"
#include "Brushes/SlateColorBrush.h"
#include "Brushes/SlateImageBrush.h"

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

FReply SAssetRepoTileView::ExecCommand()
{
	
	
	return FReply::Handled();
}

void SAssetRepoTileView::Initialize(FString InAssetRepoRootPath)
{
	TSharedPtr<UAssetInstanceData> A = MakeShareable(NewObject<UAssetInstanceData>());
	TSharedPtr<UAssetInstanceData> B = MakeShareable(NewObject<UAssetInstanceData>());
	
	AssetList.Add(A);
	AssetList.Add(B);
}

void SAssetRepoTileView::Construct(const FArguments& InArgs)
{
	Initialize(InArgs._AssetRepoRootPath.Get());
	
	SAssignNew(TileViewPtr, STileView<TSharedPtr<UAssetInstanceData>>)
	.ListItemsSource(&AssetList)
	.OnGenerateTile(this, &SAssetRepoTileView::MakeTileViewWidget);

	ChildSlot
	[
		TileViewPtr.ToSharedRef()
	];
}

TSharedRef<ITableRow> SAssetRepoTileView::MakeTileViewWidget(TSharedPtr<UAssetInstanceData> ClientItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	check(ClientItem.IsValid());
	return SNew(STableRow<TSharedPtr<UAssetInstanceData>>, OwnerTable)
		[
			SNew(SBox)
			.MinDesiredHeight(160.0f)
			.MinDesiredWidth(160.0f)
			.Padding(4.0f)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SButton)
					.OnClicked(this, &SAssetRepoTileView::ExecCommand)
				]
				+ SOverlay::Slot()
				.Padding(4.0f)
				.HAlign(EHorizontalAlignment::HAlign_Fill)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SBox)
						[
							SNew(SImage)
						]
					]
				]
			]
		];
}

// Bak
//
// + SHorizontalBox::Slot()
// 		.HAlign(EHorizontalAlignment::HAlign_Center)
// 		.VAlign(EVerticalAlignment::VAlign_Center)
// 		[
// 			SNew(STextBlock)
// 			.Visibility(EVisibility::HitTestInvisible)
// #if ENGINE_MAJOR_VERSION == 4
// 			.ColorAndOpacity(FLinearColor::Black)
// #endif
// 		]


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
