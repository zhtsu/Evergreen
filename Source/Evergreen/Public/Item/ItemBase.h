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
	static AEvergreenItemBase* CurrentObservedItem;
	bool bIsBeingObserved = false;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EvergreenItem")
	FString ItemID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "EvergreenItem")
	FText ItemName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "EvergreenItem")
	FText ItemDescription;

	UPROPERTY(EditInstanceOnly, Category = "EvergreenItem")
	ACameraActor* TargetViewCamera;

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsBeingObserved() const { return bIsBeingObserved; }

	UFUNCTION(BlueprintPure)
	static AEvergreenItemBase* GetCurrentObservedItem() { return CurrentObservedItem; }
	
private:
	void ReadItemNameFromStringTable();
	void ReadItemDescriptionFromStringTable();
};

AEvergreenItemBase* AEvergreenItemBase::CurrentObservedItem = nullptr;
