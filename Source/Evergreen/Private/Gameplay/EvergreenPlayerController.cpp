// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EvergreenPlayerController.h"

#include "Gameplay/EvergreenPlayerCameraManager.h"

AEvergreenPlayerController::AEvergreenPlayerController()
{
	PlayerCameraManagerClass = AEvergreenPlayerCameraManager::StaticClass();
}
