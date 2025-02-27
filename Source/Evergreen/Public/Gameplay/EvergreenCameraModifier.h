// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "EvergreenCameraModifier.generated.h"

/**
 * 
 */
UCLASS()
class EVERGREEN_API UEvergreenCameraModifier : public UCameraModifier
{
	GENERATED_BODY()

	void ModifyCamera(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV, FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV) override;
};
