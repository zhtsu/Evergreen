// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/ClickableInterface.h"
#include "Interface/ObservableInterface.h"
#include "ClickableItemBase.generated.h"

UCLASS(Abstract)
class EVERGREEN_API AClickableItemBase : public AEvergreenItemBase, public IClickableInterface, public IObservableInterface
{
	GENERATED_BODY()

public:
	AClickableItemBase();

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Item")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Item")
	class UBoxComponent* InteractionVolume;

	UPROPERTY(VisibleDefaultsOnly, Category = "Item")
	class USceneComponent* RootScene;

	UPROPERTY(VisibleDefaultsOnly, Category = "Item")
	class UWidgetComponent* DescriptionTextWidget;

	UPROPERTY(VisibleDefaultsOnly, Category = "Item")
	class UWidgetComponent* HoverOnlyWidget;
	
public:
	UFUNCTION(BlueprintCallable)
	void ShowDescriptionWidget(FText Text = FText(), bool bAutoPlay = false, bool bFadeIn = false, float Delay = 0.2, int CharNumPerDelay = 1);

	UFUNCTION(BlueprintCallable)
	void ShowHoverOnlyWidget();

	UFUNCTION(BlueprintCallable)
	void HideDescriptionWidget(bool bAutoHide = false, bool bFadeOut = false);

	UFUNCTION(BlueprintCallable)
	void HideHoverOnlyWidget();
	
	virtual void OnClick_Implementation() override;
	virtual void OnHover_Implementation() override;
	virtual void OnUnhover_Implementation() override;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Item")
	ACameraActor* TargetViewCamera;
	
private:
	UFUNCTION()
	void OnClickNative(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased);

	UFUNCTION()
	void OnHoverNative(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnUnhoverNative(UPrimitiveComponent* TouchedComponent);
};
