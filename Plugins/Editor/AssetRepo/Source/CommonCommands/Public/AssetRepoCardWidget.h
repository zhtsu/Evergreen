// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AssetBean.h"
#include "Framework/SlateDelegates.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class ASSETREPO_API AssetRepoCardWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(AssetRepoCardWidget)
	{}

	SLATE_ARGUMENT(FAssetBean, Asset)
	
	SLATE_END_ARGS()

	FReply ExecCommand();
	
	void Construct(const FArguments& InArgs);
	
private:
	bool Enable = false;
	TSharedPtr<SImage> ThumbnailImage;
};
