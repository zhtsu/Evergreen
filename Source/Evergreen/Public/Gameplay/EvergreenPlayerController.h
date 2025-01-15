// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EvergreenPlayerController.generated.h"

UCLASS()
class EVERGREEN_API AEvergreenPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AEvergreenPlayerController();
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE class AEvergreenCharacter* GetThirdPersonPlayer() const { return ThirdPersonPlayer; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE class AEvergreenPawn* GetInteractionPlayer() const { return InteractionPlayer; }

	void SetThirdPersonPlayer(AEvergreenCharacter* InThirdPersonPlayer)
	{
		ThirdPersonPlayer = InThirdPersonPlayer;
	}

	void SetInteractionPlayer(AEvergreenPawn* InInteractionPlayer)
	{
		InteractionPlayer = InInteractionPlayer;
	}

	void PossessThirdPersonPlayer();
	void PossessInteractionPlayer();
	
private:
	UPROPERTY()
	AEvergreenCharacter* ThirdPersonPlayer;

	UPROPERTY()
	AEvergreenPawn* InteractionPlayer;

	void SwitchToThirdPersonMode();
	void SwitchToInteractionMode();
};
