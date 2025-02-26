// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/AudioManager.h"

#include "AudioModulationStatics.h"
#include "Components/AudioComponent.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "Gameplay/EvergreenPlayerController.h"
#include "Kismet/GameplayStatics.h"

UAudioManager::UAudioManager()
{
}

void UAudioManager::InitGameAudio(USoundControlBusMix* Mix, USoundBase* DefaultMusic)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (!EGI) return;
	
	AEvergreenPlayerController* EPC = EGI->GetEvergreenPlayerController();
	if (!EPC) return;

	UAudioModulationStatics::ActivateBusMix(EGI->GetWorld(), Mix);
	MusicComponent = UGameplayStatics::SpawnSoundAttached(DefaultMusic, EPC->GetRootComponent());
}

void UAudioManager::ChangeMusic(int32 MusicIndex)
{
	if (!MusicComponent) return;

	MusicComponent->SetIntParameter(FName("MusicIndex"), MusicIndex);
	MusicComponent->SetTriggerParameter("Play");
}
