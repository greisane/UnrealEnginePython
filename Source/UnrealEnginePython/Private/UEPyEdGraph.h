#pragma once



#include "UnrealEnginePython.h"

#if WITH_EDITOR
PyObject *py_ue_graph_add_node_call_function(ue_PyUObject *, PyObject *);
PyObject *py_ue_graph_add_node_custom_event(ue_PyUObject *, PyObject *);
PyObject *py_ue_graph_add_node_variable_get(ue_PyUObject *, PyObject *);
PyObject *py_ue_graph_add_node_variable_set(ue_PyUObject *, PyObject *);

PyObject *py_ue_node_pins(ue_PyUObject *, PyObject *);
PyObject *py_ue_node_find_pin(ue_PyUObject *, PyObject *);
#endif