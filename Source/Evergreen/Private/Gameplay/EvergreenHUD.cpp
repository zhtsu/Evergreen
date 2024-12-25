// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EvergreenHUD.h"

#include "Blueprint/UserWidget.h"
#include "Common/AssetPathHub.h"
#include "Common/CommonMacro.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "Manager/UIManager.h"
#include "UI/MainUIWidget.h"

void AEvergreenHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UClass* LoadedClass = LoadClass<UUserWidget>(nullptr, *UAssetPathHub::WBP_MainUI_Path.ToString()))
	{
		UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
		UMainUIWidget* MainUI = CreateWidget<UMainUIWidget>(EGI, LoadedClass, "MainUI");
		if (MainUI)
		{
			MainUI->AddToViewport();
			
			UUIManager* UIM = EGI->GetSubsystem<UUIManager>();
			UIM->SetMainUI(MainUI);
		}
	}
	else
	{
		FAST_WARNING("Fail to load blueprint '%s'", *UAssetPathHub::WBP_MainUI_Path.ToString());
	}
}
