using UnrealBuildTool;
using System.IO;
using System.Collections.Generic;

public class PythonPluginPreload : ModuleRules
{
	public string PythonDir
	{
		get
		{
			return Path.GetFullPath(Path.Combine(ModuleDirectory, UnrealEnginePython.PythonRelativeDir));
		}
	}

	public PythonPluginPreload(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"Projects",
		});

		PublicIncludePaths.Add(PythonDir);
	}
}

