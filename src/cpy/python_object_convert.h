//
// Created by Paul Ross on 09/10/2021.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_OBJECT_CONVERT_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_OBJECT_CONVERT_H

#include <Python.h>

#include <complex>
#include <string>

namespace Python_Cpp_Containers {

#pragma mark == Object Conversion Code

    // Conversion functions.

#pragma mark -- Boolean/bool Conversion Code

    // Bool/bool
    /**
     * Converts a C++ bool to a Python bool.
     * This always succeeds.
     *
     * @param b Value to convert.
     * @return Value equivalent Python.
     */
    PyObject *cpp_bool_to_py_bool(bool const &b);

    /**
     * Converts a Python bool to a C++ bool.
     * This asserts that the given value is a Python bool.
     * If asserts are not enabled then this returns false for non-bool Python objects.
     *
     * @param op Value to convert.
     * @return true or false.
     */
    bool py_bool_to_cpp_bool(PyObject *op);

    /**
     * Return non-zero if the given value is a Python bool type.
     *
     * @param op The Python object to check to be a bool type.
     * @return Zero if not a Python bool, non-zero if a Python bool.
     */
    int py_bool_check(PyObject *op);

#pragma mark -- Long Integer/long Conversion Code

    // Long/long
    PyObject *cpp_long_to_py_long(const long &l);

    long py_long_to_cpp_long(PyObject *op);

    int py_long_check(PyObject *op);

#pragma mark -- Float/double Conversion Code

    // Float/double
    PyObject *cpp_double_to_py_float(const double &d);

    double py_float_to_cpp_double(PyObject *op);

    int py_float_check(PyObject *op);

#pragma mark -- Complex Conversion Code

    // Complex/complex
    PyObject *cpp_complex_to_py_complex(const std::complex<double> &c);

    std::complex<double> py_complex_to_cpp_complex(PyObject *op);

    int py_complex_check(PyObject *op);

#pragma mark -- Bytes/std::string Conversion Code

    // Bytes to/from string
    PyObject *cpp_string_to_py_bytes(const std::string &s);

    std::string py_bytes_to_cpp_string(PyObject *op);

    int py_bytes_check(PyObject *op);

#pragma mark -- bytearray/std::string Conversion Code

    // bytearray to/from string
    PyObject *cpp_string_to_py_bytearray(const std::string &s);

    std::string py_bytearray_to_cpp_string(PyObject *op);

    int py_bytearray_check(PyObject *op);

    // Python str (unicode) to/from string
    PyObject *cpp_string_to_py_unicode(const std::string &s);

    std::string py_unicode_to_cpp_string(PyObject *op);

    int py_unicode_check(PyObject *op);

} // namespace Python_Cpp_Containers
#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_OBJECT_CONVERT_H
