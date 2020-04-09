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

#pragma once

#include "Logging/LogMacros.h"

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

DECLARE_LOG_CATEGORY_EXTERN(LogPython, Log, All);

void LoadPythonSymbols(void* DllHandle);

//
//    Wrap Exception variables as function calls
//
UNREALENGINEPYTHON_API PyObject* _Exc_StandardError();
UNREALENGINEPYTHON_API PyObject* _Exc_ArithmeticError();
UNREALENGINEPYTHON_API PyObject* _Exc_LookupError();

UNREALENGINEPYTHON_API PyObject* _Exc_AssertionError();
UNREALENGINEPYTHON_API PyObject* _Exc_AttributeError();
UNREALENGINEPYTHON_API PyObject* _Exc_EOFError();
UNREALENGINEPYTHON_API PyObject* _Exc_Exception();
UNREALENGINEPYTHON_API PyObject* _Exc_FloatingPointError();
UNREALENGINEPYTHON_API PyObject* _Exc_EnvironmentError();
UNREALENGINEPYTHON_API PyObject* _Exc_IOError();
UNREALENGINEPYTHON_API PyObject* _Exc_OSError();
UNREALENGINEPYTHON_API PyObject* _Exc_ImportError();
UNREALENGINEPYTHON_API PyObject* _Exc_IndexError();
UNREALENGINEPYTHON_API PyObject* _Exc_KeyError();
UNREALENGINEPYTHON_API PyObject* _Exc_KeyboardInterrupt();
UNREALENGINEPYTHON_API PyObject* _Exc_MemoryError();
UNREALENGINEPYTHON_API PyObject* _Exc_ModuleNotFoundError();
UNREALENGINEPYTHON_API PyObject* _Exc_NameError();
UNREALENGINEPYTHON_API PyObject* _Exc_OverflowError();
UNREALENGINEPYTHON_API PyObject* _Exc_RuntimeError();
UNREALENGINEPYTHON_API PyObject* _Exc_NotImplementedError();
UNREALENGINEPYTHON_API PyObject* _Exc_SyntaxError();
UNREALENGINEPYTHON_API PyObject* _Exc_SystemError();
UNREALENGINEPYTHON_API PyObject* _Exc_SystemExit();
UNREALENGINEPYTHON_API PyObject* _Exc_TypeError();
UNREALENGINEPYTHON_API PyObject* _Exc_ValueError();
UNREALENGINEPYTHON_API PyObject* _Exc_ZeroDivisionError();

UNREALENGINEPYTHON_API PyObject* _Exc_MemoryErrorInst();

UNREALENGINEPYTHON_API PyObject* _Exc_IndentationError();
UNREALENGINEPYTHON_API PyObject* _Exc_TabError();
UNREALENGINEPYTHON_API PyObject* _Exc_UnboundLocalError();
UNREALENGINEPYTHON_API PyObject* _Exc_UnicodeError();

//
//    Wrap Object variables as function calls
//
UNREALENGINEPYTHON_API PyObject* _None();

UNREALENGINEPYTHON_API PyObject* _False();
UNREALENGINEPYTHON_API PyObject* _True();

//
//    Macros for the above
//
#define ue_PyExc_StandardError _Exc_StandardError()
#define ue_PyExc_ArithmeticError _Exc_ArithmeticError()
#define ue_PyExc_LookupError _Exc_LookupError()
#define ue_PyExc_AssertionError _Exc_AssertionError()
#define ue_PyExc_AttributeError _Exc_AttributeError()
#define ue_PyExc_EOFError _Exc_EOFError()
#define ue_PyExc_Exception _Exc_Exception()
#define ue_PyExc_FloatingPointError _Exc_FloatingPointError()
#define ue_PyExc_EnvironmentError _Exc_EnvironmentError()
#define ue_PyExc_IOError _Exc_IOError()
#define ue_PyExc_OSError _Exc_OSError()
#define ue_PyExc_ImportError _Exc_ImportError()
#define ue_PyExc_IndexError _Exc_IndexError()
#define ue_PyExc_KeyError _Exc_KeyError()
#define ue_PyExc_KeyboardInterrupt _Exc_KeyboardInterrupt()
#define ue_PyExc_MemoryError _Exc_MemoryError()
#define ue_PyExc_ModuleNotFoundError _Exc_ModuleNotFoundError()
#define ue_PyExc_NameError _Exc_NameError()
#define ue_PyExc_OverflowError _Exc_OverflowError()
#define ue_PyExc_RuntimeError _Exc_RuntimeError()
#define ue_PyExc_NotImplementedError _Exc_NotImplementedError()
#define ue_PyExc_SyntaxError _Exc_SyntaxError()
#define ue_PyExc_SystemError _Exc_SystemError()
#define ue_PyExc_SystemExit _Exc_SystemExit()
#define ue_PyExc_TypeError _Exc_TypeError()
#define ue_PyExc_ValueError _Exc_ValueError()
#define ue_PyExc_ZeroDivisionError _Exc_ZeroDivisionError()
#define ue_PyExc_MemoryErrorInst _Exc_MemoryErrorInst()
#define ue_PyExc_IndentationError _Exc_IndentationError()
#define ue_PyExc_TabError _Exc_TabError()
#define ue_PyExc_UnboundLocalError _Exc_UnboundLocalError()
#define ue_PyExc_UnicodeError _Exc_UnicodeError()
#define ue_Py_None _None()
#define ue_Py_False _False()
#define ue_Py_True _True()

//
//    Wrap Type variables as function calls
//
UNREALENGINEPYTHON_API PyTypeObject* _List_Type();
UNREALENGINEPYTHON_API bool _List_Check(PyObject* o);

UNREALENGINEPYTHON_API PyTypeObject* _Buffer_Type();
UNREALENGINEPYTHON_API bool _Buffer_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Class_Type();
UNREALENGINEPYTHON_API bool _Class_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Instance_Type();
UNREALENGINEPYTHON_API bool _Instance_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Method_Type();
UNREALENGINEPYTHON_API bool _Method_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _CObject_Type();
UNREALENGINEPYTHON_API bool _CObject_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Complex_Type();
UNREALENGINEPYTHON_API bool _Complex_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Dict_Type();
UNREALENGINEPYTHON_API bool _Dict_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _File_Type();
UNREALENGINEPYTHON_API bool _File_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Float_Type();
UNREALENGINEPYTHON_API bool _Float_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Frame_Type();
UNREALENGINEPYTHON_API bool _Frame_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Function_Type();
UNREALENGINEPYTHON_API bool _Function_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Bool_Type();
UNREALENGINEPYTHON_API bool _Boolean_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Int_Type();
UNREALENGINEPYTHON_API bool _Int_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _List_Type();
UNREALENGINEPYTHON_API bool _List_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Long_Type();
UNREALENGINEPYTHON_API bool _Long_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _CFunction_Type();
UNREALENGINEPYTHON_API bool _CFunction_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Module_Type();
UNREALENGINEPYTHON_API bool _Module_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Type_Type();
UNREALENGINEPYTHON_API bool _Type_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Range_Type();
UNREALENGINEPYTHON_API bool _Range_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Slice_Type();
UNREALENGINEPYTHON_API bool _Slice_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Unicode_Type();
UNREALENGINEPYTHON_API bool _Unicode_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _Bytes_Type();
UNREALENGINEPYTHON_API bool _Bytes_Check(PyObject* op);

UNREALENGINEPYTHON_API PyTypeObject* _TraceBack_Type();
UNREALENGINEPYTHON_API bool _TraceBack_Check(PyObject* v);

UNREALENGINEPYTHON_API PyTypeObject* _Tuple_Type();
UNREALENGINEPYTHON_API bool _Tuple_Check(PyObject* op);

//
//    Macros for the types above
//
#define ue_PyList_Type _List_Type()
#define ue_PyBuffer_Type _Buffer_Type()
#define ue_PyClass_Type _Class_Type()
#define ue_PyInstance_Type _Instance_Type()
#define ue_PyMethod_Type _Method_Type()
#define ue_PyCObject_Type _CObject_Type()
#define ue_PyComplex_Type _Complex_Type()
#define ue_PyDict_Type _Dict_Type()
#define ue_PyFile_Type _File_Type()
#define ue_PyFloat_Type _Float_Type()
#define ue_PyFrame_Type _Frame_Type()
#define ue_PyFunction_Type _Function_Type()
#define ue_PyBool_Type _Bool_Type()
#define ue_PyInt_Type _Int_Type()
#define ue_PyList_Type _List_Type()
#define ue_PyLong_Type _Long_Type()
#define ue_PyCFunction_Type _CFunction_Type()
#define ue_PyModule_Type _Module_Type()
#define ue_PyType_Type _Type_Type()
#define ue_PyRange_Type _Range_Type()
#define ue_PySlice_Type _Slice_Type()
#define ue_PyUnicode_Type _Unicode_Type()
#define ue_PyBytes_Type _Bytes_Type()
#define ue_PyTraceBack_Type _TraceBack_Type()
#define ue_PyTuple_Type _Tuple_Type()

UNREALENGINEPYTHON_API int& _Py_DebugFlag();
UNREALENGINEPYTHON_API int& _Py_InteractiveFlag();
UNREALENGINEPYTHON_API int& _Py_OptimizeFlag();
UNREALENGINEPYTHON_API int& _Py_NoSiteFlag();
UNREALENGINEPYTHON_API int& _Py_TabcheckFlag();
UNREALENGINEPYTHON_API int& _Py_VerboseFlag();
UNREALENGINEPYTHON_API int& _Py_UnicodeFlag();

UNREALENGINEPYTHON_API void ue_Py_XINCREF(void* op);
UNREALENGINEPYTHON_API void ue_Py_XDECREF(void* op);

UNREALENGINEPYTHON_API char* __Py_PackageContext();
