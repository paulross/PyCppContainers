#include <iostream>

#include <Python.h>

#include "python_convert.h"

int test_vector_double_to_py_tuple() {
//    std::cout << "Starting: " << __FUNCTION__ << "()" << std::endl;
    size_t SIZE = 3;
    std::vector<double> cpp_vector;
    for (size_t i = 0; i < SIZE; ++i) {
        cpp_vector.push_back(static_cast<double>(i));
    }
    PyObject *op = Python_Cpp_Homogeneous_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    int result = 0;
    if (! op) {
        result |= 1;
    } else {
        if (! PyTuple_CheckExact(op)) {
            result |= 1 << 1;
        } else {
            if ((unsigned long) PyTuple_Size(op) != cpp_vector.size()) {
                result |= 1 << 2;
            } else {
                for (size_t i = 0; i < SIZE; ++i) {
                    double value = PyFloat_AsDouble(PyTuple_GetItem(op, i));
                    if (value != cpp_vector[i]) {
                        result |= 1 << 2;
                    }
                }
            }
        }
    }
    Py_DECREF(op);
    if (result) {
        std::cout << "    FAIL: " << __FUNCTION__ << "():" << result << std::endl;
        PyErr_Print();
        PyErr_Clear();
    } else {
        std::cout << "      OK: " << __FUNCTION__ << "()" << std::endl;
    }
    return result;
}

int test_py_tuple_to_vector_double() {
//    std::cout << "Starting: " << __FUNCTION__ << "()" << std::endl;
    size_t SIZE = 3;
    PyObject *op = PyTuple_New(SIZE);
    int result = 0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < SIZE; ++i) {
            int err = PyTuple_SetItem(op, i, PyFloat_FromDouble(static_cast<double>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::vector<double> cpp_vector;
            int err = Python_Cpp_Homogeneous_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
            if (err != 0) {
                result |= 1 << 2;
            } else {
                if ((unsigned long) PyTuple_Size(op) != cpp_vector.size()) {
                    result |= 1 << 3;
                } else {
                    for (size_t i = 0; i < SIZE; ++i) {
                        double value = PyFloat_AsDouble(PyTuple_GetItem(op, i));
                        if (value != cpp_vector[i]) {
                            result |= 1 << 4;
                        }
                    }
                }
            }
        }
    }
    Py_DECREF(op);
    if (result) {
        std::cout << "    FAIL: " << __FUNCTION__ << "():" << result << std::endl;
        PyErr_Print();
        PyErr_Clear();
    } else {
        std::cout << "      OK: " << __FUNCTION__ << "()" << std::endl;
    }
    return result;
}

int test_vector_long_to_py_tuple() {
//    std::cout << "Starting: " << __FUNCTION__ << "()" << std::endl;
    size_t SIZE = 3;
    std::vector<long> cpp_vector;
    for (size_t i = 0; i < SIZE; ++i) {
        cpp_vector.push_back(static_cast<long>(i));
    }
    PyObject *op = Python_Cpp_Homogeneous_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    int result = 0;
    if (! op) {
        result |= 1;
    } else {
        if (! PyTuple_CheckExact(op)) {
            result |= 1 << 1;
        } else {
            if ((unsigned long) PyTuple_Size(op) != cpp_vector.size()) {
                result |= 1 << 2;
            } else {
                for (size_t i = 0; i < SIZE; ++i) {
                    long value = PyLong_AsLong(PyTuple_GetItem(op, i));
                    if (value != cpp_vector[i]) {
                        result |= 1 << 3;
                    }
                }
            }
        }
    }
    Py_DECREF(op);
    if (result) {
        std::cout << "    FAIL: " << __FUNCTION__ << "():" << result << std::endl;
        PyErr_Print();
        PyErr_Clear();
    } else {
        std::cout << "      OK: " << __FUNCTION__ << "()" << std::endl;
    }
    return result;
}

int test_py_tuple_to_vector_long() {
//    std::cout << "Starting: " << __FUNCTION__ << "()" << std::endl;
    size_t SIZE = 3;
    PyObject *op = PyTuple_New(SIZE);
    int result = 0;
    int err = 0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < SIZE; ++i) {
            err = PyTuple_SetItem(op, i, PyLong_FromLong(static_cast<long>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::vector<long> cpp_vector;
            err = Python_Cpp_Homogeneous_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
            if (err != 0) {
                result |= 1 << 2;
            } else {
                if ((unsigned long) PyTuple_Size(op) != cpp_vector.size()) {
                    result |= 1 << 3;
                } else {
                    for (size_t i = 0; i < SIZE; ++i) {
                        long value = PyLong_AsLong(PyTuple_GetItem(op, i));
                        if (value != cpp_vector[i]) {
                            result |= 1 << 4;
                        }
                    }
                }
            }
        }
    }
    Py_DECREF(op);
    if (result) {
        std::cout << "    FAIL: " << __FUNCTION__ << "():" << result << std::endl;
        PyErr_Print();
        PyErr_Clear();
    } else {
        std::cout << "      OK: " << __FUNCTION__ << "()" << std::endl;
    }
    return result;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    Py_Initialize();

    test_vector_double_to_py_tuple();
    test_py_tuple_to_vector_double();
    test_vector_long_to_py_tuple();
    test_py_tuple_to_vector_long();
    return 0;
}
