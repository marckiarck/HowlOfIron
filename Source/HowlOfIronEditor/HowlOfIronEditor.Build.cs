// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HowlOfIronEditor : ModuleRules
{
    public HowlOfIronEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayAbilities", "GameplayTags", "GameplayTasks", "UMG", "HeadMountedDisplay", "CinematicCamera", "AIModule", "NavigationSystem" });

        PublicDependencyModuleNames.Add("HowlOfIron");

        PrivateIncludePaths.AddRange(new string[] { "HowlOfIronEditor" });

        PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "XmlParser", "EditorStyle", "GraphEditor", "AppFramework", "PropertyEditor" });

        //Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
