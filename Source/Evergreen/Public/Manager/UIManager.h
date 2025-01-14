// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/EvergreenWidgetBase.h"
#include "UIManager.generated.h"

UCLASS()
class UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UUIManager();
	
	FORCEINLINE void SetRootCanvas(class URootCanvasWidget* InRootCanvas) { RootCanvas = InRootCanvas; }

	static void SetGamePlayers(class AEvergreenCharacter* InThirdPersonPlayer, class AEvergreenPawn* InInteractionPlayer)
	{
		ThirdPersonPlayer = InThirdPersonPlayer;
		InteractionPlayer = InInteractionPlayer;
	}
	
	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* OpenUI(
		UPARAM(meta=(AllowAbstract=false)) TSubclassOf<UEvergreenWidgetBase> WidgetClass);

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* OpenUniqueUI(
		UPARAM(meta=(AllowAbstract=false)) TSubclassOf<UEvergreenWidgetBase> WidgetClass,
		bool& Success);
	
	UFUNCTION(BlueprintCallable)
	void CloseUI(UEvergreenWidgetBase* WidgetToRemove);

	UFUNCTION(BlueprintCallable)
	void CloseUniqueUI(
		UPARAM(meta=(AllowAbstract=false)) TSubclassOf<UEvergreenWidgetBase> WidgetClassToRemove,
		bool& Success);
	
private:
	UPROPERTY()
	URootCanvasWidget* RootCanvas = nullptr;

	UPROPERTY()
	TMap<int32, UEvergreenWidgetBase*> WidgetMap;

	UPROPERTY()
	TMap<TSubclassOf<UEvergreenWidgetBase>, UEvergreenWidgetBase*> UniqueWidgetMap;
	
	static AEvergreenCharacter* ThirdPersonPlayer;
	static AEvergreenPawn* InteractionPlayer;
};

AEvergreenCharacter* UUIManager::ThirdPersonPlayer = nullptr;
AEvergreenPawn* UUIManager::InteractionPlayer = nullptr;
