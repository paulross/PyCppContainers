//
// Created by Paul Ross on 22/05/2021.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_TEST_COMMON_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_TEST_COMMON_H

#include <Python.h>

#include "cpy/python_convert.h"
#include "cpp/get_rss.h"
#include "cpp/TestFramework.h"

#define REPORT_OK_OR_FAIL 0

#if REPORT_OK_OR_FAIL
#define REPORT_TEST_OUTPUT \
    do {                   \
        if (result) { \
            std::cout << "    FAIL: " << std::string(__FUNCTION__) + type << "():" << "[" << size << "]"; \
            std::cout << result << std::endl; \
            PyErr_Print(); \
            PyErr_Clear(); \
        } else { \
            std::cout << "      OK: " << std::string(__FUNCTION__) + type << "()" << "[" << size << "]" << std::endl; \
        }                  \
        test_results.push_back(TestResult(std::string(__FUNCTION__) + type, result, exec_time, 1, size)); \
    } while (0)

#define REPORT_TEST_OUTPUT_WITH_STRING_LENGTH \
    do {                              \
        std::ostringstream title; \
        title << __FUNCTION__  << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]"; \
        if (result) { \
            std::cout << "    FAIL: " << title.str() << " " << result << std::endl; \
            PyErr_Print(); \
            PyErr_Clear(); \
        } else { \
            std::cout << "      OK: " << title.str() << " " << result << std::endl; \
        } \
        test_results.push_back(TestResult(title.str(), result, exec_time, 1, size)); \
    } while (0)
#else
#define REPORT_TEST_OUTPUT \
    do {                   \
        test_results.push_back(TestResult(std::string(__FUNCTION__) + type, result, exec_time, 1, size)); \
    } while (0)

#define REPORT_TEST_OUTPUT_WITH_STRING_LENGTH \
    do {                              \
        std::ostringstream title; \
        title << __FUNCTION__  << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]"; \
        test_results.push_back(TestResult(title.str(), result, exec_time, 1, size)); \
    } while (0)
#endif

template<typename T, T (*ConvertPyToCpp)(PyObject *)>
int test_vector_to_py_tuple(TestResultS &test_results, const std::string &type, size_t size) {
    std::vector<T> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
        cpp_vector.push_back(static_cast<T>(i));
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (! op) {
        result |= 1;
    } else {
        if (! Python_Cpp_Containers::py_tuple_check(op)) {
            result |= 1 << 1;
        } else {
            if ((unsigned long) Python_Cpp_Containers::py_tuple_len(op) != cpp_vector.size()) {
                result |= 1 << 2;
            } else {
                for (size_t i = 0; i < size; ++i) {
                    T value = ConvertPyToCpp(Python_Cpp_Containers::py_tuple_get(op, i));
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
    PyObject *op = Python_Cpp_Containers::py_tuple_new(size);
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
            int err = Python_Cpp_Containers::py_tuple_set(op, i, ConvertCppToPy(static_cast<T>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::vector<T> cpp_vector;
            ExecClock exec_clock;
            int err = Python_Cpp_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
            exec_time = exec_clock.seconds();
            if (err != 0) {
                result |= 1 << 2;
            } else {
                if ((unsigned long) Python_Cpp_Containers::py_tuple_len(op) != cpp_vector.size()) {
                    result |= 1 << 3;
                } else {
                    for (size_t i = 0; i < size; ++i) {
                        T value = ConvertPyToCpp(Python_Cpp_Containers::py_tuple_get(op, i));
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
    PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    if (op) {
        int err = Python_Cpp_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector_result);
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
    PyObject *op = Python_Cpp_Containers::py_tuple_new(size);
    int result = 0;
    double exec_time = -1.0;
    int err = 0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
            err = Python_Cpp_Containers::py_tuple_set(op, i, Convert(static_cast<T>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::vector<T> cpp_vector;
            ExecClock exec_clock;
            err = Python_Cpp_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
            if (err != 0) {
                result |= 1 << 2;
            } else {
                //  int PyObject_RichCompareBool(PyObject *o1, PyObject *o2, int opid) Py_EQ -1 error 0 false 1 true
                PyObject *op_new = Python_Cpp_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
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

// Compare a Python set or frozenset with a std::unordered_set
// Return 0 if same, non-zero if different.
template<
        typename T,
        PyObject *(*Convert_T)(const T &),
        T (*Convert_Py)(PyObject *)
>
int compare_set(const std::unordered_set<T> &cpp_set, PyObject *op) {
    assert(PySet_Check(op) || PyFrozenSet_Check(op));
    int result = 0;
    for (auto iter = cpp_set.begin(); iter != cpp_set.end(); ++iter) {
        T val = *iter;
        // New reference
        PyObject *py_val = Convert_T(val);
        if (PySet_Contains(op, py_val) == 0) {
            result |= 1 << 2;
        }
        Py_DECREF(py_val);
    }
    // Now iterate across op and check against cpp_set.
    PyObject *py_iter = PyObject_GetIter(op);
    if (! py_iter) {
        result |= 1 << 3;
    } else {
        PyObject *py_item = NULL;
        while ((py_item = PyIter_Next(py_iter))) {
            T val = (*Convert_Py)(py_item);
            if (cpp_set.count(val) == 0) {
                result |= 1 << 4;
            }
            Py_DECREF(py_item);
        }
        Py_DECREF(py_iter);
    }
    return result;
}

template<typename T, T (*ConvertPyToCpp)(PyObject *), PyObject *(*Convert_Py)(const T &)>
int test_unordered_set_to_py_set(TestResultS &test_results, const std::string &type, size_t size) {
    std::unordered_set<T> cpp_container;
    for (size_t i = 0; i < size; ++i) {
        cpp_container.insert(static_cast<T>(i));
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_unordered_set_to_py_set(cpp_container);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (! op) {
        result |= 1;
    } else {
        if (! Python_Cpp_Containers::py_set_check(op)) {
            result |= 1 << 1;
        } else {
            if (compare_set<T, Convert_Py, ConvertPyToCpp>(cpp_container, op)) {
                result |= 1 << 2;
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT;
    return result;
}

template<typename T, T (*ConvertPyToCpp)(PyObject *), PyObject *(*ConvertCppToPy)(const T &)>
int test_py_set_to_unordered_set(TestResultS &test_results, const std::string &type, size_t size) {
    PyObject *op = Python_Cpp_Containers::py_set_new();
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
            int err = Python_Cpp_Containers::py_set_add(op, ConvertCppToPy(static_cast<T>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::unordered_set<T> cpp_container;
            ExecClock exec_clock;
            int err = Python_Cpp_Containers::py_set_to_cpp_std_unordered_set(op, cpp_container);
            exec_time = exec_clock.seconds();
            if (err != 0) {
                result |= 1 << 2;
            } else {
                if (compare_set<T, ConvertCppToPy, ConvertPyToCpp>(cpp_container, op)) {
                    result |= 1 << 3;
                }
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
        PyObject *(*Convert_V)(const V &),
        K (*Convert_Py_Key)(PyObject *),
        V (*Convert_Py_Val)(PyObject *)
>
int compare_dict(std::unordered_map<K, V> &cpp_map, PyObject *op) {
    assert(PyDict_Check(op));
    int result = 0;
    PyObject *py_key = NULL;
    PyObject *py_val = NULL;
    for (auto iter = cpp_map.begin(); iter != cpp_map.end(); ++iter) {
        K key = iter->first;
        V val = iter->second;
        // New reference
        py_key = Convert_K(key);
        py_val = Convert_V(val);
        // Borrowed reference.
        PyObject *py_dict_val = PyDict_GetItem(op, py_key);
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
    // TODO: Now iterate across op and check against cpp_map.
    // Now iterate across op and check against cpp_set.
    Py_ssize_t pos = 0;
    while (PyDict_Next(op, &pos, &py_key, &py_val)) {
        K key = (*Convert_Py_Key)(py_key);
        V val = (*Convert_Py_Val)(py_val);
        if (cpp_map.count(key) == 0) {
            result |= 1 << 4;
        } else {
            if (val != cpp_map.at(key)) {
               result |= 1 << 5;
            }
        }
    }
    return result;
}

template<
        typename K,
        typename V,
        PyObject *(*Convert_K)(const K &),
        PyObject *(*Convert_V)(const V &),
        K (*Convert_Py_Key)(PyObject *),
        V (*Convert_Py_Val)(PyObject *)
>
int test_cpp_std_unordered_map_to_py_dict(TestResultS &test_results, const std::string &type, size_t size) {
    std::unordered_map<K, V> cpp_map;
    for (size_t i = 0; i < size; ++i) {
        cpp_map[static_cast<K>(i)] = static_cast<V>(i);
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_unordered_map_to_py_dict(cpp_map);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (! op) {
        result |= 1;
    } else {
        if (! PyDict_Check(op)) {
            result |= 1 << 1;
        } else {
            if ((unsigned long) PyDict_Size(op) != cpp_map.size()) {
                result |= 1 << 2;
            } else {
                result |= compare_dict<K, V, Convert_K, Convert_V,  Convert_Py_Key, Convert_Py_Val>(cpp_map, op);
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
        PyObject *(*Convert_V)(const V &),
        K (*Convert_Py_Key)(PyObject *),
        V (*Convert_Py_Val)(PyObject *)
>
int test_py_dict_to_cpp_std_unordered_map(TestResultS &test_results, const std::string &type, size_t size) {
    PyObject *op = PyDict_New();
    PyObject *py_k = NULL;
    PyObject *py_v = NULL;
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
            py_k = (*Convert_K)(static_cast<K>(i));
            if (! py_k) {
                // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                PyErr_Format(PyExc_ValueError, "C++ key of can not be converted.");
                result |= 1 << 1;
                break;
            }
            // Refcount may well be >> 1 for interned objects.
            Py_ssize_t py_k_ob_refcnt = py_k->ob_refcnt;
            py_v = (*Convert_V)(static_cast<V>(i));
            if (! py_v) {
                // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                PyErr_Format(PyExc_ValueError, "C++ value of can not be converted.");
                Py_DECREF(py_k);
                result |= 1 << 2;
                break;
            }
            // Refcount may well be >> 1 for interned objects.
            Py_ssize_t py_v_ob_refcnt = py_v->ob_refcnt;
            if (PyDict_SetItem(op, py_k, py_v)) {
                // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                PyErr_Format(PyExc_ValueError, "Can not set an item in the Python dict.");
                result |= 1 << 3;
                break;
            }
            // Oh this is nasty.
            // PyDict_SetItem() increfs the key and the value rather than stealing a reference.
            // insertdict(): https://github.com/python/cpython/blob/main/Objects/dictobject.c#L1074
            assert(py_k->ob_refcnt == py_k_ob_refcnt + 1 && "PyDict_SetItem failed to increment key refcount.");
            Py_DECREF(py_k);
            assert(py_k->ob_refcnt == py_k_ob_refcnt);
            assert(py_v->ob_refcnt == py_v_ob_refcnt + 1 && "PyDict_SetItem failed to increment value refcount.");
            Py_DECREF(py_v);
            assert(py_v->ob_refcnt == py_v_ob_refcnt);

//            // TODO: This is a memory leak.
//            int err = PyDict_SetItem(op, Convert_K(static_cast<K>(i)), Convert_V(static_cast<V>(i)));
//            if (err != 0) {
//                result |= 1 << 1;
//            }
        }
        if (result == 0) {
            std::unordered_map<K, V> cpp_map;
            ExecClock exec_clock;
            int err = Python_Cpp_Containers::py_dict_to_cpp_std_unordered_map(op, cpp_map);
            exec_time = exec_clock.seconds();
            if (err != 0) {
                result |= 1 << 2;
            } else {
                result |= compare_dict<K, V, Convert_K, Convert_V, Convert_Py_Key, Convert_Py_Val>(cpp_map, op);
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT;
    return result;
}

int test_cpp_std_unordered_map_to_py_dict_string(TestResultS &test_results, size_t size, size_t str_len);

PyObject *
new_py_tuple_bytes(size_t size, size_t str_len);
#endif // PYTHONCPPHOMOGENEOUSCONTAINERS_TEST_COMMON_H
