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
	
	UFUNCTION(Blueprintable)
	FORCEINLINE class AEvergreenCharacter* GetThirdPersonPlayer() const { return ThirdPersonPlayer; }

	UFUNCTION(Blueprintable)
	FORCEINLINE class AEvergreenPawn* GetInteractionPlayer() const { return InteractionPlayer; }

	static void SetGamePlayers(class AEvergreenCharacter* InThirdPersonPlayer, class AEvergreenPawn* InInteractionPlayer)
	{
		ThirdPersonPlayer = InThirdPersonPlayer;
		InteractionPlayer = InInteractionPlayer;
	}

	void PossessThirdPersonPlayer();
	void PossessInteractionPlayer();
	
private:
	static AEvergreenCharacter* ThirdPersonPlayer;
	static AEvergreenPawn* InteractionPlayer;

	void SwitchToThirdPersonMode();
	void SwitchToInteractionMode();
};

AEvergreenCharacter* AEvergreenPlayerController::ThirdPersonPlayer = nullptr;
AEvergreenPawn* AEvergreenPlayerController::InteractionPlayer = nullptr;
