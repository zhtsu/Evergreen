// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Brushes/SlateImageBrush.h"

class FAssetInstanceData
{
public:
	static TSharedPtr<FAssetInstanceData> New()
	{
		return MakeShareable(new FAssetInstanceData());
	}

	~FAssetInstanceData()
	{
		if (ThumbnailBrush)
		{
			delete ThumbnailBrush;
		}
	}
	
	FString Name;
	FString Uploader;
	FString Date;
	FSlateBrush* ThumbnailBrush = nullptr;
	FString Path;

private:
	FAssetInstanceData() {}
};
