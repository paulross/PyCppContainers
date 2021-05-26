//
// Created by Paul Ross on 23/05/2021.
//
#include "test_common.h"

int test_vector_string_to_py_tuple(TestResultS &test_results, size_t size, size_t str_len) {
    std::vector<std::string> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
//        cpp_vector.push_back(unique_string(str_len));
        cpp_vector.push_back(std::string(str_len, ' '));
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
                    std::string value = Python_Cpp_Homogeneous_Containers::py_bytes_as_string(
                            Python_Cpp_Homogeneous_Containers::py_tuple_get(op, i)
                            );
                    if (value != cpp_vector[i]) {
                        result |= 1 << 2;
                    }
                }
            }
        }
        Py_DECREF(op);
    }
    std::ostringstream title;
    title << __FUNCTION__  << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
    if (result) {
        std::cout << "    FAIL: " << title.str() << " " << result << std::endl;
        PyErr_Print();
        PyErr_Clear();
    } else {
        std::cout << "      OK: " << title.str() << " " << result << std::endl;
    }
    test_results.push_back(TestResult(title.str(), result, exec_time, 1, size));
    return result;
}

int test_py_tuple_string_to_vector(TestResultS &test_results, size_t size, size_t str_len) {
    PyObject *op = Python_Cpp_Homogeneous_Containers::py_tuple_new(size);
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
//            std::string str = unique_string(str_len);
            std::string str(str_len, ' ');
            int err = Python_Cpp_Homogeneous_Containers::py_tuple_set(
                    op, i, Python_Cpp_Homogeneous_Containers::py_bytes_from_string(str)
                    );
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::vector<std::string> cpp_vector;
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
                        std::string value = Python_Cpp_Homogeneous_Containers::py_bytes_as_string(
                                Python_Cpp_Homogeneous_Containers::py_tuple_get(op, i));
                        if (value != cpp_vector[i]) {
                            result |= 1 << 4;
                        }
                    }
                }
            }
        }
        Py_DECREF(op);
    }
    std::ostringstream title;
    title << __FUNCTION__  << "<std::string[" << str_len << "]>" << "():" << "[" << size << "]";
    if (result) {
        std::cout << "    FAIL: " << title.str() << " " << result << std::endl;
        PyErr_Print();
        PyErr_Clear();
    } else {
        std::cout << "      OK: " << title.str() << " " << result << std::endl;
    }
    test_results.push_back(TestResult(title.str(), result, exec_time, 1, size));
    return result;
}

