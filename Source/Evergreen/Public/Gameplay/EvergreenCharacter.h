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

	UPROPERTY()
	class AInteractableItemBase* ActiveInteractableItem = nullptr;
	
protected:
	virtual void BeginPlay() override;
	
public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	// Yaw
	UFUNCTION(BlueprintImplementableEvent)
	void K2_RotateCameraBoomYaw(float Yaw, bool bAllowMove);

	UFUNCTION(BlueprintCallable)
	void K2_StartRotateCameraBoomYawIfAllowed(float Yaw, bool bAllowMove, bool& AllowRotation);

	UFUNCTION(BlueprintCallable)
	void K2_EndRotateCameraYaw();

	// Pitch
	UFUNCTION(BlueprintImplementableEvent)
	void K2_RotateCameraBoomPitch(float Pitch, bool bAllowMove);

	UFUNCTION(BlueprintCallable)
	void K2_StartRotateCameraBoomPitchIfAllowed(float Pitch, bool bAllowMove, bool& AllowRotation);

	UFUNCTION(BlueprintCallable)
	void K2_EndRotateCameraPitch();

	// Boom length
	UFUNCTION(BlueprintImplementableEvent)
	void K2_AdjustCameraBoomLength(float Length, bool bAllowMove);

	UFUNCTION(BlueprintCallable)
	void K2_StartAdjustCameraBoomLengthIfAllowed(float Length, bool bAllowMove, bool& AllowAdjust);

	UFUNCTION(BlueprintCallable)
	void K2_EndAdjustCameraBoomLength();

	void SetCameraParams(float Yaw, float Pitch, float Length);
	
private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	class UCineCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	class UWidgetComponent* BubbleWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEvergreenPawn> InteractorClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	// Camera movement
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float StartCameraBoomYaw;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float StartCameraBoomPitch;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float TargetCameraBoomYaw;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float TargetCameraBoomPitch;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float StartCameraBoomLength;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float TargetCameraBoomLength;
	
	void ActivateMappingContext(class AEvergreenPlayerController* PlayerController, UInputComponent* PlayerInputComponent);
	void RemoveMappingContext(AEvergreenPlayerController* PlayerController);
	
	void Move(const struct FInputActionValue& InputActionValue);
	void Interact(const FInputActionValue& InputActionValue);

	bool bCameraBoomYawBlending = false;
	bool bCameraBoomPitchBlending = false;
	bool bCameraBoomLengthBlending = false;
};
