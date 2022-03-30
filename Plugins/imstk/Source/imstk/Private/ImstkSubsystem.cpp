// Fill out your copyright notice in the Description page of Project Settings.


#include "ImstkSubsystem.h"

#include "iMSTK-5.0/imstkNew.h"
#include "iMSTK-5.0/imstkSurfaceMesh.h"

void FImstkSubsystemTickFunction::ExecuteTick(float DeltaTime, enum ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
{
	check(Owner);
	//Owner->Update(DeltaTime);
}



UImstkSubsystem::UImstkSubsystem() {
	bIsCreateOnRunning = GIsRunning;
}

void UImstkSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	TickFunction.bCanEverTick = true;
	TickFunction.Owner = this;
	TickFunction.RegisterTickFunction(GetWorld()->GetCurrentLevel());
}


void UImstkSubsystem::ImstkInit() {
	// TODO: Maybe dont need scenemanager at all
	SceneManager = std::make_shared<imstk::SceneManager>();
	ActiveScene = std::make_shared<imstk::Scene>("Active Scene");
	RigidBodyModel = std::make_shared<imstk::RigidBodyModel2>();
	// TODO: task graph file path can not be accessed from the scene itself (unless theres some way i dont know about) so it will be in the engine files for unreal
	ActiveScene->getConfig()->writeTaskGraph = true;

	// Set up rigid body model using variables set in editor
	RigidBodyModel->getConfig()->m_gravity = UMathUtil::ToImstkVec3(Gravity);
	RigidBodyModel->getConfig()->m_maxNumIterations = RigidBodyMaxIterations;
	RigidBodyModel->getConfig()->m_dt = 0.01;

	if (UImstkSettings::IsLoggerActive()) {
		//imstk::Logger::startLogger();
		imstk::Logger::getInstance().addFileSink("simulation", std::string(TCHAR_TO_UTF8(*FPaths::ProjectLogDir())));
	}


	// Initialize behaviours (models, etc) and interactions after (collisions)
	for (UImstkBehaviour* Behaviour : AllBehaviours)
	{
		Behaviour->Init();
	}
	for (UImstkInteraction* Interaction : AllInteractions)
	{
		Interaction->Init();
	}

	bIsInitialized = true;
	/*if (UImstkSettings::IsDebugging()) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Subsystem Initialized"));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Objects in Imstk scene: "));
			std::unordered_set<std::shared_ptr<imstk::SceneObject>> objects = ActiveScene->getSceneObjects();

			for (auto obj : objects) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString(obj->getName().c_str()) + " ");
			}
		}
	}*/

	// Set up scene manager
	SceneManager->setActiveScene(ActiveScene);

	SceneManager->init();
	SceneManager->pause();
}

void UImstkSubsystem::Update(float DeltaTime) {
	// Set the delta time for the rigid body model and progress the scene by that amount using the Unreal time since last update
	RigidBodyModel->getConfig()->m_dt = DeltaTime;
	SceneManager->getActiveScene()->advance(DeltaTime);
	// TODO: May need to put each pbd model in here to set deltatime
}

void UImstkSubsystem::Deinitialize()
{
	/*
	for (UImstkInteraction* Interaction : AllInteractions) {
		Interaction->UnInit();
	}
	for (UImstkBehaviour* Behaviour : AllBehaviours) {
		Behaviour->UnInit();
	}
	AllInteractions.Empty();
	AllBehaviours.Empty();
	SceneManager->uninit();
	imstk::Logger::getInstance().destroy();

	SceneManager.reset();
	RigidBodyModel.reset();
	ActiveScene.reset();
	*/
}


void UImstkSubsystem::ImstkTest()
{
	imstk::Logger::getInstance().addFileSink("simulation", std::string(TCHAR_TO_UTF8(*FPaths::ProjectLogDir())));
	//std::shared_ptr<imstk::SurfaceMesh> clothMesh = std::make_shared<imstk::SurfaceMesh>();
	imstk::SurfaceMesh* clothMesh = new imstk::SurfaceMesh();

	std::shared_ptr<imstk::VecDataArray<double, 3>> verticesPtr = std::make_shared<imstk::VecDataArray<double, 3>>(16 * 16);
	imstk::VecDataArray<double, 3>& vertices = *verticesPtr.get();
	const double                      dy = 10 / (16 - 1);
	const double                      dx = 10 / (16 - 1);
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; j++)
		{
			vertices[i * 16 + j] = imstk::Vec3d(dx * static_cast<double>(i), 1.0, dy * static_cast<double>(j));
		}
	}

	// Add connectivity data
	std::shared_ptr<imstk::VecDataArray<int, 3>> indicesPtr = std::make_shared<imstk::VecDataArray<int, 3>>();
	imstk::VecDataArray<int, 3>& indices = *indicesPtr.get();
	for (int i = 0; i < 16 - 1; i++)
	{
		for (int j = 0; j < 16 - 1; j++)
		{
			const int index1 = i * 16 + j;
			const int index2 = index1 + 16;
			const int index3 = index1 + 1;
			const int index4 = index2 + 1;

			// Interleave [/][\]
			if (i % 2 ^ j % 2)
			{
				indices.push_back(imstk::Vec3i(index1, index2, index3));
				indices.push_back(imstk::Vec3i(index4, index3, index2));
			}
			else
			{
				indices.push_back(imstk::Vec3i(index2, index4, index1));
				indices.push_back(imstk::Vec3i(index4, index3, index1));
			}
		}
	}

	std::shared_ptr<imstk::VecDataArray<float, 2>> uvCoordsPtr = std::make_shared<imstk::VecDataArray<float, 2>>(16 * 16);
	imstk::VecDataArray<float, 2>& uvCoords = *uvCoordsPtr.get();
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; j++)
		{
			uvCoords[i * 16 + j] = imstk::Vec2f(static_cast<float>(i) / 16, static_cast<float>(j) / 16) * 2;
		}
	}

	clothMesh->initialize(verticesPtr, indicesPtr);
	clothMesh->setVertexTCoords("uvs", uvCoordsPtr);
	//std::shared_ptr<imstk::VecDataArray<int, 3>> Test = clothMesh->getTriangleIndices();
	clothMesh->setTriangleIndices(indicesPtr);
	
	LOG(WARNING) << clothMesh->getTriangleIndices()->size();

	// Raw pointer works if setting triangle indices again
	// Using smart pointer: can get the size if setting triangle indices but crashes when deleting
	// Using no pointer: can get size if setting triangle indices but crashes when deleting
	// Using unreal pointer: can get size if setting triangle indices but crashes when deleting
}