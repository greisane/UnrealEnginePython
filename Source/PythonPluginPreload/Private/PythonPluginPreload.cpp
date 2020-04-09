#include "CoreMinimal.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformProcess.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

THIRD_PARTY_INCLUDES_START
// We include this file to get PY_MAJOR_VERSION
// We don't include Python.h as that will trigger a link dependency which we don't want
// as this module exists to pre-load the Python DLLs, so can't link to Python itself
#include <include/patchlevel.h>
THIRD_PARTY_INCLUDES_END

class FPythonPluginPreload : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		auto LoadDll([](const FString& Path) -> void*
			{
				void* Handle = FPlatformProcess::GetDllHandle(*Path);
				if (Handle == nullptr)
				{
					UE_LOG(LogLoad, Fatal, TEXT("Failed to load module '%s'."), *Path);
				}
				return Handle;
			});

		// Load python library
		FString PluginDir = IPluginManager::Get().FindPlugin(TEXT("UnrealEnginePython"))->GetBaseDir();
		FString PythonDir = FString::Printf(TEXT("Python%d%d"), PY_MAJOR_VERSION, PY_MINOR_VERSION);

#if PLATFORM_WINDOWS
		FString DllFilename = FString::Printf(TEXT("python%d%d.dll"), PY_MAJOR_VERSION, PY_MINOR_VERSION);
		FString DllPath = PluginDir / TEXT("ThirdParty") / PythonDir / TEXT("bin/win64") / DllFilename;
		PythonHandle = LoadDll(DllPath);
#elif PLATFORM_LINUX
		FString DllFilename = FString::Printf(TEXT("libpython%d%d.so"), PY_MAJOR_VERSION, PY_MINOR_VERSION);
		FString DllPath = PluginDir / TEXT("ThirdParty") / PythonDir / TEXT("bin/linux") / DllFilename;
		PythonHandle = LoadDll(DllPath);
#endif
	}

	virtual void ShutdownModule() override
	{
		FPlatformProcess::FreeDllHandle(PythonHandle);
	}

private:
	void* PythonHandle = nullptr;
};

IMPLEMENT_MODULE(FPythonPluginPreload, PythonPluginPreload)
