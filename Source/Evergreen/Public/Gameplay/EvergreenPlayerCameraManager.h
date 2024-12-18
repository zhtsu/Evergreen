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
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	bool bCameraOffsetFollowCursorEnabled = false;

	UPROPERTY(EditDefaultsOnly)
	float OffsetScale = 0.1f;

	UPROPERTY(EditDefaultsOnly)
	float InterpSpeed = 2.f;
	
	UFUNCTION(BlueprintCallable)
	bool CameraOffsetFollowCursor(AActor* CameraTarget, FVector& NewCameraLocation, FRotator& NewCameraRotation, float& NewCameraFOV);

	FVector Location;
	FRotator Rotation;

	FORCEINLINE void SetCamera(const FVector& InLocation, const FRotator& InRotation)
	{
		Location = InLocation;
		Rotation = InRotation;
	}
	
private:
	FVector2D CurrentOffset = FVector2D();
};
