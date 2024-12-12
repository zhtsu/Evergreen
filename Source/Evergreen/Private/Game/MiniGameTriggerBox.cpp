// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MiniGameTriggerBox.h"

#include "Game/EvergreenGameInstance.h"

AMiniGameTriggerBox::AMiniGameTriggerBox()
{
	GetRootComponent()->Mobility = EComponentMobility::Static;
}

void AMiniGameTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (TriggerBoxType == EMiniGameTriggerBoxType::StartMiniGame)
	{
		UEvergreenGameInstance::GetEvergreenGameInstance()->StartMiniGame(MiniGameClass, nullptr);
	}
	else
	{
		UEvergreenGameInstance::GetEvergreenGameInstance()->EndMiniGame();
	}
}
