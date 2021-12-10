//
// Created by Paul Ross on 10/12/2021.
//
#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include "structmember.h"

static PyObject *
dict_count_PyDict_Next(PyObject *Py_UNUSED(module), PyObject *arg) {
    long ret = 0;
    PyObject *key, *value;
    Py_ssize_t pos = 0;

    while (PyDict_Next(arg, &pos, &key, &value)) {
        ++ret;
    }
    return PyLong_FromLong(ret);
}

static PyObject *
dict_count_PyIter_Next(PyObject *Py_UNUSED(module), PyObject *arg) {
    long ret = 0;
    PyObject *iterator = PyObject_GetIter(arg);
    PyObject *item;

    if (iterator) {
        while ((item = PyIter_Next(iterator))) {
            ++ret;
            Py_DECREF(item);
        }
        Py_DECREF(iterator);
    }
    return PyLong_FromLong(ret);
}

/**
 * The Python Extension methods.
 */
static PyMethodDef cDictIterMethods[] = {
        {"dict_count_PyDict_Next", dict_count_PyDict_Next, METH_O,
         "Iterates through a dict with PyDict_Next()."},
        {"dict_count_PyIter_Next", dict_count_PyIter_Next, METH_O,
         "Iterates through a dict with PyIter_Next()."},
        {NULL, NULL, 0, NULL}        /* Sentinel */
};

/**
 * The Python extension definition.
 */
static struct PyModuleDef cDictItermodule = {
        PyModuleDef_HEAD_INIT,
        "cDictIter",
        "Dictionary C API.",
        -1,
        cDictIterMethods,
        NULL,
        NULL,
        NULL,
        NULL
};

/**
 * The Python module initialisation.
 */
PyMODINIT_FUNC
PyInit_cDictIter(void) {
    PyObject *m;

    m = PyModule_Create(&cDictItermodule);
    if (m == NULL)
        return NULL;

    return m;
}

