// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dataflow/DataflowNodeParameters.h"
#include "GameFramework/Character.h"
#include "EvergreenCharacter.generated.h"

UCLASS()
class EVERGREEN_API AEvergreenCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEvergreenCharacter();

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RotateCameraYaw(float Angle);
	
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
	
	bool bCameraRotating = false;
	FRotator CurrentSpringArmRotator;
	FRotator TargetSpringArmRotator;
	float InterpSpeed = 1.f;
};
