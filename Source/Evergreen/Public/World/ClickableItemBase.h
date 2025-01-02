// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/ClickableInterface.h"
#include "ClickableItemBase.generated.h"

UCLASS(Abstract)
class EVERGREEN_API AClickableItemBase : public AEvergreenItemBase, public IClickableInterface
{
	GENERATED_BODY()

public:
	AClickableItemBase();

protected:
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "ClickableItem", meta = (AllowPrivateAccess))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	class UBoxComponent* InteractionVolume;

	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	USceneComponent* RootScene;

	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	UWidgetComponent* DescriptionTextWidget;

	UPROPERTY(VisibleDefaultsOnly, Category = "ClickableItem")
	UWidgetComponent* HoverOnlyWidget;
	
public:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "ClickableItem")
	class AEvergreenCamera* TargetViewCamera;
	
	UFUNCTION(BlueprintCallable)
	void ShowDescriptionWidget(FText Text = FText(), bool bAutoPlay = false, bool bFadeIn = false, float Delay = 0.2, int CharNumPerDelay = 1);

	UFUNCTION(BlueprintCallable)
	void ShowHoverOnlyWidget();

	UFUNCTION(BlueprintCallable)
	void HideDescriptionWidget(bool bAutoHide = false, bool bFadeOut = false);

	UFUNCTION(BlueprintCallable)
	void HideHoverOnlyWidget();
	
private:
	UFUNCTION()
	void OnClickNative(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased);

	UFUNCTION()
	void OnReleaseNative(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased);

	UFUNCTION()
	void OnHoverNative(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnUnhoverNative(UPrimitiveComponent* TouchedComponent);
};
