// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EvergreenTriggerBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTriggerActorEnter, AActor*, TriggerActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTriggerActorLeave, AActor*, TriggerActor);

UCLASS()
class EVERGREEN_API AEvergreenTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	AEvergreenTriggerBox();
	
	UPROPERTY(BlueprintAssignable)
	FOnTriggerActorEnter OnTriggerActorEnter;

	UPROPERTY(BlueprintAssignable)
	FOnTriggerActorLeave OnTriggerActorLeave;

	UPROPERTY(EditInstanceOnly, Category = "EvergreenTriggerBox")
	TArray<TSubclassOf<AActor>> AllowedTriggerActorClasses;

private:
	UFUNCTION()
	void OnActorBeginOverlapFunction(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnActorEndOverlapFunction(AActor* OverlappedActor, AActor* OtherActor);

	bool IsAllowedClass(AActor* OverlappedActor);
};
