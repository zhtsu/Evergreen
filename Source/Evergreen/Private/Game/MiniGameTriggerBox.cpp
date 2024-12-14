// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MiniGameTriggerBox.h"

#include "Game/EvergreenGameInstance.h"
#include "Game/MiniGameData.h"
#include "Manager/MiniGameManager.h"

AMiniGameTriggerBox::AMiniGameTriggerBox()
{
	GetRootComponent()->Mobility = EComponentMobility::Static;
}

void AMiniGameTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (TriggerBoxType == EMiniGameTriggerBoxType::StartMiniGame)
	{
		UMiniGameData* MiniGameData = NewObject<UMiniGameData>(this, MiniGameDataClass);
		UEvergreenGameInstance::GetEvergreenGameInstance()->GetSubsystem<UMiniGameManager>()->StartMiniGame(MiniGameClass, MiniGameData);
	}
	else
	{
		UEvergreenGameInstance::GetEvergreenGameInstance()->GetSubsystem<UMiniGameManager>()->EndMiniGame();
	}
}
