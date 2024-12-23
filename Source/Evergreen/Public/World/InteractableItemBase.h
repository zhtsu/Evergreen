// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractableInterface.h"
#include "InteractableItemBase.generated.h"

UCLASS(Abstract)
class EVERGREEN_API AInteractableItemBase : public AEvergreenItemBase, public IInteractableInterface
{
	GENERATED_BODY()
	
public:
	AInteractableItemBase();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void EndInteraction() { bInteracting = false; }

private:
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "InteractableItem", meta = (AllowPrivateAccess))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "InteractableItem")
	class UBoxComponent* CollisionVolume;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "InteractableItem")
	UBoxComponent* InteractionVolume;

	UPROPERTY(VisibleDefaultsOnly, Category = "InteractableItem")
	USceneComponent* RootScene;

	UPROPERTY(VisibleDefaultsOnly, Category = "InteractableItem")
	UWidgetComponent* ActorEnterOnlyWidget;
	
public:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "ClickableItem")
	ACameraActor* TargetViewCamera;
	
	UFUNCTION(BlueprintCallable)
	void ShowActorEnterOnlyWidget();
	
	UFUNCTION(BlueprintCallable)
	void HideActorEnterOnlyWidget();
	
private:
	bool bInteracting = false;

	UFUNCTION()
	void OnActorEnterNative(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnActorLeaveNative(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
