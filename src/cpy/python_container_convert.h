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
    /**
     * Return non-zero if the given value is a Python \c tuple.
     * This is a wrapper around \c PyTuple_Check
     *
     * @param op The Python object to check to be a \c tuple.
     * @return Zero if not a Python \c tuple, non-zero if a Python \c tuple.
     */
    int py_tuple_check(PyObject *op);

    /**
     * Creates a new Python \c tuple.
     * This is a wrapper around \c PyTuple_New
     *
     * @param len Required length of the container.
     * @return A new empty container of required length or \c NULL on failure.
     */
    PyObject *py_tuple_new(size_t len);

    /**
     * Returns the length of the Python \c tuple.
     * This is a wrapper around \c PyTuple_Size
     * This is undefined if \c *op is not a \c tuple.
     *
     * @param op The Python \c tuple.
     * @return Length.
     */
    Py_ssize_t py_tuple_len(PyObject *op);

    /**
     * Set a value in the \c tuple.
     * This is a wrapper around \c PyTuple_SET_ITEM
     * This is undefined if passed a non-tuple or the position is out of range.
     *
     * @param tuple_p The Python \c tuple
     * @param pos Index into the tuple to set.
     * @param op Value to set, the reference is stolen.
     * @return 0 on success.
     */
    int py_tuple_set(PyObject *tuple_p, size_t pos, PyObject *op);

    /**
     * Get a value from the \c tuple.
     * This is a wrapper around \c PyTuple_GET_ITEM
     * This is undefined if passed a non-tuple or the position is out of range.
     *
     * @param tuple_p The Python \c tuple
     * @param pos Index into the tuple to get.
     * @param op Value to set, the reference is stolen.
     * @return Value to get, the reference is borrowed.
     */
    PyObject *py_tuple_get(PyObject *tuple_p, size_t pos);

#pragma mark -- List Check, Create, Len, Set, Get

    // List wrappers around PyList_Check, PyList_New, PyList_Size, PyList_SET_ITEM, PyList_GET_ITEM
    /**
     * Return non-zero if the given value is a Python \c list.
     * This is a wrapper around \c PyList_Check
     *
     * @param op The Python object to check to be a \c list.
     * @return Zero if not a Python \c list, non-zero if a Python \c list.
     */
    int py_list_check(PyObject *op);

    /**
     * Creates a new Python \c list.
     * This is a wrapper around \c PyList_New
     *
     * @param len Required length of the container.
     * @return A new empty container of required length or \c NULL on failure.
     */
    PyObject *py_list_new(size_t len);

    /**
     * Returns the length of the Python \c list.
     * This is a wrapper around \c PyList_Size
     * This is undefined if \c *op is not a \c list.
     *
     * @param op The Python \c list.
     * @return Length.
     */
    Py_ssize_t py_list_len(PyObject *op);

    /**
     * Set a value in the \c list.
     * This is a wrapper around \c PyList_SET_ITEM
     * This is undefined if passed a non-list or the position is out of range.
     *
     * @param list_p The Python \c list
     * @param pos Index into the list to set.
     * @param op Value to set, the reference is stolen.
     * @return 0 on success.
     */
    int py_list_set(PyObject *list_p, size_t pos, PyObject *op);

    /**
     * Get a value from the \c list.
     * This is a wrapper around \c PyList_GET_ITEM
     * This is undefined if passed a non-list or the position is out of range.
     *
     * @param list_p The Python \c list
     * @param pos Index into the list to get.
     * @param op Value to set, the reference is stolen.
     * @return Value to get, the reference is borrowed.
     */
    PyObject *py_list_get(PyObject *list_p, size_t pos);

#pragma mark -- Set and Frozen set Check. Note Create, Add, Length are called directly.

    /**
     * Return non-zero if the given value is a Python \c set.
     * This is a wrapper around \c PySet_Check
     *
     * @param op The Python object to check to be a \c set.
     * @return Zero if not a Python \c set, non-zero if a Python \c set.
     */
    int py_set_check(PyObject *op);

    /**
     * Return non-zero if the given value is a Python \c frozenset.
     * This is a wrapper around \c PyFrozenSet_Check
     *
     * @param op The Python object to check to be a \c frozenset.
     * @return Zero if not a Python \c frozenset, non-zero if a Python \c frozenset.
     */
    int py_frozenset_check(PyObject *op);

} // namespace Python_Cpp_Containers

#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONTAINER_CONVERT_H
