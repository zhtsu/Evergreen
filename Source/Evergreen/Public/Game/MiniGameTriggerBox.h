// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MiniGameTriggerBox.generated.h"

UENUM()
enum class EMiniGameTriggerBoxType : uint8
{
	StartMiniGame,
	EndMiniGame
};

UCLASS()
class EVERGREEN_API AMiniGameTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	AMiniGameTriggerBox();
	
	UPROPERTY(EditInstanceOnly, Category = "MiniGameTriggerBox")
	EMiniGameTriggerBoxType TriggerBoxType = EMiniGameTriggerBoxType::StartMiniGame;
	
	UPROPERTY(EditInstanceOnly, Category = "MiniGameTriggerBox")
	TSubclassOf<class AMiniGameBase> MiniGameClass;

	UPROPERTY(EditInstanceOnly, Category = "MiniGameTriggerBox")
	TSubclassOf<class UMiniGameData> MiniGameDataClass;
	
protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
