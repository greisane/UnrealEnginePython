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
PyObject* _Exc_Exception();
PyObject* _Exc_StandardError();
PyObject* _Exc_ArithmeticError();
PyObject* _Exc_LookupError();

PyObject* _Exc_AssertionError();
PyObject* _Exc_AttributeError();
PyObject* _Exc_EOFError();
PyObject* _Exc_FloatingPointError();
PyObject* _Exc_EnvironmentError();
PyObject* _Exc_IOError();
PyObject* _Exc_OSError();
PyObject* _Exc_ImportError();
PyObject* _Exc_IndexError();
PyObject* _Exc_KeyError();
PyObject* _Exc_KeyboardInterrupt();
PyObject* _Exc_MemoryError();
PyObject* _Exc_NameError();
PyObject* _Exc_OverflowError();
PyObject* _Exc_RuntimeError();
PyObject* _Exc_NotImplementedError();
PyObject* _Exc_SyntaxError();
PyObject* _Exc_SystemError();
PyObject* _Exc_SystemExit();
PyObject* _Exc_TypeError();
PyObject* _Exc_ValueError();
PyObject* _Exc_ZeroDivisionError();

PyObject* _Exc_MemoryErrorInst();

PyObject* _Exc_IndentationError();
PyObject* _Exc_TabError();
PyObject* _Exc_UnboundLocalError();
PyObject* _Exc_UnicodeError();

//
//    Wrap Object variables as function calls
//
PyObject* _None();

PyObject* _False();
PyObject* _True();

//
//    Macros for the above
//
#define ue_PyExc_Exception _Exc_Exception()
#define ue_PyExc_StandardError _Exc_StandardError()
#define ue_PyExc_ArithmeticError _Exc_ArithmeticError()
#define ue_PyExc_LookupError _Exc_LookupError()
#define ue_PyExc_AssertionError _Exc_AssertionError()
#define ue_PyExc_AttributeError _Exc_AttributeError()
#define ue_PyExc_EOFError _Exc_EOFError()
#define ue_PyExc_FloatingPointError _Exc_FloatingPointError()
#define ue_PyExc_EnvironmentError _Exc_EnvironmentError()
#define ue_PyExc_IOError _Exc_IOError()
#define ue_PyExc_OSError _Exc_OSError()
#define ue_PyExc_ImportError _Exc_ImportError()
#define ue_PyExc_IndexError _Exc_IndexError()
#define ue_PyExc_KeyError _Exc_KeyError()
#define ue_PyExc_KeyboardInterrupt _Exc_KeyboardInterrupt()
#define ue_PyExc_MemoryError _Exc_MemoryError()
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
#define ue_PyExc_WindowsError _Exc_WindowsError()
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
PyTypeObject* _List_Type();
bool _List_Check(PyObject* o);

PyTypeObject* _Buffer_Type();
bool _Buffer_Check(PyObject* op);

PyTypeObject* _Class_Type();
bool _Class_Check(PyObject* op);

PyTypeObject* _Instance_Type();
bool _Instance_Check(PyObject* op);

PyTypeObject* _Method_Type();
bool _Method_Check(PyObject* op);

PyTypeObject* _CObject_Type();
bool _CObject_Check(PyObject* op);

PyTypeObject* _Complex_Type();
bool _Complex_Check(PyObject* op);

PyTypeObject* _Dict_Type();
bool _Dict_Check(PyObject* op);

PyTypeObject* _File_Type();
bool _File_Check(PyObject* op);

PyTypeObject* _Float_Type();
bool _Float_Check(PyObject* op);

PyTypeObject* _Frame_Type();
bool _Frame_Check(PyObject* op);

PyTypeObject* _Function_Type();
bool _Function_Check(PyObject* op);

PyTypeObject* _Bool_Type();
bool _Boolean_Check(PyObject* op);

PyTypeObject* _Int_Type();
bool _Int_Check(PyObject* op);

PyTypeObject* _List_Type();
bool _List_Check(PyObject* op);

PyTypeObject* _Long_Type();
bool _Long_Check(PyObject* op);

PyTypeObject* _CFunction_Type();
bool _CFunction_Check(PyObject* op);

PyTypeObject* _Module_Type();
bool _Module_Check(PyObject* op);

PyTypeObject* _Type_Type();
bool _Type_Check(PyObject* op);

PyTypeObject* _Range_Type();
bool _Range_Check(PyObject* op);

PyTypeObject* _Slice_Type();
bool _Slice_Check(PyObject* op);

PyTypeObject* _Unicode_Type();
bool _Unicode_Check(PyObject* op);

PyTypeObject* _Bytes_Type();
bool _Bytes_Check(PyObject* op);

PyTypeObject* _TraceBack_Type();
bool _TraceBack_Check(PyObject* v);

PyTypeObject* _Tuple_Type();
bool _Tuple_Check(PyObject* op);

int& _Py_DebugFlag();
int& _Py_InteractiveFlag();
int& _Py_OptimizeFlag();
int& _Py_NoSiteFlag();
int& _Py_TabcheckFlag();
int& _Py_VerboseFlag();
int& _Py_UnicodeFlag();

void _XINCREF(PyObject* op);
void _XDECREF(PyObject* op);

char* __Py_PackageContext();
