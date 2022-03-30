// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ImstkBehaviour.h"
#include "GeometryFilter.h"
#include "ImstkSubsystem.h"
#include "iMSTK-5.0/imstkCollidingObject.h"
#include "DynamicalModel.generated.h"

/** \file DynamicalModel.h
 *  \brief Abstract class to model any object that is added to the Imstk scene
 *  \details Contains a geometry filter to convert between Unreal and Imstk objects
 */
UCLASS(Abstract)
class IMSTK_API UDynamicalModel : public UImstkBehaviour
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "General")
		FGeometryFilter GeomFilter;

	/** Creates and returns the geometry of the model
	* @return std::shared_ptr<imstk::Geometry> - The colliding geometry created by the Geometry filter
	*/
	std::shared_ptr<imstk::Geometry> GetCollidingGeometry();

	// The colliding object created and assigned in child classes
	std::shared_ptr<imstk::CollidingObject> ImstkCollidingObject;

	virtual void InitializeComponent() override;


protected:
	// References to the owning object and imstk subsystem
	AActor* Owner;
	UImstkSubsystem* SubsystemInstance;
	// Cached geometry for when GetCollidingGeometry is called
	std::shared_ptr<imstk::Geometry> Geometry;
	bool bIsGeomCreated = false;

public:
	virtual void UnInit() override;
};
