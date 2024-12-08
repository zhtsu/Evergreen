// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/ClickableInterface.h"
#include "ClickableItem.generated.h"

UCLASS()
class EVERGREEN_API AClickableItem : public AActor, public IClickableInterface
{
	GENERATED_BODY()

public:
	AClickableItem();

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	class UBoxComponent* InteractionVolume;

	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	class USceneComponent* RootScene;
	
protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION()
	void OnClickNative(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased);

	UFUNCTION()
	void OnHoverNative(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnUnhoverNative(UPrimitiveComponent* TouchedComponent);
	
	virtual void OnClick_Implementation() override;
	virtual void OnHover_Implementation() override;
	virtual void OnUnhover_Implementation() override;
};
