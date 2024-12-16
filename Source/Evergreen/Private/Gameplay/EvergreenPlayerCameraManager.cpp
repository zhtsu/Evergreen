// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/EvergreenPlayerCameraManager.h"

#include "Common/CommonMacro.h"

bool AEvergreenPlayerCameraManager::CameraOffsetFollowCursor(AActor* CameraTarget, FVector& NewCameraLocation,
                                                             FRotator& NewCameraRotation, float& NewCameraFOV)
{
	if (!PCOwner) return false;
	if (!bCameraOffsetFollowCursorEnabled) return false;
	
	FVector2D MousePosition;
	PCOwner->GetMousePosition(MousePosition.X, MousePosition.Y);
	
	FIntPoint ViewportSize;
	PCOwner->GetViewportSize(ViewportSize.X, ViewportSize.Y);

	bool bIsMouseInViewport = (MousePosition.X >= 0 && MousePosition.X <= ViewportSize.X)
		&& (MousePosition.Y >= 0 && MousePosition.Y <= ViewportSize.Y);

	if (!bIsMouseInViewport) return false;
	
	FVector2D ViewportCenter = ViewportSize * 0.5;

	FVector2D TargetOffset = MousePosition - ViewportCenter;
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	CurrentOffset = FMath::Vector2DInterpTo(CurrentOffset, TargetOffset, DeltaTime, InterpSpeed);

	NewCameraLocation = PCOwner->GetPawn()->GetActorLocation();
	NewCameraRotation = PCOwner->K2_GetActorRotation();
	NewCameraFOV = 90.f;
	
	NewCameraLocation += (CurrentOffset.X * OffsetScale) * GetActorRightVector();
	NewCameraLocation += (-CurrentOffset.Y * OffsetScale) * GetActorUpVector();
	
	return true;
}
