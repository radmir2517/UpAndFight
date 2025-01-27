// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UpAndFight : ModuleRules
{
	public UpAndFight(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" });
        PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "GameplayTasks" });
    }
}
