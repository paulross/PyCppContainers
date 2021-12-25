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

#include "python_object_convert.h"

namespace Python_Cpp_Containers {
    // Conversion functions - objects.
    // Bool/bool
    PyObject *cpp_bool_to_py_bool(bool const &b) {
        if (b) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    bool py_bool_to_cpp_bool(PyObject *op) {
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
    PyObject *cpp_long_to_py_long(const long &l) {
        return PyLong_FromLong(l);
    }
    long py_long_to_cpp_long(PyObject *op) {
        assert(py_long_check(op));
        return PyLong_AsLong(op);
    }
    int py_long_check(PyObject *op) {
        return PyLong_Check(op);
    }
    // Float/double
    PyObject *cpp_double_to_py_float(const double &d) {
        return PyFloat_FromDouble(d);
    }
    double py_float_to_cpp_double(PyObject *op) {
        assert(py_float_check(op));
        return PyFloat_AsDouble(op);
    }
    int py_float_check(PyObject *op) {
        return PyFloat_Check(op);
    }
    // Complex/complex
    PyObject *cpp_complex_to_py_complex(const std::complex<double> &c) {
        return PyComplex_FromDoubles(c.real(), c.imag());
    }
    std::complex<double> py_complex_to_cpp_complex(PyObject *op) {
        assert(py_complex_check(op));
        return std::complex<double>(PyComplex_RealAsDouble(op), PyComplex_ImagAsDouble(op));
    }
    int py_complex_check(PyObject *op) {
        return PyComplex_Check(op);
    }
    // Bytes to/from string
    PyObject *cpp_vector_char_to_py_bytes(const std::vector<char> &s) {
        return PyBytes_FromStringAndSize(s.data(), s.size());
    }
    std::vector<char> py_bytes_to_cpp_vector_char(PyObject *op) {
        assert(op);
        assert(py_bytes_check(op));
        std::vector<char> ret(PyBytes_GET_SIZE(op));
        char *pChar = PyBytes_AS_STRING(op);
        for(Py_ssize_t i = 0; i < PyBytes_GET_SIZE(op); ++i, ++pChar) {
            ret[i] = *pChar;
        }
        return ret;
    }
    int py_bytes_check(PyObject *op) {
        return PyBytes_Check(op);
    }
    // Bytearray to/from string
    PyObject *cpp_string_to_py_bytearray(const std::vector<char> &s) {
        return PyByteArray_FromStringAndSize(s.data(), s.size());
    }
    std::vector<char> py_bytearray_to_cpp_string(PyObject *op) {
        assert(op);
        assert(py_bytearray_check(op));
        std::vector<char> ret(PyByteArray_GET_SIZE(op));
        char *pChar = PyByteArray_AS_STRING(op);
        for(Py_ssize_t i = 0; i < PyByteArray_GET_SIZE(op); ++i, ++pChar) {
            ret[i] = *pChar;
        }
        return ret;
    }
    int py_bytearray_check(PyObject *op) {
        return PyByteArray_Check(op);
    }
    // str to/from string
    PyObject *cpp_string_to_py_unicode(const std::string &s) {
        return PyUnicode_FromStringAndSize(s.c_str(), s.size());
    }
    std::string py_unicode_to_cpp_string(PyObject *op) {
        assert(op);
        assert(py_unicode_check(op));
        std::string ret((const char *)PyUnicode_1BYTE_DATA(op), PyUnicode_GET_LENGTH(op));
        return ret;
    }
    int py_unicode_check(PyObject *op) {
        return PyUnicode_Check(op);
    }

} // namespace Python_Cpp_Containers
