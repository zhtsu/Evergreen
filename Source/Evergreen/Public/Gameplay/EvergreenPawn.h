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

	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE class UCineCameraComponent* GetCamera() const { return Camera; }
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetCameraOffsetFollowCursorEnabled(bool bEnabled) { bCameraOffsetFollowCursorEnabled = bEnabled; }
	FORCEINLINE void SetCameraOffsetScale_X(float Scale) { CameraOffsetScale_X = Scale; }
	FORCEINLINE void SetCameraOffsetScale_Y(float Scale) { CameraOffsetScale_Y = Scale; }
	FORCEINLINE bool GetCameraOffsetFollowCursorEnabled() const { return bCameraOffsetFollowCursorEnabled; }
	FORCEINLINE float GetCameraOffsetScale_X() const { return CameraOffsetScale_X; }
	FORCEINLINE float GetCameraOffsetScale_Y() const { return CameraOffsetScale_Y; }
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Evergreen Player", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEvergreenCharacter> ThirdPersonPlayerClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UCineCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Camera")
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Movement")
	class UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(VisibleDefaultsOnly, Category = "Item")
	USceneComponent* RootScene;
	
	void ActivateMappingContext(class AEvergreenPlayerController* PlayerController, UInputComponent* PlayerInputComponent);
	void RemoveMappingContext(AEvergreenPlayerController* PlayerController);
	
	void Move(const struct FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	
	bool bCameraOffsetFollowCursorEnabled = false;
	float CameraOffsetScale_X = 0.1f;
	float CameraOffsetScale_Y = 0.1f;
	float InterpSpeed = 2.f;
};
