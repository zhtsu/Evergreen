// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MiniGameTriggerBox.h"

#include "Game/EvergreenGameInstance.h"
#include "Game/MiniGameData.h"

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
		UEvergreenGameInstance::GetEvergreenGameInstance()->StartMiniGame(MiniGameClass, MiniGameData);
	}
	else
	{
		UEvergreenGameInstance::GetEvergreenGameInstance()->EndMiniGame();
	}
}
