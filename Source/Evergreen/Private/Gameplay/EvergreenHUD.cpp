// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EvergreenHUD.h"

#include "Blueprint/UserWidget.h"
#include "Common/AssetPathHub.h"
#include "Common/CommonMacro.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "Manager/UIManager.h"
#include "UI/RootCanvasWidget.h"

void AEvergreenHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UClass* LoadedClass = LoadClass<UUserWidget>(nullptr, *UAssetPathHub::WBP_RootCanvas_Path.ToString()))
	{
		UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
		URootCanvasWidget* RootCanvas = CreateWidget<URootCanvasWidget>(EGI, LoadedClass, "RootCanvas");
		if (RootCanvas)
		{
			RootCanvas->AddToViewport();
			
			UUIManager* UIM = EGI->GetSubsystem<UUIManager>();
			UIM->SetRootCanvas(RootCanvas);
		}
	}
	else
	{
		FAST_WARNING("Fail to load blueprint '%s'", *UAssetPathHub::WBP_RootCanvas_Path.ToString());
	}
}
