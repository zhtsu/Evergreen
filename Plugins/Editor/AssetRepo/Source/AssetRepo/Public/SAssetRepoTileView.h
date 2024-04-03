// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AssetInstanceData.h"
#include "Framework/SlateDelegates.h"
#include "Widgets/SCompoundWidget.h"
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

	FReply ExecCommand();

	void Initialize(FString InAssetRepoRootPath);
	
	void Construct(const FArguments& InArg);

	TSharedRef<ITableRow> MakeTileViewWidget(TSharedPtr<UAssetInstanceData> ClientItem, const TSharedRef<STableViewBase>& OwnerTable);
	
private:
	TSharedPtr<STileView<TSharedPtr<UAssetInstanceData>>> TileViewPtr;
	TArray<TSharedPtr<UAssetInstanceData>> AssetList;
};
