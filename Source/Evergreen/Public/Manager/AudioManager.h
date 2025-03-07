// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AudioManager.generated.h"

UCLASS()
class UAudioManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UAudioManager();

	UFUNCTION(BlueprintCallable)
	void InitGameAudio(class USoundControlBusMix* Mix, USoundBase* DefaultMusic);

	UFUNCTION(BlueprintCallable)
	void ChangeMusic(int32 MusicIndex);

	UFUNCTION(BlueprintCallable)
	void PlayMusic(bool bContinue = false);
	
	UFUNCTION(BlueprintCallable)
	void PauseMusic();
	
private:
	UPROPERTY()
	UAudioComponent* MusicComponent = nullptr;

	bool bIsManualPaused = false;
};
