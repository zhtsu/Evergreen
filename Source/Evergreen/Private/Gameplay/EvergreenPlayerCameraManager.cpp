// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/EvergreenPlayerCameraManager.h"

#include "Camera/CameraComponent.h"
#include "Common/CommonMacro.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gameplay/EvergreenCharacter.h"
#include "Gameplay/EvergreenGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ViewManager.h"

void AEvergreenPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	UEvergreenGameInstance* EGI = UEvergreenGameInstance::GetEvergreenGameInstance();
	if (UViewManager* ViewManager = EGI->GetSubsystem<UViewManager>())
	{
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

	FVector2D TargetOffset;
	if (MousePosition.X <= 0.f)
	{
		TargetOffset = FVector2D::ZeroVector;
	}
	else
	{
		TargetOffset = MousePosition - ViewportCenter;
	}
	
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	CurrentOffset = FMath::Vector2DInterpTo(CurrentOffset, TargetOffset, DeltaTime, InterpSpeed);
	
	AEvergreenCharacter* Character = Cast<AEvergreenCharacter>(PCOwner->GetPawn());
	if (!Character) return false;

	FVector TargetLocation = Character->GetActorLocation();
	TargetLocation.Y = -6.f;
	TargetLocation.Z = 60.f;
	NewCameraLocation = TargetLocation;
	NewCameraRotation = Character->GetActorRotation();
	NewCameraFOV = 90.f;

	FVector ModifiedOffset = FVector::ZeroVector;

	FRotator CharacterRotation = Character->GetActorRotation();
	FVector RightVector = FRotationMatrix(CharacterRotation).GetUnitAxis(EAxis::Y);
	FVector UpVector = FRotationMatrix(CharacterRotation).GetUnitAxis(EAxis::Z);

	ModifiedOffset += (CurrentOffset.X * OffsetScale) * RightVector;
	ModifiedOffset += (-CurrentOffset.Y * OffsetScale) * UpVector;

	NewCameraLocation += ModifiedOffset;
	
	return true;
}
