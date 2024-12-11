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
	AMiniGameBase();
	
protected:
	virtual void BeginPlay() override;
	
public:
	virtual void OnStartMiniGame_Implementation() override;
	virtual void OnEndMiniGame_Implementation() override;
};
