// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrahedralMeshAsset.h"
#include "MathUtil.h"

void UTetrahedralMeshAsset::SetTetrahedralMesh(std::shared_ptr<imstk::TetrahedralMesh> Input) {
	Vertices = UMathUtil::ToUnrealFVecArray(Input->getVertexPositions());
	Indices = UMathUtil::ToUnrealUIntArray(Input->getTetrahedraIndices());
}

std::shared_ptr<imstk::TetrahedralMesh> UTetrahedralMeshAsset::GetTetrahedralMesh() {
	std::shared_ptr<imstk::TetrahedralMesh> Output = std::make_shared<imstk::TetrahedralMesh>();
	Output->initialize(UMathUtil::ToImstkVecDataArray3d(Vertices), UMathUtil::ToImstkVecDataArray4i(Indices));
	return Output;
}