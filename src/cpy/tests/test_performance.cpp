//
// Created by Paul Ross on 22/05/2021.
//

#include <Python.h>

#include "cpy/python_convert.h"
#include "test_common.h"
#include "test_performance.h"

// Test ranges
// Container lengths.
const size_t MIN_SIZE_OF_CONTAINER = 2;
const size_t LIMIT_SIZE_OF_CONTAINER = 1 << 21; // Maximum value < this value
const size_t INC_SIZE_OF_CONTAINER_MULTIPLE = 4;
// String lengths.
const size_t MIN_STRING_LENGTH = 8;
const size_t LIMIT_STRING_LENGTH = 4096 * 2; // Maximum value < this value
const size_t INC_STRING_LENGTH_MULTIPLE = 4;

template<typename T, T (*ConvertPyToCpp)(PyObject *)>
int test_perf_vector_to_py_tuple(TestResultS &test_results, const std::string &type) {
    int result = 0;
    for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
        result |= test_vector_to_py_tuple<T, ConvertPyToCpp>(test_results, type, size);
    }
    return result;
}

template<typename T, PyObject *(*ConvertCppToPy)(const T &), T (*ConvertPyToCpp)(PyObject *)>
int test_perf_py_tuple_to_vector(TestResultS &test_results, const std::string &type) {
    int result = 0;
    for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
        result |= test_py_tuple_to_vector<T, ConvertCppToPy, ConvertPyToCpp>(test_results, type, size);
    }
    return result;
}

int test_perf_vector_string_to_py_tuple(TestResultS &test_results) {
    int result = 0;
    for (size_t str_len = MIN_STRING_LENGTH; str_len < LIMIT_STRING_LENGTH; str_len *= INC_STRING_LENGTH_MULTIPLE) {
        for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
            result |= test_vector_string_to_py_tuple(test_results, size, str_len);
        }
    }
    return result;
}

int test_perf_vector_string_to_py_tuple_multiple(TestResultS &test_results, size_t repeat) {
    int result = 0;
    for (size_t str_len = MIN_STRING_LENGTH; str_len < LIMIT_STRING_LENGTH; str_len *= INC_STRING_LENGTH_MULTIPLE) {
        for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
            result |= test_vector_string_to_py_tuple_multiple(test_results, size, str_len, repeat);
        }
    }
    return result;
}

int test_perf_py_tuple_string_to_vector(TestResultS &test_results) {
    int result = 0;
    for (size_t str_len = MIN_STRING_LENGTH; str_len < LIMIT_STRING_LENGTH; str_len *= INC_STRING_LENGTH_MULTIPLE) {
        for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
            result |= test_py_tuple_string_to_vector(test_results, size, str_len);
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
int test_perf_cpp_std_unordered_map_to_py_dict(TestResultS &test_results, const std::string &type) {
    int result = 0;
    for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
        result |= test_cpp_std_unordered_map_to_py_dict<
                K, V, Convert_K, Convert_V, Convert_Py_Key, Convert_Py_Val>(test_results, type, size);
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
int test_perf_py_dict_to_cpp_std_unordered_map(TestResultS &test_results, const std::string &type) {
    int result = 0;
    for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
        result |= test_py_dict_to_cpp_std_unordered_map<
                K, V, Convert_K, Convert_V, Convert_Py_Key, Convert_Py_Val>(test_results, type, size);
    }
    return result;
}

int test_cpp_std_unordered_map_to_py_dict_string(TestResultS &test_results) {
    int result = 0;
    for (size_t str_len = MIN_STRING_LENGTH; str_len < LIMIT_STRING_LENGTH; str_len *= INC_STRING_LENGTH_MULTIPLE) {
        for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
            result |= test_cpp_std_unordered_map_to_py_dict_string(test_results, size, str_len);
        }
    }
    return result;
}


void test_performance_all(TestResultS &test_results) {
    RSSSnapshot rss_overall("==== test_performance.cpp");
    {
        RSSSnapshot rss("test_perf_vector_to_py_tuple<bool>");
        test_perf_vector_to_py_tuple<
                bool, &Python_Cpp_Containers::py_bool_to_cpp_bool
        >(test_results, "<bool>");
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_vector_to_py_tuple<long>");
        test_perf_vector_to_py_tuple<
                long, &Python_Cpp_Containers::py_long_to_cpp_long
        >(test_results, "<long>");
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_vector_to_py_tuple<double>");
        test_perf_vector_to_py_tuple<
                double,
                &Python_Cpp_Containers::py_float_to_cpp_double
        >(test_results, "<double>");
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_tuple_to_vector<bool>");
        test_perf_py_tuple_to_vector<
                bool,
                &Python_Cpp_Containers::cpp_bool_to_py_bool,
                &Python_Cpp_Containers::py_bool_to_cpp_bool
        >(test_results, "<bool>");
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_tuple_to_vector<long>");
        test_perf_py_tuple_to_vector<
                long,
                &Python_Cpp_Containers::cpp_long_to_py_long,
                &Python_Cpp_Containers::py_long_to_cpp_long
        >(test_results, "<long>");
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_tuple_to_vector<double>");
        test_perf_py_tuple_to_vector<
                double,
                &Python_Cpp_Containers::cpp_double_to_py_float,
                &Python_Cpp_Containers::py_float_to_cpp_double
        >(test_results, "<double>");
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_vector_string_to_py_tuple");
        test_perf_vector_string_to_py_tuple(test_results);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_tuple_string_to_vector");
        test_perf_py_tuple_string_to_vector(test_results);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_cpp_std_unordered_map_to_py_dict<double>");
        test_perf_cpp_std_unordered_map_to_py_dict<
                double,
                double,
                &Python_Cpp_Containers::cpp_double_to_py_float,
                &Python_Cpp_Containers::cpp_double_to_py_float,
                &Python_Cpp_Containers::py_float_to_cpp_double,
                &Python_Cpp_Containers::py_float_to_cpp_double
        >(test_results, "<double>");
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_dict_to_cpp_std_unordered_map<double>");
        test_perf_py_dict_to_cpp_std_unordered_map<
                double,
                double,
                &Python_Cpp_Containers::cpp_double_to_py_float,
                &Python_Cpp_Containers::cpp_double_to_py_float,
                &Python_Cpp_Containers::py_float_to_cpp_double,
                &Python_Cpp_Containers::py_float_to_cpp_double
        >(test_results, "<double>");
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_cpp_std_unordered_map_to_py_dict_string");
        test_cpp_std_unordered_map_to_py_dict_string(test_results);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_vector_string_to_py_tuple_multiple");
        test_perf_vector_string_to_py_tuple_multiple(test_results, 10);
        std::cout << rss << std::endl;
    }
    std::cout << "====" << rss_overall << std::endl;
}
