// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System.Collections.Generic;

public class imstk : ModuleRules {
    public imstk(ReadOnlyTargetRules Target) : base(Target) {
        bUseRTTI = true;
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
            }
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                //"Engine",
                //"Projects",
                "ImstkAPI"
				// ... add other public dependencies that you statically link with here ...
			}
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "ImstkAPI",
                "DeveloperSettings",
                "PropertyEditor",
                "UnrealEd",
                "ProceduralMeshComponent",
                "RawMesh"
				// ... add private dependencies that you statically link with here ...	
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );

        if (UnrealTargetPlatform.Win32 == Target.Platform || UnrealTargetPlatform.Win64 == Target.Platform) //decide the platform to package the binaries
        {
            string ProjRedistFolder = Path.Combine(ModuleDirectory, @"..\ThirdParty\ImstkAPI\lib\");

            List<string> RuntimeModuleNames = new List<string>();

            DirectoryInfo d = new DirectoryInfo(ProjRedistFolder);
            FileInfo[] dllFiles = d.GetFiles("*.dll");

            foreach (FileInfo file in dllFiles) {
                RuntimeModuleNames.Add(file.Name);
            }


            foreach (string RuntimeModuleName in RuntimeModuleNames) {
                string ModulePath = Path.Combine(ProjRedistFolder, RuntimeModuleName);
                if (!File.Exists(ModulePath)) {
                    string Err = string.Format("PROJ SDK module '{0}' not found.", ModulePath);
                    System.Console.WriteLine(Err);
                    throw new BuildException(Err);
                }
                RuntimeDependencies.Add("$(BinaryOutputDir)/" + RuntimeModuleName, ModulePath);
            }

            // Stage Proj data files
            RuntimeDependencies.Add("$(BinaryOutputDir)/proj-data/*", Path.Combine(ProjRedistFolder, "proj-data/*"), StagedFileType.SystemNonUFS);
        }
    }
}
