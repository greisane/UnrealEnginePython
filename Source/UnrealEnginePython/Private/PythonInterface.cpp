//-----------------------------------------------------------------------------
//
// Copyright (c) 1998 - 2007, The Regents of the University of California
// Produced at the Lawrence Livermore National Laboratory
// All rights reserved.
//
// This file is part of PyCXX. For details,see http://cxx.sourceforge.net/. The
// full copyright notice is contained in the file COPYRIGHT located at the root
// of the PyCXX distribution.
//
// Redistribution  and  use  in  source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
//  - Redistributions of  source code must  retain the above  copyright notice,
//    this list of conditions and the disclaimer below.
//  - Redistributions in binary form must reproduce the above copyright notice,
//    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
//    documentation and/or materials provided with the distribution.
//  - Neither the name of the UC/LLNL nor  the names of its contributors may be
//    used to  endorse or  promote products derived from  this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
// ARE  DISCLAIMED.  IN  NO  EVENT  SHALL  THE  REGENTS  OF  THE  UNIVERSITY OF
// CALIFORNIA, THE U.S.  DEPARTMENT  OF  ENERGY OR CONTRIBUTORS BE  LIABLE  FOR
// ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
// SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
// CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
// LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
// OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
//-----------------------------------------------------------------------------

#include "PythonInterface.h"
#include "UnrealEnginePython.h"
#include "HAL/PlatformProcess.h"
#include "Containers/StringConv.h"

bool _CFunction_Check(PyObject* op) { return op->ob_type == _CFunction_Type(); }
bool _CObject_Check(PyObject* op) { return op->ob_type == _CObject_Type(); }
bool _Complex_Check(PyObject* op) { return op->ob_type == _Complex_Type(); }
bool _Dict_Check(PyObject* op) { return op->ob_type == _Dict_Type(); }
bool _Float_Check(PyObject* op) { return op->ob_type == _Float_Type(); }
bool _Function_Check(PyObject* op) { return op->ob_type == _Function_Type(); }
bool _Boolean_Check(PyObject* op) { return op->ob_type == _Bool_Type(); }
bool _List_Check(PyObject* op) { return op->ob_type == _List_Type(); }
bool _Long_Check(PyObject* op) { return op->ob_type == _Long_Type(); }
bool _Method_Check(PyObject* op) { return op->ob_type == _Method_Type(); }
bool _Module_Check(PyObject* op) { return op->ob_type == _Module_Type(); }
bool _Range_Check(PyObject* op) { return op->ob_type == _Range_Type(); }
bool _Slice_Check(PyObject* op) { return op->ob_type == _Slice_Type(); }
bool _TraceBack_Check(PyObject* op) { return op->ob_type == _TraceBack_Type(); }
bool _Tuple_Check(PyObject* op) { return op->ob_type == _Tuple_Type(); }
bool _Type_Check(PyObject* op) { return op->ob_type == _Type_Type(); }
bool _Unicode_Check(PyObject* op) { return op->ob_type == _Unicode_Type(); }
bool _Bytes_Check(PyObject* op) { return op->ob_type == _Bytes_Type(); }

#if DELAYLOAD_PYTHON_DLL

static PyObject* ptr__Exc_ArithmeticError = nullptr;
static PyObject* ptr__Exc_AssertionError = nullptr;
static PyObject* ptr__Exc_AttributeError = nullptr;
static PyObject* ptr__Exc_EnvironmentError = nullptr;
static PyObject* ptr__Exc_EOFError = nullptr;
static PyObject* ptr__Exc_Exception = nullptr;
static PyObject* ptr__Exc_FloatingPointError = nullptr;
static PyObject* ptr__Exc_ImportError = nullptr;
static PyObject* ptr__Exc_IndexError = nullptr;
static PyObject* ptr__Exc_IOError = nullptr;
static PyObject* ptr__Exc_KeyboardInterrupt = nullptr;
static PyObject* ptr__Exc_KeyError = nullptr;
static PyObject* ptr__Exc_LookupError = nullptr;
static PyObject* ptr__Exc_MemoryError = nullptr;
static PyObject* ptr__Exc_MemoryErrorInst = nullptr;
static PyObject* ptr__Exc_ModuleNotFoundError = nullptr;
static PyObject* ptr__Exc_NameError = nullptr;
static PyObject* ptr__Exc_NotImplementedError = nullptr;
static PyObject* ptr__Exc_OSError = nullptr;
static PyObject* ptr__Exc_OverflowError = nullptr;
static PyObject* ptr__Exc_RuntimeError = nullptr;
static PyObject* ptr__Exc_StandardError = nullptr;
static PyObject* ptr__Exc_SyntaxError = nullptr;
static PyObject* ptr__Exc_SystemError = nullptr;
static PyObject* ptr__Exc_SystemExit = nullptr;
static PyObject* ptr__Exc_TypeError = nullptr;
static PyObject* ptr__Exc_ValueError = nullptr;
static PyObject* ptr__Exc_ZeroDivisionError = nullptr;

static PyObject* ptr__Exc_IndentationError = nullptr;
static PyObject* ptr__Exc_TabError = nullptr;
static PyObject* ptr__Exc_UnboundLocalError = nullptr;
static PyObject* ptr__Exc_UnicodeError = nullptr;
static PyObject* ptr__PyNone = nullptr;
static PyObject* ptr__PyFalse = nullptr;
static PyObject* ptr__PyTrue = nullptr;
static PyTypeObject* ptr__CFunction_Type = nullptr;
static PyTypeObject* ptr__CObject_Type = nullptr;
static PyTypeObject* ptr__Complex_Type = nullptr;
static PyTypeObject* ptr__Dict_Type = nullptr;
static PyTypeObject* ptr__Float_Type = nullptr;
static PyTypeObject* ptr__Function_Type = nullptr;
static PyTypeObject* ptr__Bool_Type = nullptr;
static PyTypeObject* ptr__List_Type = nullptr;
static PyTypeObject* ptr__Long_Type = nullptr;
static PyTypeObject* ptr__Method_Type = nullptr;
static PyTypeObject* ptr__Module_Type = nullptr;
static PyTypeObject* ptr__Range_Type = nullptr;
static PyTypeObject* ptr__Slice_Type = nullptr;
static PyTypeObject* ptr__TraceBack_Type = nullptr;
static PyTypeObject* ptr__Tuple_Type = nullptr;
static PyTypeObject* ptr__Type_Type = nullptr;
static PyTypeObject* ptr__Unicode_Type = nullptr;
static PyTypeObject* ptr__Bytes_Type = nullptr;

static int* ptr_Py_DebugFlag = nullptr;
static int* ptr_Py_InteractiveFlag = nullptr;
static int* ptr_Py_OptimizeFlag = nullptr;
static int* ptr_Py_NoSiteFlag = nullptr;
static int* ptr_Py_VerboseFlag = nullptr;

static char** ptr__Py_PackageContext = nullptr;

#ifdef Py_REF_DEBUG
int* ptr_Py_RefTotal;
#endif


//--------------------------------------------------------------------------------
static PyObject* GetPyObjectPointer_As_PyObjectPointer(void* DllHandle, const char* name)
{
    void* addr = FPlatformProcess::GetDllExport(DllHandle, UTF8_TO_TCHAR(name));
    if (addr == nullptr)
    {
        UE_LOG(LogPython, Fatal, TEXT("Failed to import symbol '%s'."), UTF8_TO_TCHAR(name));
    }

    return *(PyObject**)addr;
}

static PyObject* GetPyObject_As_PyObjectPointer(void* DllHandle, const char* name)
{
    void* addr = FPlatformProcess::GetDllExport(DllHandle, UTF8_TO_TCHAR(name));
    if (addr == nullptr)
    {
        UE_LOG(LogPython, Fatal, TEXT("Failed to import symbol '%s'."), UTF8_TO_TCHAR(name));
    }

    return (PyObject*)addr;
}

static PyTypeObject* GetPyTypeObjectPointer_As_PyTypeObjectPointer(void* DllHandle, const char* name)
{
    void* addr = FPlatformProcess::GetDllExport(DllHandle, UTF8_TO_TCHAR(name));
    if (addr == nullptr)
    {
        UE_LOG(LogPython, Fatal, TEXT("Failed to import symbol '%s'."), UTF8_TO_TCHAR(name));
    }

    return *(PyTypeObject**)addr;
}

static PyTypeObject* GetPyTypeObject_As_PyTypeObjectPointer(void* DllHandle, const char* name)
{
    void* addr = FPlatformProcess::GetDllExport(DllHandle, UTF8_TO_TCHAR(name));
    if (addr == nullptr)
    {
        UE_LOG(LogPython, Fatal, TEXT("Failed to import symbol '%s'."), UTF8_TO_TCHAR(name));
    }

    return (PyTypeObject*)addr;
}

static int* GetInt_as_IntPointer(void* DllHandle, const char* name)
{
    void* addr = FPlatformProcess::GetDllExport(DllHandle, UTF8_TO_TCHAR(name));
    if (addr == nullptr)
    {
        UE_LOG(LogPython, Fatal, TEXT("Failed to import symbol '%s'."), UTF8_TO_TCHAR(name));
    }

    return (int*)addr;
}

static char** GetCharPointer_as_CharPointerPointer(void* DllHandle, const char* name)
{
    void* addr = FPlatformProcess::GetDllExport(DllHandle, UTF8_TO_TCHAR(name));
    if (addr == nullptr)
    {
        UE_LOG(LogPython, Fatal, TEXT("Failed to import symbol '%s'."), UTF8_TO_TCHAR(name));
    }

    return (char**)addr;
}


//--------------------------------------------------------------------------------
void LoadPythonSymbols(void* DllHandle)
{
#ifdef Py_REF_DEBUG
    ptr_Py_RefTotal = GetInt_as_IntPointer(DllHandle, "_Py_RefTotal");
#endif
    ptr_Py_DebugFlag = GetInt_as_IntPointer(DllHandle, "Py_DebugFlag");
    ptr_Py_InteractiveFlag = GetInt_as_IntPointer(DllHandle, "Py_InteractiveFlag");
    ptr_Py_OptimizeFlag = GetInt_as_IntPointer(DllHandle, "Py_OptimizeFlag");
    ptr_Py_NoSiteFlag = GetInt_as_IntPointer(DllHandle, "Py_NoSiteFlag");
    ptr_Py_VerboseFlag = GetInt_as_IntPointer(DllHandle, "Py_VerboseFlag");
    ptr__Py_PackageContext = GetCharPointer_as_CharPointerPointer(DllHandle, "_Py_PackageContext");

    ptr__Exc_ArithmeticError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_ArithmeticError");
    ptr__Exc_AssertionError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_AssertionError");
    ptr__Exc_AttributeError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_AttributeError");
    ptr__Exc_EnvironmentError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_EnvironmentError");
    ptr__Exc_EOFError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_EOFError");
    ptr__Exc_Exception = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_Exception");
    ptr__Exc_FloatingPointError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_FloatingPointError");
    ptr__Exc_ImportError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_ImportError");
    ptr__Exc_IndexError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_IndexError");
    ptr__Exc_IOError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_IOError");
    ptr__Exc_KeyboardInterrupt = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_KeyboardInterrupt");
    ptr__Exc_KeyError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_KeyError");
    ptr__Exc_LookupError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_LookupError");
    ptr__Exc_MemoryError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_MemoryError");
    ptr__Exc_MemoryErrorInst = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_MemoryErrorInst");
    ptr__Exc_ModuleNotFoundError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_ModuleNotFoundError");
    ptr__Exc_NameError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_NameError");
    ptr__Exc_NotImplementedError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_NotImplementedError");
    ptr__Exc_OSError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_OSError");
    ptr__Exc_OverflowError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_OverflowError");
    ptr__Exc_RuntimeError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_RuntimeError");
    ptr__Exc_StandardError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_StandardError");
    ptr__Exc_SyntaxError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_SyntaxError");
    ptr__Exc_SystemError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_SystemError");
    ptr__Exc_SystemExit = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_SystemExit");
    ptr__Exc_TypeError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_TypeError");
    ptr__Exc_ValueError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_ValueError");
    ptr__Exc_ZeroDivisionError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_ZeroDivisionError");
    ptr__Exc_IndentationError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_IndentationError");
    ptr__Exc_TabError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_TabError");
    ptr__Exc_UnboundLocalError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_UnboundLocalError");
    ptr__Exc_UnicodeError = GetPyObjectPointer_As_PyObjectPointer(DllHandle, "PyExc_UnicodeError");
    ptr__PyNone = GetPyObject_As_PyObjectPointer(DllHandle, "_Py_NoneStruct");

    ptr__PyFalse = GetPyObject_As_PyObjectPointer(DllHandle, "_Py_ZeroStruct");
    ptr__PyTrue = GetPyObject_As_PyObjectPointer(DllHandle, "_Py_TrueStruct");

    ptr__CFunction_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyCFunction_Type");
    ptr__CObject_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyCObject_Type");
    ptr__Complex_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyComplex_Type");
    ptr__Dict_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyDict_Type");
    ptr__Float_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyFloat_Type");
    ptr__Function_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyFunction_Type");
    ptr__Bool_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyBool_Type");
    ptr__List_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyList_Type");
    ptr__Long_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyLong_Type");
    ptr__Method_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyMethod_Type");
    ptr__Module_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyModule_Type");
    ptr__Range_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyRange_Type");
    ptr__Slice_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PySlice_Type");
    ptr__TraceBack_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyTraceBack_Type");
    ptr__Tuple_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyTuple_Type");
    ptr__Type_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyType_Type");
    ptr__Unicode_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyUnicode_Type");
    ptr__Bytes_Type = GetPyTypeObject_As_PyTypeObjectPointer(DllHandle, "PyBytes_Type");
}

//
//    Wrap variables as function calls
//
PyObject* _Exc_ArithmeticError() { return ptr__Exc_ArithmeticError; }
PyObject* _Exc_AssertionError() { return ptr__Exc_AssertionError; }
PyObject* _Exc_AttributeError() { return ptr__Exc_AttributeError; }
PyObject* _Exc_EnvironmentError() { return ptr__Exc_EnvironmentError; }
PyObject* _Exc_EOFError() { return ptr__Exc_EOFError; }
PyObject* _Exc_Exception() { return ptr__Exc_Exception; }
PyObject* _Exc_FloatingPointError() { return ptr__Exc_FloatingPointError; }
PyObject* _Exc_ImportError() { return ptr__Exc_ImportError; }
PyObject* _Exc_IndexError() { return ptr__Exc_IndexError; }
PyObject* _Exc_IOError() { return ptr__Exc_IOError; }
PyObject* _Exc_KeyboardInterrupt() { return ptr__Exc_KeyboardInterrupt; }
PyObject* _Exc_KeyError() { return ptr__Exc_KeyError; }
PyObject* _Exc_LookupError() { return ptr__Exc_LookupError; }
PyObject* _Exc_MemoryError() { return ptr__Exc_MemoryError; }
PyObject* _Exc_MemoryErrorInst() { return ptr__Exc_MemoryErrorInst; }
PyObject* _Exc_ModuleNotFoundError() { return ptr__Exc_ModuleNotFoundError; }
PyObject* _Exc_NameError() { return ptr__Exc_NameError; }
PyObject* _Exc_NotImplementedError() { return ptr__Exc_NotImplementedError; }
PyObject* _Exc_OSError() { return ptr__Exc_OSError; }
PyObject* _Exc_OverflowError() { return ptr__Exc_OverflowError; }
PyObject* _Exc_RuntimeError() { return ptr__Exc_RuntimeError; }
PyObject* _Exc_StandardError() { return ptr__Exc_StandardError; }
PyObject* _Exc_SyntaxError() { return ptr__Exc_SyntaxError; }
PyObject* _Exc_SystemError() { return ptr__Exc_SystemError; }
PyObject* _Exc_SystemExit() { return ptr__Exc_SystemExit; }
PyObject* _Exc_TypeError() { return ptr__Exc_TypeError; }
PyObject* _Exc_ValueError() { return ptr__Exc_ValueError; }
PyObject* _Exc_ZeroDivisionError() { return ptr__Exc_ZeroDivisionError; }
PyObject* _Exc_IndentationError() { return ptr__Exc_IndentationError; }
PyObject* _Exc_TabError() { return ptr__Exc_TabError; }
PyObject* _Exc_UnboundLocalError() { return ptr__Exc_UnboundLocalError; }
PyObject* _Exc_UnicodeError() { return ptr__Exc_UnicodeError; }

//
//    wrap items in Object.h
//
PyObject* _None() { return ptr__PyNone; }

PyObject* _False() { return ptr__PyFalse; }
PyObject* _True() { return ptr__PyTrue; }

PyTypeObject* _CFunction_Type() { return ptr__CFunction_Type; }
PyTypeObject* _CObject_Type() { return ptr__CObject_Type; }
PyTypeObject* _Complex_Type() { return ptr__Complex_Type; }
PyTypeObject* _Dict_Type() { return ptr__Dict_Type; }
PyTypeObject* _Float_Type() { return ptr__Float_Type; }
PyTypeObject* _Function_Type() { return ptr__Function_Type; }
PyTypeObject* _Bool_Type() { return ptr__Bool_Type; }
PyTypeObject* _List_Type() { return ptr__List_Type; }
PyTypeObject* _Long_Type() { return ptr__Long_Type; }
PyTypeObject* _Method_Type() { return ptr__Method_Type; }
PyTypeObject* _Module_Type() { return ptr__Module_Type; }
PyTypeObject* _Range_Type() { return ptr__Range_Type; }
PyTypeObject* _Slice_Type() { return ptr__Slice_Type; }
PyTypeObject* _TraceBack_Type() { return ptr__TraceBack_Type; }
PyTypeObject* _Tuple_Type() { return ptr__Tuple_Type; }
PyTypeObject* _Type_Type() { return ptr__Type_Type; }
PyTypeObject* _Unicode_Type() { return ptr__Unicode_Type; }
PyTypeObject* _Bytes_Type() { return ptr__Bytes_Type; }

char* __Py_PackageContext() { return *ptr__Py_PackageContext; }


//
//    wrap the Python Flag variables
//
int& _Py_DebugFlag() { return *ptr_Py_DebugFlag; }
int& _Py_InteractiveFlag() { return *ptr_Py_InteractiveFlag; }
int& _Py_OptimizeFlag() { return *ptr_Py_OptimizeFlag; }
int& _Py_NoSiteFlag() { return *ptr_Py_NoSiteFlag; }
int& _Py_VerboseFlag() { return *ptr_Py_VerboseFlag; }

#if 0
#define Py_INCREF(op) (                         \
    _Py_INC_REFTOTAL  _Py_REF_DEBUG_COMMA       \
    ((PyObject*)(op))->ob_refcnt++)

#define Py_DECREF(op)                           \
    if (_Py_DEC_REFTOTAL  _Py_REF_DEBUG_COMMA   \
        --((PyObject*)(op))->ob_refcnt != 0)    \
        _Py_CHECK_REFCNT(op)                    \
    else                                        \
        _Py_Dealloc((PyObject *)(op))
#endif

void ue_Py_XINCREF(void* op)
{
    // This function must match the contents of Py_XINCREF(op)
    if (op == nullptr)
        return;

#ifdef Py_REF_DEBUG
    (*ptr_Py_RefTotal)++;
#endif
    ((PyObject*)op)->ob_refcnt++;

}

void ue_Py_XDECREF(void* op)
{
    // This function must match the contents of Py_XDECREF(op);
    if (op == nullptr)
        return;

#ifdef Py_REF_DEBUG
    (*ptr_Py_RefTotal)--;
#endif

    if (--((PyObject*)op)->ob_refcnt == 0)
        _Py_Dealloc((PyObject*)op);
}


#else

//================================================================================
//
//    Map onto Macros
//
//================================================================================

//
//    Wrap variables as function calls
//

PyObject* _Exc_ArithmeticError() { return ::PyExc_ArithmeticError; }
PyObject* _Exc_AssertionError() { return ::PyExc_AssertionError; }
PyObject* _Exc_AttributeError() { return ::PyExc_AttributeError; }
PyObject* _Exc_EnvironmentError() { return ::PyExc_EnvironmentError; }
PyObject* _Exc_EOFError() { return ::PyExc_EOFError; }
PyObject* _Exc_Exception() { return ::PyExc_Exception; }
PyObject* _Exc_FloatingPointError() { return ::PyExc_FloatingPointError; }
PyObject* _Exc_ImportError() { return ::PyExc_ImportError; }
PyObject* _Exc_IndexError() { return ::PyExc_IndexError; }
PyObject* _Exc_IOError() { return ::PyExc_IOError; }
PyObject* _Exc_KeyboardInterrupt() { return ::PyExc_KeyboardInterrupt; }
PyObject* _Exc_KeyError() { return ::PyExc_KeyError; }
PyObject* _Exc_LookupError() { return ::PyExc_LookupError; }
PyObject* _Exc_MemoryError() { return ::PyExc_MemoryError; }
PyObject* _Exc_MemoryErrorInst() { return ::PyExc_MemoryErrorInst; }
PyObject* _Exc_ModuleNotFoundError() { return ::PyExc_ModuleNotFoundError; }
PyObject* _Exc_NameError() { return ::PyExc_NameError; }
PyObject* _Exc_NotImplementedError() { return ::PyExc_NotImplementedError; }
PyObject* _Exc_OSError() { return ::PyExc_OSError; }
PyObject* _Exc_OverflowError() { return ::PyExc_OverflowError; }
PyObject* _Exc_RuntimeError() { return ::PyExc_RuntimeError; }
PyObject* _Exc_SyntaxError() { return ::PyExc_SyntaxError; }
PyObject* _Exc_SystemError() { return ::PyExc_SystemError; }
PyObject* _Exc_SystemExit() { return ::PyExc_SystemExit; }
PyObject* _Exc_TypeError() { return ::PyExc_TypeError; }
PyObject* _Exc_ValueError() { return ::PyExc_ValueError; }
PyObject* _Exc_ZeroDivisionError() { return ::PyExc_ZeroDivisionError; }
PyObject* _Exc_IndentationError() { return ::PyExc_IndentationError; }
PyObject* _Exc_TabError() { return ::PyExc_TabError; }
PyObject* _Exc_UnboundLocalError() { return ::PyExc_UnboundLocalError; }
PyObject* _Exc_UnicodeError() { return ::PyExc_UnicodeError; }


//
//    wrap items in Object.h
//
PyObject* _None() { return &::Py_None; }

PyObject* _False() { return Py_False; }
PyObject* _True() { return Py_True; }

PyTypeObject* _CFunction_Type() { return &PyCFunction_Type; }
PyTypeObject* _CObject_Type() { return &PyCObject_Type; }
PyTypeObject* _Complex_Type() { return &PyComplex_Type; }
PyTypeObject* _Dict_Type() { return &PyDict_Type; }
PyTypeObject* _Float_Type() { return &PyFloat_Type; }
PyTypeObject* _Function_Type() { return &PyFunction_Type; }
PyTypeObject* _Bool_Type() { return &PyBool_Type; }
PyTypeObject* _List_Type() { return &PyList_Type; }
PyTypeObject* _Long_Type() { return &PyLong_Type; }
PyTypeObject* _Method_Type() { return &PyMethod_Type; }
PyTypeObject* _Module_Type() { return &PyModule_Type; }
PyTypeObject* _Range_Type() { return &PyRange_Type; }
PyTypeObject* _Slice_Type() { return &PySlice_Type; }
PyTypeObject* _TraceBack_Type() { return &PyTraceBack_Type; }
PyTypeObject* _Tuple_Type() { return &PyTuple_Type; }
PyTypeObject* _Type_Type() { return &PyType_Type; }
PyTypeObject* _Unicode_Type() { return &PyUnicode_Type; }
PyTypeObject* _Bytes_Type() { return &PyBytes_Type; }

//
//    wrap flags
//
int& _Py_DebugFlag() { return Py_DebugFlag; }
int& _Py_InteractiveFlag() { return Py_InteractiveFlag; }
int& _Py_OptimizeFlag() { return Py_OptimizeFlag; }
int& _Py_NoSiteFlag() { return Py_NoSiteFlag; }
int& _Py_VerboseFlag() { return Py_VerboseFlag; }
char* __Py_PackageContext() { return __Py_PackageContext; }

//
//    Needed to keep the abstactions for delayload interface
//
void ue_Py_XINCREF(void* op)
{
    Py_XINCREF(op);
}

void ue_Py_XDECREF(void* op)
{
    Py_XDECREF(op);
}

#endif
