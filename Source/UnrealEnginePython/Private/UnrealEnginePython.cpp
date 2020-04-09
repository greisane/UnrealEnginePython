// Copyright 20Tab S.r.l.

#include "UnrealEnginePython.h"
#include "UEPyModule.h"
#include "PythonBlueprintFunctionLibrary.h"
#include "HAL/IConsoleManager.h"
#include "HAL/PlatformFilemanager.h"
#include "HAL/FileManagerGeneric.h"
#include "Misc/App.h"
#include "Misc/CommandLine.h"
#include "Misc/ConfigCacheIni.h"
//#include "Runtime/Core/Public/GenericPlatform/GenericPlatformFile.h"
//#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMisc.h"
#include <locale.h>

#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

#if ENGINE_MINOR_VERSION >= 18
#define PROJECT_CONTENT_DIR FPaths::ProjectContentDir()
#else
#define PROJECT_CONTENT_DIR FPaths::GameContentDir()
#endif

#if PLATFORM_WINDOWS
#include <fcntl.h>
#endif
#if PLATFORM_MAC
#include "Runtime/Core/Public/Mac/CocoaThread.h"
#endif
#if PLATFORM_LINUX
const char* ue4_module_options = "linux_global_symbols";
#endif
#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

void unreal_engine_init_py_module();
void init_unreal_engine_builtin();

const char *UEPyUnicode_AsUTF8(PyObject *py_str)
{
#if PY_MAJOR_VERSION < 3
	if (PyUnicode_Check(py_str))
	{
		PyObject *unicode = PyUnicode_AsUTF8String(py_str);
		if (unicode)
		{
			return PyString_AsString(unicode);
		}
		// just a hack to avoid crashes
		return (char *)"<invalid_string>";
	}
	return (const char *)PyString_AsString(py_str);
#elif PY_MINOR_VERSION < 7
	return (const char *)PyUnicode_AsUTF8(py_str);
#else
	return PyUnicode_AsUTF8(py_str);
#endif
}

#if PY_MAJOR_VERSION < 3
int PyGILState_Check()
{
	PyThreadState * tstate = _PyThreadState_Current;
	return tstate && (tstate == PyGILState_GetThisThreadState());
}
#endif

bool PyUnicodeOrString_Check(PyObject *py_obj)
{
	if (PyUnicode_Check(py_obj))
	{
		return true;
	}
#if PY_MAJOR_VERSION < 3
	else if (PyString_Check(py_obj))
	{
		return true;
	}
#endif
	return false;
}

#define SCRIPTS_FOLDER "Python"
#define TEXT_SCRIPTS_FOLDER TEXT(SCRIPTS_FOLDER)

#define LOCTEXT_NAMESPACE "FUnrealEnginePythonModule"

void FUnrealEnginePythonModule::UESetupPythonInterpreter(bool verbose)
{
	const TCHAR* CommandLine = FCommandLine::GetOriginal();
	const SIZE_T CommandLineSize = FCString::Strlen(CommandLine) + 1;
	TCHAR* CommandLineCopy = new TCHAR[CommandLineSize];
	FCString::Strcpy(CommandLineCopy, CommandLineSize, CommandLine);
	const TCHAR* ParsedCmdLine = CommandLineCopy;

	TArray<FString> Args;
	for (;;)
	{
		FString Arg = FParse::Token(ParsedCmdLine, 0);
		if (Arg.Len() <= 0)
			break;
		Args.Add(Arg);
	}

#if PY_MAJOR_VERSION >= 3
	wchar_t **argv = (wchar_t **)FMemory::Malloc(sizeof(wchar_t *) * (Args.Num() + 1));
#else
	char **argv = (char **)FMemory::Malloc(sizeof(char *) * (Args.Num() + 1));
#endif
	argv[Args.Num()] = nullptr;

	for (int32 i = 0; i < Args.Num(); i++)
	{
#if PY_MAJOR_VERSION >= 3
	#if ENGINE_MINOR_VERSION >= 20
		argv[i] = (wchar_t *)(TCHAR_TO_WCHAR(*Args[i]));
	#else
		argv[i] = (wchar_t *)(*Args[i]);
	#endif
#else
		argv[i] = TCHAR_TO_UTF8(*Args[i]);
#endif
	}

	PySys_SetArgv(Args.Num(), argv);

	if (verbose)
	{
		UE_LOG(LogPython, Log, TEXT("Python VM initialized: %s"), UTF8_TO_TCHAR(Py_GetVersion()));
	}
}

static void setup_stdout_stderr()
{
	// Redirecting stdout
	char const* code = "import sys\n"
		"import unreal_engine\n"
		"class UnrealEngineOutput:\n"
		"    def __init__(self, logger):\n"
		"        self.logger = logger\n"
		"    def write(self, buf):\n"
		"        self.logger(buf)\n"
		"    def flush(self):\n"
		"        return\n"
		"    def isatty(self):\n"
		"        return False\n"
		"sys.stdout = UnrealEngineOutput(unreal_engine.log)\n"
		"sys.stderr = UnrealEngineOutput(unreal_engine.log_error)\n"
		"\n"
		"class event:\n"
		"    def __init__(self, event_signature):\n"
		"        self.event_signature = event_signature\n"
		"    def __call__(self, f):\n"
		"        f.ue_event = self.event_signature\n"
		"        return f\n"
		"\n"
		"unreal_engine.event = event";
	PyRun_SimpleString(code);
}

static void setup_importlib()
{
	char const* code = "import sys\n"
		"import importlib\n"
		"import importlib.machinery\n"
		"import importlib.util\n"
		"import unreal_engine\n"
		"\n"
		"class UFSFileFinder:\n"
		"    def __init__(self, path, *loader_details):\n"
		"        loaders = []\n"
		"        for loader, suffixes in loader_details:\n"
		"            loaders.extend((suffix, loader) for suffix in suffixes)\n"
		"        self._loaders = loaders\n"
		"        self.path = path or '.' # Base (directory) path\n"
		"        self._path_cache = None\n"
		"    def invalidate_caches(self):\n"
		"        self._path_cache = None\n"
		"    def _get_spec(self, loader_class, fullname, path, smsl, target):\n"
		"        loader = loader_class(fullname, path)\n"
		"        return importlib.util.spec_from_file_location(fullname, path, loader=loader, submodule_search_locations=smsl)\n"
		"    def find_spec(self, fullname, target=None):\n"
		"        print(f'UFSFileFinder.find_spec: {fullname} {target}')\n"
		"        is_namespace = False\n"
		"        tail_module = fullname.rpartition('.')[2]\n"
		"        if self._path_cache == None:\n"
		"            self._fill_cache()\n"
		"        # Check if the module is the name of a directory (and thus a package)\n"
		"        if tail_module in self._path_cache:\n"
		"            base_path = self.path + '/' + tail_module\n"
		"            for suffix, loader_class in self._loaders:\n"
		"                full_path = base_path + '/__init__' + suffix\n"
		"                if unreal_engine.file_exists(full_path):\n"
		"                    return self._get_spec(loader_class, fullname, full_path, [base_path], target)\n"
		"            else:\n"
		"                # If a namespace package, return the path if we don't find a module in the next section\n"
		"                is_namespace = unreal_engine.directory_exists(base_path)\n"
		"        # Check for a file w/ a proper suffix exists\n"
		"        for suffix, loader_class in self._loaders:\n"
		"            full_path = self.path + '/' + tail_module + suffix\n"
		"            unreal_engine.log(f'trying {full_path}')\n"
		"            if tail_module + suffix in self._path_cache:\n"
		"                if unreal_engine.file_exists(full_path):\n"
		"                    return self._get_spec(loader_class, fullname, full_path, None, target)\n"
		"        if is_namespace:\n"
		"            unreal_engine.log(f'possible namespace for {base_path}')\n"
		"            spec = importlib.machinery.ModuleSpec(fullname, None)\n"
		"            spec.submodule_search_locations = [base_path]\n"
		"            return spec\n"
		"        return None\n"
		"    def _fill_cache(self):\n"
		"        self._path_cache = set(unreal_engine.find_files(self.path + '/*'))\n"
		"    @classmethod\n"
		"    def path_hook(cls, *loader_details):\n"
		"        def path_hook_for_UFSFileFinder(path):\n"
		"            # if not _path_isdir(path):\n"
		"            #     raise ImportError('only directories are supported', path=path)\n"
		"            return cls(path, *loader_details)\n"
		"        return path_hook_for_UFSFileFinder\n"
		"    def __repr__(self):\n"
		"        return 'UFSFileFinder({!r})'.format(self.path)\n"
		"\n"
		"class UFSFileLoader:\n"
		"    def path_mtime(self, path):\n"
		"        raise OSError\n"
		"    def get_data(self, path):\n"
		"        unreal_engine.log(f'{self.__class__.__name__}.get_data: {path}')\n"
		"        return unreal_engine.load_bytes(path)\n"
		"\n"
		"class UFSSourceFileLoader(UFSFileLoader, importlib.machinery.SourceFileLoader):\n"
		"    pass\n"
		"\n"
		"class UFSSourcelessFileLoader(UFSFileLoader, importlib.machinery.SourcelessFileLoader):\n"
		"    pass\n"
		"\n"
		"def _get_supported_file_loaders():\n"
		"    source = UFSSourceFileLoader, importlib.machinery.SOURCE_SUFFIXES\n"
		"    bytecode = UFSSourcelessFileLoader, importlib.machinery.BYTECODE_SUFFIXES\n"
		"    return [source, bytecode]\n"
		"sys.path_hooks = [UFSFileFinder.path_hook(*_get_supported_file_loaders())]\n"
		"sys.path.append(unreal_engine.get_content_dir() + '" SCRIPTS_FOLDER "')\n";
	
	PyRun_SimpleString(code);
}

namespace
{
	static void consoleExecScript(const TArray<FString>& Args)
	{
		if (Args.Num() != 1)
		{
			UE_LOG(LogPython, Display, TEXT("Usage: 'py.exec <scriptname>'."));
			UE_LOG(LogPython, Display, TEXT("  scriptname: Name of script, must reside in " TEXT_SCRIPTS_FOLDER " folder. Ex: myscript.py"));
		}
		else
		{
			UPythonBlueprintFunctionLibrary::ExecutePythonScript(Args[0]);
		}
	}

	static void consoleExecString(const TArray<FString>& Args)
	{
		if (Args.Num() == 0)
		{
			UE_LOG(LogPython, Display, TEXT("Usage: 'py.cmd <command string>'."));
			UE_LOG(LogPython, Display, TEXT("  scriptname: Name of script, must reside in " TEXT_SCRIPTS_FOLDER " folder. Ex: myscript.py"));
		}
		else
		{
			FString cmdString;
			for (const FString& argStr : Args)
			{
				cmdString += argStr.TrimQuotes() + '\n';
			}
			UPythonBlueprintFunctionLibrary::ExecutePythonString(cmdString);
		}
	}
}

FAutoConsoleCommand ExecPythonScriptCommand(
	TEXT("py.exec"),
	*NSLOCTEXT("UnrealEnginePython", "CommandText_Exec", "Execute python script").ToString(),
	FConsoleCommandWithArgsDelegate::CreateStatic(consoleExecScript));

FAutoConsoleCommand ExecPythonStringCommand(
	TEXT("py.cmd"),
	*NSLOCTEXT("UnrealEnginePython", "CommandText_Cmd", "Execute python string").ToString(),
	FConsoleCommandWithArgsDelegate::CreateStatic(consoleExecString));

void FUnrealEnginePythonModule::StartupModule()
{
	BrutalFinalize = false;

	// Save the current locale (should be "C") to restore later. TCharTest::RunTest will fail otherwise
	FString SavedLocale(setlocale(LC_CTYPE, nullptr));

	// Manual import of data symbols that would prevent delay loading of python dll
	//LoadPythonSymbols(PythonHandle);

	// Point sys.path to the embedded python zip. Extraneous python installations are also cleared out
	FString PluginDir = IPluginManager::Get().FindPlugin(TEXT("UnrealEnginePython"))->GetBaseDir();
	FString PythonDir = FString::Printf(TEXT("Python%d%d"), PY_MAJOR_VERSION, PY_MINOR_VERSION);
	FString ZipFilename = FString::Printf(TEXT("python%d%d.zip"), PY_MAJOR_VERSION, PY_MINOR_VERSION);
	FString ZipPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(PluginDir, TEXT("ThirdParty"), PythonDir, ZipFilename));
#if PY_MAJOR_VERSION >= 3
	Py_SetPath(TCHAR_TO_WCHAR(*ZipPath));
#else
	Py_SetPath(TCHAR_TO_UTF8(*ZipPath));
#endif

	// Redundant because sys.path is manually set, clear PYTHONHOME for completeness
	FPlatformMisc::SetEnvironmentVar(TEXT("PYTHONHOME"), TEXT(""));
	FPlatformMisc::SetEnvironmentVar(TEXT("PYTHONPATH"), TEXT(""));
	Py_SetPythonHome(TCHAR_TO_WCHAR(*ZipPath));
	Py_SetProgramName(TCHAR_TO_WCHAR(FApp::GetProjectName()));

	ScriptsPath = FPaths::Combine(*PROJECT_CONTENT_DIR, TEXT_SCRIPTS_FOLDER);
	if (!FPaths::DirectoryExists(ScriptsPath))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*ScriptsPath);
	}

#if PY_MAJOR_VERSION >= 3
	init_unreal_engine_builtin();
#if PLATFORM_ANDROID
	extern FString GOBBFilePathBase;
	extern FString GFilePathBase;
	extern FString GExternalFilePath;
	extern FString GPackageName;
	extern int32 GAndroidPackageVersion;
	FString OBBDir1 = GOBBFilePathBase + FString(TEXT("/Android/obb/") + GPackageName);
	FString OBBDir2 = GOBBFilePathBase + FString(TEXT("/obb/") + GPackageName);
	FString MainOBBName = FString::Printf(TEXT("main.%d.%s.obb"), GAndroidPackageVersion, *GPackageName);
	FString PatchOBBName = FString::Printf(TEXT("patch.%d.%s.obb"), GAndroidPackageVersion, *GPackageName);
	FString UnrealEnginePython_OBBPath;
	if (FPaths::FileExists(*(OBBDir1 / MainOBBName)))
	{
		UnrealEnginePython_OBBPath = OBBDir1 / MainOBBName / FApp::GetProjectName() / FString(TEXT("Content/Scripts"));
	}
	else if (FPaths::FileExists(*(OBBDir2 / MainOBBName)))
	{
		UnrealEnginePython_OBBPath = OBBDir2 / MainOBBName / FApp::GetProjectName() / FString(TEXT("Content/Scripts"));
	}
	if (FPaths::FileExists(*(OBBDir1 / PatchOBBName)))
	{
		UnrealEnginePython_OBBPath = OBBDir1 / PatchOBBName / FApp::GetProjectName() / FString(TEXT("Content/Scripts"));
	}
	else if (FPaths::FileExists(*(OBBDir2 / PatchOBBName)))
	{
		UnrealEnginePython_OBBPath = OBBDir1 / PatchOBBName / FApp::GetProjectName() / FString(TEXT("Content/Scripts"));
	}

	if (!UnrealEnginePython_OBBPath.IsEmpty())
	{
		ScriptsPaths.Add(UnrealEnginePython_OBBPath);
	}

	FString FinalPath = GFilePathBase / FString("UE4Game") / FApp::GetProjectName() / FApp::GetProjectName() / FString(TEXT("Content/Scripts"));
	ScriptsPaths.Add(FinalPath);

	FString BasePythonPath = FinalPath / FString(TEXT("stdlib.zip")) + FString(":") + FinalPath;

	if (!UnrealEnginePython_OBBPath.IsEmpty())
	{
		BasePythonPath += FString(":") + UnrealEnginePython_OBBPath;
	}

	UE_LOG(LogPython, Warning, TEXT("Setting Base Path to %s"), *BasePythonPath);

	Py_SetPath(Py_DecodeLocale(TCHAR_TO_UTF8(*BasePythonPath), NULL));
#endif
#endif

#ifdef UEPY_OUTPUT_DEBUG
	freopen("cout.log", "w", stdout);
	freopen("cerr.log", "w", stderr);
	fflush(stdout);
	fflush(stderr);
#endif

	Py_Initialize();

	// Init unreal_engine module and importlib machinery to load scripts from uassets
	unreal_engine_init_py_module();
	setup_importlib();

#if PLATFORM_WINDOWS
	// Restore stdio state after Py_Initialize set it to O_BINARY, otherwise
	// everything that the engine will output is going to be encoded in UTF-16.
	// The behaviour is described here: https://bugs.python.org/issue16587
	_setmode(_fileno(stdin), O_TEXT);
	_setmode(_fileno(stdout), O_TEXT);
	_setmode(_fileno(stderr), O_TEXT);

	// Restore the user-requested UTF-8 flag if relevant (behaviour copied from LaunchEngineLoop.cpp).
	if (FParse::Param(FCommandLine::Get(), TEXT("UTF8Output")))
	{
		FPlatformMisc::SetUTF8Output();
	}
#endif

	PyEval_InitThreads();

#if WITH_EDITOR
	StyleSet = MakeShareable(new FSlateStyleSet("UnrealEnginePython"));
	StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin("UnrealEnginePython")->GetBaseDir() / "Resources");
	StyleSet->Set("ClassThumbnail.PythonScript", new FSlateImageBrush(StyleSet->RootToContentDir("Icon128.png"), FVector2D(128.0f, 128.0f)));
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
#if ENGINE_MINOR_VERSION < 13
	FClassIconFinder::RegisterIconSource(StyleSet.Get());
#endif
#endif

	UESetupPythonInterpreter(true);

	main_module = PyImport_AddModule("__main__");
	main_dict = PyModule_GetDict((PyObject*)main_module);
	local_dict = main_dict;// PyDict_New();

	setup_stdout_stderr();

	if (PyImport_ImportModule("ue_site"))
	{
		UE_LOG(LogPython, Log, TEXT("ue_site Python module successfully imported"));
	}
	else
	{
#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 6
		if (PyErr_ExceptionMatches(PyExc_ModuleNotFoundError))
		{
			UE_LOG(LogPython, Log, TEXT("ue_site Python module not found"));
			PyErr_Clear();
		}
		else
		{
			unreal_engine_py_log_error();
		}
#else
		unreal_engine_py_log_error();
#endif
	}

	// release the GIL
	PyThreadState *UEPyGlobalState = PyEval_SaveThread();

	// Restore locale
	setlocale(LC_CTYPE, TCHAR_TO_UTF8(*SavedLocale));
}

void FUnrealEnginePythonModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UE_LOG(LogPython, Log, TEXT("Goodbye Python"));
	if (!BrutalFinalize)
	{
		PyGILState_Ensure();
		Py_Finalize();
	}
}

void FUnrealEnginePythonModule::RunString(char *str)
{
	FScopePythonGIL gil;

	PyObject *eval_ret = PyRun_String(str, Py_file_input, (PyObject *)main_dict, (PyObject *)local_dict);
	if (!eval_ret)
	{
		if (PyErr_ExceptionMatches(PyExc_SystemExit))
		{
			PyErr_Clear();
			return;
		}
		unreal_engine_py_log_error();
		return;
	}
	Py_DECREF(eval_ret);
}

#if PLATFORM_MAC
void FUnrealEnginePythonModule::RunStringInMainThread(char *str)
{
	MainThreadCall(^{
	RunString(str);
		});
}

void FUnrealEnginePythonModule::RunFileInMainThread(char *filename)
{
	MainThreadCall(^{
	RunFile(filename);
		});
}
#endif

FString FUnrealEnginePythonModule::Pep8ize(FString Code)
{
	FScopePythonGIL gil;

	PyObject *pep8izer_module = PyImport_ImportModule("autopep8");
	if (!pep8izer_module)
	{
		unreal_engine_py_log_error();
		UE_LOG(LogPython, Error, TEXT("unable to load autopep8 module, please install it"));
		// return the original string to avoid losing data
		return Code;
	}

	PyObject *pep8izer_func = PyObject_GetAttrString(pep8izer_module, (char*)"fix_code");
	if (!pep8izer_func)
	{
		unreal_engine_py_log_error();
		UE_LOG(LogPython, Error, TEXT("unable to get autopep8.fix_code function"));
		// return the original string to avoid losing data
		return Code;
	}

	PyObject *ret = PyObject_CallFunction(pep8izer_func, (char *)"s", TCHAR_TO_UTF8(*Code));
	if (!ret)
	{
		unreal_engine_py_log_error();
		// return the original string to avoid losing data
		return Code;
	}

	if (!PyUnicodeOrString_Check(ret))
	{
		UE_LOG(LogPython, Error, TEXT("returned value is not a string"));
		// return the original string to avoid losing data
		return Code;
	}

	const char *pep8ized = UEPyUnicode_AsUTF8(ret);
	FString NewCode = FString(pep8ized);
	Py_DECREF(ret);

	return NewCode;
}

void FUnrealEnginePythonModule::RunFile(char *filename)
{
	FScopePythonGIL gil;
	FString full_path = UTF8_TO_TCHAR(filename);
	FString original_path = full_path;
	bool foundFile = FPaths::FileExists(filename);
	if (!foundFile)
	{
		full_path = FPaths::Combine(*ScriptsPath, original_path);
		foundFile = FPaths::FileExists(full_path);
	}

	if (!foundFile)
	{
		UE_LOG(LogPython, Error, TEXT("Unable to find file %s"), UTF8_TO_TCHAR(filename));
		return;
	}

#if PY_MAJOR_VERSION >= 3
	FILE *fd = nullptr;

#if PLATFORM_WINDOWS
	if (fopen_s(&fd, TCHAR_TO_UTF8(*full_path), "r") != 0)
	{
		UE_LOG(LogPython, Error, TEXT("Unable to open file %s"), *full_path);
		return;
	}
#else
	fd = fopen(TCHAR_TO_UTF8(*full_path), "r");
	if (!fd)
	{
		UE_LOG(LogPython, Error, TEXT("Unable to open file %s"), *full_path);
		return;
	}
#endif

	PyObject *eval_ret = PyRun_File(fd, TCHAR_TO_UTF8(*full_path), Py_file_input, (PyObject *)main_dict, (PyObject *)local_dict);
	fclose(fd);
	if (!eval_ret)
	{
		if (PyErr_ExceptionMatches(PyExc_SystemExit))
		{
			PyErr_Clear();
			return;
		}
		unreal_engine_py_log_error();
		return;
	}
	Py_DECREF(eval_ret);
#else
	// damn, this is horrible, but it is the only way i found to avoid the CRT error :(
	FString command = FString::Printf(TEXT("execfile(\"%s\")"), *full_path);
	PyObject *eval_ret = PyRun_String(TCHAR_TO_UTF8(*command), Py_file_input, (PyObject *)main_dict, (PyObject *)local_dict);
	if (!eval_ret)
	{
		if (PyErr_ExceptionMatches(PyExc_SystemExit))
		{
			PyErr_Clear();
			return;
		}
		unreal_engine_py_log_error();
		return;
	}
#endif

}

void ue_py_register_magic_module(char *name, PyObject *(*func)())
{
	PyObject *py_sys = PyImport_ImportModule("sys");
	PyObject *py_sys_dict = PyModule_GetDict(py_sys);

	PyObject *py_sys_modules = PyDict_GetItemString(py_sys_dict, "modules");
	PyObject *u_module = func();
	Py_INCREF(u_module);
	PyDict_SetItemString(py_sys_modules, name, u_module);
}

PyObject *ue_py_register_module(const char *name)
{
	return PyImport_AddModule(name);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealEnginePythonModule, UnrealEnginePython)
