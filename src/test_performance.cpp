//
// Created by Paul Ross on 22/05/2021.
//

#include <Python.h>

#include "python_convert.h"
#include "test_common.h"
#include "test_performance.h"

template<typename T, T (*ConvertPyToCpp)(PyObject *)>
int test_perf_vector_to_py_tuple(TestResultS &test_results, const std::string &type) {
    int result = 0;
    for (size_t size = 2; size < 1 << 24; size *= 2) {
        result |= test_vector_to_py_tuple<T, ConvertPyToCpp>(test_results, type, size);
    }
    return result;
}

int test_perf_vector_string_to_py_tuple(TestResultS &test_results) {
    int result = 0;
    for (size_t str_len = 1; str_len <= 512; str_len *=2) {
        for (size_t size = 2; size < 1 << 21; size *= 2) {
            result |= test_vector_string_to_py_tuple(test_results, size, str_len);
        }
    }
    return result;
}

int test_perf_py_tuple_string_to_vector(TestResultS &test_results) {
    int result = 0;
    for (size_t str_len = 1; str_len <= 512; str_len *=2) {
        for (size_t size = 2; size < 1 << 21; size *= 2) {
            result |= test_py_tuple_string_to_vector(test_results, size, str_len);
        }
    }
    return result;
}

void test_performance_all(TestResultS &test_results) {
    test_perf_vector_to_py_tuple<bool, &Python_Cpp_Homogeneous_Containers::py_bool_as_bool>(test_results,
                                                                                                 "<bool>");
    test_perf_vector_to_py_tuple<long, &Python_Cpp_Homogeneous_Containers::py_long_as_long>(test_results,
                                                                                                 "<long>");
    test_perf_vector_to_py_tuple<double, &Python_Cpp_Homogeneous_Containers::py_float_as_double>(test_results,
                                                                                                 "<double>");
    test_perf_vector_string_to_py_tuple(test_results);
    test_perf_py_tuple_string_to_vector(test_results);
}


