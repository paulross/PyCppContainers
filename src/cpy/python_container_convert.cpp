//
// Created by Paul Ross on 09/10/2021.
//

#include "python_container_convert.h"

namespace Python_Cpp_Containers {

    // Conversion functions - Containers
    // Tuple check, create, set, get functions.
    int py_tuple_check(PyObject *op) {
        return PyTuple_Check(op);
    }
    PyObject *py_tuple_new(size_t len) {
        return PyTuple_New(len);
    }
    Py_ssize_t py_tuple_len(PyObject *op) {
        return PyTuple_Size(op);
    }
    int py_tuple_set(PyObject *tuple_p, size_t pos, PyObject *op) {
        PyTuple_SET_ITEM(tuple_p, pos, op);
        return 0;
    }
    PyObject *py_tuple_get(PyObject *tuple_p, size_t pos) {
        return PyTuple_GET_ITEM(tuple_p, pos);
    }
    // List wrappers around PyList_Check, PyList_New, PyList_SET_ITEM, PyList_GET_ITEM
    int py_list_check(PyObject *op) {
        return PyList_Check(op);
    }
    PyObject *py_list_new(size_t len) {
        return PyList_New(len);
    }
    Py_ssize_t py_list_len(PyObject *op) {
        return PyList_Size(op);
    }
    int py_list_set(PyObject *list_p, size_t pos, PyObject *op) {
        PyList_SET_ITEM(list_p, pos, op);
        return 0;
    }
    PyObject *py_list_get(PyObject *list_p, size_t pos) {
        return PyList_GET_ITEM(list_p, pos);
    }

#pragma mark -- Set and Frozen set Check

    // Wrappers around macos
    int py_set_check(PyObject *op) {
        return PySet_Check(op);
    }
    PyObject *py_set_new(PyObject *iterable) {
        return PySet_New(iterable);
    }
    int py_set_add(PyObject *set, PyObject*key) {
        return PySet_Add(set, key);
    }
    Py_ssize_t py_set_len(PyObject *op) {
        return PySet_Size(op);
    }

    int py_frozenset_check(PyObject *op) {
        return PyFrozenSet_Check(op);
    }
    PyObject *py_frozenset_new(PyObject *iterable) {
        return PyFrozenSet_New(iterable);
    }
    Py_ssize_t py_frozenset_len(PyObject *op) {
        return PySet_Size(op);
    }

} // namespace Python_Cpp_Containers
