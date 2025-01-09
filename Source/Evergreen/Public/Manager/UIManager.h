// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UIManager.generated.h"

UCLASS()
class UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UUIManager();
	
	FORCEINLINE void SetMainUI(class UMainUIWidget* InMainUI) { MainUI = InMainUI; }

	static void SetGamePlayers(class AEvergreenCharacter* InThirdPersonPlayer, class AEvergreenPawn* InInteractionPlayer)
	{
		ThirdPersonPlayer = InThirdPersonPlayer;
		InteractionPlayer = InInteractionPlayer;
	}
	
	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* OpenUI(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* OpenUniqueUI(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass, bool& Success);
	
	UFUNCTION(BlueprintCallable)
	void CloseUI(UCommonActivatableWidget* WidgetToRemove);

	UFUNCTION(BlueprintCallable)
	void CloseUniqueUI(TSubclassOf<UCommonActivatableWidget> WidgetClassToRemove, bool& Success);
	
private:
	UPROPERTY()
	UMainUIWidget* MainUI = nullptr;

	TMap<int32, TSharedPtr<UCommonActivatableWidget>> WidgetMap;
	TMap<TSubclassOf<UCommonActivatableWidget>, TSharedPtr<UCommonActivatableWidget>> UniqueWidgetMap;
	
	static AEvergreenCharacter* ThirdPersonPlayer;
	static AEvergreenPawn* InteractionPlayer;
};

AEvergreenCharacter* UUIManager::ThirdPersonPlayer = nullptr;
AEvergreenPawn* UUIManager::InteractionPlayer = nullptr;
