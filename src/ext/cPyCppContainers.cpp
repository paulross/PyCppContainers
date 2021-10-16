//
// Created by Paul Ross on 18/06/2021.
//
#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include "structmember.h"

#include "cpy/python_convert.h"
using namespace Python_Cpp_Containers;

static PyObject *
list_x2(PyObject *Py_UNUSED(module), PyObject *arg) {
    std::vector<double> vec;
    // py_list_to_cpp_std_vector() will return non-zero if the Python
    // argument can not be converted to a std::vector<double>
    // and a Python exception will be set.
    if (!py_list_to_cpp_std_vector(arg, vec)) {
        for (size_t i = 0; i < vec.size(); ++i) {
            vec[i] *= 2.0;
        }
        // cpp_std_vector_to_py_list() returns NULL on failure
        // and a Python exception will be set.
        return cpp_std_vector_to_py_list(vec);
    }
    return NULL;
}

static PyMethodDef cPyCppContainersMethods[] = {
        {"list_x2", list_x2, METH_O,
         "Take a list of floats and return a new list with the values doubled."},
        {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef cPyCppContainersmodule = {
        PyModuleDef_HEAD_INIT,
        "cPyCppContainers",
        "Example extension module that converts Python containers to and from their C++ equivalents.",
        -1,
        cPyCppContainersMethods,
        NULL,
        NULL,
        NULL,
        NULL
};

PyMODINIT_FUNC
PyInit_cPyCppContainers(void) {
    PyObject *m;

    m = PyModule_Create(&cPyCppContainersmodule);
    if (m == NULL)
        return NULL;

    return m;
}

