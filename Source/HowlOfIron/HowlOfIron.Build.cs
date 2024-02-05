// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HowlOfIron : ModuleRules
{
    public HowlOfIron(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] 
        { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "GameplayAbilities", 
            "GameplayTags", 
            "GameplayTasks", 
            "UMG", 
            "HeadMountedDisplay", 
            "CinematicCamera", 
            "AIModule", 
            "NavigationSystem",
            "Niagara"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { "MediaAssets" });

        PrivateIncludePaths.AddRange(new string[] { "HowlOfIron" });

        //Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            PublicDependencyModuleNames.AddRange(new string[] { "GameplayDebugger" });
        }
    }
}
