// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EvergreenTriggerBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorEnter, AActor*, TriggerActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorLeave, AActor*, TriggerActor);

UCLASS()
class EVERGREEN_API AEvergreenTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	AEvergreenTriggerBox();
	
	UPROPERTY(BlueprintAssignable)
	FOnActorEnter OnActorEnter;

	UPROPERTY(BlueprintAssignable)
	FOnActorLeave OnActorLeave;

	UPROPERTY(EditInstanceOnly, Category = "EvergreenTriggerBox")
	TArray<TSubclassOf<AActor>> AllowedActorClasses;

private:
	UFUNCTION()
	void OnActorBeginOverlapFunction(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnActorEndOverlapFunction(AActor* OverlappedActor, AActor* OtherActor);

	bool IsAllowedClass(AActor* OverlappedActor);
};
