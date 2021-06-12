//
//  python_convert.cpp
//  PythonC++
//
//  Created by Paul Ross on 22/11/2018.
//  Copyright © 2018 Paul Ross. All rights reserved.
//
// This contains the non-template hand maintained functions.
// Basically type conversion and checking functions.
//

#include "python_convert.h"

namespace Python_Cpp_Containers {
    // Conversion functions - objects.
    // Bool/bool
    PyObject *py_bool_from_bool(bool const &b) {
        if (b) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    bool py_bool_as_bool(PyObject *op) {
        assert(py_bool_check(op));
        if (op == Py_True) {
            return true;
        }
        return false;
    }
    int py_bool_check(PyObject *op) {
        return PyBool_Check(op);
    }
    // Long/long
    PyObject *py_long_from_long(const long &l) {
        return PyLong_FromLong(l);
    }
    long py_long_as_long(PyObject *op) {
        assert(py_long_check(op));
        return PyLong_AsLong(op);
    }
    int py_long_check(PyObject *op) {
        return PyLong_Check(op);
    }
    // Float/double
    PyObject *py_float_from_double(const double &d) {
        return PyFloat_FromDouble(d);
    }
    double py_float_as_double(PyObject *op) {
        assert(py_float_check(op));
        return PyFloat_AsDouble(op);
    }
    int py_float_check(PyObject *op) {
        return PyFloat_Check(op);
    }
    // Complex/complex
    PyObject *py_complex_from_complex(const std::complex<double> &c) {
        return PyComplex_FromDoubles(c.real(), c.imag());
    }
    std::complex<double> py_complex_as_complex(PyObject *op) {
        assert(py_complex_check(op));
        return std::complex<double>(PyComplex_RealAsDouble(op), PyComplex_ImagAsDouble(op));
    }
    int py_complex_check(PyObject *op) {
        return PyComplex_Check(op);
    }
    // Bytes to/from string
    PyObject *py_bytes_from_string(const std::string &s) {
        return PyBytes_FromStringAndSize(s.c_str(), s.size());
    }
    std::string py_bytes_as_string(PyObject *op) {
        assert(op);
        assert(py_bytes_check(op));
        std::string ret(PyBytes_AS_STRING(op), PyBytes_GET_SIZE(op));
        return ret;
    }
    int py_bytes_check(PyObject *op) {
        return PyBytes_Check(op);
    }

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
    PyObject *py_set_new() {
        return PySet_New(NULL);
    }
    Py_ssize_t py_set_len(PyObject *op) {
        return PySet_Size(op);
    }

    int py_frozenset_check(PyObject *op) {
        return PyFrozenSet_Check(op);
    }
    PyObject *py_frozenset_new() {
        return PyFrozenSet_New(NULL);
    }
    Py_ssize_t py_frozenset_len(PyObject *op) {
        return PySet_Size(op);
    }

} // namespace Python_Cpp_Containers
