//
// Created by Paul Ross on 09/10/2021.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_OBJECT_CONVERT_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_OBJECT_CONVERT_H

#include <Python.h>

#include <complex>
#include <string>
#include <vector>

namespace Python_Cpp_Containers {

#pragma mark == Object Conversion Code

    // Conversion functions.

#pragma mark -- Boolean/bool Conversion Code

    // Bool/bool
    /**
     * Converts a C++ \c bool to a Python \c bool.
     * This always succeeds.
     *
     * @param b Value to convert.
     * @return Value equivalent in Python.
     */
    PyObject *cpp_bool_to_py_bool(bool const &b);

    /**
     * Converts a Python \c bool to a C++ \c  bool.
     * This asserts that the given value is a Python bool.
     * If asserts are enabled then this asserts that the argument is a Python \c bool objects.
     * If asserts are not enabled then this is undefined.
     *
     * @param op Python value to convert.
     * @return \c true or \c false.
     */
    bool py_bool_to_cpp_bool(PyObject *op);

    /**
     * Return non-zero if the given value is a Python \c bool type.
     *
     * @param op The Python object to check to be a bool type.
     * @return Zero if not a Python \c bool, non-zero if a Python \c bool.
     */
    int py_bool_check(PyObject *op);

#pragma mark -- Long Integer/long Conversion Code

    // Long/long
    /**
     * Converts a C++ \c long to a Python \c long.
     * This always succeeds.
     *
     * @param b Value to convert.
     * @return Value equivalent in Python.
     */
    PyObject *cpp_long_to_py_long(const long &l);

    /**
     * Converts a Python \c long to a C++ \c long.
     * This asserts that the given value is a Python long.
     * If asserts are enabled then this asserts that the argument is a Python \c long objects.
     * If asserts are not enabled then this is undefined.
     *
     * @param op Python value to convert.
     * @return The C++ \c long.
     */
    long py_long_to_cpp_long(PyObject *op);

    /**
     * Return non-zero if the given value is a Python \c long type.
     *
     * @param op The Python object to check to be a \c long type.
     * @return Zero if not a Python \c long, non-zero if a Python \c long.
     */
    int py_long_check(PyObject *op);

#pragma mark -- Float/double Conversion Code

    // Float/double
    /**
     * Converts a C++ \c double to a Python \c float.
     * This always succeeds.
     *
     * @param b Value to convert.
     * @return Value equivalent in Python.
     */
    PyObject *cpp_double_to_py_float(const double &d);

    /**
     * Converts a Python \c float to a C++ \c float.
     * This asserts that the given value is a Python float.
     * If asserts are enabled then this asserts that the argument is a Python \c double objects.
     * If asserts are not enabled then this is undefined.
     *
     * @param op Python value to convert.
     * @return The C++ \c float.
     */
    double py_float_to_cpp_double(PyObject *op);

    /**
     * Return non-zero if the given value is a Python \c float type.
     *
     * @param op The Python object to check to be a \c float type.
     * @return Zero if not a Python \c float, non-zero if a Python \c float.
     */
    int py_float_check(PyObject *op);

#pragma mark -- Complex Conversion Code

    // Complex/complex
    /**
     * Converts a C++ \c std::complex to a Python \c complex.
     * This always succeeds.
     *
     * @param b Value to convert.
     * @return Value equivalent in Python.
     */
    PyObject *cpp_complex_to_py_complex(const std::complex<double> &c);

    /**
     * Converts a Python \c complex to a C++ \c std::complex.
     * This asserts that the given value is a Python complex.
     * If asserts are enabled then this asserts that the argument is a Python \c complex objects.
     * If asserts are not enabled then this is undefined.
     *
     * @param op Python value to convert.
     * @return The C++ \c std::complex.
     */
    std::complex<double> py_complex_to_cpp_complex(PyObject *op);

    /**
     * Return non-zero if the given value is a Python \c complex type.
     *
     * @param op The Python object to check to be a \c complex type.
     * @return Zero if not a Python \c complex, non-zero if a Python \c complex.
     */
    int py_complex_check(PyObject *op);

#pragma mark -- Bytes/std::vector<char> Conversion Code

    // Bytes to/from string
    /**
     * Converts a C++ \c std::complex<char> to a Python \c bytes.
     * This always succeeds.
     *
     * @param b Value to convert.
     * @return Value equivalent in Python.
     */
    PyObject *cpp_vector_char_to_py_bytes(const std::vector<char> &s);

    /**
     * Converts a Python \c bytes to a C++ \c std::vector<char>.
     * This asserts that the given value is a Python \c bytes.
     * If asserts are enabled then this asserts that the argument is a Python \c bytes objects.
     * If asserts are not enabled then this is undefined.
     *
     * @param op Python value to convert.
     * @return The C++ \c std::vector<char>.
     */
    std::vector<char> py_bytes_to_cpp_vector_char(PyObject *op);

    /**
     * Return non-zero if the given value is a Python \c bytes type.
     *
     * @param op The Python object to check to be a \c bytes type.
     * @return Zero if not a Python \c bytes, non-zero if a Python \c bytes.
     */
    int py_bytes_check(PyObject *op);

#pragma mark -- bytearray/std::vector<char> Conversion Code

    // bytearray to/from string
    // TODO: Delete?
    /**
     * Converts a C++ \c std::vector<char> to a Python \c bytearray.
     * This always succeeds.
     *
     * @param b Value to convert.
     * @return Value equivalent in Python.
     */
    PyObject *cpp_vector_char_to_py_bytearray(const std::vector<char> &s);

    // TODO: Delete?
    /**
     * Converts a Python \c bytearray to a C++ \c std::vector<char>.
     * This asserts that the given value is a Python \c bytearray.
     * If asserts are enabled then this asserts that the argument is a Python \c bytearray objects.
     * If asserts are not enabled then this is undefined.
     *
     * @param op Python value to convert.
     * @return The C++ \c std::vector<char>.
     */
    std::vector<char> py_bytearray_to_cpp_vector_char(PyObject *op);

    // TODO: Delete?
    /**
     * Return non-zero if the given value is a Python \c bytearray type.
     *
     * @param op The Python object to check to be a \c bytearray type.
     * @return Zero if not a Python \c bytearray, non-zero if a Python \c bytearray.
     */
    int py_bytearray_check(PyObject *op);

#pragma mark -- str/std::string Conversion Code

    // Python str (unicode) to/from string
    /**
     * Converts a C++ \c std::string to a Python \c str.
     * This always succeeds.
     *
     * @param b Value to convert.
     * @return Value equivalent in Python.
     */
    PyObject *cpp_string_to_py_unicode(const std::string &s);

    /**
     * Converts a Python \c str to a C++ \c std::string.
     * This asserts that the given value is a Python \c str.
     * If asserts are enabled then this asserts that the argument is a Python \c str objects.
     * If asserts are not enabled then this is undefined.
     *
     * @param op Python value to convert.
     * @return The C++ \c std::str.
     */
    std::string py_unicode_to_cpp_string(PyObject *op);

    /**
     * Return non-zero if the given value is a Python \c str type.
     *
     * @param op The Python object to check to be a \c str type.
     * @return Zero if not a Python \c str, non-zero if a Python \c str.
     */
    int py_unicode_check(PyObject *op);

} // namespace Python_Cpp_Containers
#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_OBJECT_CONVERT_H
