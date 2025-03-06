// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "LoadMapHelper.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMapLoadFinished, TSoftObjectPtr<UWorld>, LoadedMap);

UCLASS()
class ULoadMapHelper : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void AsyncLoadMap(TSoftObjectPtr<UWorld> TargetMap, bool bShowLoadingWidget = true);

	UFUNCTION(BlueprintCallable)
	static void StartAsyncLoadMap_CallInTransitMap(const FOnMapLoadFinished& OnFinished);

	UFUNCTION(BlueprintCallable)
	void ShowLoadingWidget();

	UFUNCTION(BlueprintCallable)
	void HideLoadingWidget();
	
	// UFUNCTION(BlueprintPure)
	// static float GetLoadMapProgress();
	
private:
	UPROPERTY()
	UUserWidget* LoadingWidget;
	
	UFUNCTION()
	void OnFinishedCallback();

	FOnMapLoadFinished OnLoadMapFinished;
	TSoftObjectPtr<UWorld> LoadedMap;
	TSharedPtr<FStreamableHandle> LoadHandle;
};
