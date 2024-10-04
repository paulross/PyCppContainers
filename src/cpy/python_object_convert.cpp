///
///  python_convert.cpp
///  PythonC++
///
///  Created by Paul Ross on 22/11/2018.
///  Copyright © 2018 Paul Ross. All rights reserved.
///
/// This contains the non-template hand maintained functions.
/// Basically type conversion and checking functions.
///

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
        std::vector<char> ret(PyBytes_AS_STRING(op), PyBytes_AS_STRING(op) + PyBytes_GET_SIZE(op));
        return ret;
    }
    int py_bytes_check(PyObject *op) {
        return PyBytes_Check(op);
    }
    // Bytearray to/from string
    PyObject *cpp_string_to_py_bytearray(const std::vector<char> &s) {
        // TODO: Delete?
        return PyByteArray_FromStringAndSize(s.data(), s.size());
    }
    std::vector<char> py_bytearray_to_cpp_string(PyObject *op) {
        // TODO: Delete?
        assert(op);
        assert(py_bytearray_check(op));
        std::vector<char> ret(PyByteArray_AS_STRING(op), PyByteArray_AS_STRING(op) + PyByteArray_GET_SIZE(op));
        return ret;
    }
    int py_bytearray_check(PyObject *op) {
        // TODO: Delete?
        return PyByteArray_Check(op);
    }

#pragma mark # str to/from string
#pragma mark # 8 bit strings.

    /** Returns 1 if the Python object is a 8 bit Unicode string. */
    int py_unicode8_check(PyObject *op) {
        return PyUnicode_Check(op) && PyUnicode_KIND(op) == PyUnicode_1BYTE_KIND;
    }

    /** Create a Python 16 bit unicode object from a C++ std::string. */
    PyObject *cpp_string_to_py_unicode8(const std::string &s) {
        return PyUnicode_FromKindAndData(PyUnicode_1BYTE_KIND, s.c_str(), s.size());
    }

    /** Converts a Python 8 bit Unicode string to a C++ \c std::string. */
    std::string py_unicode8_to_cpp_string(PyObject *op) {
        assert(op);
        assert(py_unicode8_check(op));
        std::string ret((const char *)PyUnicode_1BYTE_DATA(op), PyUnicode_GET_LENGTH(op));
        return ret;
    }

#pragma mark # 16 bit strings.

    /** Returns 1 if the Python object is a 16 bit Unicode string. */
    int py_unicode16_check(PyObject *op) {
        return PyUnicode_Check(op) && PyUnicode_KIND(op) == PyUnicode_2BYTE_KIND;
    }

    /**
     * Create a Python 16 bit unicode object from a C++ std::u16string.
     *
     * NOTE: We can't use <tt>PyUnicode_FromKindAndData(PyUnicode_2BYTE_KIND, (Py_UCS2 *)s.c_str(), s.size())</tt>
     * since that function may produce a \c PyUnicode_1BYTE_KIND if the character values permit.
     * Instead we use <tt>PyUnicode_New(s.size(), maxchar = 65535)</tt> to compel a 2 byte word size and then copy each
     * character individually.
     *
     * See: https://docs.python.org/3/c-api/unicode.html#c.PyUnicode_New
     *
     * @param s The C++ string.
     * @return The Python string.
     */
    PyObject *cpp_u16string_to_py_unicode16(const std::u16string &s) {
        assert(! PyErr_Occurred());
        PyObject *ret = PyUnicode_New(s.size(), 65535);
        assert(py_unicode16_check(ret));
        for (std::u16string::size_type i = 0; i < s.size(); ++i) {
            int result = PyUnicode_WriteChar(ret, i, s[i]);
            if (result) {
                PyErr_Format(PyExc_SystemError,
                             "PyUnicode_WriteChar() failed to write at [%ld] returning %d.", i, result
                );
                Py_DECREF(ret);
                return NULL;
            }
        }
        assert(py_unicode16_check(ret));
        assert(! PyErr_Occurred());
        return ret;
    }

    /** Converts a Python 16 bit Unicode string to a C++ \c std::u16string. */
    std::u16string py_unicode16_to_cpp_u16string(PyObject *op) {
        assert(op);
        assert(py_unicode16_check(op));
        std::u16string ret((const char16_t *)PyUnicode_2BYTE_DATA(op), PyUnicode_GET_LENGTH(op));
        return ret;
    }

#pragma mark # 32 bit strings.

    /** Returns 1 if the Python object is a 32 bit Unicode string. */
    int py_unicode32_check(PyObject *op) {
        int unicode_kind = PyUnicode_KIND(op);
        return PyUnicode_Check(op) && unicode_kind == PyUnicode_4BYTE_KIND;
    }

    /**
     * Create a Python 32 bit unicode object from a C++ std::u32string.
     *
     * NOTE: We can't use <tt>PyUnicode_FromKindAndData(PyUnicode_4BYTE_KIND, (Py_UCS4 *)s.c_str(), s.size())</tt>
     * since that function may produce a \c PyUnicode_1BYTE_KIND or \c PyUnicode_2BYTE_KIND if the character values
     * permit.
     * Instead we use <tt>PyUnicode_New(s.size(), maxchar = 1114111)</tt> to compel a 4 byte word size and then copy
     * each character individually.
     *
     * See: https://docs.python.org/3/c-api/unicode.html#c.PyUnicode_New
     *
     * @param s The C++ string.
     * @return The Python string.
     */
    PyObject *cpp_u32string_to_py_unicode32(const std::u32string &s) {
        assert(! PyErr_Occurred());
        PyObject *ret = PyUnicode_New(s.size(), 1114111);
        assert(py_unicode32_check(ret));
        for (std::u32string::size_type i = 0; i < s.size(); ++i) {
            int result = PyUnicode_WriteChar(ret, i, s[i]);
            if (result) {
                PyErr_Format(PyExc_SystemError,
                             "PyUnicode_WriteChar() failed to write at [%ld] returning %d.", i, result
                );
                Py_DECREF(ret);
                return NULL;
            }
        }
        assert(py_unicode32_check(ret));
        assert(! PyErr_Occurred());
        return ret;
    }

    /** Converts a Python 32 bit Unicode string to a C++ \c std::u32string. */
    std::u32string py_unicode32_to_cpp_u32string(PyObject *op) {
        assert(op);
        assert(py_unicode32_check(op));
        std::u32string ret((const char32_t *)PyUnicode_4BYTE_DATA(op), PyUnicode_GET_LENGTH(op));
        return ret;
    }

} // namespace Python_Cpp_Containers
