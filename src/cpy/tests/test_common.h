//
// Created by Paul Ross on 22/05/2021.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_TEST_COMMON_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_TEST_COMMON_H

#include <Python.h>

#include "cpy/python_convert.h"
#include "cpp/get_rss.h"
#include "cpp/TestFramework.h"

/// If non-zero then report the result of every test. This is very verbose.
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

#define REPORT_TEST_OUTPUT_WITH_CONTAINER_TYPE_STRING_LENGTH \
    do {                              \
        std::ostringstream title; \
        title << __FUNCTION__  << container_type << "<" << "std::string[" << str_len << "]>" << ">" << "():" << "[" << size << "]"; \
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
        title << __FUNCTION__  << " std::string[" << str_len << "]>" << "():" << "[" << size << "]"; \
        test_results.push_back(TestResult(title.str(), result, exec_time, 1, size)); \
    } while (0)

#define REPORT_TEST_OUTPUT_WITH_CONTAINER_TYPE_STRING_LENGTH \
    do {                              \
        std::ostringstream title; \
        title << __FUNCTION__  << container_type << "<" << "std::string[" << str_len << "]>" << ">" << "():" << "[" << size << "]"; \
        test_results.push_back(TestResult(title.str(), result, exec_time, 1, size)); \
    } while (0)
#endif

/// Enable the macros that do RSS snapshots.
#define RSS_SNAPSHOT
//#undef RSS_SNAPSHOT

#ifdef RSS_SNAPSHOT

/**
 * Take a snapshot of the current RSS value. The snapshot title is the function name.
 */
#define RSS_SNAPSHOT_WITHOUT_TYPE RSSSnapshot rss(__FUNCTION__);

/**
 * Take a snapshot of the current RSS value.
 * The snapshot title is the function name followed immediately by the type.
 * For example if the function is "foo" and the type is "<long>" the title will be "foo<long>".
 */
#define RSS_SNAPSHOT_WITH_TYPE(type) \
        std::ostringstream rss_title; \
        rss_title << __FUNCTION__ << type; \
        RSSSnapshot rss(rss_title.str());

/**
 * Take a snapshot of the current RSS value.
 * The snapshot title is the function name followed by the container and type.
 * For example if the function is "foo", the container is "vector" and the type is "long" the title will be "foo vector<long>".
 */
#define RSS_SNAPSHOT_WITH_CONTAINER_TYPE_AND_TYPE(container_type, type) \
        std::ostringstream rss_title; \
        rss_title << __FUNCTION__ << " " << container_type << "<" << type << ">"; \
        RSSSnapshot rss(rss_title.str());

/**
 * Report the RSS usage to \c stdout.
 */
#define RSS_SNAPSHOT_REPORT std::cout << rss << std::endl;
#else
#define RSS_SNAPSHOT_WITHOUT_TYPE
#define RSS_SNAPSHOT_WITH_TYPE(type)
#define RSS_SNAPSHOT_WITH_CONTAINER_TYPE_AND_TYPE(container_type, type)
#define RSS_SNAPSHOT_REPORT
#endif // RSS_SNAPSHOT

const int PY_ERR_ON_ENTRY_RETURN_CODE = -1;
const int PY_ERR_ON_EXIT_RETURN_CODE = -2;

#define TEST_FOR_PY_ERR_ON_ENTRY                \
    do {                                        \
        if (PyErr_Occurred()) {                 \
            PyErr_Print();                      \
            return PY_ERR_ON_ENTRY_RETURN_CODE; \
        }                                       \
    } while(0)

#define TEST_FOR_PY_ERR_ON_EXIT                 \
    do {                                        \
        if (PyErr_Occurred()) {                 \
            PyErr_Print();                      \
            return PY_ERR_ON_EXIT_RETURN_CODE;  \
        }                                       \
    } while(0)

#pragma mark Comparison templates

/**
 * Compares a Python tuple or list with a C++ \c std::vector.
 *
 * @tparam T C++ type of objects in the vector.
 * @tparam Convert_T_To_Py Pointer to function to convert a C++ type \c T to a \c PyObject*.
 * @tparam Convert_Py_To_T Pointer to function to convert a \c PyObject* to a C++ type \c T.
 * @tparam PyUnaryContainer_Check A function that takes a \c PyObject* and returns 1 if it is of a suitable container,
 *  0 otherwise.
 * @tparam PyUnaryContainer_Size A function that returns the length of the Python container.
 * @tparam PyUnaryContainer_GetA function that gets a \c PyObject* from the Python container at a given index as a
 *  \c size_t.
 * @param cpp_vector The C++ \c std::vector.
 * @param op The Python \c tuple or \c list.
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
    TEST_FOR_PY_ERR_ON_ENTRY;
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
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Specialisation of \c compare_tuple_or_list that compares a Python tuple with a C++ \c std::vector.
 *
 * @tparam T C++ type of objects in the vector.
 * @tparam Convert_T_To_Py Pointer to function to convert a C++ type \c T to a \c PyObject*.
 * @tparam Convert_Py_To_T Pointer to function to convert a \c PyObject* to a C++ type \c T.
 * @param cpp_vector The C++ vector.
 * @param op The Python \c tuple.
 * @return 0 if identical, non-zero if not.
 */
template<
        typename T,
        PyObject *(*Convert_T_To_Py)(const T &),
        T (*Convert_Py_To_T)(PyObject *)
>
int compare_tuple(std::vector<T> const &cpp_vector, PyObject *op) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    int ret = compare_tuple_or_list<
            T, Convert_T_To_Py, Convert_Py_To_T,
            &Python_Cpp_Containers::py_tuple_check, &Python_Cpp_Containers::py_tuple_len, &Python_Cpp_Containers::py_tuple_get
        >(cpp_vector, op);
    TEST_FOR_PY_ERR_ON_EXIT;
    return ret;
}

// Base template
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

template <>
int
compare_tuple<std::u16string>(const std::vector<std::u16string> &cpp_vector, PyObject *op);

template <>
int
compare_tuple<std::u32string>(const std::vector<std::u32string> &cpp_vector, PyObject *op);

/**
 * Specialisation of \c compare_tuple_or_list that compares a Python \c list with a C++ \c std::vector.
 *
 * @tparam T C++ type of objects in the vector.
 * @tparam Convert_T_To_Py Pointer to function to convert a C++ type \c T to a \c PyObject*.
 * @tparam Convert_Py_To_T Pointer to function to convert a \c PyObject* to a C++ type \c T.
 * @param cpp_vector The C++ \c std::vector.
 * @param op The Python \c list.
 * @return 0 if identical, non-zero if not.
 */
template<
        typename T,
        PyObject *(*Convert_T_To_Py)(const T &),
        T (*Convert_Py_To_T)(PyObject *)
>
int compare_list(std::vector<T> const &cpp_vector, PyObject *op) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    int ret = compare_tuple_or_list<
            T, Convert_T_To_Py, Convert_Py_To_T,
            &Python_Cpp_Containers::py_list_check, &Python_Cpp_Containers::py_list_len, &Python_Cpp_Containers::py_list_get
    >(cpp_vector, op);
    TEST_FOR_PY_ERR_ON_EXIT;
    return ret;
}

// Base declaration
template<typename T>
int
compare_list(const std::vector<T> &cpp_vector, PyObject *op);

// Instantiations, implementations are in test_common.cpp
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
 * Compares a Python \c set or \c frozenset with a C++ \c std::unordered_set.
 *
 * @tparam T C++ type of objects in the set.
 * @tparam Convert_T_To_Py Pointer to function to convert a C++ type \c T to a \c PyObject*.
 * @tparam Convert_Py_To_T Pointer to function to convert a \c PyObject* to a C++ type \c T.
 * @param cpp_set The C++ \c std::unordered_set.
 * @param op The Python \c set.
 * @return 0 if identical, non-zero if not.
 */
template<
        typename T,
        PyObject *(*Convert_T_To_Py)(const T &),
        T (*Convert_Py_To_T)(PyObject *)
>
int compare_set(const std::unordered_set<T> &cpp_set, PyObject *op) {
    TEST_FOR_PY_ERR_ON_ENTRY;
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
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

// Base declaration
template<typename T>
int
compare_set(const std::unordered_set<T> &cpp_set, PyObject *op);

// Instantiations, implementations are in test_common.cpp
template <>
int
compare_set<std::vector<char>>(const std::unordered_set<std::vector<char>> &cpp_set, PyObject *op);

template <>
int
compare_set<std::string>(const std::unordered_set<std::string> &cpp_set, PyObject *op);

/**
 * Compare a Python \c dict with a C++ \c std::unordered_map or \c std::map.
 *
 * @tparam MapLike The C++ type of the container.
 * @tparam K The C++ type of the keys.
 * @tparam V The C++ type of the values.
 * @tparam Convert_K Pointer to function to convert a C++ type \c K to a \c PyObject*.
 * @tparam Convert_V Pointer to function to convert a C++ type \c V to a PyObject*.
 * @tparam Convert_Py_Key Pointer to function to convert a \c PyObject* key to a C++ type \c K.
 * @tparam Convert_Py_Val Pointer to function to convert a \c PyObject* value to a C++ type \c V.
 * @param cpp_map The C++ \c std::unordered_map or \c std::map.
 * @param op The Python \c dict.
 * @return 0 if the same, non-zero if different.
 */
template<
        template<typename ...> class MapLike,
        typename K,
        typename V,
        PyObject *(*Convert_K)(const K &),
        PyObject *(*Convert_V)(const V &),
        K (*Convert_Py_Key)(PyObject *),
        V (*Convert_Py_Val)(PyObject *)
>
int compare_dict(MapLike<K, V> const &cpp_map, PyObject *op) {
    TEST_FOR_PY_ERR_ON_ENTRY;
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
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

// Base declaration
template<template<typename ...> class MapLike, typename K, typename V>
int
compare_dict(const MapLike<K, V> &cpp_map, PyObject *op);

// Instantiations, implementations are in test_common.cpp
template <>
int
compare_dict<
        std::unordered_map, std::vector<char>, std::vector<char>
        >(const std::unordered_map<std::vector<char>, std::vector<char>> &cpp_map, PyObject *op);

template <>
int
compare_dict<
        std::unordered_map, std::string, std::string
        >(const std::unordered_map<std::string, std::string> &cpp_map, PyObject *op);

template <>
int
compare_dict<
        std::map, std::vector<char>, std::vector<char>
        >(const std::map<std::vector<char>, std::vector<char>> &cpp_map, PyObject *op);

template <>
int
compare_dict<
        std::map, std::string, std::string
        >(const std::map<std::string, std::string> &cpp_map, PyObject *op);

#pragma mark Tests of containers of strings.

// Functional test of tuples of vector<char>
int test_vector_vector_char_to_py_tuple(TestResultS &test_results, size_t size, size_t str_len);
int test_py_tuple_bytes_to_vector(TestResultS &test_results, size_t size, size_t str_len);
// Functional test of tuples of strings
int test_vector_string_to_py_tuple(TestResultS &test_results, size_t size, size_t str_len);
int test_py_tuple_str_to_vector(TestResultS &test_results, size_t size, size_t str_len);
// Functional test of tuples of 16 bit strings
int test_vector_u16string_to_py_tuple(TestResultS &test_results, size_t size, size_t str_len);
int test_py_tuple_str16_to_vector(TestResultS &test_results, size_t size, size_t str_len);
// Functional test of tuples of 32 bit strings
int test_vector_u32string_to_py_tuple(TestResultS &test_results, size_t size, size_t str_len);
int test_py_tuple_str32_to_vector(TestResultS &test_results, size_t size, size_t str_len);

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

// Functional tests of dict of bytes to and from std::unordered_map
int test_cpp_std_unordered_map_to_py_dict_bytes(TestResultS &test_results, size_t size, size_t str_len);
int test_py_dict_to_cpp_std_unordered_map_bytes(TestResultS &test_results, size_t size, size_t str_len);
// Functional tests of dict of strings to and from std::unordered_map
int test_cpp_std_unordered_map_to_py_dict_string(TestResultS &test_results, size_t size, size_t str_len);
int test_py_dict_to_cpp_std_unordered_map_string(TestResultS &test_results, size_t size, size_t str_len);

// Functional tests of dict of bytes to and from std::map
int test_cpp_std_map_to_py_dict_bytes(TestResultS &test_results, size_t size, size_t str_len);
int test_py_dict_to_cpp_std_map_bytes(TestResultS &test_results, size_t size, size_t str_len);
// Functional tests of dict of strings to and from std::map
int test_cpp_std_map_to_py_dict_string(TestResultS &test_results, size_t size, size_t str_len);
int test_py_dict_to_cpp_std_map_string(TestResultS &test_results, size_t size, size_t str_len);

#pragma mark Generic test templates

/**
 * Tests a C++ \c std::vector to a Python \c tuple.
 *
 * @tparam T Type of the vector objects.
 * @tparam ConvertPyToCpp Function to convert a Python object to a C++ \c <T>
 * @param test_results The test results to update.
 * @param type Type of \c <T>
 * @param size Size of the \c std::vector to create.
 * @return 0 on success. Non-zero on failure.
 */
template<typename T, T (*ConvertPyToCpp)(PyObject *)>
int test_vector_to_py_tuple(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    std::vector<T> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
        cpp_vector.push_back(static_cast<T>(i));
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_list_like_to_py_tuple(cpp_vector);
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

/**
 * Tests a C++ \c std::vector to a Python \c tuple.
 *
 * @tparam T Type of the vector objects.
 * @tparam ConvertCppToPy Function to convert a C++ \c <T> to a Python object.
 * @param test_results The test results to update.
 * @param type Type of \c <T>
 * @param size Size of the \c std::vector to create.
 * @return 0 on success. Non-zero on failure.
 */
template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
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
            int err = Python_Cpp_Containers::py_tuple_to_cpp_std_list_like(op, cpp_vector);
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

/**
 * Tests a C++ \c std::vector to a Python \c tuple and back to a C++ \c std::vector.
 *
 * @tparam T Type of the vector objects.
 * @param test_results The test results to update.
 * @param type Type of \c <T>
 * @param size Size of the \c std::vector to create.
 * @return 0 on success. Non-zero on failure.
 */
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
    PyObject *op = Python_Cpp_Containers::cpp_std_list_like_to_py_tuple(cpp_vector);
    if (op) {
        int err = Python_Cpp_Containers::py_tuple_to_cpp_std_list_like(op, cpp_vector_result);
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

/**
 * Tests a Python \c tuple to a C++ \c std::vector and back to a Python \c tuple.
 *
 * @tparam T Type of the vector objects.
 * @tparam ConvertCppToPy Function to convert a C++ \c <T> to a Python object.
 * @param test_results The test results to update.
 * @param type Type of \c <T>
 * @param size Size of the \c std::vector to create.
 * @return 0 on success. Non-zero on failure.
 */
template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
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
            err = Python_Cpp_Containers::py_tuple_set(op, i, ConvertCppToPy(static_cast<T>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::vector<T> cpp_vector;
            ExecClock exec_clock;
            err = Python_Cpp_Containers::py_tuple_to_cpp_std_list_like(op, cpp_vector);
            if (err != 0) {
                result |= 1 << 2;
            } else {
                //  int PyObject_RichCompareBool(PyObject *o1, PyObject *o2, int opid) Py_EQ -1 error 0 false 1 true
                PyObject *op_new = Python_Cpp_Containers::cpp_std_list_like_to_py_tuple(cpp_vector);
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

/**
 * Tests a Python \c vector to a C++ \c std::vector.
 *
 * @tparam T Type of the vector objects.
 * @param test_results The test results to update.
 * @param type Type of \c <T>
 * @param size Size of the \c std::vector to create.
 * @return 0 on success. Non-zero on failure.
 */
template<typename T>
int test_vector_to_py_list(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    std::vector<T> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
        cpp_vector.push_back(static_cast<T>(i));
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_list_like_to_py_list(cpp_vector);
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
            int err = Python_Cpp_Containers::py_list_to_cpp_std_list_like(op, cpp_vector);
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
    PyObject *op = Python_Cpp_Containers::cpp_std_list_like_to_py_list(cpp_vector);
    if (op) {
        int err = Python_Cpp_Containers::py_list_to_cpp_std_list_like(op, cpp_vector_result);
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

template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
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
            err = Python_Cpp_Containers::py_list_set(op, i, ConvertCppToPy(static_cast<T>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::vector<T> cpp_vector;
            ExecClock exec_clock;
            err = Python_Cpp_Containers::py_list_to_cpp_std_list_like(op, cpp_vector);
            if (err != 0) {
                result |= 1 << 2;
            } else {
                //  int PyObject_RichCompareBool(PyObject *o1, PyObject *o2, int opid) Py_EQ -1 error 0 false 1 true
                PyObject *op_new = Python_Cpp_Containers::cpp_std_list_like_to_py_list(cpp_vector);
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

template<typename T, T (*ConvertPyToCpp)(PyObject *), PyObject *(*ConvertCppToPy)(const T &)>
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
            if (compare_set<T, ConvertCppToPy, ConvertPyToCpp>(cpp_container, op)) {
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
        template<typename ...> class MapLike,
        typename K,
        typename V,
        PyObject *(*Convert_K)(const K &),
        PyObject *(*Convert_V)(const V &),
        K (*Convert_Py_Key)(PyObject *),
        V (*Convert_Py_Val)(PyObject *)
>
int test_cpp_std_map_like_to_py_dict(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    MapLike<K, V> cpp_map;
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
                result |= compare_dict<MapLike, K, V, Convert_K, Convert_V,  Convert_Py_Key, Convert_Py_Val>(cpp_map, op);
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
int test_cpp_std_unordered_map_to_py_dict(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    int result = test_cpp_std_map_like_to_py_dict<std::unordered_map, K, V, Convert_K, Convert_V, Convert_Py_Key, Convert_Py_Val>(
            test_results, type, size);
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
int test_cpp_std_map_to_py_dict(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    int result = test_cpp_std_map_like_to_py_dict<std::map, K, V, Convert_K, Convert_V, Convert_Py_Key, Convert_Py_Val>(
            test_results, type, size);
    RSS_SNAPSHOT_REPORT;
    return result;
}

template<
        template<typename ...> class MapLike,
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
            py_v = (*Convert_V)(static_cast<V>(i));
            if (! py_v) {
                // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                PyErr_Format(PyExc_ValueError, "C++ value of can not be converted.");
                Py_DECREF(py_k);
                result |= 1 << 2;
                break;
            }
            if (PyDict_SetItem(op, py_k, py_v)) {
                // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                PyErr_Format(PyExc_ValueError, "Can not set an item in the Python dict.");
                result |= 1 << 3;
                break;
            }
            Py_DECREF(py_k);
            Py_DECREF(py_v);
        }
        if (result == 0) {
            MapLike<K, V> cpp_map;
            ExecClock exec_clock;
            int err = Python_Cpp_Containers::py_dict_to_cpp_std_map_like(op, cpp_map);
            exec_time = exec_clock.seconds();
            if (err != 0) {
                result |= 1 << 2;
            } else {
                result |= compare_dict<MapLike, K, V, Convert_K, Convert_V, Convert_Py_Key, Convert_Py_Val>(cpp_map, op);
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
int test_py_dict_to_cpp_std_unordered_map(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    int result = test_py_dict_to_cpp_std_map_like<std::unordered_map, K, V, Convert_K, Convert_V, Convert_Py_Key, Convert_Py_Val>(
            test_results, type, size);
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
int test_py_dict_to_cpp_std_map(TestResultS &test_results, const std::string &type, size_t size) {
    RSS_SNAPSHOT_WITH_TYPE(type);
    int result = test_py_dict_to_cpp_std_map_like<std::map, K, V, Convert_K, Convert_V, Convert_Py_Key, Convert_Py_Val>(
            test_results, type, size);
    RSS_SNAPSHOT_REPORT;
    return result;
}

#pragma mark Creation of new containers populated with bytes or strings.

PyObject *
new_py_tuple_bytes(size_t size, size_t str_len);
PyObject *
new_py_tuple_string(size_t size, size_t str_len);
PyObject *
new_py_tuple_string16(size_t size, size_t str_len);
PyObject *
new_py_tuple_string32(size_t size, size_t str_len);
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
