// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CineCameraActor.h"
#include "EvergreenCamera.generated.h"

UCLASS()
class EVERGREEN_API AEvergreenCamera : public ACineCameraActor
{
	GENERATED_BODY()

public:
	AEvergreenCamera(const FObjectInitializer& ObjectInitializer);
	~AEvergreenCamera();
	
	static AEvergreenCamera* FindFirstFixedCamera(const FString& InCameraID);
	
	FORCEINLINE FString GetCameraID() const { return CameraID; }
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "EvergreenCamera", meta = (AllowPrivateAccess))
	UBillboardComponent* Logo;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess))
	FString CameraID;

	inline static TArray<AEvergreenCamera*> EvergreenCameras = {};
};
