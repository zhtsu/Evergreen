// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EvergreenGameInstance.generated.h"

UENUM()
enum class EEvergreenGameMode : uint8
{
	ThirdPerson,
	Interaction
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameModeChanged, EEvergreenGameMode, CurrentMode);

UCLASS()
class EVERGREEN_API UEvergreenGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	EEvergreenGameMode GameMode = EEvergreenGameMode::ThirdPerson;
	bool DebugModeEnabled = false;
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnGameModeChanged OnGameModeChanged;
	
	UFUNCTION(BlueprintCallable)
	void SetEvergreenGameMode(EEvergreenGameMode InGameMode);

	UFUNCTION(BlueprintPure)
	FORCEINLINE EEvergreenGameMode GetEvergreenGameMode() const { return GameMode; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDebugMode(bool Enabled) { DebugModeEnabled = Enabled; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsDebugModeEnabled() const { return DebugModeEnabled; }
};
