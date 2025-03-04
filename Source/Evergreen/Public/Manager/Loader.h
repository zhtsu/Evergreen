// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "Loader.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMapLoadFinished, TSoftObjectPtr<UWorld>, LoadedMap);

UCLASS(Blueprintable)
class ULoader : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AsyncLoadMap(TSoftObjectPtr<UWorld> TargetMap, const FOnMapLoadFinished& OnFinished);

	UFUNCTION(BlueprintCallable)
	float GetLoadProgress() const;

	UFUNCTION(BlueprintCallable)
	TSoftObjectPtr<UWorld> GetLoadedMapSoftObjectPtr() const;
	
private:
	FOnMapLoadFinished OnMapLoadFinished;
	
	TSharedPtr<FStreamableHandle> Handle;
	TSoftObjectPtr<UWorld> LoadedMap;
	
	void ExecuteOnFinished();
};
