// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Agora : ModuleRules
{
	public Agora(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D" });

		PrivateDependencyModuleNames.AddRange( new string[] { "Slate", "SlateCore" } );
	}
}
