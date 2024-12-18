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
	UPROPERTY(EditDefaultsOnly)
	bool bCameraOffsetFollowCursorEnabled = false;

	UPROPERTY(EditDefaultsOnly)
	float OffsetScale = 0.1f;

	UPROPERTY(EditDefaultsOnly)
	float InterpSpeed = 2.f;
	
	UFUNCTION(BlueprintCallable)
	bool CameraOffsetFollowCursor(AActor* CameraTarget, FVector& NewCameraLocation, FRotator& NewCameraRotation, float& NewCameraFOV);

private:
	FVector2D CurrentOffset = FVector2D();
};
