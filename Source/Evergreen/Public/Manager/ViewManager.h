// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ViewManager.generated.h"

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
	void SetCameraOffsetScale(float OffsetScale);

	UFUNCTION(BlueprintPure)
	float GetCameraOffsetScale() const;
	
	UFUNCTION(BlueprintCallable)
	void SetCameraOffsetInterpSpeed(float InterpSpeed);

	UFUNCTION(BlueprintPure)
	float GetCameraOffsetInterpSpeed() const;

	UFUNCTION(BlueprintCallable)
	void RotateCharacterCameraBoomYaw(float Yaw);

	UFUNCTION(BlueprintCallable)
	void AdjustCharacterCameraBoom(float Length = 600.f, float Pitch = -25.f);

	UFUNCTION(BlueprintCallable)
	void SetCharacterCameraBoom(float Length = 600.f, float Pitch = -25.f);

	FORCEINLINE void SetPlayerCameraManager(class AEvergreenPlayerCameraManager* InPCM) { PCM = InPCM; }
	
private:
	static UObject* CurrentObservedObject;
	FTimerHandle TimerHandle;

	UPROPERTY()
	AEvergreenPlayerCameraManager* PCM = nullptr;
	
	void CallOnStartObserve();
	void CallOnAttainPlayerView();
};

UObject* UViewManager::CurrentObservedObject = nullptr;
