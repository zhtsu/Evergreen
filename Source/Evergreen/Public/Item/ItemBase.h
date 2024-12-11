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
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EvergreenItem")
	FText ItemID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "EvergreenItem")
	FText ItemName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "EvergreenItem")
	FText ItemDescription;

private:
	void ReadItemNameFromStringTable();
	void ReadItemDescriptionFromStringTable();
};
