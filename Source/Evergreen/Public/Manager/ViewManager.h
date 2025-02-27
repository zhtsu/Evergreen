// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ViewManager.generated.h"

UENUM(BlueprintType)
enum ECameraViewType
{
	SuperFarView,
	FarView,
	FullView,
	MidView,
	CloseView,
	CloseUpView,
	SuperCloseUpView
};

UCLASS()
class UViewManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UViewManager();

	UFUNCTION(BlueprintPure)
	bool IsObserved(UObject* ObservableObject);

	UFUNCTION(BlueprintPure)
	UObject* GetCurrentObservedObject() const { return CurrentObservedObject; }

	UFUNCTION(BlueprintCallable)
	void Observe(UObject* ObservableObject, FViewTargetTransitionParams ViewTargetTransitionParams);

	UFUNCTION(BlueprintCallable)
	void SetToPlayerView(FViewTargetTransitionParams ViewTargetTransitionParams);

	UFUNCTION(BlueprintCallable)
	static void PlayCutscene(class ULevelSequence* LevelSequence, class ALevelSequenceActor*& LevelSequenceActor, class ULevelSequencePlayer*& LevelSequencePlayer);

	UFUNCTION(BlueprintCallable)
	void SetCameraOffsetFollowMouseEnabled(bool bEnabled);

	UFUNCTION(BlueprintPure)
	bool GetCameraOffsetFollowMouseEnabled() const;

	UFUNCTION(BlueprintCallable)
	void SetCameraOffsetScale_X(float Scale);

	UFUNCTION(BlueprintCallable)
	void SetCameraOffsetScale_Y(float Scale);
	
	UFUNCTION(BlueprintPure)
	float GetCameraOffsetScale_X() const;

	UFUNCTION(BlueprintPure)
	float GetCameraOffsetScale_Y() const;

	UFUNCTION(BlueprintCallable)
	void RotateCameraBoomYaw_ThirdPerson(float Yaw = -1.f, bool bAllowMove = true);

	UFUNCTION(BlueprintCallable)
	void RotateCameraBoomPitch_ThirdPerson(float Pitch = -1.f, bool bAllowMove = true);
	
	UFUNCTION(BlueprintCallable)
	void AdjustCameraBoomLength_ThirdPerson(float Length = -1.f, bool bAllowMove = true);

	UFUNCTION(BlueprintCallable)
	void ChangeCameraParams(ECameraViewType ViewType, bool bBlend = true, bool bAllowMove = true);

	UFUNCTION(BlueprintCallable)
	void ChangeCamera(const FString& CameraID, bool& Success, FViewTargetTransitionParams TransitionParams = FViewTargetTransitionParams());

	void SetThirdPersonPlayer(class AEvergreenCharacter* InThirdPersonPlayer)
	{
		ThirdPersonPlayer = InThirdPersonPlayer;
	}
	
private:
	UPROPERTY()
	AEvergreenCharacter* ThirdPersonPlayer;

	UPROPERTY()
	UObject* CurrentObservedObject = nullptr;
	
	FTimerHandle TimerHandle;
	
	void CallOnStartObserve();
	void CallOnAttainPlayerView();

	bool bCameraOffsetFollowMouseEnabled = true;
	float CameraOffsetScale_X = 0.1f;
	float CameraOffsetScale_Y = 0.1f;
};
