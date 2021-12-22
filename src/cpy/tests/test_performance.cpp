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
const size_t LIMIT_SIZE_OF_CONTAINER_DICT = 1 << 21; // Maximum size < this value
const size_t INC_SIZE_OF_CONTAINER_MULTIPLE = 2; // How much to increment the container size.
// How many times to repeat tests.
const size_t TEST_REPEAT = 5;
// String lengths.
// Either 8, 64, 512, 4096
// Or could use 4, 32, 256, 2048
// Or could use 2, 16, 128, 1024
const size_t MIN_STRING_LENGTH = 2;//8;
const size_t LIMIT_STRING_LENGTH = 1024 * 2;//4096 * 2; // Maximum value < this value
const size_t INC_STRING_LENGTH_MULTIPLE = 8; // How much to increment the string size.

#pragma mark Testing of object conversion

int test_long_to_py_int_multiple(TestResultS &test_results, size_t size, size_t repeat) {
    std::ostringstream title;
    title << __FUNCTION__ << "[" << size << "]";
    TestResult test_result(title.str());
    for (size_t i = 0; i < repeat; ++i) {
        ExecClock exec_clock;
        for (size_t j = 0; j < size; ++j) {
            PyObject *op = Python_Cpp_Containers::cpp_long_to_py_long(1234);
            Py_DECREF(op);
        }
        double exec_time = exec_clock.seconds();
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    test_results.push_back(test_result);
    return 0;
}

int test_py_int_to_cpp_long_multiple(TestResultS &test_results, size_t size, size_t repeat) {
    std::ostringstream title;
    title << __FUNCTION__ << "[" << size << "]";
    TestResult test_result(title.str());
    PyObject *op = Python_Cpp_Containers::cpp_long_to_py_long(1234);
    for (size_t i = 0; i < repeat; ++i) {
        ExecClock exec_clock;
        for (size_t j = 0; j < size; ++j) {
            Python_Cpp_Containers::py_long_to_cpp_long(op);
        }
        double exec_time = exec_clock.seconds();
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    Py_DECREF(op);
    test_results.push_back(test_result);
    return 0;
}

int test_double_to_py_float_multiple(TestResultS &test_results, size_t size, size_t repeat) {
    std::ostringstream title;
    title << __FUNCTION__ << "[" << size << "]";
    TestResult test_result(title.str());
    for (size_t i = 0; i < repeat; ++i) {
        ExecClock exec_clock;
        for (size_t j = 0; j < size; ++j) {
            PyObject *op = Python_Cpp_Containers::cpp_double_to_py_float(100.0);
            Py_DECREF(op);
        }
        double exec_time = exec_clock.seconds();
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    test_results.push_back(test_result);
    return 0;
}

int test_py_float_to_cpp_double_multiple(TestResultS &test_results, size_t size, size_t repeat) {
    std::ostringstream title;
    title << __FUNCTION__ << "[" << size << "]";
    TestResult test_result(title.str());
    PyObject *op = Python_Cpp_Containers::cpp_double_to_py_float(1234.0);
    for (size_t i = 0; i < repeat; ++i) {
        ExecClock exec_clock;
        for (size_t j = 0; j < size; ++j) {
            Python_Cpp_Containers::py_float_to_cpp_double(op);
        }
        double exec_time = exec_clock.seconds();
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    Py_DECREF(op);
    test_results.push_back(test_result);
    return 0;
}

int test_cpp_string_to_py_bytes_multiple(TestResultS &test_results, size_t string_size, size_t size, size_t repeat) {
    std::ostringstream title;
    title << __FUNCTION__ << "_" << string_size << "[" << size << "]";
    TestResult test_result(title.str());
    std::string str(string_size, ' ');
    for (size_t i = 0; i < repeat; ++i) {
        ExecClock exec_clock;
        for (size_t j = 0; j < size; ++j) {
            PyObject *op = Python_Cpp_Containers::cpp_string_to_py_bytes(str);
            Py_DECREF(op);
        }
        double exec_time = exec_clock.seconds();
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    test_results.push_back(test_result);
    return 0;
}

int test_py_bytes_to_cpp_string_multiple(TestResultS &test_results, size_t string_size, size_t size, size_t repeat) {
    std::ostringstream title;
    title << __FUNCTION__ << "_" << string_size << "[" << size << "]";
    TestResult test_result(title.str());
    std::string str(string_size, ' ');
    PyObject *op = Python_Cpp_Containers::cpp_string_to_py_bytes(str);
    for (size_t i = 0; i < repeat; ++i) {
        ExecClock exec_clock;
        for (size_t j = 0; j < size; ++j) {
            Python_Cpp_Containers::py_bytes_to_cpp_string(op);
        }
        double exec_time = exec_clock.seconds();
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    Py_DECREF(op);
    test_results.push_back(test_result);
    return 0;
}


#pragma mark Testing of tuples multiple times

template<typename T>
int test_vector_to_py_tuple_multiple(TestResultS &test_results, const std::string &type, size_t size, size_t repeat) {
    std::vector<T> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
        cpp_vector.push_back(T(i));
    }
    std::ostringstream title;
    title << __FUNCTION__ << type << "[" << size << "]";
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
int test_perf_vector_to_py_tuple_multiple(TestResultS &test_results, const std::string &type, size_t repeat) {
    int result = 0;
    for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
        result |= test_vector_to_py_tuple_multiple<T>(test_results, type, size, repeat);
    }
    return result;
}

template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
int test_py_tuple_to_vector_multiple(TestResultS &test_results, const std::string &type, size_t size, size_t repeat) {
    PyObject *op = Python_Cpp_Containers::py_list_new(size);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
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
            for (size_t r = 0; r < repeat; ++r) {
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
            test_results.push_back(test_result);
        }
    }
    return result;
}

template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
int test_perf_py_tuple_to_vector_multiple(TestResultS &test_results, const std::string &type, size_t repeat) {
    int result = 0;
    for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
        result |= test_py_tuple_to_vector_multiple<T, ConvertCppToPy>(test_results, type, size, repeat);
    }
    return result;
}

int test_vector_string_to_py_tuple_multiple(TestResultS &test_results, size_t size, size_t str_len, size_t repeat) {
    std::vector<std::string> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
        cpp_vector.push_back(std::string(str_len, ' '));
    }
    std::ostringstream title;
    title << __FUNCTION__ << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
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
        for (size_t size = MIN_SIZE_OF_CONTAINER;
             size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
            result |= test_vector_string_to_py_tuple_multiple(test_results, size, str_len, repeat);
        }
    }
    return result;
}

int
test_py_tuple_bytes_to_vector_string_multiple(TestResultS &test_results, size_t size, size_t str_len, size_t repeat) {
    int result = 0;
    std::ostringstream title;
    title << __FUNCTION__ << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
    TestResult test_result(title.str());
    PyObject *op = new_py_tuple_bytes(size, str_len);
    for (size_t i = 0; i < repeat; ++i) {
        std::vector<std::string> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
        double exec_time = exec_clock.seconds();
        if (err) {
            result = -1;
            break;
        }
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    Py_DECREF(op);
    test_results.push_back(test_result);
    return result;
}

int test_perf_py_tuple_to_vector_string_multiple(TestResultS &test_results, size_t repeat) {
    int result = 0;
    for (size_t str_len = MIN_STRING_LENGTH; str_len < LIMIT_STRING_LENGTH; str_len *= INC_STRING_LENGTH_MULTIPLE) {
        for (size_t size = MIN_SIZE_OF_CONTAINER;
             size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
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
        cpp_vector.push_back(T(i));
    }
    std::ostringstream title;
    title << __FUNCTION__ << type << "[" << size << "]";
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

template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
int test_py_list_to_vector_multiple(TestResultS &test_results, const std::string &type, size_t size, size_t repeat) {
    PyObject *op = Python_Cpp_Containers::py_list_new(size);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
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
            for (size_t r = 0; r < repeat; ++r) {
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
            test_results.push_back(test_result);
        }
    }
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

int
test_py_list_bytes_to_vector_string_multiple(TestResultS &test_results, size_t size, size_t str_len, size_t repeat) {
    int result = 0;
    std::ostringstream title;
    title << __FUNCTION__ << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
    TestResult test_result(title.str());
    PyObject *op = new_py_list_bytes(size, str_len);
    for (size_t i = 0; i < repeat; ++i) {
        std::vector<std::string> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_list_to_cpp_std_vector(op, cpp_vector);
        double exec_time = exec_clock.seconds();
        if (err) {
            result = -1;
            break;
        }
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    Py_DECREF(op);
    test_results.push_back(test_result);
    return result;
}

int test_perf_py_list_to_vector_string_multiple(TestResultS &test_results, size_t repeat) {
    int result = 0;
    for (size_t str_len = MIN_STRING_LENGTH; str_len < LIMIT_STRING_LENGTH; str_len *= INC_STRING_LENGTH_MULTIPLE) {
        for (size_t size = MIN_SIZE_OF_CONTAINER;
             size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
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
    title << __FUNCTION__ << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
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
        for (size_t size = MIN_SIZE_OF_CONTAINER;
             size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
            result |= test_vector_string_to_py_list_multiple(test_results, size, str_len, repeat);
        }
    }
    return result;
}

#pragma mark Testing of sets multiple times

template<typename T>
int
test_unordered_set_to_py_set_multiple(TestResultS &test_results, const std::string &type, size_t size, size_t repeat) {
    std::unordered_set<T> cpp_set;
    for (size_t i = 0; i < size; ++i) {
        cpp_set.insert(T(i));
    }
    std::ostringstream title;
    title << __FUNCTION__ << type << "[" << size << "]";
    TestResult test_result(title.str());
    for (size_t i = 0; i < repeat; ++i) {
        ExecClock exec_clock;
        PyObject *op = Python_Cpp_Containers::cpp_std_unordered_set_to_py_set(cpp_set);
        double exec_time = exec_clock.seconds();
        Py_DECREF(op);
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    test_results.push_back(test_result);
    return 0;
}

template<typename T>
int test_perf_unordered_set_to_py_set_multiple(TestResultS &test_results, const std::string &type, size_t repeat) {
    int result = 0;
    for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
        result |= test_unordered_set_to_py_set_multiple<T>(test_results, type, size, repeat);
    }
    return result;
}

template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
int
test_py_set_to_unordered_set_multiple(TestResultS &test_results, const std::string &type, size_t size, size_t repeat) {
    PyObject *op = Python_Cpp_Containers::py_set_new(NULL);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
            int err = Python_Cpp_Containers::py_set_add(op, ConvertCppToPy(static_cast<T>(i)));
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::unordered_set<T> cpp_set;
            std::ostringstream title;
            title << __FUNCTION__ << type << "[" << size << "]";
            TestResult test_result(title.str());
            for (size_t r = 0; r < repeat; ++r) {
                ExecClock exec_clock;
                int err = Python_Cpp_Containers::py_set_to_cpp_std_unordered_set(op, cpp_set);
                exec_time = exec_clock.seconds();
                if (err != 0) {
                    result |= 1 << 2;
                } else {
                    if ((unsigned long) Python_Cpp_Containers::py_set_len(op) != cpp_set.size()) {
                        result |= 1 << 3;
                    } else {
                        // Omit comparison of values as this is a performance test.
                    }
                }
                test_result.execTimeAdd(0, exec_time, 1, size);
            }
            Py_DECREF(op);
            test_results.push_back(test_result);
        }
    }
    // Check PyErr_Occurred
    return result;
}

template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
int test_perf_py_set_to_unordered_set_multiple(TestResultS &test_results, const std::string &type, size_t repeat) {
    int result = 0;
    for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
        result |= test_py_set_to_unordered_set_multiple<T, ConvertCppToPy>(test_results, type, size, repeat);
    }
    return result;
}

int test_unordered_set_string_to_py_set_multiple(TestResultS &test_results, size_t size, size_t str_len, size_t repeat) {
    std::unordered_set<std::string> cpp_set;
    for (size_t i = 0; i < size; ++i) {
        cpp_set.insert(unique_string(str_len));
    }
    std::ostringstream title;
    title << __FUNCTION__  << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
    TestResult test_result(title.str());
    for (size_t i = 0; i < repeat; ++i) {
        ExecClock exec_clock;
        PyObject *op = Python_Cpp_Containers::cpp_std_unordered_set_to_py_set(cpp_set);
        double exec_time = exec_clock.seconds();
        Py_DECREF(op);
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    test_results.push_back(test_result);
    return 0;
}

int test_perf_unordered_set_string_to_py_set_multiple(TestResultS &test_results, size_t repeat) {
    int result = 0;
    for (size_t str_len = MIN_STRING_LENGTH; str_len < LIMIT_STRING_LENGTH; str_len *= INC_STRING_LENGTH_MULTIPLE) {
        for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
            result |= test_unordered_set_string_to_py_set_multiple(test_results, size, str_len, repeat);
        }
    }
    return result;
}

int test_py_set_bytes_to_unordered_set_string_multiple(TestResultS &test_results, size_t size, size_t str_len, size_t repeat) {
    int result = 0;
    std::ostringstream title;
    title << __FUNCTION__  << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
    TestResult test_result(title.str());
    PyObject *op = new_py_set_bytes(size, str_len);
    for (size_t i = 0; i < repeat; ++i) {
        std::unordered_set<std::string> cpp_set;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_set_to_cpp_std_unordered_set(op, cpp_set);
        double exec_time = exec_clock.seconds();
        if (err) {
            result = -1;
            break;
        }
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    Py_DECREF(op);
    test_results.push_back(test_result);
    return result;
}

int test_perf_py_set_bytes_to_unordered_set_string_multiple(TestResultS &test_results, size_t repeat) {
    int result = 0;
    for (size_t str_len = MIN_STRING_LENGTH; str_len < LIMIT_STRING_LENGTH; str_len *= INC_STRING_LENGTH_MULTIPLE) {
        for (size_t size = MIN_SIZE_OF_CONTAINER; size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
            result |= test_py_set_bytes_to_unordered_set_string_multiple(test_results, size, str_len, repeat);
        }
    }
    return result;
}

#pragma mark Testing of dicts multiple times

template<typename K, typename V>
int test_cpp_std_unordered_map_to_py_dict_multiple(TestResultS &test_results, const std::string &type, size_t size,
                                                   size_t repeat) {
    std::unordered_map<K, V> cpp_map;
    for (size_t i = 0; i < size; ++i) {
        cpp_map[static_cast<K>(i)] = static_cast<V>(i);
    }
    std::ostringstream title;
    title << __FUNCTION__ << type << "[" << size << "]";
    TestResult test_result(title.str());
    for (size_t i = 0; i < repeat; ++i) {
        ExecClock exec_clock;
        PyObject *op = Python_Cpp_Containers::cpp_std_unordered_map_to_py_dict(cpp_map);
        double exec_time = exec_clock.seconds();
        Py_DECREF(op);
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    test_results.push_back(test_result);
    return 0;
}

template<typename K, typename V>
int
test_perf_cpp_std_unordered_map_to_py_dict_multiple(TestResultS &test_results, const std::string &type, size_t repeat) {
    int result = 0;
    for (size_t size = MIN_SIZE_OF_CONTAINER;
         size < LIMIT_SIZE_OF_CONTAINER_DICT; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
        result |= test_cpp_std_unordered_map_to_py_dict_multiple<K, V>(test_results, type, size, repeat);
    }
    return result;
}

template<
        typename K,
        typename V,
        PyObject *(*Convert_K)(const K &),
        PyObject *(*Convert_V)(const V &)
>
int test_py_dict_to_cpp_std_unordered_map_multiple(TestResultS &test_results, const std::string &type, size_t size,
                                                   size_t repeat) {
    PyObject *op = PyDict_New();
    PyObject *py_k = NULL;
    PyObject *py_v = NULL;
    std::ostringstream title;
    title << __FUNCTION__ << type << "[" << size << "]";
    TestResult test_result(title.str());
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result |= 1;
    } else {
        // Create a Python Dict
        for (size_t i = 0; i < size; ++i) {
            py_k = (*Convert_K)(static_cast<K>(i));
            if (!py_k) {
                // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                PyErr_Format(PyExc_ValueError, "C++ key of can not be converted.");
                result |= 1 << 1;
                break;
            }
            // Refcount may well be >> 1 for interned objects.
            Py_ssize_t py_k_ob_refcnt = py_k->ob_refcnt;
            py_v = (*Convert_V)(static_cast<V>(i));
            if (!py_v) {
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
        }
        if (result == 0) {
            std::unordered_map<K, V> cpp_map;
            for (size_t i = 0; i < repeat; ++i) {
                ExecClock exec_clock;
                result = Python_Cpp_Containers::py_dict_to_cpp_std_unordered_map(op, cpp_map);
                exec_time = exec_clock.seconds();
//                std::cout << "TRACE" << " Size: " << cpp_map.size()  << " Type" << type << " t=" << exec_time << std::endl;
                if (result) {
                    test_result.execTimeAdd(1, exec_time, 1, size);
                    break;
                } else {
                    test_result.execTimeAdd(0, exec_time, 1, size);
                }
            }
            test_results.push_back(test_result);
        }
        Py_DECREF(op);
    }
    return result;
}

template<
        typename K,
        typename V,
        PyObject *(*Convert_K)(const K &),
        PyObject *(*Convert_V)(const V &)
>
int
test_perf_py_dict_to_cpp_std_unordered_map_multiple(TestResultS &test_results, const std::string &type, size_t repeat) {
    int result = 0;
    for (size_t size = MIN_SIZE_OF_CONTAINER;
         size < LIMIT_SIZE_OF_CONTAINER_DICT; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
        result |= test_py_dict_to_cpp_std_unordered_map_multiple<K, V, Convert_K, Convert_V>(test_results, type, size,
                                                                                             repeat);
    }
    return result;
}

int test_cpp_std_unordered_map_to_py_dict_string_multiple(TestResultS &test_results, size_t size, size_t str_len, size_t repeat) {
    int result = 0;
    std::unordered_map<std::string, std::string> cpp_map;
    for (size_t i = 0; i < size; ++i) {
        cpp_map[unique_string(str_len)] = std::string(str_len, ' ');
    }
    std::ostringstream title;
    title << __FUNCTION__ << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
    TestResult test_result(title.str());
    for (size_t i = 0; i < repeat; ++i) {
        ExecClock exec_clock;
        PyObject *op = Python_Cpp_Containers::cpp_std_unordered_map_to_py_dict(cpp_map);
        double exec_time = exec_clock.seconds();
        if (op) {
            Py_DECREF(op);
        } else {
            result = 1;
        }
        test_result.execTimeAdd(result, exec_time, 1, size);
    }
    test_results.push_back(test_result);
    return result;
}

int test_perf_cpp_std_unordered_map_to_py_dict_string_multiple(TestResultS &test_results, size_t repeat) {
    int result = 0;
    for (size_t str_len = MIN_STRING_LENGTH; str_len < LIMIT_STRING_LENGTH; str_len *= INC_STRING_LENGTH_MULTIPLE) {
        for (size_t size = MIN_SIZE_OF_CONTAINER;
             size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
            result |= test_cpp_std_unordered_map_to_py_dict_string_multiple(test_results, size, str_len, repeat);
        }
    }
    return result;
}

int test_py_dict_to_cpp_std_unordered_map_string_multiple(TestResultS &test_results, size_t size, size_t str_len, size_t repeat) {
    int result = 0;
    std::ostringstream title;
    title << __FUNCTION__  << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
    TestResult test_result(title.str());
    PyObject *op = new_py_dict_bytes(size, str_len);
    for (size_t i = 0; i < repeat; ++i) {
        std::unordered_map<std::string, std::string> cpp_map;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_dict_to_cpp_std_unordered_map(op, cpp_map);
        double exec_time = exec_clock.seconds();
        if (err) {
            result = -1;
            break;
        }
        test_result.execTimeAdd(0, exec_time, 1, size);
    }
    Py_DECREF(op);
    test_results.push_back(test_result);
    return result;
}

int test_perf_py_dict_to_cpp_std_unordered_map_string_multiple(TestResultS &test_results, size_t repeat) {
    int result = 0;
    for (size_t str_len = MIN_STRING_LENGTH; str_len < LIMIT_STRING_LENGTH; str_len *= INC_STRING_LENGTH_MULTIPLE) {
        for (size_t size = MIN_SIZE_OF_CONTAINER;
             size < LIMIT_SIZE_OF_CONTAINER; size *= INC_SIZE_OF_CONTAINER_MULTIPLE) {
            result |= test_py_dict_to_cpp_std_unordered_map_string_multiple(test_results, size, str_len, repeat);
        }
    }
    return result;
}

#define TEST_PERFORMANCE_FUNDAMENTAL_TYPES
//#define TEST_PERFORMANCE_TUPLES
//#define TEST_PERFORMANCE_LISTS
//#define TEST_PERFORMANCE_SETS
//#define TEST_PERFORMANCE_DICTS

void test_performance_all(TestResultS &test_results) {
    RSSSnapshot rss_overall("==== test_performance.cpp");
#ifdef TEST_PERFORMANCE_FUNDAMENTAL_TYPES
    // Fundamental type tests
    {
        size_t fundamental_types_test_size = 1000 * 1000;
        size_t fundamental_types_test_repeat = TEST_REPEAT * 4;
        test_long_to_py_int_multiple(test_results, fundamental_types_test_size, fundamental_types_test_repeat);
        test_py_int_to_cpp_long_multiple(test_results, fundamental_types_test_size, fundamental_types_test_repeat);
        test_double_to_py_float_multiple(test_results, fundamental_types_test_size, fundamental_types_test_repeat);
        test_py_float_to_cpp_double_multiple(test_results, fundamental_types_test_size, fundamental_types_test_repeat);
        test_cpp_string_to_py_bytes_multiple(test_results, 2, fundamental_types_test_size,
                                             fundamental_types_test_repeat);
        test_cpp_string_to_py_bytes_multiple(test_results, 16, fundamental_types_test_size,
                                             fundamental_types_test_repeat);
        test_cpp_string_to_py_bytes_multiple(test_results, 128, fundamental_types_test_size,
                                             fundamental_types_test_repeat);
        test_cpp_string_to_py_bytes_multiple(test_results, 1024, fundamental_types_test_size,
                                             fundamental_types_test_repeat);
        test_cpp_string_to_py_bytes_multiple(test_results, 1024 * 8, fundamental_types_test_size,
                                             fundamental_types_test_repeat);
        test_cpp_string_to_py_bytes_multiple(test_results, 1024 * 8 * 8, fundamental_types_test_size,
                                             fundamental_types_test_repeat);
        test_py_bytes_to_cpp_string_multiple(test_results, 2, fundamental_types_test_size,
                                             fundamental_types_test_repeat);
        test_py_bytes_to_cpp_string_multiple(test_results, 16, fundamental_types_test_size,
                                             fundamental_types_test_repeat);
        test_py_bytes_to_cpp_string_multiple(test_results, 128, fundamental_types_test_size,
                                             fundamental_types_test_repeat);
        test_py_bytes_to_cpp_string_multiple(test_results, 1024, fundamental_types_test_size,
                                             fundamental_types_test_repeat);
        test_py_bytes_to_cpp_string_multiple(test_results, 1024 * 8, fundamental_types_test_size,
                                             fundamental_types_test_repeat);
        test_py_bytes_to_cpp_string_multiple(test_results, 1024 * 8 * 8, fundamental_types_test_size,
                                             fundamental_types_test_repeat);
    }
#endif
#ifdef TEST_PERFORMANCE_TUPLES
    // Tuple tests
    // Tuple fundamental types C++ -> Python
    {
        RSSSnapshot rss("test_perf_vector_to_py_tuple_multiple<bool>");
        test_perf_vector_to_py_tuple_multiple<bool>(test_results, "<bool>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_vector_to_py_tuple_multiple<long>");
        test_perf_vector_to_py_tuple_multiple<long>(test_results, "<long>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_vector_to_py_tuple_multiple<double>");
        test_perf_vector_to_py_tuple_multiple<double>(test_results, "<double>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    // Tuple fundamental types Python -> C++
    {
        RSSSnapshot rss("test_perf_py_tuple_to_vector_multiple<bool>");
        test_perf_py_tuple_to_vector_multiple<
                bool,
                &Python_Cpp_Containers::cpp_bool_to_py_bool
        >(test_results,"<bool>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_tuple_to_vector_multiple<long>");
        test_perf_py_tuple_to_vector_multiple<
                long,
                &Python_Cpp_Containers::cpp_long_to_py_long
        >(test_results,"<long>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_tuple_to_vector_multiple<double>");
        test_perf_py_tuple_to_vector_multiple<
                double,
                &Python_Cpp_Containers::cpp_double_to_py_float
        >(test_results,"<double>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    // Test list of strings Python <-> C++
    {
        RSSSnapshot rss("test_perf_vector_string_to_py_tuple_multiple");
        test_perf_vector_string_to_py_tuple_multiple(test_results, TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_tuple_to_vector_string_multiple");
        test_perf_py_tuple_to_vector_string_multiple(test_results, TEST_REPEAT);
        std::cout << rss << std::endl;
    }
#endif
#ifdef TEST_PERFORMANCE_LISTS
    // Test lists
    // List fundamental types C++ -> Python
    {
        RSSSnapshot rss("test_perf_vector_to_py_list_multiple<bool>");
        test_perf_vector_to_py_list_multiple<bool>(test_results, "<bool>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_vector_to_py_list_multiple<long>");
        test_perf_vector_to_py_list_multiple<long>(test_results, "<long>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_vector_to_py_list_multiple<double>");
        test_perf_vector_to_py_list_multiple<double>(test_results, "<double>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    // List fundamental types Python -> C++
    {
        RSSSnapshot rss("test_perf_py_list_to_vector_multiple<bool>");
        test_perf_py_list_to_vector_multiple<
                bool,
                &Python_Cpp_Containers::cpp_bool_to_py_bool
        >(test_results,"<bool>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_list_to_vector_multiple<long>");
        test_perf_py_list_to_vector_multiple<
                long,
                &Python_Cpp_Containers::cpp_long_to_py_long
        >(test_results,"<long>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_list_to_vector_multiple<double>");
        test_perf_py_list_to_vector_multiple<
                double,
                &Python_Cpp_Containers::cpp_double_to_py_float
        >(test_results,"<double>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    // Test list of strings Python <-> C++
    {
        RSSSnapshot rss("test_perf_vector_string_to_py_list_multiple");
        test_perf_vector_string_to_py_list_multiple(test_results, TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_list_to_vector_string_multiple");
        test_perf_py_list_to_vector_string_multiple(test_results, TEST_REPEAT);
        std::cout << rss << std::endl;
    }
#endif
#ifdef TEST_PERFORMANCE_SETS
    // Test sets.
    // Set fundamental types C++ to Python
    {
        RSSSnapshot rss("test_perf_unordered_set_to_py_set_multiple<long>");
        test_perf_unordered_set_to_py_set_multiple<long>(test_results, "<long>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_unordered_set_to_py_set_multiple<double>");
        test_perf_unordered_set_to_py_set_multiple<double>(test_results, "<double>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    // Set fundamental types Python to C++
    {
        RSSSnapshot rss("test_perf_py_set_to_unordered_set_multiple<long>");
        test_perf_py_set_to_unordered_set_multiple<long, &Python_Cpp_Containers::cpp_long_to_py_long>(test_results,
                                                                                                      "<long>",
                                                                                                      TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_set_to_unordered_set_multiple<double>");
        test_perf_py_set_to_unordered_set_multiple<double, &Python_Cpp_Containers::cpp_double_to_py_float>(test_results,
                                                                                                           "<double>",
                                                                                                           TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    // Test set of strings Python <-> C++
    {
        RSSSnapshot rss("test_perf_unordered_set_string_to_py_set_multiple");
        test_perf_unordered_set_string_to_py_set_multiple(test_results, TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_set_bytes_to_unordered_set_string_multiple");
        test_perf_py_set_bytes_to_unordered_set_string_multiple(test_results, TEST_REPEAT);
        std::cout << rss << std::endl;
    }
#endif
#ifdef TEST_PERFORMANCE_DICTS
    // Test dicts.
    {
        RSSSnapshot rss("test_perf_cpp_std_unordered_map_to_py_dict_multiple<long,long>");
        test_perf_cpp_std_unordered_map_to_py_dict_multiple<long, long>(test_results, "<long,long>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_cpp_std_unordered_map_to_py_dict_multiple<double,double>");
        test_perf_cpp_std_unordered_map_to_py_dict_multiple<double, double>(test_results, "<double,double>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_dict_to_cpp_std_unordered_map_multiple<long,long>");
        test_perf_py_dict_to_cpp_std_unordered_map_multiple<
                long,
                long,
                &Python_Cpp_Containers::cpp_long_to_py_long,
                &Python_Cpp_Containers::cpp_long_to_py_long
        >(test_results, "<long,long>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_dict_to_cpp_std_unordered_map_multiple<double,double>");
        test_perf_py_dict_to_cpp_std_unordered_map_multiple<
                double,
                double,
                &Python_Cpp_Containers::cpp_double_to_py_float,
                &Python_Cpp_Containers::cpp_double_to_py_float
        >(test_results, "<double,double>", TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_cpp_std_unordered_map_to_py_dict_string_multiple");
        test_perf_cpp_std_unordered_map_to_py_dict_string_multiple(test_results, TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_perf_py_dict_to_cpp_std_unordered_map_string_multiple");
        test_perf_py_dict_to_cpp_std_unordered_map_string_multiple(test_results, TEST_REPEAT);
        std::cout << rss << std::endl;
    }
    std::cout << "==== " << rss_overall << std::endl;
#endif
}
