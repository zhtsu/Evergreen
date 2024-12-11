// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityActor.h"
#include "EvergreenEditorUtilityActor.generated.h"

UCLASS()
class EVERGREEN_API AEvergreenEditorUtilityActor : public AEditorUtilityActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "EvergreenEditorUtility")
	TArray<FText> StringTableLoaderArray;
	
	UFUNCTION(BlueprintCallable, Category = "EvergreenEditorUtility")
	void ImportStringTableFromCSV();
};
