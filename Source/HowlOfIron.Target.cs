// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class HowlOfIronTarget : TargetRules
{
    public HowlOfIronTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange(new string[] { "HowlOfIron" });

        if ((Target.Configuration != UnrealTargetConfiguration.Shipping))
        {
            ExtraModuleNames.Add("GameplayDebugger");
        }
    }
}
