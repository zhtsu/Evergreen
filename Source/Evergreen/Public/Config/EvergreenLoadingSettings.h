// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EvergreenLoadingSettings.generated.h"

UCLASS(Config = "EvergreenLoading", meta = (DisplayName = "Evergreen Loading"), DefaultConfig)
class UEvergreenLoadingSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	virtual FName GetContainerName() const override { return TEXT("Project"); }
	virtual FName GetCategoryName() const override { return TEXT("Project"); }
	virtual FName GetSectionName() const override { return TEXT("EvergreenLoading"); }
	
	static UEvergreenLoadingSettings* Get()
	{
		return GetMutableDefault<UEvergreenLoadingSettings>();
	}

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Loading")
	TSoftObjectPtr<UWorld> TransitMap = nullptr;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Loading")
	TSubclassOf<UUserWidget> LoadingWidgetClass = nullptr;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Loading")
	float DelayTimeOfLoadingWidget = 1.0;
};
