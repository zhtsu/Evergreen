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

	void BeginPlay() override;
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE class AEvergreenCharacter* GetThirdPersonPlayer() const { return ThirdPersonPlayer; }

	UFUNCTION(Blueprintable)
	void SetMousePosition(const FVector2D& Position);

	void SetThirdPersonPlayer(AEvergreenCharacter* InThirdPersonPlayer)
	{
		ThirdPersonPlayer = InThirdPersonPlayer;
	}

	void SetPlayerHiddenInGame(bool bHide);
	
private:
	UPROPERTY()
	AEvergreenCharacter* ThirdPersonPlayer;
};
