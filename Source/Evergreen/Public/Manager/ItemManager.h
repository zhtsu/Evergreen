// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ItemManager.generated.h"

USTRUCT(BlueprintType)
struct FEvergreenItemInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(BlueprintReadWrite)
	FText ItemDescription;
};

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

	UFUNCTION(BlueprintPure)
	bool HasItem(FString ItemID);

	UFUNCTION(BlueprintPure)
	static void GetItemInfo(FString ItemID, FEvergreenItemInfo& OutItemInfo);

	UFUNCTION(BlueprintPure)
	FORCEINLINE void GetCollectedItemIdArray(TArray<FString>& OutArray) const { OutArray = CollectedItemIdArray; }
	
private:
	TArray<FString> CollectedItemIdArray;
};
