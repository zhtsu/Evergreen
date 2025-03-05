// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EvergreenCameraSettings.generated.h"

USTRUCT(BlueprintType)
struct FCameraParams
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	float CameraBoomLength = -1.f;

	UPROPERTY(EditAnywhere)
	float CameraBoomYaw = -1.f;

	UPROPERTY(EditAnywhere)
	float CameraBoomPitch = -1.f;
};

UCLASS(Config = "EvergreenCamera", meta = (DisplayName = "Evergreen Camera"), DefaultConfig)
class UEvergreenCameraSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	virtual FName GetContainerName() const override { return TEXT("Project"); }
	virtual FName GetCategoryName() const override { return TEXT("Project"); }
	virtual FName GetSectionName() const override { return TEXT("EvergreenCamera"); }
	
	static UEvergreenCameraSettings* Get()
	{
		return GetMutableDefault<UEvergreenCameraSettings>();
	}

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Character")
	FCameraParams SuperFarView;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Character")
	FCameraParams FarView;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Character")
	FCameraParams FullView;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Character")
	FCameraParams MidView;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Character")
	FCameraParams CloseView;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Character")
	FCameraParams CloseUpView;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Character")
	FCameraParams SuperCloseUpView;
};
