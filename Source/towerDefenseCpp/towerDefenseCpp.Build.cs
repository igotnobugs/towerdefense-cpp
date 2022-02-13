// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class towerDefenseCpp : ModuleRules
{
	public towerDefenseCpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "UMG" });
    }
}
