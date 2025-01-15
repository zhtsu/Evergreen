// Fill out your copyright notice in the Description page of Project Settings.

#include "Common/EvergreenBPFL.h"

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
