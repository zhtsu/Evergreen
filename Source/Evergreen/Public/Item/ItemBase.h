// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

USTRUCT(BlueprintType)
struct FEvergreenItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText ItemName;

	UPROPERTY(EditAnywhere)
	FText ItemDescription;
};

UCLASS()
class EVERGREEN_API AEvergreenItemBase : public AActor
{
	GENERATED_BODY()
	
public:
	AEvergreenItemBase();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EvergreenItem")
	FText ItemID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "EvergreenItem")
	FEvergreenItemInfo ItemInfo;

protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	void ReadItemNameFromStringTable();
	void ReadItemDescriptionFromStringTable();
};
