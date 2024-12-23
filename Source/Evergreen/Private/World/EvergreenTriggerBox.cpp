// Fill out your copyright notice in the Description page of Project Settings.


#include "World/EvergreenTriggerBox.h"

AEvergreenTriggerBox::AEvergreenTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AEvergreenTriggerBox::OnActorBeginOverlapFunction);
	OnActorEndOverlap.AddDynamic(this, &AEvergreenTriggerBox::OnActorEndOverlapFunction);
}

void AEvergreenTriggerBox::OnActorBeginOverlapFunction(AActor* OverlappedActor, AActor* OtherActor)
{
	if (IsAllowedClass(OtherActor))
	{
		OnActorEnter.Broadcast(OtherActor);
	}
}

void AEvergreenTriggerBox::OnActorEndOverlapFunction(AActor* OverlappedActor, AActor* OtherActor)
{
	if (IsAllowedClass(OtherActor))
	{
		OnActorLeave.Broadcast(OtherActor);
	}
}

bool AEvergreenTriggerBox::IsAllowedClass(AActor* TriggerActor)
{
	for (const TSubclassOf<AActor>& Iter : AllowedActorClasses)
	{
		if (TriggerActor->GetClass() == Iter)
			return true;
	}
	return false;
}
