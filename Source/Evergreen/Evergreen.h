// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define FAST_PRINT(Message) \
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Message); }

#define FAST_LOG(Message, ...) \
	UE_LOG(LogTemp, Display, Message, ##...)

#define FAST_WARNING(Message) \
	UE_LOG(LogTemp, Warning, Message) \
	UE_LOG(LogTemp, Warning, "Check the file: %s - Line: %d", __FILEW__, __LINE__)

