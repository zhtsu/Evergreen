// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/MiniGameInterface.h"
#include "MiniGameBase.generated.h"

UCLASS(Abstract)
class EVERGREEN_API AMiniGameBase : public AActor, public IMiniGameInterface
{
	GENERATED_BODY()

public:
	virtual void OnStartMiniGame_Implementation(UObject* MiniGameData) override;
	virtual void OnEndMiniGame_Implementation() override;
};
