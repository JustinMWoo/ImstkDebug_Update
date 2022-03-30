// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicalModel.h"

void UDynamicalModel::InitializeComponent()
{
	Super::InitializeComponent();

	// Set variables to use during execution
	Owner = GetOwner();
	UStaticMeshComponent* MeshComp = (UStaticMeshComponent*)Owner->GetComponentByClass(UStaticMeshComponent::StaticClass());

	if (MeshComp)
		MeshComp->SetMobility(EComponentMobility::Type::Movable);
	Owner->SetActorEnableCollision(false);
	if (GetWorld()) {
		SubsystemInstance = GetWorld()->GetGameInstance()->GetSubsystem<UImstkSubsystem>();
	}
	else {
		// ERROR
	}
}

// TODO: change some of the naming (confusing to call it getcollidinggeometry when it returns geometry and not colliding object, etc)
std::shared_ptr<imstk::Geometry> UDynamicalModel::GetCollidingGeometry()
{
	// If already created return cached value
	if (bIsGeomCreated)
		return Geometry;

	// Initialize imstk geometry
	bIsGeomCreated = true;
	Geometry = GeomFilter.Init(Owner);
	return Geometry;

}

void UDynamicalModel::UnInit()
{
	Super::UnInit();
	Geometry.reset();
	ImstkCollidingObject.reset();
}
