// Fill out your copyright notice in the Description page of Project Settings.


#include "World/InteractableItemBase.h"

#include "Common/AssetPathHub.h"
#include "Common/CommonMacro.h"
#include "Components/BoxComponent.h"
#include "Gameplay/EvergreenCharacter.h"

AInteractableItemBase::AInteractableItemBase()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootScene->Mobility = EComponentMobility::Static;
	RootComponent = RootScene;
	
	CollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionVolume"));
	CollisionVolume->Mobility = EComponentMobility::Static;
	CollisionVolume->SetCollisionProfileName("Pawn");
	CollisionVolume->SetupAttachment(RootScene);
	
	InteractionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolume"));
	InteractionVolume->Mobility = EComponentMobility::Static;
	InteractionVolume->SetCollisionProfileName("OverlapOnlyPawn");
	InteractionVolume->SetupAttachment(RootScene);
	InteractionVolume->OnComponentBeginOverlap.AddUniqueDynamic(this, &AInteractableItemBase::OnActorEnterNative);
	InteractionVolume->OnComponentEndOverlap.AddUniqueDynamic(this, &AInteractableItemBase::OnActorLeaveNative);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->Mobility = EComponentMobility::Static;
	StaticMesh->SetGenerateOverlapEvents(false);
	StaticMesh->SetCollisionProfileName("NoCollision");
	StaticMesh->SetupAttachment(RootScene);

	ActorEnterOnlyWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActorEnterOnlyWidget"));
	ActorEnterOnlyWidget->SetupAttachment(StaticMesh);
	ActorEnterOnlyWidget->SetWidgetSpace(EWidgetSpace::Screen);
	ActorEnterOnlyWidget->SetDrawAtDesiredSize(true);
	if (UClass* LoadedClass = LoadClass<UUserWidget>(nullptr, *UAssetPathHub::WBP_Item_ShowOnActorEnter_Path.ToString()))
	{
		ActorEnterOnlyWidget->SetWidgetClass(LoadedClass);
	}
	else
	{
		FAST_WARNING("Fail to load blueprint '%s'", *UAssetPathHub::WBP_Item_ShowOnActorEnter_Path.ToString());
	}
}

void AInteractableItemBase::ShowActorEnterOnlyWidget()
{
	UUserWidget* UserWidget = ActorEnterOnlyWidget->GetWidget();
	if (UserWidget)
	{
		UserWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void AInteractableItemBase::HideActorEnterOnlyWidget()
{
	UUserWidget* UserWidget = ActorEnterOnlyWidget->GetWidget();
	if (UserWidget)
	{
		UserWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AInteractableItemBase::OnActorEnterNative(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEvergreenCharacter* ThirdPersonPlayer = Cast<AEvergreenCharacter>(OtherActor))
	{
		ThirdPersonPlayer->ActiveInteractableItem = this;
		Execute_OnActorEnter(this);
	}
}

void AInteractableItemBase::OnActorLeaveNative(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEvergreenCharacter* ThirdPersonPlayer = Cast<AEvergreenCharacter>(OtherActor))
	{
		ThirdPersonPlayer->ActiveInteractableItem = nullptr;
		Execute_OnActorLeave(this);
	}
}
