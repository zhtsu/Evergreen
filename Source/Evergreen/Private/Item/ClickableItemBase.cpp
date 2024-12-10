// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ClickableItemBase.h"

#include "Components/BoxComponent.h"
#include "Evergreen/Evergreen.h"
#include "Game/EvergreenGameInstance.h"

AClickableItemBase::AClickableItemBase()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootScene->Mobility = EComponentMobility::Static;
	RootComponent = RootScene;
	
	InteractionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolume"));
	InteractionVolume->Mobility = EComponentMobility::Static;
	InteractionVolume->SetCollisionProfileName("UI");
	InteractionVolume->SetupAttachment(RootScene);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->Mobility = EComponentMobility::Static;
	StaticMesh->SetGenerateOverlapEvents(false);
	StaticMesh->SetCollisionProfileName("NoCollision");
	StaticMesh->SetupAttachment(RootScene);
}

void AClickableItemBase::BeginPlay()
{
	Super::BeginPlay();

	InteractionVolume->OnClicked.AddUniqueDynamic(this, &AClickableItemBase::OnClickNative);
	InteractionVolume->OnBeginCursorOver.AddUniqueDynamic(this, &AClickableItemBase::OnHoverNative);
	InteractionVolume->OnEndCursorOver.AddUniqueDynamic(this, &AClickableItemBase::OnUnhoverNative);
}

void AClickableItemBase::OnClickNative(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (!EGI->IsAllowInput()) return;
	
	Execute_OnClick(this);
}

void AClickableItemBase::OnHoverNative(UPrimitiveComponent* TouchedComponent)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (!EGI->IsAllowInput()) return;
	
	Execute_OnHover(this);
}

void AClickableItemBase::OnUnhoverNative(UPrimitiveComponent* TouchedComponent)
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (!EGI->IsAllowInput()) return;
	
	Execute_OnUnhover(this);
}

void AClickableItemBase::OnClick_Implementation()
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (!EGI->IsTestModeEnabled()) return;
	
	FAST_PRINT("Default OnClick")
}

void AClickableItemBase::OnHover_Implementation()
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (!EGI->IsTestModeEnabled()) return;
	
	FAST_PRINT("Default OnHover")
}

void AClickableItemBase::OnUnhover_Implementation()
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (!EGI->IsTestModeEnabled()) return;

	FAST_PRINT("Default OnUnhover")
}
