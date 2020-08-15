#include "CoreMinimal.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformProcess.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

THIRD_PARTY_INCLUDES_START
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
		const FString PluginDir = IPluginManager::Get().FindPlugin(TEXT("UnrealEnginePython"))->GetBaseDir();
		const FString PythonDir = FString::Printf(TEXT("Python%d%d"), PY_MAJOR_VERSION, PY_MINOR_VERSION);

#if PLATFORM_WINDOWS
		const FString DllDir = PluginDir / TEXT("ThirdParty") / PythonDir / TEXT("bin/win64");
		const FString DllFilename = FString::Printf(TEXT("python%d%d.dll"), PY_MAJOR_VERSION, PY_MINOR_VERSION);
		PythonHandle = LoadDll(DllDir / DllFilename);
		SqliteHandle = LoadDll(DllDir / TEXT("sqlite3.dll"));
#elif PLATFORM_LINUX
		const FString DllDir = PluginDir / TEXT("ThirdParty") / PythonDir / TEXT("bin/linux");
		const FString DllFilename = FString::Printf(TEXT("libpython%d%d.so"), PY_MAJOR_VERSION, PY_MINOR_VERSION);
		PythonHandle = LoadDll(DllDir / DllFilename);
		SqliteHandle = LoadDll(DllDir / TEXT("sqlite3.dll"));
#endif
	}

	virtual void ShutdownModule() override
	{
		FPlatformProcess::FreeDllHandle(PythonHandle);
		FPlatformProcess::FreeDllHandle(SqliteHandle);
	}

private:
	void* PythonHandle = nullptr;
	void* SqliteHandle = nullptr;
};

IMPLEMENT_MODULE(FPythonPluginPreload, PythonPluginPreload)
