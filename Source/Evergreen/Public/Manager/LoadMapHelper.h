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
	void ShowLoadingWidget();

	UFUNCTION(BlueprintCallable)
	void HideLoadingWidget();

	UFUNCTION(BlueprintPure)
	static bool IsMapEqual(TSoftObjectPtr<UWorld> A, TSoftObjectPtr<UWorld> B);
	
private:
	UPROPERTY()
	UUserWidget* LoadingWidget;
};
