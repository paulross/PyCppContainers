//
// Created by Paul Ross on 22/05/2021.
//

#include <Python.h>

#include "cpy/python_convert.h"
#include "test_common.h"
#include "test_performance.h"

// Test ranges
// Container lengths.
const size_t MIN_SIZE_OF_CONTAINER = 1;
const size_t LIMIT_SIZE_OF_CONTAINER = 1 << 21; // Maximum value < this value
const size_t INC_SIZE_OF_CONTAINER_MULTIPLE = 2; // How much to increment the container size.
// How many times to repeat tests.
const size_t TEST_REPEAT = 5;
// String lengths.
const size_t MIN_STRING_LENGTH = 8;
const size_t LIMIT_STRING_LENGTH = 4096 * 2; // Maximum value < this value
const size_t INC_STRING_LENGTH_MULTIPLE = 8; // How much to increment the string size.

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

int test_vector_string_to_py_tuple_multiple(TestResultS &test_results, size_t size, size_t str_len, size_t repeat) {
    std::vector<std::string> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
        cpp_vector.push_back(std::string(str_len, ' '));
    }
    std::ostringstream title;
    title << __FUNCTION__  << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
    TestResult test_result(title.str());
    for (size_t i = 0; i < repeat; ++i) {
        ExecClock exec_clock;
        PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
        double exec_time = exec_clock.seconds();
        Py_DECREF(op);
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    test_results.push_back(test_result);
    return 0;
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

int test_py_tuple_bytes_to_vector_string_multiple(TestResultS &test_results, size_t size, size_t str_len, size_t repeat) {
    int result = 0;
    std::ostringstream title;
    title << __FUNCTION__  << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
    TestResult test_result(title.str());
    for (size_t i = 0; i < repeat; ++i) {
        PyObject *op = new_py_tuple_bytes(size, str_len);
        std::vector<std::string> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
        if (err) {
            result = -1;
            break;
        }
        double exec_time = exec_clock.seconds();
        Py_DECREF(op);
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    test_results.push_back(test_result);
    return result;
}

int test_perf_py_tuple_to_vector_string_multiple(TestResultS &test_results, size_t repeat) {
    int result = 0;
    for (size_t str_len = MIN_STRING_LENGTH; str_len < LIMIT_STRING_LENGTH; str_len *= INC_STRING_LENGTH_MULTIPLE) {
        for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
            result |= test_py_tuple_bytes_to_vector_string_multiple(test_results, size, str_len, repeat);
        }
    }
    return result;
}

#pragma mark Testing of lists multiple times

template<typename T>
int test_vector_to_py_list_multiple(TestResultS &test_results, const std::string &type, size_t size, size_t repeat) {
    std::vector<T> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
        cpp_vector.push_back(T());
    }
    std::ostringstream title;
    title << __FUNCTION__  << type << "[" << size << "]";
    TestResult test_result(title.str());
    for (size_t i = 0; i < repeat; ++i) {
        ExecClock exec_clock;
        PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_list(cpp_vector);
        double exec_time = exec_clock.seconds();
        Py_DECREF(op);
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    test_results.push_back(test_result);
    return 0;
}

template<typename T>
int test_perf_vector_to_py_list_multiple(TestResultS &test_results, const std::string &type, size_t repeat) {
    int result = 0;
    for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
        result |= test_vector_to_py_list_multiple<T>(test_results, type, size, repeat);
    }
    return result;
}


// TODO:
template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
int test_py_list_to_vector_multiple(TestResultS &test_results, const std::string &type, size_t size, size_t repeat) {
    PyObject *op = Python_Cpp_Containers::py_list_new(size);
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
            int err = Python_Cpp_Containers::py_list_set(op, i, ConvertCppToPy(static_cast<T>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::vector<T> cpp_vector;
            std::ostringstream title;
            title << __FUNCTION__ << type << "[" << size << "]";
            TestResult test_result(title.str());
            for (size_t i = 0; i < repeat; ++i) {
                ExecClock exec_clock;
                int err = Python_Cpp_Containers::py_list_to_cpp_std_vector(op, cpp_vector);
                exec_time = exec_clock.seconds();
                if (err != 0) {
                    result |= 1 << 2;
                } else {
                    if ((unsigned long) Python_Cpp_Containers::py_list_len(op) != cpp_vector.size()) {
                        result |= 1 << 3;
                    } else {
                        // Omit comparison of values as this is a performance test.
                    }
                }
                test_result.execTimeAdd(0, exec_time, 1, size);
            }
            Py_DECREF(op);
        }
    }
    REPORT_TEST_OUTPUT;
    return result;
}

template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
int test_perf_py_list_to_vector_multiple(TestResultS &test_results, const std::string &type, size_t repeat) {
    int result = 0;
    for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
        result |= test_py_list_to_vector_multiple<T, ConvertCppToPy>(test_results, type, size, repeat);
    }
    return result;
}

int test_py_list_bytes_to_vector_string_multiple(TestResultS &test_results, size_t size, size_t str_len, size_t repeat) {
    int result = 0;
    std::ostringstream title;
    title << __FUNCTION__  << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
    TestResult test_result(title.str());
    for (size_t i = 0; i < repeat; ++i) {
        PyObject *op = new_py_list_bytes(size, str_len);
        std::vector<std::string> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_list_to_cpp_std_vector(op, cpp_vector);
        if (err) {
            result = -1;
            break;
        }
        double exec_time = exec_clock.seconds();
        Py_DECREF(op);
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    test_results.push_back(test_result);
    return result;
}

int test_perf_py_list_to_vector_string_multiple(TestResultS &test_results, size_t repeat) {
    int result = 0;
    for (size_t str_len = MIN_STRING_LENGTH; str_len < LIMIT_STRING_LENGTH; str_len *= INC_STRING_LENGTH_MULTIPLE) {
        for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
            result |= test_py_list_bytes_to_vector_string_multiple(test_results, size, str_len, repeat);
        }
    }
    return result;
}

int test_vector_string_to_py_list_multiple(TestResultS &test_results, size_t size, size_t str_len, size_t repeat) {
    std::vector<std::string> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
        cpp_vector.push_back(std::string(str_len, ' '));
    }
    std::ostringstream title;
    title << __FUNCTION__  << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
    TestResult test_result(title.str());
    for (size_t i = 0; i < repeat; ++i) {
        ExecClock exec_clock;
        PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_list(cpp_vector);
        double exec_time = exec_clock.seconds();
        Py_DECREF(op);
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    test_results.push_back(test_result);
    return 0;
}

int test_perf_vector_string_to_py_list_multiple(TestResultS &test_results, size_t repeat) {
    int result = 0;
    for (size_t str_len = MIN_STRING_LENGTH; str_len < LIMIT_STRING_LENGTH; str_len *= INC_STRING_LENGTH_MULTIPLE) {
        for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
            result |= test_vector_string_to_py_list_multiple(test_results, size, str_len, repeat);
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
//    {
//        RSSSnapshot rss("test_perf_vector_to_py_tuple<bool>");
//        test_perf_vector_to_py_tuple<
//                bool, &Python_Cpp_Containers::py_bool_to_cpp_bool
//        >(test_results, "<bool>");
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_perf_vector_to_py_tuple<long>");
//        test_perf_vector_to_py_tuple<
//                long, &Python_Cpp_Containers::py_long_to_cpp_long
//        >(test_results, "<long>");
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_perf_vector_to_py_tuple<double>");
//        test_perf_vector_to_py_tuple<
//                double,
//                &Python_Cpp_Containers::py_float_to_cpp_double
//        >(test_results, "<double>");
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_perf_py_tuple_to_vector<bool>");
//        test_perf_py_tuple_to_vector<
//                bool,
//                &Python_Cpp_Containers::cpp_bool_to_py_bool,
//                &Python_Cpp_Containers::py_bool_to_cpp_bool
//        >(test_results, "<bool>");
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_perf_py_tuple_to_vector<long>");
//        test_perf_py_tuple_to_vector<
//                long,
//                &Python_Cpp_Containers::cpp_long_to_py_long,
//                &Python_Cpp_Containers::py_long_to_cpp_long
//        >(test_results, "<long>");
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_perf_py_tuple_to_vector<double>");
//        test_perf_py_tuple_to_vector<
//                double,
//                &Python_Cpp_Containers::cpp_double_to_py_float,
//                &Python_Cpp_Containers::py_float_to_cpp_double
//        >(test_results, "<double>");
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_perf_vector_string_to_py_tuple");
//        test_perf_vector_string_to_py_tuple(test_results);
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_perf_py_tuple_string_to_vector");
//        test_perf_py_tuple_string_to_vector(test_results);
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_perf_cpp_std_unordered_map_to_py_dict<double>");
//        test_perf_cpp_std_unordered_map_to_py_dict<
//                double,
//                double,
//                &Python_Cpp_Containers::cpp_double_to_py_float,
//                &Python_Cpp_Containers::cpp_double_to_py_float,
//                &Python_Cpp_Containers::py_float_to_cpp_double,
//                &Python_Cpp_Containers::py_float_to_cpp_double
//        >(test_results, "<double>");
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_perf_py_dict_to_cpp_std_unordered_map<double>");
//        test_perf_py_dict_to_cpp_std_unordered_map<
//                double,
//                double,
//                &Python_Cpp_Containers::cpp_double_to_py_float,
//                &Python_Cpp_Containers::cpp_double_to_py_float,
//                &Python_Cpp_Containers::py_float_to_cpp_double,
//                &Python_Cpp_Containers::py_float_to_cpp_double
//        >(test_results, "<double>");
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_cpp_std_unordered_map_to_py_dict_string");
//        test_cpp_std_unordered_map_to_py_dict_string(test_results);
//        std::cout << rss << std::endl;
//    }
    // Test the performance of a Python tuple of bytes to and from C++
//    {
//        RSSSnapshot rss("test_perf_vector_string_to_py_tuple_multiple");
//        test_perf_vector_string_to_py_tuple_multiple(test_results, TEST_REPEAT);
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_perf_py_tuple_to_vector_string_multiple");
//        test_perf_py_tuple_to_vector_string_multiple(test_results, TEST_REPEAT);
//        std::cout << rss << std::endl;
//    }

//    // Test the performance of a Python list of bytes to and from C++
//    {
//        RSSSnapshot rss("test_perf_vector_string_to_py_list_multiple");
//        test_perf_vector_string_to_py_list_multiple(test_results, TEST_REPEAT);
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_perf_py_list_to_vector_string_multiple");
//        test_perf_py_list_to_vector_string_multiple(test_results, TEST_REPEAT);
//        std::cout << rss << std::endl;
//    }

//    // Fundamental types with test_perf_vector_to_py_list_multiple<>() for C++ -> Python
//    {
//        RSSSnapshot rss("test_perf_vector_to_py_list_multiple<bool>");
//        test_perf_vector_to_py_list_multiple<bool>(test_results, "<bool>", TEST_REPEAT);
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_perf_vector_to_py_list_multiple<long>");
//        test_perf_vector_to_py_list_multiple<long>(test_results, "<long>", TEST_REPEAT);
//        std::cout << rss << std::endl;
//    }
    {
        RSSSnapshot rss("test_perf_vector_to_py_list_multiple<double>");
        test_perf_vector_to_py_list_multiple<double>(test_results, "<double>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }

    // Fundamental types with test_perf_py_list_to_vector_multiple<>() for Python -> C++
//    {
//        RSSSnapshot rss("test_perf_py_list_to_vector_multiple<bool>");
//        test_perf_py_list_to_vector_multiple<
//                bool,
//                &Python_Cpp_Containers::cpp_bool_to_py_bool
//            >(test_results,"<bool>", TEST_REPEAT);
//        std::cout << rss << std::endl;
//    }
//    {
//        RSSSnapshot rss("test_perf_py_list_to_vector_multiple<long>");
//        test_perf_py_list_to_vector_multiple<
//                long,
//                &Python_Cpp_Containers::cpp_long_to_py_long
//            >(test_results,"<double>", TEST_REPEAT);
//        std::cout << rss << std::endl;
//    }
    {
        RSSSnapshot rss("test_perf_py_list_to_vector_multiple<double>");
        test_perf_py_list_to_vector_multiple<
                double,
                &Python_Cpp_Containers::cpp_double_to_py_float
            >(test_results,"<double>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }

    std::cout << "====" << rss_overall << std::endl;
}
