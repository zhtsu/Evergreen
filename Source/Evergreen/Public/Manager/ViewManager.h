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
	static bool IsObserved(UObject* ObservableObject);

	UFUNCTION(BlueprintPure)
	static UObject* GetCurrentObservedObject() { return CurrentObservedObject; }

	UFUNCTION(BlueprintCallable)
	void Observe(UObject* ObservableObject, FViewTargetTransitionParams ViewTargetTransitionParams);

	UFUNCTION(BlueprintCallable)
	void SetToPlayerView(FViewTargetTransitionParams ViewTargetTransitionParams);

	UFUNCTION(BlueprintCallable)
	static void PlayCutscene(class ULevelSequence* LevelSequence, class ALevelSequenceActor*& LevelSequenceActor, class ULevelSequencePlayer*& LevelSequencePlayer);

	UFUNCTION(BlueprintCallable)
	void SetCameraOffsetFollowCursorEnabled(bool bEnabled);

	UFUNCTION(BlueprintPure)
	bool GetCameraOffsetFollowCursorEnabled() const;

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
	void ChangeCameraParamsTo(ECameraViewType ViewType, bool bBlend = false, bool bAllowMove = true);

	static void SetGamePlayers(class AEvergreenCharacter* InThirdPersonPlayer, class AEvergreenPawn* InInteractionPlayer)
	{
		ThirdPersonPlayer = InThirdPersonPlayer;
		InteractionPlayer = InInteractionPlayer;
	}
	
private:
	static AEvergreenCharacter* ThirdPersonPlayer;
	static AEvergreenPawn* InteractionPlayer;
	
	static UObject* CurrentObservedObject;
	FTimerHandle TimerHandle;
	
	void CallOnStartObserve();
	void CallOnAttainPlayerView();
};

UObject* UViewManager::CurrentObservedObject = nullptr;
AEvergreenCharacter* UViewManager::ThirdPersonPlayer = nullptr;
AEvergreenPawn* UViewManager::InteractionPlayer = nullptr;
