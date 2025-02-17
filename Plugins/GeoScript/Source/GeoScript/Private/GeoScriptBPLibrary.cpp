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
	UDynamicMesh* TargetMesh,
	float MaxDistance, int32 RayCount,
	float Angle, FVector Location, FRotator Rotator)
{
	if (TargetMesh == nullptr)
	{
		UGeometryScriptDebug* Debug = nullptr;
		const FText ErrorMsg = FText::FromString("GenerateConeArea: TargetMesh is Null");
		UE::Geometry::AppendError(Debug, EGeometryScriptErrorType::InvalidInputs, ErrorMsg);
		return TargetMesh;
	}

	TargetMesh->Reset();
	FDynamicMesh3* Mesh = TargetMesh->GetMeshPtr();

	TArray<FVector3d> Vertices;
	Vertices.Add(FVector3d(Location));

	FVector ForwardVector = Rotator.Vector();

	for (int32 i = 0; i < RayCount; i++)
	{
		float CurrentAngle = (float)i / RayCount * 2 * PI;

		FVector RayDir = ForwardVector.RotateAngleAxis(Angle, FVector::UpVector);
		RayDir = RayDir.RotateAngleAxis(CurrentAngle * 180.f / PI, ForwardVector);

		FWorldContext* WorldContext = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
		UWorld* World = WorldContext->World();

		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		// QueryParams.bTraceComplex = true;
		
		if (World && World->LineTraceSingleByChannel(
			HitResult,
			Location,
			Location + RayDir * MaxDistance,
			ECC_Visibility,
			QueryParams))
		{
			Vertices.Add(FVector3d(HitResult.Location));
		}
		else
		{
			Vertices.Add(FVector3d(Location + RayDir * MaxDistance));
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

	UE::Geometry::FMeshNormals::QuickComputeVertexNormals(*Mesh);
	
	return TargetMesh;
}
