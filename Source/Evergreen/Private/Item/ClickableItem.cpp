// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ClickableItem.h"

#include "Components/BoxComponent.h"
#include "Evergreen/Evergreen.h"

AClickableItem::AClickableItem()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootScene->Mobility = EComponentMobility::Static;
	RootComponent = RootScene;
	
	InteractionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolume"));
	InteractionVolume->Mobility = EComponentMobility::Static;
	InteractionVolume->SetupAttachment(RootScene);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->Mobility = EComponentMobility::Static;
	StaticMesh->SetupAttachment(RootScene);
}

void AClickableItem::BeginPlay()
{
	Super::BeginPlay();

	InteractionVolume->OnClicked.AddUniqueDynamic(this, &AClickableItem::OnClickNative);
	InteractionVolume->OnBeginCursorOver.AddUniqueDynamic(this, &AClickableItem::OnHoverNative);
	InteractionVolume->OnEndCursorOver.AddUniqueDynamic(this, &AClickableItem::OnUnhoverNative);
}

void AClickableItem::OnClickNative(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased)
{
	Execute_OnClick(this);
}

void AClickableItem::OnHoverNative(UPrimitiveComponent* TouchedComponent)
{
	Execute_OnHover(this);
}

void AClickableItem::OnUnhoverNative(UPrimitiveComponent* TouchedComponent)
{
	Execute_OnUnhover(this);
}

void AClickableItem::OnClick_Implementation()
{
	FAST_PRINT("Default OnClick")
}

void AClickableItem::OnHover_Implementation()
{
	FAST_PRINT("Default OnHover")
}

void AClickableItem::OnUnhover_Implementation()
{
	FAST_PRINT("Default OnUnhover")
}
