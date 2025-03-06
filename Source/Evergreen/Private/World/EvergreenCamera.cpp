// Fill out your copyright notice in the Description page of Project Settings.


#include "World/EvergreenCamera.h"

#include "Components/BillboardComponent.h"

AEvergreenCamera::AEvergreenCamera(const FObjectInitializer& ObjectInitializer) : ACineCameraActor(ObjectInitializer)
{
	EvergreenCameras.Add(this);
}

AEvergreenCamera::~AEvergreenCamera()
{
	EvergreenCameras.Remove(this);
}

AEvergreenCamera* AEvergreenCamera::FindFirstFixedCamera(const FString& InCameraID)
{
	for (AEvergreenCamera* Camera : EvergreenCameras)
	{
		if (Camera && Camera->GetCameraID() == InCameraID)
		{
			return Camera;
		}
	}
	return nullptr;
}
