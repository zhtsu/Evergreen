// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/EvergreenPlayerCameraManager.h"

#include "Gameplay/EvergreenGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ViewManager.h"

void AEvergreenPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (EGI && EGI->GetSubsystem<UViewManager>())
	{
		UViewManager* ViewManager = EGI->GetSubsystem<UViewManager>();
		AEvergreenPlayerCameraManager* PCM = Cast<AEvergreenPlayerCameraManager>(
			UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));

		ViewManager->SetPlayerCameraManager(PCM);
	}
}

bool AEvergreenPlayerCameraManager::CameraOffsetFollowCursor(AActor* CameraTarget, FVector& NewCameraLocation,
                                                             FRotator& NewCameraRotation, float& NewCameraFOV)
{
	if (!PCOwner) return false;
	if (!bCameraOffsetFollowCursorEnabled) return false;
	if (!UEvergreenGameInstance::GetEvergreenGameInstance()->IsInteractionMode()) return false;
	
	FVector2D MousePosition;
	PCOwner->GetMousePosition(MousePosition.X, MousePosition.Y);
	
	FIntPoint ViewportSize;
	PCOwner->GetViewportSize(ViewportSize.X, ViewportSize.Y);

	FVector2D ViewportCenter = FVector2D(ViewportSize) * 0.5;

	bool bIsMouseInViewport = (MousePosition.X >= 0 && MousePosition.X <= ViewportSize.X)
		&& (MousePosition.Y >= 0 && MousePosition.Y <= ViewportSize.Y);

	FVector2D TargetOffset = MousePosition - ViewportCenter;
	if (!bIsMouseInViewport)
	{
		TargetOffset = FVector2D::ZeroVector;
	}
	
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	CurrentOffset = FMath::Vector2DInterpTo(CurrentOffset, TargetOffset, DeltaTime, InterpSpeed);

	NewCameraLocation = PCOwner->GetPawn()->GetActorLocation();
	NewCameraRotation = PCOwner->K2_GetActorRotation();
	NewCameraFOV = 90.f;
	
	NewCameraLocation += (CurrentOffset.X * OffsetScale) * GetActorRightVector();
	NewCameraLocation += (-CurrentOffset.Y * OffsetScale) * GetActorUpVector();
	
	return true;
}
