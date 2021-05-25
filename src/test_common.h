//
// Created by Paul Ross on 22/05/2021.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_TEST_COMMON_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_TEST_COMMON_H

#include <Python.h>

#include "python_convert.h"
#include "TestFramework.h"

#define REPORT_TEST_OUTPUT \
    do {                       \
        if (result) { \
            std::cout << "    FAIL: " << std::string(__FUNCTION__) + type << "():" << "[" << size << "]"; \
            std::cout << result << std::endl; \
            PyErr_Print(); \
            PyErr_Clear(); \
        } else { \
            std::cout << "      OK: " << std::string(__FUNCTION__) + type << "()" << "[" << size << "]" << std::endl; \
        } \
        test_results.push_back(TestResult(std::string(__FUNCTION__) + type, result, exec_time, 1, size)); \
    } while (0)

template<typename T, T (*ConvertPyToCpp)(PyObject *)>
int test_vector_to_py_tuple(TestResultS &test_results, const std::string &type, size_t size) {
    std::vector<T> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
        cpp_vector.push_back(static_cast<T>(i));
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Homogeneous_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (! op) {
        result |= 1;
    } else {
        if (! Python_Cpp_Homogeneous_Containers::py_tuple_check(op)) {
            result |= 1 << 1;
        } else {
            if ((unsigned long) Python_Cpp_Homogeneous_Containers::py_tuple_len(op) != cpp_vector.size()) {
                result |= 1 << 2;
            } else {
                for (size_t i = 0; i < size; ++i) {
                    T value = ConvertPyToCpp(Python_Cpp_Homogeneous_Containers::py_tuple_get(op, i));
                    if (value != cpp_vector[i]) {
                        result |= 1 << 2;
                    }
                }
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT;
    return result;
}

template<typename T, PyObject *(*ConvertCppToPy)(const T &), T (*ConvertPyToCpp)(PyObject *)>
int test_py_tuple_to_vector(TestResultS &test_results, const std::string &type, size_t size) {
    PyObject *op = Python_Cpp_Homogeneous_Containers::py_tuple_new(size);
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
            int err = Python_Cpp_Homogeneous_Containers::py_tuple_set(op, i, ConvertCppToPy(static_cast<T>(i)));
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
                if ((unsigned long) Python_Cpp_Homogeneous_Containers::py_tuple_len(op) != cpp_vector.size()) {
                    result |= 1 << 3;
                } else {
                    for (size_t i = 0; i < size; ++i) {
                        T value = ConvertPyToCpp(Python_Cpp_Homogeneous_Containers::py_tuple_get(op, i));
                        if (value != cpp_vector[i]) {
                            result |= 1 << 4;
                        }
                    }
                }
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT;
    return result;
}

template<typename T>
int test_vector_to_py_tuple_round_trip(TestResultS &test_results, const std::string &type, size_t size) {
    std::vector<T> cpp_vector;
    std::vector<T> cpp_vector_result;
    for (size_t i = 0; i < size; ++i) {
        cpp_vector.push_back(static_cast<T>(i));
    }
    int result = 0;
    double exec_time = -1.0;
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Homogeneous_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    if (op) {
        int err = Python_Cpp_Homogeneous_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector_result);
        exec_time = exec_clock.seconds();
        if (err) {
            result |= 1;
        } else {
            if (cpp_vector != cpp_vector_result) {
                result |= 1 << 1;
            }
        }
        Py_DECREF(op);
    } else {
        result |= 1 << 2;
    }
    REPORT_TEST_OUTPUT;
    return result;
}

template<typename T, PyObject *(*Convert)(const T &)>
int test_py_tuple_to_vector_round_trip(TestResultS &test_results, const std::string &type, size_t size) {
    PyObject *op = Python_Cpp_Homogeneous_Containers::py_tuple_new(size);
    int result = 0;
    double exec_time = -1.0;
    int err = 0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
            err = Python_Cpp_Homogeneous_Containers::py_tuple_set(op, i, Convert(static_cast<T>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::vector<T> cpp_vector;
            ExecClock exec_clock;
            err = Python_Cpp_Homogeneous_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
            if (err != 0) {
                result |= 1 << 2;
            } else {
                //  int PyObject_RichCompareBool(PyObject *o1, PyObject *o2, int opid) Py_EQ -1 error 0 false 1 true
                PyObject *op_new = Python_Cpp_Homogeneous_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
                if (op_new) {
                    exec_time = exec_clock.seconds();
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
    REPORT_TEST_OUTPUT;
    return result;
}

int test_vector_string_to_py_tuple(TestResultS &test_results, size_t size, size_t str_len);
int test_py_tuple_string_to_vector(TestResultS &test_results, size_t size, size_t str_len);

template<
        typename K,
        typename V,
        PyObject *(*Convert_K)(const K &),
        PyObject *(*Convert_V)(const V &)
>
int compare_dict(std::unordered_map<K, V> &cpp_map, PyObject *op) {
    int result = 0;
    for (auto iter = cpp_map.begin(); iter != cpp_map.end(); ++iter) {
        K key = iter->first;
        V val = iter->second;
        // New reference
        PyObject *py_key = Convert_K(key);
        PyObject *py_val = Convert_V(val);
        // Borrowed reference.
        PyObject *py_dict_val = Python_Cpp_Homogeneous_Containers::py_dict_get(op, py_key);
        if (py_dict_val == NULL) {
            result |= 1 << 2;
        } else {
            if (PyObject_RichCompareBool(py_val, py_dict_val, Py_EQ) != 1) {
                result |= 1 << 3;
            }
        }
        Py_DECREF(py_key);
        Py_DECREF(py_val);
    }
    return result;
}

template<
        typename K,
        typename V,
        PyObject *(*Convert_K)(const K &),
        PyObject *(*Convert_V)(const V &)
>
int test_cpp_std_unordered_map_to_py_dict(TestResultS &test_results, const std::string &type, size_t size) {
    std::unordered_map<K, V> cpp_map;
    for (size_t i = 0; i < size; ++i) {
        cpp_map[static_cast<K>(i)] = static_cast<V>(i);
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Homogeneous_Containers::cpp_std_unordered_map_to_py_dict(cpp_map);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (! op) {
        result |= 1;
    } else {
        if (! Python_Cpp_Homogeneous_Containers::py_dict_check(op)) {
            result |= 1 << 1;
        } else {
            if ((unsigned long) Python_Cpp_Homogeneous_Containers::py_dict_len(op) != cpp_map.size()) {
                result |= 1 << 2;
            } else {
                result |= compare_dict<K, V, Convert_K, Convert_V>(cpp_map, op);
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT;
    return result;
}

template<
        typename K,
        typename V,
        PyObject *(*Convert_K)(const K &),
        PyObject *(*Convert_V)(const V &)
>
int test_py_dict_to_cpp_std_unordered_map(TestResultS &test_results, const std::string &type, size_t size) {
    PyObject *op = Python_Cpp_Homogeneous_Containers::py_dict_new();
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
            int err = Python_Cpp_Homogeneous_Containers::py_dict_set(op, Convert_K(static_cast<K>(i)),
                                                                     Convert_V(static_cast<V>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::unordered_map<K, V> cpp_map;
            ExecClock exec_clock;
            int err = Python_Cpp_Homogeneous_Containers::py_dict_to_cpp_std_unordered_map(op, cpp_map);
            exec_time = exec_clock.seconds();
            if (err != 0) {
                result |= 1 << 2;
            } else {
                result |= compare_dict<K, V, Convert_K, Convert_V>(cpp_map, op);
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT;
    return result;
}

#endif // PYTHONCPPHOMOGENEOUSCONTAINERS_TEST_COMMON_H
