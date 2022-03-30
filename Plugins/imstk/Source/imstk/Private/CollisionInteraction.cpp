// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionInteraction.h"

CollisionInteractionType UCollisionInteraction::GetAutoCollisionType() 
{
	std::shared_ptr<imstk::Geometry> Geom1 = Model1->GetCollidingGeometry();
	std::shared_ptr<imstk::Geometry> Geom2 = Model2->GetCollidingGeometry();
	
	// Cast both models to determine what types they are and return the corresponding CollisionInteractionType for each combination of imstk geometries 
	if (std::dynamic_pointer_cast<imstk::Sphere>(Geom1) && std::dynamic_pointer_cast<imstk::Sphere>(Geom2)) {
		return CollisionInteractionType::SphereToSphereCD;
	}
	else if ((std::dynamic_pointer_cast<imstk::Sphere>(Geom1) && std::dynamic_pointer_cast<imstk::SurfaceMesh>(Geom2)) || 
		(std::dynamic_pointer_cast<imstk::SurfaceMesh>(Geom1) && std::dynamic_pointer_cast<imstk::Sphere>(Geom2))){
		return CollisionInteractionType::SurfaceMeshToSphereCD;
	}
	else if ((std::dynamic_pointer_cast<imstk::SurfaceMesh>(Geom1) && std::dynamic_pointer_cast<imstk::SurfaceMesh>(Geom2)) ||
		(std::dynamic_pointer_cast<imstk::PointSet>(Geom1) && std::dynamic_pointer_cast<imstk::SurfaceMesh>(Geom2)) ||
		(std::dynamic_pointer_cast<imstk::SurfaceMesh>(Geom1) && std::dynamic_pointer_cast<imstk::PointSet>(Geom2))) {
		return CollisionInteractionType::MeshToMeshBruteForceCD;
	}
	else if ((std::dynamic_pointer_cast<imstk::PointSet>(Geom1) && std::dynamic_pointer_cast<imstk::Sphere>(Geom2)) ||
		(std::dynamic_pointer_cast<imstk::Sphere>(Geom1) && std::dynamic_pointer_cast<imstk::PointSet>(Geom2)))  {
		return CollisionInteractionType::PointSetToSphereCD;
	}
	else if ((std::dynamic_pointer_cast<imstk::PointSet>(Geom1) && std::dynamic_pointer_cast<imstk::Capsule>(Geom2)) ||
		(std::dynamic_pointer_cast<imstk::Capsule>(Geom1) && std::dynamic_pointer_cast<imstk::PointSet>(Geom2))) {
		return CollisionInteractionType::PointSetToCapsuleCD;
	}
	else {
		// Print an error if there is no type found and return Auto
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "ERROR COULD NOT FIND COLLISION TYPE");
	}

	return CollisionInteractionType::Auto;
}

void UCollisionInteraction::Init() 
{
	if (Model1 == nullptr || Model2 == nullptr)
		return;

	// Determine the collision type if set to auto
	if (CollisionType == CollisionInteractionType::Auto)
		CollisionType = GetAutoCollisionType();

	// If GetAutoCollisionType returns Auto, then collision type was not found. Therefore return
	if (CollisionType == CollisionInteractionType::Auto)
		return;

	// Create interaction and add to scene
	UImstkSubsystem* SubsystemInstance = GetWorld()->GetGameInstance()->GetSubsystem<UImstkSubsystem>();
	std::shared_ptr<imstk::CollisionInteraction> Interaction;
	if (Cast<URBDModel>(Model1) && Cast<URBDModel>(Model2))
	{
		Interaction = std::make_shared<imstk::RigidObjectCollision>(std::dynamic_pointer_cast<imstk::RigidObject2>(Model1->ImstkCollidingObject), std::dynamic_pointer_cast<imstk::RigidObject2>(Model2->ImstkCollidingObject), std::string(TCHAR_TO_UTF8(*UEnum::GetValueAsString(CollisionType))));
	}
	else if (Cast<URBDModel>(Model1) && Cast<UStaticModel>(Model2)) 
	{
		Interaction = std::make_shared<imstk::RigidObjectCollision>(std::dynamic_pointer_cast<imstk::RigidObject2>(Model1->ImstkCollidingObject), Model2->ImstkCollidingObject, std::string(TCHAR_TO_UTF8(*UEnum::GetValueAsString(CollisionType))));
	}
	else if (Cast<UStaticModel>(Model1) && Cast<URBDModel>(Model2))
	{
		Interaction = std::make_shared<imstk::RigidObjectCollision>(std::dynamic_pointer_cast<imstk::RigidObject2>(Model2->ImstkCollidingObject), Model1->ImstkCollidingObject, std::string(TCHAR_TO_UTF8(*UEnum::GetValueAsString(CollisionType))));
	}
	else if (Cast<UDeformableModel>(Model1) && Cast<UDeformableModel>(Model2))
	{
		Interaction = std::make_shared<imstk::PbdObjectCollision>(std::dynamic_pointer_cast<imstk::PbdObject>(Model1->ImstkCollidingObject), std::dynamic_pointer_cast<imstk::PbdObject>(Model2->ImstkCollidingObject), std::string(TCHAR_TO_UTF8(*UEnum::GetValueAsString(CollisionType))));
	}
	else if (Cast<UDeformableModel>(Model1) && (Cast<UStaticModel>(Model2) || Cast<URBDModel>(Model2)))
	{
		Interaction = std::make_shared<imstk::PbdObjectCollision>(std::dynamic_pointer_cast<imstk::PbdObject>(Model1->ImstkCollidingObject), Model2->ImstkCollidingObject, std::string(TCHAR_TO_UTF8(*UEnum::GetValueAsString(CollisionType))));
	}
	else if ((Cast<UStaticModel>(Model1) || Cast<URBDModel>(Model1)) && Cast<UDeformableModel>(Model2))
	{
		Interaction = std::make_shared<imstk::PbdObjectCollision>(std::dynamic_pointer_cast<imstk::PbdObject>(Model2->ImstkCollidingObject), Model1->ImstkCollidingObject, std::string(TCHAR_TO_UTF8(*UEnum::GetValueAsString(CollisionType))));
	}
	else if (Cast<UDeformableModel>(Model1) && Cast<URBDModel>(Model2))
	{
		//Interaction = std::make_shared<imstk::PbdObjectCollision>(std::dynamic_pointer_cast<imstk::PbdObject>(Model1->ImstkCollidingObject), std::dynamic_pointer_cast<imstk::PbdObject>(Model2->ImstkCollidingObject), std::string(TCHAR_TO_UTF8(*UEnum::GetValueAsString(CollisionType))));
	}
	else if (Cast<URBDModel>(Model1) && Cast<UDeformableModel>(Model2))
	{

	}
	else {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Error Initializing: " + FString(Model1->ImstkCollidingObject->getName().c_str()) + " " + Model2->ImstkCollidingObject->getName().c_str());
		return;
	}

	// Set parameters of the interaction

	if (std::shared_ptr<imstk::RigidObjectCollision> RBDInteraction = std::dynamic_pointer_cast<imstk::RigidObjectCollision>(Interaction))
	{
		RBDInteraction->setFriction(Friction);
		RBDInteraction->setStiffness(Stiffness);
	}
	else if (std::shared_ptr<imstk::PbdObjectCollision> PBDInteraction = std::dynamic_pointer_cast<imstk::PbdObjectCollision>(Interaction)) 
	{
		PBDInteraction->setFriction(Friction);
		PBDInteraction->setRestitution(0);
	}


	SubsystemInstance->ActiveScene->addInteraction(Interaction);

	//if (GEngine)
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Interaction Initialized: " + FString(Model1->ImstkCollidingObject->getName().c_str()) + " " + Model2->ImstkCollidingObject->getName().c_str());
}