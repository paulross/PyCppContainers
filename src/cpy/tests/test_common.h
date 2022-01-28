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

#define REPORT_TEST_OUTPUT_WITH_TYPE \
    do {                   \
        std::ostringstream title; \
        title << __FUNCTION__  << '<' << type << ">():" << "[" << size << "]"; \
        if (result) { \
            std::cout << "    FAIL: " << title.str() << std::endl; \
            std::cout << result << std::endl; \
            PyErr_Print(); \
            PyErr_Clear(); \
        } else { \
            std::cout << "      OK: " << title.str() << std::endl; \
        }                  \
        test_results.push_back(TestResult(title.str(), result, exec_time, 1, size)); \
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
        std::ostringstream title; \
        title << __FUNCTION__  << "():" << "[" << size << "]"; \
        test_results.push_back(TestResult(title.str(), result, exec_time, 1, size)); \
    } while (0)

#define REPORT_TEST_OUTPUT_WITH_TYPE \
    do {                   \
        std::ostringstream title; \
        title << __FUNCTION__  << '<' << type << ">():" << "[" << size << "]"; \
        test_results.push_back(TestResult(title.str(), result, exec_time, 1, size)); \
    } while (0)

#define REPORT_TEST_OUTPUT_WITH_STRING_LENGTH \
    do {                              \
        std::ostringstream title; \
        title << __FUNCTION__  << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]"; \
        test_results.push_back(TestResult(title.str(), result, exec_time, 1, size)); \
    } while (0)
#endif

// Some macros to do RSS snapshots.
#define RSS_SNAPSHOT
//#undef RSS_SNAPSHOT

#ifdef RSS_SNAPSHOT
#define RSS_SNAPSHOT_WITHOUT_TYPE RSSSnapshot rss(__FUNCTION__);

#define RSS_SNAPSHOT_WITH_TYPE(type) \
        std::ostringstream rss_title; \
        rss_title << __FUNCTION__ << type; \
        RSSSnapshot rss(rss_title.str());

#define RSS_SNAPSHOT_REPORT std::cout << rss << std::endl;
#else
#define RSS_SNAPSHOT_WITHOUT_TYPE
#define RSS_SNAPSHOT_WITH_TYPE(type)
#define RSS_SNAPSHOT_REPORT
#endif // RSS_SNAPSHOT

#pragma mark Comparison templates

/**
 * Compares a Python tuple or list with a C++ std::vector.
 *
 * @tparam T C++ Type of objects in the vector.
 * @tparam Convert_T_To_Py Pointer to function to convert a C++ type T to a PyObject.
 * @tparam Convert_Py_To_T Pointer to function to convert a PyObject* to a C++ type T.
 * @tparam PyUnaryContainer_Check A function that takes a PyObject* and returns 1 if it is of a suitable container,
 * 0 otherwise.
 * @tparam PyUnaryContainer_Size A function that returns the length of the Python container.
 * @tparam PyUnaryContainer_GetA function that gets a PyObject* from the Python container at a given index as a
 * size_t.
 * @param cpp_vector The C++ vector.
 * @param op The Python tuple or list.
 * @return 0 if identical, non-zero if not.
 */
template<
        typename T,
        PyObject *(*Convert_T_To_Py)(const T &),
        T (*Convert_Py_To_T)(PyObject *),
        int(*PyUnaryContainer_Check)(PyObject *),
        Py_ssize_t(*PyUnaryContainer_Size)(PyObject *),
        PyObject *(*PyUnaryContainer_Get)(PyObject *, size_t)
>
int compare_tuple_or_list(std::vector<T> const &cpp_vector, PyObject *op) {
    assert(op);
    int result = 0;
    if (!PyUnaryContainer_Check(op)) {
        result = 1;
    } else {
        if (cpp_vector.size() != static_cast<size_t>(PyUnaryContainer_Size(op))) {
            result = 2;
        } else {
            // Iterate across cpp_vector and compare against PyObject *op.
            for (size_t i = 0; i < cpp_vector.size(); ++i) {
                // Check C++ == Python
                // Borrowed reference.
                PyObject *py_item = PyUnaryContainer_Get(op, i);
                T cpp_item = Convert_Py_To_T(py_item);
                if (cpp_vector[i] != cpp_item) {
                    result = 3;
                }
                // Check Python == C++
                // New reference
                PyObject *py_new_item = Convert_T_To_Py(cpp_vector[i]);
                if (PyObject_RichCompareBool(py_item, py_new_item, Py_EQ) != 1) {
                    result = 4;
                }
                Py_DECREF(py_new_item);
            }
        }
    }
    return result;
}

/**
 * Compares a Python tuple with a C++ std::vector.
 *
 * @tparam T C++ Type of objects in the vector.
 * @tparam Convert_T_To_Py Pointer to function to convert a C++ type T to a PyObject.
 * @tparam Convert_Py_To_T Pointer to function to convert a PyObject* to a C++ type T.
 * @param cpp_vector The C++ vector.
 * @param op The Python tuple.
 * @return 0 if identical, non-zero if not.
 */
template<
        typename T,
        PyObject *(*Convert_T_To_Py)(const T &),
        T (*Convert_Py_To_T)(PyObject *)
>
int compare_tuple(std::vector<T> const &cpp_vector, PyObject *op) {
    return compare_tuple_or_list<
            T, Convert_T_To_Py, Convert_Py_To_T,
            &Python_Cpp_Containers::py_tuple_check, &Python_Cpp_Containers::py_tuple_len, &Python_Cpp_Containers::py_tuple_get
        >(cpp_vector, op);
}

// Base tamplate
template<typename T>
int
compare_tuple(const std::vector<T> &cpp_vector, PyObject *op);

// Instantiations
template <>
int
compare_tuple<bool>(const std::vector<bool> &cpp_vector, PyObject *op);

template <>
int
compare_tuple<long>(const std::vector<long> &cpp_vector, PyObject *op);

template <>
int
compare_tuple<double>(const std::vector<double> &cpp_vector, PyObject *op);

template <>
int
compare_tuple<std::complex<double>>(const std::vector<std::complex<double>> &cpp_vector, PyObject *op);

template <>
int
compare_tuple<std::vector<char>>(const std::vector<std::vector<char>> &cpp_vector, PyObject *op);

template <>
int
compare_tuple<std::string>(const std::vector<std::string> &cpp_vector, PyObject *op);

/**
 * Compares a Python list with a C++ std::vector.
 *
 * @tparam T C++ Type of objects in the vector.
 * @tparam Convert_T_To_Py Pointer to function to convert a C++ type T to a PyObject.
 * @tparam Convert_Py_To_T Pointer to function to convert a PyObject* to a C++ type T.
 * @param cpp_vector The C++ vector.
 * @param op The Python list.
 * @return 0 if identical, non-zero if not.
 */
template<
        typename T,
        PyObject *(*Convert_T_To_Py)(const T &),
        T (*Convert_Py_To_T)(PyObject *)
>
int compare_list(std::vector<T> const &cpp_vector, PyObject *op) {
    return compare_tuple_or_list<
            T, Convert_T_To_Py, Convert_Py_To_T,
            &Python_Cpp_Containers::py_list_check, &Python_Cpp_Containers::py_list_len, &Python_Cpp_Containers::py_list_get
    >(cpp_vector, op);
}

// Base declaration
template<typename T>
int
compare_list(const std::vector<T> &cpp_vector, PyObject *op);

// Instatiations
template <>
int
compare_list<bool>(const std::vector<bool> &cpp_vector, PyObject *op);

template <>
int
compare_list<long>(const std::vector<long> &cpp_vector, PyObject *op);

template <>
int
compare_list<double>(const std::vector<double> &cpp_vector, PyObject *op);

template <>
int
compare_list<std::complex<double>>(const std::vector<std::complex<double>> &cpp_vector, PyObject *op);

template <>
int
compare_list<std::vector<char>>(const std::vector<std::vector<char>> &cpp_vector, PyObject *op);

template <>
int
compare_list<std::string>(const std::vector<std::string> &cpp_vector, PyObject *op);

/**
 * Compares a Python set or frozenset with a C++ std::unordered_set.
 *
 * @tparam T C++ Type of objects in the set.
 * @tparam Convert_T_To_Py Pointer to function to convert a C++ type T to a PyObject.
 * @tparam Convert_Py_To_T Pointer to function to convert a PyObject* to a C++ type T.
 * @param cpp_set The C++ set.
 * @param op The Python set.
 * @return 0 if identical, non-zero if not.
 */
template<
        typename T,
        PyObject *(*Convert_T_To_Py)(const T &),
        T (*Convert_Py_To_T)(PyObject *)
>
int compare_set(const std::unordered_set<T> &cpp_set, PyObject *op) {
    assert(op);
    int result = 0;
    if (!PySet_Check(op) && !PyFrozenSet_Check(op)) {
        result = 1;
    } else {
        // Iterate across cpp_set and compare against PyObject *op.
        PyObject *py_val = NULL;
        for (auto iter = cpp_set.begin(); iter != cpp_set.end(); ++iter) {
            T val = *iter;
            // New reference
            py_val = Convert_T_To_Py(val);
            // Borrowed reference.
            if (PySet_Contains(op, py_val) != 1) {
                result = 2;
            }
            Py_DECREF(py_val);
        }
        // Now iterate across PyObject *op and check against cpp_set.
        Py_ssize_t pos = 0;
        PyObject *py_set_iter = PyObject_GetIter(op);
        if (py_set_iter) {
            PyObject *item = NULL;
            while ((item = PyIter_Next(py_set_iter))) {
                T cpp_item = Convert_Py_To_T(item);
                if (cpp_set.count(cpp_item) != 1) {
                    result = 3;
                }
                Py_DECREF(item);
            }
            Py_DECREF(py_set_iter);
        }
    }
    return result;
}

// Base declaration
template<typename T>
int
compare_set(const std::unordered_set<T> &cpp_set, PyObject *op);

// Instatiations
template <>
int
compare_set<std::vector<char>>(const std::unordered_set<std::vector<char>> &cpp_set, PyObject *op);

template <>
int
compare_set<std::string>(const std::unordered_set<std::string> &cpp_set, PyObject *op);

/**
 * Compare a Python dict with a C++ std::unordered_map.
 * @tparam K The C++ type of the keys.
 * @tparam V The C++ type of the values.
 * @tparam Convert_K Pointer to function to convert a C++ type K to a PyObject.
 * @tparam Convert_V Pointer to function to convert a C++ type V to a PyObject.
 * @tparam Convert_Py_Key Pointer to function to convert a PyObject key to a C++ type K.
 * @tparam Convert_Py_Val Pointer to function to convert a PyObject value to a C++ type K.
 * @param cpp_map The C++ std::unordered_map.
 * @param op The Python dict.
 * @return 0 if the same, non-zero if different.
 */
template<
        typename K,
        typename V,
        PyObject *(*Convert_K)(const K &),
        PyObject *(*Convert_V)(const V &),
        K (*Convert_Py_Key)(PyObject *),
        V (*Convert_Py_Val)(PyObject *)
>
int compare_dict(std::unordered_map<K, V> const &cpp_map, PyObject *op) {
    assert(op);
    int result = 0;
    if (!PyDict_Check(op)) {
        result = 1;
    } else {
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
        // Now iterate across op and check against cpp_map.
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
    }
    return result;
}

// Base declaration
template<typename K, typename V>
int
compare_dict(const std::unordered_map<K, V> &cpp_map, PyObject *op);

// Instatiations
template <>
int
compare_dict<
        std::vector<char>, std::vector<char>
        >(const std::unordered_map<std::vector<char>, std::vector<char>> &cpp_map, PyObject *op);

template <>
int
compare_dict<
        std::string, std::string
        >(const std::unordered_map<std::string, std::string> &cpp_map, PyObject *op);

#pragma mark Tests of containers of strings.

// Functional test of tuples of vector<char>
int test_vector_vector_char_to_py_tuple(TestResultS &test_results, size_t size, size_t str_len);
int test_py_tuple_bytes_to_vector(TestResultS &test_results, size_t size, size_t str_len);
// Functional test of tuples of strings
int test_vector_string_to_py_tuple(TestResultS &test_results, size_t size, size_t str_len);
int test_py_tuple_str_to_vector(TestResultS &test_results, size_t size, size_t str_len);

// Functional test of list of vector<char>
int test_vector_vector_char_to_py_list(TestResultS &test_results, size_t size, size_t str_len);
int test_py_list_bytes_to_vector(TestResultS &test_results, size_t size, size_t str_len);
// Functional test of list of string
int test_vector_string_to_py_list(TestResultS &test_results, size_t size, size_t str_len);
int test_py_list_str_to_vector(TestResultS &test_results, size_t size, size_t str_len);

// Functional tests of sets of bytes
int test_unordered_set_bytes_to_py_set(TestResultS &test_results, size_t size, size_t str_len);
int test_py_set_bytes_to_unordered_set(TestResultS &test_results, size_t size, size_t str_len);
// Functional tests of sets of strings
int test_unordered_set_string_to_py_set(TestResultS &test_results, size_t size, size_t str_len);
int test_py_set_string_to_unordered_set(TestResultS &test_results, size_t size, size_t str_len);

// Functional tests of dict of bytes
int test_cpp_std_map_like_to_py_dict_bytes(TestResultS &test_results, size_t size, size_t str_len);
int test_py_dict_to_cpp_std_map_like_bytes(TestResultS &test_results, size_t size, size_t str_len);
// Functional tests of dict of strings
int test_cpp_std_map_like_to_py_dict_string(TestResultS &test_results, size_t size, size_t str_len);
int test_py_dict_to_cpp_std_map_like_string(TestResultS &test_results, size_t size, size_t str_len);

#pragma mark Generic test templates

template<typename T, T (*ConvertPyToCpp)(PyObject *)>
int test_vector_to_py_tuple(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    std::vector<T> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
        cpp_vector.push_back(static_cast<T>(i));
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (! op) {
        result = 1;
    } else {
        if (! Python_Cpp_Containers::py_tuple_check(op)) {
            result = 2;
        } else {
            if (compare_tuple(cpp_vector, op)) {
                result = 3;
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_TYPE;
    RSS_SNAPSHOT_REPORT;
    return result;
}

template<typename T, PyObject *(*ConvertCppToPy)(const T &), T (*ConvertPyToCpp)(PyObject *)>
int test_py_tuple_to_vector(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    PyObject *op = Python_Cpp_Containers::py_tuple_new(size);
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result = 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
            int err = Python_Cpp_Containers::py_tuple_set(op, i, ConvertCppToPy(static_cast<T>(i)));
            if (err != 0) {
                result = 2;
            }
        }
        if (result == 0) {
            std::vector<T> cpp_vector;
            ExecClock exec_clock;
            int err = Python_Cpp_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
            exec_time = exec_clock.seconds();
            if (err != 0) {
                result = 3;
            } else {
                if (compare_tuple(cpp_vector, op)) {
                    result = 4;
                }
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_TYPE;
    RSS_SNAPSHOT_REPORT;
    return result;
}

template<typename T>
int test_vector_to_py_tuple_round_trip(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
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
    REPORT_TEST_OUTPUT_WITH_TYPE;
    RSS_SNAPSHOT_REPORT;
    return result;
}

template<typename T, PyObject *(*Convert)(const T &)>
int test_py_tuple_to_vector_round_trip(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
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
    REPORT_TEST_OUTPUT_WITH_TYPE;
    RSS_SNAPSHOT_REPORT;
    return result;
}

template<typename T, T (*ConvertPyToCpp)(PyObject *)>
int test_vector_to_py_list(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    std::vector<T> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
        cpp_vector.push_back(static_cast<T>(i));
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_list(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (! op) {
        result = 1;
    } else {
        if (! Python_Cpp_Containers::py_list_check(op)) {
            result = 2;
        } else {
            if (compare_list(cpp_vector, op)) {
                result = 3;
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_TYPE;
    RSS_SNAPSHOT_REPORT;
    return result;
}

template<typename T, PyObject *(*ConvertCppToPy)(const T &), T (*ConvertPyToCpp)(PyObject *)>
int test_py_list_to_vector(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    PyObject *op = Python_Cpp_Containers::py_list_new(size);
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result = 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
            int err = Python_Cpp_Containers::py_list_set(op, i, ConvertCppToPy(static_cast<T>(i)));
            if (err != 0) {
                result = 2;
            }
        }
        if (result == 0) {
            std::vector<T> cpp_vector;
            ExecClock exec_clock;
            int err = Python_Cpp_Containers::py_list_to_cpp_std_vector(op, cpp_vector);
            exec_time = exec_clock.seconds();
            if (err != 0) {
                result = 3;
            } else {
                if (compare_list(cpp_vector, op)) {
                    result = 4;
                }
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_TYPE;
    RSS_SNAPSHOT_REPORT;
    return result;
}

template<typename T>
int test_vector_to_py_list_round_trip(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    std::vector<T> cpp_vector;
    std::vector<T> cpp_vector_result;
    for (size_t i = 0; i < size; ++i) {
        cpp_vector.push_back(static_cast<T>(i));
    }
    int result = 0;
    double exec_time = -1.0;
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_list(cpp_vector);
    if (op) {
        int err = Python_Cpp_Containers::py_list_to_cpp_std_vector(op, cpp_vector_result);
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
    REPORT_TEST_OUTPUT_WITH_TYPE;
    RSS_SNAPSHOT_REPORT;
    return result;
}

template<typename T, PyObject *(*Convert)(const T &)>
int test_py_list_to_vector_round_trip(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    PyObject *op = Python_Cpp_Containers::py_list_new(size);
    int result = 0;
    double exec_time = -1.0;
    int err = 0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
            err = Python_Cpp_Containers::py_list_set(op, i, Convert(static_cast<T>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::vector<T> cpp_vector;
            ExecClock exec_clock;
            err = Python_Cpp_Containers::py_list_to_cpp_std_vector(op, cpp_vector);
            if (err != 0) {
                result |= 1 << 2;
            } else {
                //  int PyObject_RichCompareBool(PyObject *o1, PyObject *o2, int opid) Py_EQ -1 error 0 false 1 true
                PyObject *op_new = Python_Cpp_Containers::cpp_std_vector_to_py_list(cpp_vector);
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
    REPORT_TEST_OUTPUT_WITH_TYPE;
    RSS_SNAPSHOT_REPORT;
    return result;
}

template<typename T, T (*ConvertPyToCpp)(PyObject *), PyObject *(*Convert_Py)(const T &)>
int test_unordered_set_to_py_set(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
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
    REPORT_TEST_OUTPUT_WITH_TYPE;
    RSS_SNAPSHOT_REPORT;
    return result;
}

template<typename T, T (*ConvertPyToCpp)(PyObject *), PyObject *(*ConvertCppToPy)(const T &)>
int test_py_set_to_unordered_set(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    PyObject *op = PySet_New(NULL);
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
            int err = PySet_Add(op, ConvertCppToPy(static_cast<T>(i)));
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
    REPORT_TEST_OUTPUT_WITH_TYPE;
    RSS_SNAPSHOT_REPORT;
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
int test_cpp_std_map_like_to_py_dict(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    std::unordered_map<K, V> cpp_map;
    for (size_t i = 0; i < size; ++i) {
//        cpp_map[1000 + static_cast<K>(i)] = 2000 + static_cast<V>(i);
        cpp_map[static_cast<K>(i)] = static_cast<V>(i);
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_map_like_to_py_dict(cpp_map);
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
    REPORT_TEST_OUTPUT_WITH_TYPE;
    RSS_SNAPSHOT_REPORT;
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
int test_py_dict_to_cpp_std_map_like(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
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
//            assert(py_k->ob_refcnt == py_k_ob_refcnt + 1 && "PyDict_SetItem failed to increment key refcount.");
            Py_DECREF(py_k);
//            assert(py_k->ob_refcnt == py_k_ob_refcnt);
//            assert(py_v->ob_refcnt == py_v_ob_refcnt + 1 && "PyDict_SetItem failed to increment value refcount.");
            Py_DECREF(py_v);
//            assert(py_v->ob_refcnt == py_v_ob_refcnt);

//            // TODO: This is a memory leak.
//            int err = PyDict_SetItem(op, Convert_K(static_cast<K>(i)), Convert_V(static_cast<V>(i)));
//            if (err != 0) {
//                result |= 1 << 1;
//            }
        }
        if (result == 0) {
            std::unordered_map<K, V> cpp_map;
            ExecClock exec_clock;
            int err = Python_Cpp_Containers::py_dict_to_cpp_std_map_like(op, cpp_map);
            exec_time = exec_clock.seconds();
            if (err != 0) {
                result |= 1 << 2;
            } else {
                result |= compare_dict<K, V, Convert_K, Convert_V, Convert_Py_Key, Convert_Py_Val>(cpp_map, op);
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_TYPE;
    RSS_SNAPSHOT_REPORT;
    return result;
}

#pragma mark Creation of new containers populated with bytes or strings.

PyObject *
new_py_tuple_bytes(size_t size, size_t str_len);
PyObject *
new_py_tuple_string(size_t size, size_t str_len);
PyObject *
new_py_list_bytes(size_t size, size_t str_len);
PyObject *
new_py_list_string(size_t size, size_t str_len);
PyObject *
new_py_set_bytes(size_t size, size_t str_len);
PyObject *
new_py_set_string(size_t size, size_t str_len);
PyObject *
new_py_dict_bytes(size_t size, size_t str_len);
PyObject *
new_py_dict_string(size_t size, size_t str_len);

#endif // PYTHONCPPHOMOGENEOUSCONTAINERS_TEST_COMMON_H
