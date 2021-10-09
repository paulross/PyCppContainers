//
// Created by Paul Ross on 09/10/2021.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONTAINER_CONVERT_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONTAINER_CONVERT_H

#include <Python.h>


namespace Python_Cpp_Containers {

#pragma mark == Container Check, Create, Len, Set, Get

#pragma mark -- Tuple Check, Create, Len, Set, Get

    // Tuple wrappers around PyTuple_Check, PyTuple_New, PyTuple_Size, PyTuple_SET_ITEM, PyTuple_GET_ITEM
    int py_tuple_check(PyObject *op);

    PyObject *py_tuple_new(size_t len);

    Py_ssize_t py_tuple_len(PyObject *op);

    int py_tuple_set(PyObject *tuple_p, size_t pos, PyObject *op);

    PyObject *py_tuple_get(PyObject *tuple_p, size_t pos);

#pragma mark -- List Check, Create, Len, Set, Get

    // List wrappers around PyList_Check, PyList_New, PyList_Size, PyList_SET_ITEM, PyList_GET_ITEM
    int py_list_check(PyObject *op);

    PyObject *py_list_new(size_t len);

    Py_ssize_t py_list_len(PyObject *op);

    int py_list_set(PyObject *list_p, size_t pos, PyObject *op);

    PyObject *py_list_get(PyObject *list_p, size_t pos);

#pragma mark -- Set and Frozen set Check, Create, Length.

    // Wrappers around macros
    int py_set_check(PyObject *op);

    PyObject *py_set_new(PyObject *iterable = NULL);

    int py_set_add(PyObject *set, PyObject *key);

    Py_ssize_t py_set_len(PyObject *op);

    int py_frozenset_check(PyObject *op);

    PyObject *py_frozenset_new(PyObject *iterable = NULL);

    Py_ssize_t py_frozenset_len(PyObject *op);

} // namespace Python_Cpp_Containers

#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONTAINER_CONVERT_H
