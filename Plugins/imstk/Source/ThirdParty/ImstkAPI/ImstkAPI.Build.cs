// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class ImstkAPI : ModuleRules
{
    public ImstkAPI(ReadOnlyTargetRules Target) : base(Target) {
        bUseRTTI = true;
        Type = ModuleType.External;

        if (Target.Platform == UnrealTargetPlatform.Win64) {
            // add include path
            string PlatformDir = Target.Platform.ToString();
            string IncPath = Path.Combine(ModuleDirectory, "include");
            PublicSystemIncludePaths.Add(IncPath);
            IncPath = Path.Combine(ModuleDirectory, "include/eigen3");
            PublicSystemIncludePaths.Add(IncPath);

            string LibPath = Path.Combine(ModuleDirectory, "lib");
            DirectoryInfo d = new DirectoryInfo(LibPath);
            FileInfo[] Files = d.GetFiles("*.lib");

            foreach (FileInfo file in Files) {
                PublicAdditionalLibraries.Add(Path.Combine(LibPath, file.Name));
            }


        }
    }
}
