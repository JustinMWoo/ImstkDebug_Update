// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

//#include "Tickable.h"
#include "Engine/GameEngine.h"
#include "ImstkSettings.h"
#include "ImstkBehaviour.h"
#include "ImstkInteraction.h"
#include "MathUtil.h"

//#include "iMSTK-5.0/imstkSphere.h"
//#include "iMSTK-5.0/imstkPlane.h"
#include "iMSTK-5.0/imstkSceneManager.h"
#include "iMSTK-5.0/imstkRigidBodyModel2.h"
//#include "iMSTK-5.0/imstkRigidObject2.h"
//#include "iMSTK-5.0/imstkPbdObject.h"
//#include "iMSTK-5.0/imstkPbdModel.h"


//#include "iMSTK-5.0/imstkSceneObject.h"
#include "iMSTK-5.0/imstkScene.h"
#include "iMSTK-5.0/imstkSimulationManager.h"
//#include "iMSTK-5.0/imstkDynamicObject.h"
#include "iMSTK-5.0/imstkLogger.h"

#include "ImstkSubsystem.generated.h"

struct FImstkSubsystemTickFunction : public FTickFunction 
{
	UImstkSubsystem* Owner;
	virtual void ExecuteTick(float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;
};


/** \file ImstkSubsystem.h
 *  \brief Subsystem to manage and initialize Imstk.
 *  \details Creates the Imstk scene manager, scene and rigidbody model as well as initializing all imstk behaviours assigned in Unreal. 
 */
UCLASS()
class IMSTK_API UImstkSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	/** Default constructor.
	* @return None
	*/
	UImstkSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Function to initialize required managers for Imstk and then initialize all Imstk behaviours.
	* @return None
	*/
	UFUNCTION(BlueprintCallable, Category = "iMSTKSubsystem")
		void ImstkInit();

	UFUNCTION(BlueprintCallable, Category = "iMSTKSubsystem")
		void ImstkTest();

	FImstkSubsystemTickFunction TickFunction;
	/*
	// From FTickableGameObject
	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickableInEditor() const {
		return false;
	}
	virtual TStatId GetStatId() const override;
	*/

	/** Updates the scene and progresses by the amount of time provided
	* @param DeltaTime - The amount of time to progress the scene
	* @return None
	*/
	void Update(float DeltaTime);

private:
	bool bIsCreateOnRunning = false;

	// Used to tick the Subsystem only if system is initialized properly
	bool bIsInitialized = false;

public:
	// Required for Imstk's Scene and interactions
	std::shared_ptr<imstk::SceneManager> SceneManager;
	std::shared_ptr<imstk::RigidBodyModel2> RigidBodyModel;
	std::shared_ptr<imstk::Scene> ActiveScene;

	// Values to be set as defaults in the manager for imstk
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "General")
		int RigidBodyMaxIterations;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "General")
		FVector Gravity;

	// All ImstkBehaviours attached to objects in Unreal, used to initialize the objects
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "General")
		TArray<UImstkBehaviour*> AllBehaviours;

	// All ImstkInteractions in Unreal, used to initialize the imstk interactions between objects
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "General")
		TArray<UImstkInteraction*> AllInteractions;


	virtual void Deinitialize() override;

	bool TEMP = false;
};
