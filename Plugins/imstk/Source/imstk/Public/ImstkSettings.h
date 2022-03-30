// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ImstkSettings.generated.h"

/** \file ImstkSettings.h
 *  \brief Provides settings in editor for imstk
 *  \details Has settings for imstk logging and debugging messages in unreal
 */
UCLASS(config = Game, defaultconfig, Category = "Holds settings for iMSTK")
class IMSTK_API UImstkSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UImstkSettings(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(config, EditAnywhere, Category = "Debugging", meta = (Tooltip = "If true, the iMSTK logger will be written to."))
		bool bLoggerActive = false;
	
	UPROPERTY(config, EditAnywhere, Category = "Debugging", meta = (Tooltip = "If true, debugging information will be provided in Unreal."))
		bool bDebuggingActive = false;

public:
	static bool IsDebugging();
	static bool IsLoggerActive();
};
