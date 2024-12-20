// Fill out your copyright notice in the Description page of Project Settings.


#include "World/EvergreenTriggerBox.h"

AEvergreenTriggerBox::AEvergreenTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AEvergreenTriggerBox::OnActorBeginOverlapFunction);
	OnActorEndOverlap.AddDynamic(this, &AEvergreenTriggerBox::OnActorEndOverlapFunction);
}

void AEvergreenTriggerBox::OnActorBeginOverlapFunction(AActor* OverlappedActor, AActor* OtherActor)
{
	if (IsAllowedClass(OverlappedActor))
	{
		OnTriggerActorEnter.Broadcast(OverlappedActor);
	}
}

void AEvergreenTriggerBox::OnActorEndOverlapFunction(AActor* OverlappedActor, AActor* OtherActor)
{
	if (IsAllowedClass(OverlappedActor))
	{
		OnTriggerActorLeave.Broadcast(OverlappedActor);
	}
}

bool AEvergreenTriggerBox::IsAllowedClass(AActor* OverlappedActor)
{
	for (const TSubclassOf<AActor>& Iter : AllowedTriggerActorClasses)
	{
		if (OverlappedActor->GetClass() == Iter)
			return true;
	}
	return false;
}
