// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "iMSTK-5.0/imstkTetrahedralMesh.h"
#include "TetrahedralMeshAsset.generated.h"

/**
 *
 */
UCLASS()
class IMSTK_API UTetrahedralMeshAsset : public UObject
{
	GENERATED_BODY()

public:
	void SetTetrahedralMesh(std::shared_ptr<imstk::TetrahedralMesh> Input);
	std::shared_ptr<imstk::TetrahedralMesh> GetTetrahedralMesh();
	//protected:
	UPROPERTY(EditAnywhere, Category = "General")
		TArray<FVector> Vertices;
	UPROPERTY(EditAnywhere, Category = "General")
		TArray<uint32> Indices;
	// TODO: Maybe try to cache a mesh and return that instead of creating on each run (would only matter for the editor)
	//std::shared_ptr<imstk::TetrahedralMesh> TetMesh;
};
