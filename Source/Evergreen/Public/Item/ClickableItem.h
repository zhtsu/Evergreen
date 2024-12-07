// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/ClickableItemInterface.h"
#include "ClickableItem.generated.h"

UCLASS()
class EVERGREEN_API AClickableItem : public AActor, public IClickableItemInterface
{
	GENERATED_BODY()

public:
	AClickableItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnClicked_Implementation() override;
	virtual void OnHovered_Implementation() override;
	virtual void OnUnhovered_Implementation() override;
};
