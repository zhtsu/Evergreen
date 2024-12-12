// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "GameFramework/Actor.h"
#include "Interface/ClickableInterface.h"
#include "ClickableItemBase.generated.h"

UCLASS(Abstract)
class EVERGREEN_API AClickableItemBase : public AEvergreenItemBase, public IClickableInterface
{
	GENERATED_BODY()

public:
	AClickableItemBase();

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	class UBoxComponent* InteractionVolume;

	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	class USceneComponent* RootScene;

	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	class UWidgetComponent* DescriptionTextWidget;

	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	class UWidgetComponent* HoverOnlyWidget;
	
protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void ShowDescriptionWidget(bool bAutoPlay = false, bool bFadeIn = false, float Delay = 0.2, int CharNumPerDelay = 1);

	UFUNCTION(BlueprintCallable)
	void ShowHoverOnlyWidget();

	UFUNCTION(BlueprintCallable)
	void HideDescriptionWidget(bool bAutoHide = false, bool bFadeOut = false);

	UFUNCTION(BlueprintCallable)
	void HideHoverOnlyWidget();
	
	virtual void OnClick_Implementation() override;
	virtual void OnHover_Implementation() override;
	virtual void OnUnhover_Implementation() override;

private:
	UFUNCTION()
	void OnClickNative(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased);

	UFUNCTION()
	void OnHoverNative(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnUnhoverNative(UPrimitiveComponent* TouchedComponent);
};
