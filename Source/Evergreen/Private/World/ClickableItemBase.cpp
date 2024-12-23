// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ClickableItemBase.h"

#include "Common/CommonMacro.h"
#include "Common/AssetPathHub.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "UI/TypewriterTextWidget.h"

AClickableItemBase::AClickableItemBase()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootScene->Mobility = EComponentMobility::Static;
	RootComponent = RootScene;
	
	InteractionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolume"));
	InteractionVolume->Mobility = EComponentMobility::Static;
	InteractionVolume->SetCollisionProfileName("UI");
	InteractionVolume->SetupAttachment(RootScene);
	InteractionVolume->OnClicked.AddUniqueDynamic(this, &AClickableItemBase::OnClickNative);
	InteractionVolume->OnBeginCursorOver.AddUniqueDynamic(this, &AClickableItemBase::OnHoverNative);
	InteractionVolume->OnEndCursorOver.AddUniqueDynamic(this, &AClickableItemBase::OnUnhoverNative);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->Mobility = EComponentMobility::Static;
	StaticMesh->SetGenerateOverlapEvents(false);
	StaticMesh->SetCollisionProfileName("NoCollision");
	StaticMesh->SetupAttachment(RootScene);
	
	DescriptionTextWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DescriptionText"));
	DescriptionTextWidget->SetupAttachment(StaticMesh);
	DescriptionTextWidget->SetWidgetSpace(EWidgetSpace::Screen);
	DescriptionTextWidget->SetDrawAtDesiredSize(true);
	if (UClass* LoadedClass = LoadClass<UTypewriterTextWidget>(nullptr, *UAssetPathHub::WBP_Item_DescriptionText_Path.ToString()))
	{
		DescriptionTextWidget->SetWidgetClass(LoadedClass);
	}
	else
	{
		FAST_WARNING("Fail to load blueprint '%s'", *UAssetPathHub::WBP_Item_DescriptionText_Path.ToString());
	}
	
	HoverOnlyWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ShowOnHovered"));
	HoverOnlyWidget->SetupAttachment(StaticMesh);
	HoverOnlyWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HoverOnlyWidget->SetDrawAtDesiredSize(true);
	if (UClass* LoadedClass = LoadClass<UUserWidget>(nullptr, *UAssetPathHub::WBP_Item_ShowOnHover_Path.ToString()))
	{
		HoverOnlyWidget->SetWidgetClass(LoadedClass);
	}
	else
	{
		FAST_WARNING("Fail to load blueprint '%s'", *UAssetPathHub::WBP_Item_ShowOnHover_Path.ToString());
	}
}

void AClickableItemBase::ShowDescriptionWidget(FText Text, bool bAutoPlay, bool bFadeIn, float Delay, int CharNumPerDelay)
{
	UTypewriterTextWidget* TypewriterTextWidget = Cast<UTypewriterTextWidget>(DescriptionTextWidget->GetWidget());
	if (TypewriterTextWidget)
	{
		TypewriterTextWidget->SetTypewriter(Text, Delay, CharNumPerDelay);
		TypewriterTextWidget->Show(bAutoPlay, bFadeIn);
	}
}

void AClickableItemBase::ShowHoverOnlyWidget()
{
	UUserWidget* UserWidget = HoverOnlyWidget->GetWidget();
	if (UserWidget)
	{
		UserWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void AClickableItemBase::HideDescriptionWidget(bool bAutoHide, bool bFadeOut)
{
	UTypewriterTextWidget* TypewriterTextWidget = Cast<UTypewriterTextWidget>(DescriptionTextWidget->GetWidget());
	if (TypewriterTextWidget)
	{
		TypewriterTextWidget->Hide(bAutoHide, bFadeOut);
	}
}

void AClickableItemBase::HideHoverOnlyWidget()
{
	UUserWidget* UserWidget = HoverOnlyWidget->GetWidget();
	if (UserWidget)
	{
		UserWidget->SetVisibility(ESlateVisibility::Hidden);
	}
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
