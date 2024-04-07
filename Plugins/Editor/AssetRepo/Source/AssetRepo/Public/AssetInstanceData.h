// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetInstanceData.generated.h"

UCLASS()
class UAssetInstanceData : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString Uploader;

	UPROPERTY()
	FString Date;

	UPROPERTY()
	FSlateBrush ThumbnailBrush;

	UPROPERTY()
	FString Path;
};
