// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Manager/LifeStateManager.h"

void ULifeStateManager::AddLifeStateValue(int AddedValue)
{
	LifeStateValue += AddedValue;
	OnLifeStateValueUpdated.Broadcast(LifeStateValue);
}

void ULifeStateManager::SubtractLifeStateValue(int SubtractedValue)
{
	LifeStateValue -= SubtractedValue;
	OnLifeStateValueUpdated.Broadcast(LifeStateValue);
}
