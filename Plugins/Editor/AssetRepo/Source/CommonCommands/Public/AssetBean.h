// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetBean.generated.h"

USTRUCT()
struct FAssetBean
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString Uploader;

	UPROPERTY()
	FString Date;

	UPROPERTY()
	UTexture2D* Thumbnail = nullptr;

	UPROPERTY()
	FString Path;
};
