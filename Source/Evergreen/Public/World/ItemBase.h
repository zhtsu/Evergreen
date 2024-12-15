// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS(Abstract)
class EVERGREEN_API AEvergreenItemBase : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Item", meta = (DisplayPriority="1"))
	FString ItemID;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetItemID(FString InItemID) { ItemID = InItemID; }
};
