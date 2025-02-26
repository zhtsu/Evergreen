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
	
private:
	UPROPERTY()
	UAudioComponent* MusicComponent = nullptr;
};
