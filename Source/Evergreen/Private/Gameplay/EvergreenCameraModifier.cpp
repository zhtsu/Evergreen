// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EvergreenCameraModifier.h"

#include "Gameplay/EvergreenGameInstance.h"
#include "Gameplay/EvergreenPlayerController.h"
#include "Manager/ViewManager.h"

void UEvergreenCameraModifier::ModifyCamera(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV,
                                            FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV)
{
	Super::ModifyCamera(DeltaTime, ViewLocation, ViewRotation, FOV, NewViewLocation, NewViewRotation, NewFOV);

	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (!EGI) return;

	UViewManager* ViewManager = EGI->GetSubsystem<UViewManager>();
	if (!ViewManager) return;
	
	if (!ViewManager->GetCameraOffsetFollowMouseEnabled()) return;
	if (!UEvergreenGameInstance::GetEvergreenGameInstance()->IsInteractionMode()) return;
	
	AEvergreenPlayerController* PlayerController = EGI->GetEvergreenPlayerController();
	if (!PlayerController) return;
	
	FVector2D MousePosition;
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	
	FIntPoint ViewportSize;
	PlayerController->GetViewportSize(ViewportSize.X, ViewportSize.Y);
	
	FVector2D ViewportCenter = FVector2D(ViewportSize) * 0.5;
	
	FVector2D MouseOffset = MousePosition - ViewportCenter;

	bool bIsMouseInViewport = (MousePosition.X > KINDA_SMALL_NUMBER && MousePosition.X < ViewportSize.X)
		&& (MousePosition.Y > KINDA_SMALL_NUMBER && MousePosition.Y < ViewportSize.Y);

	FVector TargetOffset = FVector::ZeroVector;
	if (bIsMouseInViewport)
	{
		FVector RightOffset = ViewRotation.RotateVector(FVector::RightVector) * 
							 (MouseOffset.X * ViewManager->GetCameraOffsetScale_X());
		FVector UpOffset = ViewRotation.RotateVector(FVector::UpVector) * 
						  (-MouseOffset.Y * ViewManager->GetCameraOffsetScale_Y());

		TargetOffset = RightOffset + UpOffset;
	}
	
	NewViewLocation = ViewLocation + TargetOffset;
	NewViewRotation = ViewRotation;
	NewFOV = FOV;
}
