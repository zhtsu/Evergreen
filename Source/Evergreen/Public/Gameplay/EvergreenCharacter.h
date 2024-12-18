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

	UFUNCTION(BlueprintImplementableEvent)
	void K2_RotateCameraBoomYaw(float Yaw);

	UFUNCTION(BlueprintCallable)
	void K2_StartRotateCameraBoomYawIfAllowed(float Yaw, bool& AllowRotation);

	UFUNCTION(BlueprintCallable)
	void K2_EndRotateCameraYaw();
	
	UFUNCTION(BlueprintImplementableEvent)
	void K2_AdjustCameraBoom(float Length, float Pitch);

	UFUNCTION(BlueprintCallable)
	void K2_StartAdjustCameraBoomIfAllowed(float Length, float Pitch, bool& AllowAdjust);

	UFUNCTION(BlueprintCallable)
	void K2_EndAdjustCameraBoom();

	void SetCameraBoom(float Length, float Pitch);
	
private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class UCameraComponent* Camera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	FRotator StartCameraBoomRotation;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	FRotator TargetCameraBoomRotation;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float StartCameraBoomLength;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float TargetCameraBoomLength;
	
	void Move(const struct FInputActionValue& InputActionValue);
};
