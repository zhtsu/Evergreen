// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AssetInstanceData.h"
#include "Framework/SlateDelegates.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SScrollBox.h"
#include "WIdgets/Views/STileView.h"

/**
 * 
 */
class ASSETREPO_API SAssetRepoTileView : public SCompoundWidget
{
public:
	
	SLATE_BEGIN_ARGS(SAssetRepoTileView)
	{}

	SLATE_ATTRIBUTE(FString, AssetRepoRootPath)
	
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArg);
	
private:
	FReply OpenAssetPath();
	FReply FlushAssetTileView();
	
	TSharedPtr<STileView<TSharedPtr<FAssetInstanceData>>> TileViewPtr;
	TArray<TSharedPtr<FAssetInstanceData>> AssetList;

	TSharedRef<ITableRow> MakeTileViewWidget(TSharedPtr<FAssetInstanceData> ClientItem, const TSharedRef<STableViewBase>& OwnerTable);
	void InitializeAssetList(FString InAssetRepoRootPath);
	void OnListMouseButtonLeftClick(TSharedPtr<FAssetInstanceData> Item);
	void OnAssetRepoRootPathChanged(const FText& Text);
	
	TSharedPtr<STextBlock> SelectedAssetNameText;
	TSharedPtr<STextBlock> SelectedAssetUploaderText;
	TSharedPtr<STextBlock> SelectedAssetDateText;
	TSharedPtr<STextBlock> SelectedAssetPathText;
	TSharedPtr<SScrollBox> TileViewBox;

	FString AssetRepoRootPath;
};
