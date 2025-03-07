// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/AudioManager.h"

#include "AudioModulationStatics.h"
#include "Common/EvergreenBPFL.h"
#include "Components/AudioComponent.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "Gameplay/EvergreenPlayerController.h"

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
	
	MusicComponent = UEvergreenBPFL::SpawnSoundAttached_NoPlay(DefaultMusic, EPC->GetRootComponent());
}

void UAudioManager::ChangeMusic(int32 MusicIndex)
{
	if (!MusicComponent) return;

	MusicComponent->SetIntParameter(FName("MusicIndex"), MusicIndex);
	MusicComponent->SetTriggerParameter("Play");
}

void UAudioManager::PlayMusic(bool bContinue)
{
	if (MusicComponent)
	{
		MusicComponent->SetPaused(false);

		if (bContinue)
		{
			if (!bIsManualPaused)
			{
				bIsManualPaused = false;
				MusicComponent->Play();
			}
		}
		else
		{
			MusicComponent->Play();
		}
	}
}

void UAudioManager::PauseMusic()
{
	bIsManualPaused = true;
	MusicComponent->SetPaused(true);
}
