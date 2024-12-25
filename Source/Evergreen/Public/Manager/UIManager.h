// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UIManager.generated.h"

UCLASS()
class UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UUIManager();
	
	FORCEINLINE void SetMainUI(class UMainUIWidget* InMainUI) { MainUI = InMainUI; }

	static void SetGamePlayers(class AEvergreenCharacter* InThirdPersonPlayer, class AEvergreenPawn* InInteractionPlayer)
	{
		ThirdPersonPlayer = InThirdPersonPlayer;
		InteractionPlayer = InInteractionPlayer;
	}
	
private:
	UPROPERTY()
	UMainUIWidget* MainUI;

	static AEvergreenCharacter* ThirdPersonPlayer;
	static AEvergreenPawn* InteractionPlayer;
};

AEvergreenCharacter* UUIManager::ThirdPersonPlayer = nullptr;
AEvergreenPawn* UUIManager::InteractionPlayer = nullptr;
