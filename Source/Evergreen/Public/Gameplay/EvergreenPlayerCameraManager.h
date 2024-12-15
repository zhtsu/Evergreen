// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "EvergreenPlayerCameraManager.generated.h"

UCLASS()
class EVERGREEN_API AEvergreenPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	virtual void UpdateCamera(float DeltaTime) override;
};
