// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EvergreenCharacter.generated.h"

UCLASS()
class EVERGREEN_API AEvergreenCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEvergreenCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class UCameraComponent* Camera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	
	void Move(const struct FInputActionValue& InputActionValue);
};
