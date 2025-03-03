// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EvergreenPlayerController.h"

#include "Gameplay/EvergreenCameraModifier.h"
#include "Gameplay/EvergreenCharacter.h"
#include "Gameplay/EvergreenGameInstance.h"

AEvergreenPlayerController::AEvergreenPlayerController()
{
	UEvergreenGameInstance::SetEvergreenPlayerController(this);
}

void AEvergreenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCameraManager->AddNewCameraModifier(UEvergreenCameraModifier::StaticClass());
}

FVector2D AEvergreenPlayerController::GetViewportCenter()
{
	AEvergreenPlayerController* EPC = UEvergreenGameInstance::GetEvergreenGameInstance()->GetEvergreenPlayerController();
	
	FIntPoint ViewportSize;
	EPC->GetViewportSize(ViewportSize.X, ViewportSize.Y);

	return FVector2D(ViewportSize) * 0.5;
}

void AEvergreenPlayerController::SetMousePosition(const FVector2D& Position)
{
	if (FViewport* Viewport = GetLocalPlayer()->ViewportClient->Viewport)
	{
		Viewport->SetMouse(Position.X, Position.Y);
	}
}

void AEvergreenPlayerController::SetPlayerHiddenInGame(bool bHide)
{
	if (ThirdPersonPlayer)
	{
		if (ThirdPersonPlayer->GetMesh())
		{
			ThirdPersonPlayer->GetMesh()->SetHiddenInGame(bHide);
		}
	}
}
