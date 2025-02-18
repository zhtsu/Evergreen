// Copyright Epic Games, Inc. All Rights Reserved.

#include "GeoScriptBPLibrary.h"

#include "Editor.h"
#include "UDynamicMesh.h"
#include "DynamicMesh/MeshNormals.h"
#include "GeometryScript/GeometryScriptTypes.h"

UGeoScriptBPLibrary::UGeoScriptBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

UDynamicMesh* UGeoScriptBPLibrary::GenerateConeArea(
		AActor* DynamicMeshActor,
		UDynamicMesh* TargetMesh,
		float MaxDistance,
		int32 RayCount,
		float ConeAngle)
{
	if (DynamicMeshActor == nullptr || TargetMesh == nullptr)
	{
		UGeometryScriptDebug* Debug = nullptr;
		const FText ErrorMsg = FText::FromString("GenerateConeArea: DynamicMeshActor or TargetMesh is Null");
		UE::Geometry::AppendError(Debug, EGeometryScriptErrorType::InvalidInputs, ErrorMsg);
		return TargetMesh;
	}

	MaxDistance = FMath::Max(100.0, MaxDistance);
	RayCount = FMath::Max(3, RayCount);
	ConeAngle = FMath::Max(15, ConeAngle);

	TargetMesh->Reset();
	FDynamicMesh3* Mesh = TargetMesh->GetMeshPtr();

	TArray<FVector3d> Vertices;
	Vertices.Add(FVector3d(FVector::ZeroVector));

	FVector Location = DynamicMeshActor->GetActorLocation();
	FVector ForwardVector = DynamicMeshActor->GetActorForwardVector();
	FVector RightVector = DynamicMeshActor->GetActorRightVector();
	
	for (int32 i = 0; i < RayCount; i++)
	{
		float CurrentAngle = (float)i / RayCount * 360.f;
		
		FVector RayDir = ForwardVector.RotateAngleAxis(ConeAngle, RightVector);
		RayDir = RayDir.RotateAngleAxis(CurrentAngle, ForwardVector);
		RayDir.Normalize();

		FVector Start = Location;
		FVector End = Location + RayDir * MaxDistance;
		
		FHitResult OutHit;
		FCollisionQueryParams Params;
		Params.bTraceComplex = true;
		Params.AddIgnoredActor(DynamicMeshActor);
		
		FWorldContext* WorldContext = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
		UWorld* World = WorldContext->World();
		
		if (World && World->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, Params))
		{
			FVector LocalPoint = DynamicMeshActor->GetActorTransform().InverseTransformPosition(OutHit.ImpactPoint);
			Vertices.Add(FVector3d(LocalPoint));
		}
		else
		{
			FVector LocalPoint = DynamicMeshActor->GetActorTransform().InverseTransformPosition(End);
			Vertices.Add(FVector3d(LocalPoint));
		}
	}

	TArray<int32> VertexIndices;
	for (const FVector3d& Vertex : Vertices)
	{
		VertexIndices.Add(Mesh->AppendVertex(Vertex));
	}

	for (int32 i = 1; i < RayCount; i++)
	{
		Mesh->AppendTriangle(VertexIndices[0], VertexIndices[i], VertexIndices[i + 1]);
	}

	Mesh->AppendTriangle(VertexIndices[0], VertexIndices[RayCount], VertexIndices[1]);
	
	return TargetMesh;
}
