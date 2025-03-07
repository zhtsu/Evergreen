// Fill out your copyright notice in the Description page of Project Settings.

#include "Common/EvergreenBPFL.h"

#include "AudioDevice.h"
#include "Blueprint/UserWidget.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Slate/WidgetRenderer.h"

FVector UEvergreenBPFL::GenerateLocationFromCircle(const FVector& Center, float Radius)
{
	float RandomAngle = FMath::RandRange(0.f, 2.f * PI);
	float RandomRadius = FMath::RandRange(0.f, Radius);

	float X = Center.X + RandomRadius * FMath::Cos(RandomAngle);
	float Y = Center.Y + RandomRadius * FMath::Sin(RandomAngle);
	
	return FVector(X, Y, 0.f);
}

UTexture2D* UEvergreenBPFL::GenerateTextureFromWidget(UUserWidget* Widget, const FVector2D& DrawSize)
{
	if (!FSlateApplication::IsInitialized()) return nullptr;
	if (!Widget) return nullptr;
	if (DrawSize.X < 1. || DrawSize.Y < 1.) return nullptr;

	TSharedPtr<SWidget> SlateWidget(Widget->TakeWidget());
	if (!SlateWidget.IsValid()) return nullptr;

	TSharedPtr<FWidgetRenderer> WidgetRenderer = MakeShareable(new FWidgetRenderer(true));
	if (!WidgetRenderer.IsValid()) return nullptr;

	UTextureRenderTarget2D* TextureRenderTarget = WidgetRenderer->DrawWidget(SlateWidget.ToSharedRef(), DrawSize);
	UTexture2D* Texture = UTexture2D::CreateTransient(DrawSize.X, DrawSize.Y, PF_B8G8R8A8);
#if WITH_EDITORONLY_DATA
	Texture->MipGenSettings = TMGS_NoMipmaps;
#endif

	TArray<FColor> SurfaceData;
	FRenderTarget* RenderTarget = TextureRenderTarget->GameThread_GetRenderTargetResource();
	RenderTarget->ReadPixels(SurfaceData);

	void* TextureData = Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	const int32 TextureDataSize = SurfaceData.Num() * 4;
	FMemory::Memcpy(TextureData, SurfaceData.GetData(), TextureDataSize);
	
	Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
	Texture->UpdateResource();

	SurfaceData.Empty();
	TextureRenderTarget->ConditionalBeginDestroy();
	SlateWidget.Reset();
	WidgetRenderer.Reset();

	return Texture;
}

UAudioComponent* UEvergreenBPFL::SpawnSoundAttached_NoPlay(USoundBase* Sound, USceneComponent* AttachToComponent,
	FName AttachPointName, FVector Location, FRotator Rotation, EAttachLocation::Type LocationType,
	bool bStopWhenAttachedToDestroyed, float VolumeMultiplier, float PitchMultiplier,
	USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy)
{
	if (!Sound)
	{
		return nullptr;
	}

	if (!AttachToComponent)
	{
		UE_LOG(LogScript, Warning, TEXT("UGameplayStatics::SpawnSoundAttached: NULL AttachComponent specified! Trying to spawn sound [%s],"), *Sound->GetName());
		return nullptr;
	}

	UWorld* const ThisWorld = AttachToComponent->GetWorld();
	if (ThisWorld && ThisWorld->IsNetMode(NM_DedicatedServer))
	{
		// FAudioDevice::CreateComponent will fail to create the AudioComponent in a real dedicated server, but we need to check netmode here for Editor support.
		return nullptr;
	}

	// Location used to check whether to create a component if out of range
	FVector TestLocation = Location;
	if (LocationType == EAttachLocation::KeepRelativeOffset)
	{
		if (AttachPointName != NAME_None)
		{
			TestLocation = AttachToComponent->GetSocketTransform(AttachPointName).TransformPosition(Location);
		}
		else
		{
			TestLocation = AttachToComponent->GetComponentTransform().TransformPosition(Location);
		}
	}
	else if (LocationType == EAttachLocation::SnapToTarget || LocationType == EAttachLocation::SnapToTargetIncludingScale)
	{
		// If AttachPointName is NAME_None, will return just the component position
		TestLocation = AttachToComponent->GetSocketLocation(AttachPointName);
	}

	FAudioDevice::FCreateComponentParams Params(ThisWorld, AttachToComponent->GetOwner());
	Params.SetLocation(TestLocation);
	Params.bStopWhenOwnerDestroyed = bStopWhenAttachedToDestroyed;
	Params.AttenuationSettings = AttenuationSettings;

	if (ConcurrencySettings)
	{
		Params.ConcurrencySet.Add(ConcurrencySettings);
	}

	UAudioComponent* AudioComponent = FAudioDevice::CreateComponent(Sound, Params);
	if (AudioComponent)
	{
		if (UWorld* ComponentWorld = AudioComponent->GetWorld())
		{
			const bool bIsInGameWorld = ComponentWorld->IsGameWorld();

			if (LocationType == EAttachLocation::SnapToTarget || LocationType == EAttachLocation::SnapToTargetIncludingScale)
			{
				AudioComponent->AttachToComponent(AttachToComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachPointName);
			}
			else
			{
				AudioComponent->AttachToComponent(AttachToComponent, FAttachmentTransformRules::KeepRelativeTransform, AttachPointName);
				if (LocationType == EAttachLocation::KeepWorldPosition)
				{
					AudioComponent->SetWorldLocationAndRotation(Location, Rotation);
				}
				else
				{
					AudioComponent->SetRelativeLocationAndRotation(Location, Rotation);
				}
			}

			AudioComponent->SetVolumeMultiplier(VolumeMultiplier);
			AudioComponent->SetPitchMultiplier(PitchMultiplier);
			AudioComponent->bAllowSpatialization = Params.ShouldUseAttenuation();
			AudioComponent->bIsUISound = !bIsInGameWorld;
			AudioComponent->bAutoDestroy = bAutoDestroy;
			AudioComponent->SubtitlePriority = Sound->GetSubtitlePriority();
		}
	}

	return AudioComponent;
}
