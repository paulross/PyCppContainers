//
// Created by Paul Ross on 18/06/2021.
//
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"

static PyModuleDef cPyCppContainersmodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "cPyCppContainers",
        .m_doc = "Example extension module that converts Python containers to and from their C++ equivalents.",
        .m_size = -1,
};

PyMODINIT_FUNC
PyInit_cPyCppContainers(void) {
    PyObject *m;
//    if (PyType_Ready(&CustomType) < 0)
//        return NULL;

    m = PyModule_Create(&cPyCppContainersmodule);
    if (m == NULL)
        return NULL;

//    Py_INCREF(&CustomType);
//    if (PyModule_AddObject(m, "Custom", (PyObject *) &CustomType) < 0) {
//        Py_DECREF(&CustomType);
//        Py_DECREF(m);
//        return NULL;
//    }

    return m;
}

