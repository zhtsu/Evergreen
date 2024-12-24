// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EvergreenHUD.generated.h"

UCLASS()
class EVERGREEN_API AEvergreenHUD : public AHUD
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	
public:
	UPROPERTY(BlueprintReadOnly)
	class UMainUIWidget* MainUI;
};
