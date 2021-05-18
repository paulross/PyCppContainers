//
//  python_convert.cpp
//  PythonC++
//
//  Created by Paul Ross on 22/11/2018.
//  Copyright © 2018 Paul Ross. All rights reserved.
//

#include "python_convert.h"

namespace Python_Cpp_Homogeneous_Containers {

// Conversion functions.
// Float/double
    PyObject *py_float_from_double(const double &d) {
        return PyFloat_FromDouble(d);
    }

    double py_float_as_double(PyObject *op) {
        return PyFloat_AsDouble(op);
    }
    int py_float_check(PyObject *op) {
        return PyFloat_Check(op);
    }
// Long/long
    PyObject *py_long_from_long(const long &l) {
        return PyLong_FromLong(l);
    }
    long py_long_as_long(PyObject *op) {
        return PyLong_AsLong(op);
    }
    int py_long_check(PyObject *op) {
        return PyLong_Check(op);
    }
//
//PyObject *py_bytes_from_string(const std::string &s) {
//    return PyBytes_FromStringAndSize(s.c_str(), s.size());
//}
//
//std::string py_bytes_as_string(PyObject *op) {
//    std::string ret(PyUnicode_AsUTF8(op), PyUnicode_GET_LENGTH(op));
//    return ret;
//}


} // namespace Python_Cpp_Homogeneous_Containers
