// Fill out your copyright notice in the Description page of Project Settings.

#include "Common/EvergreenBPFL.h"

FVector UEvergreenBPFL::GenerateLocationFromCircle(const FVector& Center, float Radius)
{
	float RandomAngle = FMath::RandRange(0.f, 2.f * PI);
	float RandomRadius = FMath::RandRange(0.f, Radius);

	float X = Center.X + RandomRadius * FMath::Cos(RandomAngle);
	float Y = Center.Y + RandomRadius * FMath::Sin(RandomAngle);
	
	return FVector(X, Y, 0.f);
}
