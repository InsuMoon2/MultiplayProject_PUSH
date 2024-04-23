// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Push : ModuleRules
{
	public Push(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Slate", "SlateCore", "Niagara", "UMG", "PhysicsCore", "OnlineSubsystem", "OnlineSubsystemUtils",
		});
	}
}
