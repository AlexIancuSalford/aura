// Copywright AI

using UnrealBuildTool;
using System.Collections.Generic;

public class AuraEditorTarget : TargetRules
{
	public AuraEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		CppCompileWarningSettings.UndefinedIdentifierWarningLevel = WarningLevel.Error;

		ExtraModuleNames.AddRange( new string[] { "Aura" } );
	}
}
