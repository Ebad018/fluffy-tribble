// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ai_Assignment : ModuleRules
{
	public Ai_Assignment(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"GameplayTasks",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Ai_Assignment",
			"Ai_Assignment/Variant_Platforming",
			"Ai_Assignment/Variant_Platforming/Animation",
			"Ai_Assignment/Variant_Combat",
			"Ai_Assignment/Variant_Combat/AI",
			"Ai_Assignment/Variant_Combat/Animation",
			"Ai_Assignment/Variant_Combat/Gameplay",
			"Ai_Assignment/Variant_Combat/Interfaces",
			"Ai_Assignment/Variant_Combat/UI",
			"Ai_Assignment/Variant_SideScrolling",
			"Ai_Assignment/Variant_SideScrolling/AI",
			"Ai_Assignment/Variant_SideScrolling/Gameplay",
			"Ai_Assignment/Variant_SideScrolling/Interfaces",
			"Ai_Assignment/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
