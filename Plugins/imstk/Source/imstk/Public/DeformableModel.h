// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicalModel.h"

#include "ProceduralMeshComponent.h"
#include "TetrahedralMeshAsset.h"
#include "KismetProceduralMeshLibrary.h"
#include "iMSTK-5.0/imstkPbdObject.h"
#include "iMSTK-5.0/imstkPbdModel.h"
#include "iMSTK-5.0/imstkSelectEnclosedPoints.h"

#include "DeformableModel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Imstk), meta = (BlueprintSpawnableComponent))
class IMSTK_API UDeformableModel : public UDynamicalModel
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "General")
		//bool TetrahedralMesh;
		UTetrahedralMeshAsset* TetrahedralMesh;

	// PBD model config settings
	UPROPERTY(EditAnywhere, Category = "General")
		double Mass = 1.0;

	UPROPERTY(EditAnywhere, Category = "General")
		double ViscousDampingCoeff = 0.01;

	UPROPERTY(EditAnywhere, Category = "General")
		double ContactStiffness = 1.0;

	UPROPERTY(EditAnywhere, Category = "Constraints")
		bool bUseDistanceConstraint = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseDistanceConstraint == true", EditConditionHides), Category = "Constraints")
		float DistanceConstraint = 0.0;

	UPROPERTY(EditAnywhere, Category = "Constraints")
		bool bUseDihedralConstraint = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseDihedralConstraint == true", EditConditionHides), Category = "Constraints")
		float DihedralConstraint = 0.0;

	UPROPERTY(EditAnywhere, Category = "Constraints")
		bool bUseVolumeConstraint = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseVolumeConstraint == true", EditConditionHides), Category = "Constraints")
		float VolumeConstraint = 0.0;

	UPROPERTY(EditAnywhere, Category = "Constraints")
		bool bUseFEMConstraint = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseFEMConstraint == true", EditConditionHides), Category = "Constraints")
		float YoungsModulus = 0.0;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseFEMConstraint == true", EditConditionHides), Category = "Constraints")
		float PossionsRatio = 0.0;

	UPROPERTY(EditAnywhere, Category = "Constraints")
		bool bUseBendConstraint = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseBendConstraint == true", EditConditionHides), Category = "Constraints")
		float BendConstraint = 0.0;

	UPROPERTY(EditAnywhere, Category = "Constraints")
		bool bUseConstantDensityConstraint = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseConstantDensityConstraint == true", EditConditionHides), Category = "Constraints")
		float ConstantDensityConstraint = 0.0;

	UPROPERTY(EditAnywhere, Category = "Constraints")
		bool bUseAreaConstraint = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseAreaConstraint == true", EditConditionHides), Category = "Constraints")
		float AreaConstraint = 0.0;

	//UPROPERTY(EditAnywhere)
	TArray<int> FixedNodes;

	UPROPERTY(EditAnywhere, Category = "Boundaries")
		AActor* BoundaryConditionActor;
	UPROPERTY(EditAnywhere, Category = "Boundaries")
		bool bInverseBoundary;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	/** Initializes the geometry and the PBD model for the deformable model
	* @return None
	*/
	virtual void Init() override;

	/** Updates the mesh's vertices in Unreal to visualize the scene in imstk
	* @return None
	*/
	virtual void UpdateModel();

	// 
	std::shared_ptr<imstk::PbdObject> PbdObject;

	// TODO: Find a way to hide unwanted geometry types when viewing in editor
	virtual void OnRegister() override;

protected:
	UProceduralMeshComponent* MeshComp;
	// Maybe add this to a geometry util class
	void ConvertStaticToProceduralMesh(UStaticMeshComponent* StaticMesh);

	void ProcessBoundaryConditions();
	
public:
	virtual void UnInit() override;
};
