// Copyright 20Tab S.r.l.

#pragma once

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
#endif


//#define UEPY_MEMORY_DEBUG 1
#define UEPY_OUTPUT_DEBUG 1

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Runtime/SlateCore/Public/Styling/SlateStyle.h"
#include "UObject/ScriptMacros.h"
#include "Runtime/Launch/Resources/Version.h"

#if PLATFORM_MAC
#include <include/Python.h>
#include <include/structmember.h>
#elif PLATFORM_LINUX
#include <include/Python.h>
#include <include/structmember.h>
#elif PLATFORM_ANDROID
#include <include/Python.h>
#include <include/structmember.h>
#elif PLATFORM_WINDOWS
#include <include/pyconfig.h>
#ifndef SIZEOF_PID_T
#define SIZEOF_PID_T 4
#endif
#include <include/Python.h>
#include <include/structmember.h>
#endif

typedef struct
{
	PyObject_HEAD
	/* Type-specific fields go here. */
	UObject *ue_object;
	// reference to proxy class (can be null)
	PyObject *py_proxy;
	// the __dict__
	PyObject *py_dict;
	// if true RemoveFromRoot will be called at object destruction time
	int auto_rooted;
	// if owned the life of the UObject is related to the life of PyObject
	int owned;
} ue_PyUObject;

DECLARE_LOG_CATEGORY_EXTERN(LogPython, Log, All);

UNREALENGINEPYTHON_API void ue_py_register_magic_module(char *name, PyObject *(*)());
UNREALENGINEPYTHON_API PyObject *ue_py_register_module(const char *);

#if ENGINE_MINOR_VERSION >= 18
#define FStringAssetReference FSoftObjectPath
#endif

#define ue_py_check(py_u) if (!FUnrealEnginePythonHouseKeeper::Get()->IsValidPyUObject(py_u))\
	return PyErr_Format(PyExc_Exception, "PyUObject is in invalid state")

#define ue_py_check_int(py_u) if (!FUnrealEnginePythonHouseKeeper::Get()->IsValidPyUObject(py_u))\
	{\
		PyErr_SetString(PyExc_Exception, "PyUObject is in invalid state");\
		return -1;\
	}

const char *UEPyUnicode_AsUTF8(PyObject *py_str);

#if PY_MAJOR_VERSION < 3
int PyGILState_Check();
#endif
bool PyUnicodeOrString_Check(PyObject *py_obj);

UNREALENGINEPYTHON_API void unreal_engine_py_log_error();
UNREALENGINEPYTHON_API ue_PyUObject *ue_get_python_uobject(UObject *);
UNREALENGINEPYTHON_API ue_PyUObject *ue_get_python_uobject_inc(UObject *);

#define Py_RETURN_UOBJECT(py_uobj) ue_PyUObject *ret = ue_get_python_uobject_inc(py_uobj);\
	if (!ret)\
		return PyErr_Format(PyExc_Exception, "uobject is in invalid state");\
	return (PyObject *)ret;

#define Py_RETURN_UOBJECT_NOINC(py_uobj) ue_PyUObject *ret = ue_get_python_uobject(py_uobj);\
	if (!ret)\
		return PyErr_Format(PyExc_Exception, "uobject is in invalid state");\
	return (PyObject *)ret;

#if ENGINE_MINOR_VERSION < 16
template<class CPPSTRUCT>
struct TStructOpsTypeTraitsBase2 : TStructOpsTypeTraitsBase
{

};
#endif

class UNREALENGINEPYTHON_API FUnrealEnginePythonModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void RunString(char *);
	void RunFile(char *);

#if PLATFORM_MAC
	void RunStringInMainThread(char *);
	void RunFileInMainThread(char *);
#endif

	void UESetupPythonInterpreter(bool);

	bool BrutalFinalize;

	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline FUnrealEnginePythonModule& Get()
	{
		return FModuleManager::LoadModuleChecked< FUnrealEnginePythonModule >("UnrealEnginePython");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("UnrealEnginePython");
	}

	// pep8ize a string using various strategy (currently only autopep8 is supported)
	FString Pep8ize(FString Code);

	FString GetScriptsPath() { return ScriptsPath; }

	static PyObject* __Py_NoneStruct; /* Don't use this directly */
	static PyObject* __Py_TrueStruct; /* Don't use this directly */
	static PyObject* __Py_FalseStruct; /* Don't use this directly */

private:
	FString ScriptsPath;
	void *ue_python_gil;
	// used by console
	void *main_dict;
	void *local_dict;
	void *main_module;

	TSharedPtr<FSlateStyleSet> StyleSet;
};

struct FScopePythonGIL
{
	PyGILState_STATE state;

	FScopePythonGIL()
	{
		state = PyGILState_Ensure();
	}

	~FScopePythonGIL()
	{
		PyGILState_Release(state);
	}
};
