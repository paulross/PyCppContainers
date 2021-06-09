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
    PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (! op) {
        result |= 1;
    } else {
        assert(op->ob_refcnt ==  1);
        if (! Python_Cpp_Containers::py_tuple_check(op)) {
            result |= 1 << 1;
        } else {
            if ((unsigned long) Python_Cpp_Containers::py_tuple_len(op) != cpp_vector.size()) {
                result |= 1 << 2;
            } else {
                for (size_t i = 0; i < size; ++i) {
                    std::string value = Python_Cpp_Containers::py_bytes_as_string(
                            Python_Cpp_Containers::py_tuple_get(op, i)
                            );
                    if (value != cpp_vector[i]) {
                        result |= 1 << 2;
                    }
                }
            }
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
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

int test_py_tuple_string_to_vector(TestResultS &test_results, size_t size, size_t str_len) {
    PyObject *op = Python_Cpp_Containers::py_tuple_new(size);
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result |= 1;
    } else {
        for (size_t i = 0; i < size; ++i) {
//            std::string str = unique_string(str_len);
            std::string str(str_len, ' ');
            int err = Python_Cpp_Containers::py_tuple_set(
                    op, i, Python_Cpp_Containers::py_bytes_from_string(str)
                    );
            if (err != 0) {
                result |= 1 << 1;
            }
        }
        if (result == 0) {
            std::vector<std::string> cpp_vector;
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
                        std::string value = Python_Cpp_Containers::py_bytes_as_string(
                                Python_Cpp_Containers::py_tuple_get(op, i));
                        if (value != cpp_vector[i]) {
                            result |= 1 << 4;
                        }
                    }
                }
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    return result;
}

int test_cpp_std_unordered_map_to_py_dict_string(TestResultS &test_results, size_t size, size_t str_len) {
    std::unordered_map<std::string, std::string> cpp_map;
    for (size_t i = 0; i < size; ++i) {
        cpp_map[unique_string(str_len)] = std::string(str_len, ' ');
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_unordered_map_to_py_dict(cpp_map);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (! op) {
        result |= 1;
    } else {
        assert(op->ob_refcnt ==  1);
        if (! PyDict_Check(op)) {
            result |= 1 << 1;
        } else {
            if (static_cast<unsigned long>(PyDict_Size(op)) != cpp_map.size()) {
                result |= 1 << 2;
            } else {
                // Now check the Python dict against the C++ map.
                PyObject *py_key, *py_val;
                Py_ssize_t pos = 0;
                while (PyDict_Next(op, &pos, &py_key, &py_val)) {
                    std::string cp_key = Python_Cpp_Containers::py_bytes_as_string(py_key);
                    std::string cp_val = Python_Cpp_Containers::py_bytes_as_string(py_val);
                    if (cpp_map.find(cp_key) == cpp_map.end()) {
                        result |= 1 << 3;
                    } else {
                        if (cpp_map[cp_key] != cp_val) {
                            result |= 1 << 4;
                        }
                    }
                }
            }
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    return result;
}

//int test_py_dict_to_cpp_std_unordered_map_string(TestResultS &test_results, size_t size, size_t str_len) {
//    PyObject *op = Python_Cpp_Containers::py_tuple_new(size);
//    int result = 0;
//    double exec_time = -1.0;
//    if (! op) {
//        result |= 1;
//    } else {
//        for (size_t i = 0; i < size; ++i) {
////            std::string str = unique_string(str_len);
//            std::string str(str_len, ' ');
//            int err = Python_Cpp_Containers::py_tuple_set(
//                    op, i, Python_Cpp_Containers::py_bytes_from_string(str)
//                    );
//            if (err != 0) {
//                result |= 1 << 1;
//            }
//        }
//        if (result == 0) {
//            std::vector<std::string> cpp_vector;
//            ExecClock exec_clock;
//            int err = Python_Cpp_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
//            exec_time = exec_clock.seconds();
//            if (err != 0) {
//                result |= 1 << 2;
//            } else {
//                if ((unsigned long) Python_Cpp_Containers::py_tuple_len(op) != cpp_vector.size()) {
//                    result |= 1 << 3;
//                } else {
//                    for (size_t i = 0; i < size; ++i) {
//                        std::string value = Python_Cpp_Containers::py_bytes_as_string(
//                                Python_Cpp_Containers::py_tuple_get(op, i));
//                        if (value != cpp_vector[i]) {
//                            result |= 1 << 4;
//                        }
//                    }
//                }
//            }
//        }
//        Py_DECREF(op);
//    }
//    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
//    return result;
//}

