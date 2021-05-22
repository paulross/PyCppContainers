//
// Created by Paul Ross on 21/05/2021.
//

#include <Python.h>

#include "python_convert.h"

#include "test_functional.h"

template<typename T, T (*ConvertPyToCpp)(PyObject *)>
int test_vector_to_py_tuple(TestResultS &test_results, const std::string &type) {
//    std::cout << "Starting: " << __FUNCTION__ << "()" << std::endl;
    size_t SIZE = 1024;
    std::vector<T> cpp_vector;
    for (size_t i = 0; i < SIZE; ++i) {
        cpp_vector.push_back(static_cast<T>(i));
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
                    T value = ConvertPyToCpp(PyTuple_GetItem(op, i));
                    if (value != cpp_vector[i]) {
                        result |= 1 << 2;
                    }
                }
            }
        }
        Py_DECREF(op);
    }
    if (result) {
        std::cout << "    FAIL: " << std::string(__FUNCTION__) + type << "():" << result << std::endl;
        PyErr_Print();
        PyErr_Clear();
    } else {
        std::cout << "      OK: " << std::string(__FUNCTION__) + type << "()" << std::endl;
    }
    test_results.push_back(TestResult(std::string(__FUNCTION__) + type, result, exec_time, 1, SIZE));
    return result;
}

template<typename T, PyObject *(*ConvertCppToPy)(const T &), T (*ConvertPyToCpp)(PyObject *)>
int test_py_tuple_to_vector(TestResultS &test_results, const std::string &type) {
//    std::cout << "Starting: " << __FUNCTION__ << "()" << std::endl;
    size_t SIZE = 1024;
    PyObject *op = PyTuple_New(SIZE);
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < SIZE; ++i) {
            int err = PyTuple_SetItem(op, i, ConvertCppToPy(static_cast<T>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::vector<T> cpp_vector;
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
                        T value = ConvertPyToCpp(PyTuple_GetItem(op, i));
                        if (value != cpp_vector[i]) {
                            result |= 1 << 4;
                        }
                    }
                }
            }
        }
        Py_DECREF(op);
    }
    if (result) {
        std::cout << "    FAIL: " << std::string(__FUNCTION__) + type << "():" << result << std::endl;
        PyErr_Print();
        PyErr_Clear();
    } else {
        std::cout << "      OK: " << std::string(__FUNCTION__) + type << "()" << std::endl;
    }
    test_results.push_back(TestResult(std::string(__FUNCTION__) + type, result, exec_time, 1, SIZE));
    return result;
}

template<typename T>
int test_vector_to_py_tuple_round_trip(TestResultS &test_results, const std::string &type) {
//    std::cout << "Starting: " << __FUNCTION__ << "()" << std::endl;
    size_t SIZE = 1024;
    std::vector<T> cpp_vector;
    std::vector<T> cpp_vector_result;
    for (size_t i = 0; i < SIZE; ++i) {
        cpp_vector.push_back(static_cast<T>(i));
    }
    int result = 0;
    double exec_time = -1.0;
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Homogeneous_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    if (op) {
        int err = Python_Cpp_Homogeneous_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector_result);
        if (err) {
            result |= 1;
        } else {
            exec_time = exec_clock.seconds();
            if (cpp_vector != cpp_vector_result) {
                result |= 1 << 1;
            }
        }
        Py_DECREF(op);
    } else {
        result |= 1 << 2;
    }
    if (result) {
        std::cout << "    FAIL: " << std::string(__FUNCTION__) + type << "():" << result << std::endl;
        PyErr_Print();
        PyErr_Clear();
    } else {
        std::cout << "      OK: " << std::string(__FUNCTION__) + type << "()" << std::endl;
    }
    test_results.push_back(TestResult(std::string(__FUNCTION__) + type, result, exec_time, 1, SIZE));
    return result;
}

template<typename T, PyObject *(*Convert)(const T &)>
int test_py_tuple_to_vector_round_trip(TestResultS &test_results, const std::string &type) {
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
            err = PyTuple_SetItem(op, i, Convert(static_cast<T>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::vector<T> cpp_vector;
            ExecClock exec_clock;
            err = Python_Cpp_Homogeneous_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
            exec_time = exec_clock.seconds();
            if (err != 0) {
                result |= 1 << 2;
            } else {
                //  int PyObject_RichCompareBool(PyObject *o1, PyObject *o2, int opid) Py_EQ -1 error 0 false 1 true
                PyObject *op_new = Python_Cpp_Homogeneous_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
                if (op_new) {
                    if (PyObject_RichCompareBool(op, op_new, Py_EQ) != 1) {
                        result |= 1 << 3;
                    }
                    Py_DECREF(op_new);
                } else {
                    result |= 1 << 4;
                }
            }
        }
        Py_DECREF(op);
    }
    if (result) {
        std::cout << "    FAIL: " << std::string(__FUNCTION__) + type << "():" << result << std::endl;
        PyErr_Print();
        PyErr_Clear();
    } else {
        std::cout << "      OK: " << std::string(__FUNCTION__) + type << "()" << std::endl;
    }
    test_results.push_back(TestResult(std::string(__FUNCTION__) + type, result, exec_time, 1, SIZE));
    return result;
}

void test_functional_all(TestResultS &test_results) {
    test_vector_to_py_tuple<bool, &Python_Cpp_Homogeneous_Containers::py_bool_as_bool>(test_results, "<bool>");
    test_vector_to_py_tuple<long, &Python_Cpp_Homogeneous_Containers::py_long_as_long>(test_results, "<long>");
    test_vector_to_py_tuple<double, &Python_Cpp_Homogeneous_Containers::py_float_as_double>(test_results, "<double>");
    test_py_tuple_to_vector<bool, &Python_Cpp_Homogeneous_Containers::py_bool_from_bool, &Python_Cpp_Homogeneous_Containers::py_bool_as_bool>(
            test_results, "<bool>");
    test_py_tuple_to_vector<long, &Python_Cpp_Homogeneous_Containers::py_long_from_long, &Python_Cpp_Homogeneous_Containers::py_long_as_long>(
            test_results, "<long>");
    test_py_tuple_to_vector<double, &Python_Cpp_Homogeneous_Containers::py_float_from_double, &Python_Cpp_Homogeneous_Containers::py_float_as_double>(
            test_results, "<double>");
    test_vector_to_py_tuple_round_trip<bool>(test_results, "<bool>");
    test_vector_to_py_tuple_round_trip<long>(test_results, "<long>");
    test_vector_to_py_tuple_round_trip<double>(test_results, "<double>");
    test_py_tuple_to_vector_round_trip<bool, &Python_Cpp_Homogeneous_Containers::py_bool_from_bool>(test_results,
                                                                                                    "<bool>");
    test_py_tuple_to_vector_round_trip<long, &Python_Cpp_Homogeneous_Containers::py_long_from_long>(test_results,
                                                                                                    "<long>");
    test_py_tuple_to_vector_round_trip<double, &Python_Cpp_Homogeneous_Containers::py_float_from_double>(test_results,
                                                                                                         "<double>");
}
