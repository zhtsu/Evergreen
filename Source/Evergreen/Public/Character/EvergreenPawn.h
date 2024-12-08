// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EvergreenPawn.generated.h"

UCLASS()
class EVERGREEN_API AEvergreenPawn : public APawn
{
	GENERATED_BODY()

public:
	AEvergreenPawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "Movement")
	class UFloatingPawnMovement* FloatingPawnMovement;

	void Move(const struct FInputActionValue& InputActionValue);
	void Look(const struct FInputActionValue& InputActionValue);
};
