#include <iostream>

#include <Python.h>

#include "python_convert.h"
#include "TestFramework.h"

int test_vector_double_to_py_tuple(TestResultS &test_results) {
//    std::cout << "Starting: " << __FUNCTION__ << "()" << std::endl;
    size_t SIZE = 1024;
    std::vector<double> cpp_vector;
    for (size_t i = 0; i < SIZE; ++i) {
        cpp_vector.push_back(static_cast<double>(i));
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Homogeneous_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    double exec_time = exec_clock.seconds();
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
    test_results.push_back(TestResult(__FUNCTION__, result, exec_time, 1, SIZE));
    return result;
}

int test_py_tuple_to_vector_double(TestResultS &test_results) {
//    std::cout << "Starting: " << __FUNCTION__ << "()" << std::endl;
    size_t SIZE = 1024;
    PyObject *op = PyTuple_New(SIZE);
    int result = 0;
    double exec_time = -1.0;
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
            ExecClock exec_clock;
            int err = Python_Cpp_Homogeneous_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
            exec_time = exec_clock.seconds();
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
    test_results.push_back(TestResult(__FUNCTION__, result, exec_time, 1, SIZE));
    return result;
}

int test_vector_long_to_py_tuple(TestResultS &test_results) {
//    std::cout << "Starting: " << __FUNCTION__ << "()" << std::endl;
    size_t SIZE = 1024;
    std::vector<long> cpp_vector;
    for (size_t i = 0; i < SIZE; ++i) {
        cpp_vector.push_back(static_cast<long>(i));
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Homogeneous_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    double exec_time = exec_clock.seconds();
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
    test_results.push_back(TestResult(__FUNCTION__, result, exec_time, 1, SIZE));
    return result;
}

int test_py_tuple_to_vector_long(TestResultS &test_results) {
//    std::cout << "Starting: " << __FUNCTION__ << "()" << std::endl;
    size_t SIZE = 1024;
    PyObject *op = PyTuple_New(SIZE);
    int result = 0;
    double exec_time = -1.0;
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
            ExecClock exec_clock;
            err = Python_Cpp_Homogeneous_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
            exec_time = exec_clock.seconds();
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
    test_results.push_back(TestResult(__FUNCTION__, result, exec_time, 1, SIZE));
    return result;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    Py_Initialize();

    TestResultS test_results;
    test_vector_double_to_py_tuple(test_results);
    test_py_tuple_to_vector_double(test_results);
    test_vector_long_to_py_tuple(test_results);
    test_py_tuple_to_vector_long(test_results);

    std::cout << test_results << std::endl;
    return 0;
}
