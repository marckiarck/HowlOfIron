// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class HowlOfIronEditorTarget : TargetRules
{
    public HowlOfIronEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange(new string[] { "HowlOfIron", "HowlOfIronEditor" });

        if ((Target.Configuration != UnrealTargetConfiguration.Shipping))
        {
            ExtraModuleNames.Add("GameplayDebugger");
        }
    }
}
