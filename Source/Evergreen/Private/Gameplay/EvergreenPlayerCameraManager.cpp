// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/EvergreenPlayerCameraManager.h"

#include "Gameplay/EvergreenGameInstance.h"
#include "Manager/ViewManager.h"

AEvergreenPlayerCameraManager::AEvergreenPlayerCameraManager()
{
	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (!EGI) return;
	
	UViewManager* ViewManager = EGI->GetSubsystem<UViewManager>();
	if (!ViewManager) return;

	if (ViewManager)
	{
		ViewManager->SetPlayerCameraManager(this);
	}
}

bool AEvergreenPlayerCameraManager::CameraOffsetFollowCursor(AActor* CameraTarget, FVector& NewCameraLocation,
                                                             FRotator& NewCameraRotation, float& NewCameraFOV)
{
	if (!PCOwner) return false;
	if (!bCameraOffsetFollowCursorEnabled) return false;
	
	NewCameraLocation = PCOwner->GetPawn()->GetActorLocation();
	NewCameraRotation = PCOwner->K2_GetActorRotation();
	NewCameraFOV = 90.f;
	
	FVector2D MousePosition;
	PCOwner->GetMousePosition(MousePosition.X, MousePosition.Y);
	
	FIntPoint ViewportSize;
	PCOwner->GetViewportSize(ViewportSize.X, ViewportSize.Y);

	FVector2D ViewportCenter = ViewportSize * 0.5;

	FVector2D TargetOffset = MousePosition - ViewportCenter;
	//FVector LerpX = FMath::Lerp(NewCameraLocation);
	NewCameraLocation += (TargetOffset.X * OffsetScale) * GetActorRightVector();
	NewCameraLocation += (-TargetOffset.Y * OffsetScale) * GetActorUpVector();
	
	return true;
}
