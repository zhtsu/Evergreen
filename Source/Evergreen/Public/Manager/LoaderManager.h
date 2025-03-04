// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Loader.h"
#include "LoaderManager.generated.h"

UCLASS()
class ULoaderManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AsyncLoadMap(TSoftObjectPtr<UWorld> TargetMap);

	UFUNCTION(BlueprintCallable)
	float GetLoadMapProgress(TSoftObjectPtr<UWorld> LoadingMap) const;
	
private:
	UPROPERTY()
	TMap<TSoftObjectPtr<UWorld>, ULoader*> LoaderDict;

	UFUNCTION()
	void OnLoadMapFinished(TSoftObjectPtr<UWorld> LoadedMap);
};
