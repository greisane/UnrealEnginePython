// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System.Collections.Generic;

public class UnrealEnginePython : ModuleRules
{
	protected int PythonVersionMajor = 3;
	protected int PythonVersionMinor = 8;

	public string PythonDir
	{
		get
		{
			string folderName = string.Format("Python{0}{1}", PythonVersionMajor, PythonVersionMinor);
			return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/", folderName));
		}
	}

#if WITH_FORWARDED_MODULE_RULES_CTOR
	public UnrealEnginePython(ReadOnlyTargetRules Target) : base(Target)
#else
	public UnrealEnginePython(TargetInfo Target)
#endif
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		string enableUnityBuild = System.Environment.GetEnvironmentVariable("UEP_ENABLE_UNITY_BUILD");
		bUseUnity = string.IsNullOrEmpty(enableUnityBuild);

		PublicIncludePaths.AddRange(new string[] {
			PythonDir,
		});

		PrivateIncludePaths.AddRange(new string[] {
		});

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"Sockets",
			"Networking",
			"Projects",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"CoreUObject",
			"Engine",
			"InputCore",
			"Slate",
			"SlateCore",
			"MovieScene",
			"LevelSequence",
			"HTTP",
			"UMG",
			"AppFramework",
			"RHI",
			"Voice",
			"RenderCore",
			"MovieSceneCapture",
			"Landscape",
			"Foliage",
			"AIModule",
		});

#if WITH_FORWARDED_MODULE_RULES_CTOR
		BuildVersion Version;
		if (BuildVersion.TryRead(BuildVersion.GetDefaultFileName(), out Version))
		{
			if (Version.MinorVersion >= 18)
			{
				PrivateDependencyModuleNames.Add("ApplicationCore");
			}
		}
#endif

#if WITH_FORWARDED_MODULE_RULES_CTOR
		if (Target.bBuildEditor)
#else
		if (UEBuildConfiguration.bBuildEditor)
#endif
		{
			PrivateDependencyModuleNames.AddRange(new string[] {
				"UnrealEd",
				"LevelEditor",
				"BlueprintGraph",
				"Projects",
				"Sequencer",
				"SequencerWidgets",
				"AssetTools",
				"LevelSequenceEditor",
				"MovieSceneTools",
				"MovieSceneTracks",
				"CinematicCamera",
				"EditorStyle",
				"GraphEditor",
				"UMGEditor",
				"AIGraph",
				"RawMesh",
				"DesktopWidgets",
				"EditorWidgets",
				"FBX",
				"Persona",
				"PropertyEditor",
				"LandscapeEditor",
				"MaterialEditor"
			});
		}

		string zipFilename = string.Format("python{0}{1}.zip", PythonVersionMajor, PythonVersionMinor);
		string zipPath = Path.Combine(PythonDir, zipFilename);
		System.Console.WriteLine("Using Python at: " + zipPath);
		RuntimeDependencies.Add(zipPath);
		PublicIncludePaths.Add(PythonDir);

		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			string libFilename = string.Format("python{0}{1}.lib", PythonVersionMajor, PythonVersionMinor);
			string libPath = Path.Combine(PythonDir, "libs", libFilename);
			System.Console.WriteLine("Lib path: " + libPath);
			PublicSystemLibraryPaths.Add(Path.GetDirectoryName(libPath));
			PublicAdditionalLibraries.Add(libPath);

			string dllFilename = string.Format("python{0}{1}.dll", PythonVersionMajor, PythonVersionMinor);
			string dllPath = Path.Combine(PythonDir, "bin", "win64", dllFilename);
			System.Console.WriteLine("Dll path: " + dllPath);
            //PublicDelayLoadDLLs.Add(dllFilename);
			RuntimeDependencies.Add(dllPath);
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			string libFilename = string.Format("libpython{0}.{1}.dylib", PythonVersionMajor, PythonVersionMinor);
			string libPath = Path.Combine(PythonDir, "libs", libFilename);
			System.Console.WriteLine("Lib path: " + libPath);
			PublicSystemLibraryPaths.Add(Path.GetDirectoryName(libPath));
			PublicDelayLoadDLLs.Add(libFilename);
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			string libFilename = string.Format("libpython{0}.{1}.so", PythonVersionMajor, PythonVersionMinor);
			string libPath = Path.Combine(PythonDir, "libs", libFilename);
			System.Console.WriteLine("Lib path: " + libPath);
			PublicAdditionalLibraries.Add(libPath);
		}
#if WITH_FORWARDED_MODULE_RULES_CTOR
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PublicIncludePaths.Add(System.IO.Path.Combine(ModuleDirectory, "../../android/python35/include"));
			PublicSystemLibraryPaths.Add(System.IO.Path.Combine(ModuleDirectory, "../../android/armeabi-v7a"));
			PublicAdditionalLibraries.Add("python3.5m");

			string APLName = "UnrealEnginePython_APL.xml";
			string RelAPLPath = Utils.MakePathRelativeTo(System.IO.Path.Combine(ModuleDirectory, APLName), Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", RelAPLPath);
		}
#endif
	}
}
