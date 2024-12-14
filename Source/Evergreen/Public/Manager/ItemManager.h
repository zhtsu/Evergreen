// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ItemManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemCollected, FString, CollectedItemID);

UCLASS()
class UItemManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnItemCollected OnItemCollected;
	
	UItemManager();

	UFUNCTION(BlueprintCallable)
	void CollectItem(class AEvergreenItemBase* Item);

	UFUNCTION(BlueprintCallable)
	bool HasItem(FString ItemID);

	UFUNCTION(BlueprintPure)
	FORCEINLINE void GetCollectedItemIdArray(TArray<FString>& OutArray) const { OutArray = CollectedItemIdArray; }
	
private:
	TArray<FString> CollectedItemIdArray;
};
