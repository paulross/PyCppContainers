//
// Created by Paul Ross on 23/05/2021.
//
#include "test_common.h"

#pragma mark Comparison template specialisations.

template <>
int
compare_tuple<bool>(const std::vector<bool> &cpp_vector, PyObject *op) {
    return compare_tuple<
            bool,
            &Python_Cpp_Containers::cpp_bool_to_py_bool,
            &Python_Cpp_Containers::py_bool_to_cpp_bool>(cpp_vector, op);
}

template <>
int
compare_tuple<long>(const std::vector<long> &cpp_vector, PyObject *op) {
    return compare_tuple<
            long,
            &Python_Cpp_Containers::cpp_long_to_py_long,
            &Python_Cpp_Containers::py_long_to_cpp_long>(cpp_vector, op);
}

template <>
int
compare_tuple<double>(const std::vector<double> &cpp_vector, PyObject *op) {
    return compare_tuple<
            double,
            &Python_Cpp_Containers::cpp_double_to_py_float,
            &Python_Cpp_Containers::py_float_to_cpp_double>(cpp_vector, op);
}

template <>
int
compare_tuple<std::vector<char>>(const std::vector<std::vector<char>> &cpp_vector, PyObject *op) {
    return compare_tuple<
            std::vector<char>,
            &Python_Cpp_Containers::cpp_vector_char_to_py_bytes,
            &Python_Cpp_Containers::py_bytes_to_cpp_vector_char>(cpp_vector, op);
}

template <>
int
compare_list<bool>(const std::vector<bool> &cpp_vector, PyObject *op) {
    return compare_list<
            bool,
            &Python_Cpp_Containers::cpp_bool_to_py_bool,
            &Python_Cpp_Containers::py_bool_to_cpp_bool>(cpp_vector, op);
}

template <>
int
compare_list<long>(const std::vector<long> &cpp_vector, PyObject *op) {
    return compare_list<
            long,
            &Python_Cpp_Containers::cpp_long_to_py_long,
            &Python_Cpp_Containers::py_long_to_cpp_long>(cpp_vector, op);
}

template <>
int
compare_list<double>(const std::vector<double> &cpp_vector, PyObject *op) {
    return compare_list<
            double,
            &Python_Cpp_Containers::cpp_double_to_py_float,
            &Python_Cpp_Containers::py_float_to_cpp_double>(cpp_vector, op);
}

template <>
int
compare_list<std::vector<char>>(const std::vector<std::vector<char>> &cpp_vector, PyObject *op) {
    return compare_list<
            std::vector<char>,
            &Python_Cpp_Containers::cpp_vector_char_to_py_bytes,
            &Python_Cpp_Containers::py_bytes_to_cpp_vector_char
            >(cpp_vector, op);
}

template <>
int
compare_set<std::vector<char>>(const std::unordered_set<std::vector<char>> &cpp_set, PyObject *op) {
    return compare_set<
            std::vector<char>,
            &Python_Cpp_Containers::cpp_vector_char_to_py_bytes,
            &Python_Cpp_Containers::py_bytes_to_cpp_vector_char>(cpp_set, op);
}

template <>
int
compare_dict<
        std::vector<char>, std::vector<char>
>(const std::unordered_map<std::vector<char>, std::vector<char>> &cpp_map, PyObject *op) {
    return compare_dict<
            std::vector<char>,
            std::vector<char>,
            &Python_Cpp_Containers::cpp_vector_char_to_py_bytes,
            &Python_Cpp_Containers::cpp_vector_char_to_py_bytes,
            &Python_Cpp_Containers::py_bytes_to_cpp_vector_char,
            &Python_Cpp_Containers::py_bytes_to_cpp_vector_char
            >(cpp_map, op);
}

int test_vector_vector_char_to_py_tuple(TestResultS &test_results, size_t size, size_t str_len) {
    std::vector<std::vector<char>> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
//        cpp_vector.push_back(unique_vector_char(str_len));
        cpp_vector.push_back(std::vector<char>(str_len, ' '));
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (! op) {
        result |= 1;
    } else {
        assert(op->ob_refcnt ==  1);
        if (compare_tuple(cpp_vector, op)) {
            result = 2;
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    return result;
}

int test_py_tuple_bytes_to_vector(TestResultS &test_results, size_t size, size_t str_len) {
    PyObject *op = new_py_tuple_bytes(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result = 1;
    } else {
        std::vector<std::vector<char>> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
        exec_time = exec_clock.seconds();
        if (err != 0) {
            result = 2;
        } else {
            if (compare_tuple(cpp_vector, op)) {
                result = 3;
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    return result;
}

int test_vector_vector_char_to_py_list(TestResultS &test_results, size_t size, size_t str_len) {
    std::vector<std::vector<char>> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
//        cpp_vector.push_back(unique_vector_char(str_len));
        cpp_vector.push_back(std::vector<char>(str_len, ' '));
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_list(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (! op) {
        result |= 1;
    } else {
        assert(op->ob_refcnt ==  1);
        if (compare_list(cpp_vector, op)) {
            result = 2;
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    return result;
}

int test_py_list_bytes_to_vector(TestResultS &test_results, size_t size, size_t str_len) {
    PyObject *op = new_py_list_bytes(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result = 1;
    } else {
        std::vector<std::vector<char>> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_list_to_cpp_std_vector(op, cpp_vector);
        exec_time = exec_clock.seconds();
        if (err != 0) {
            result = 2;
        } else {
            if (compare_list(cpp_vector, op)) {
                result = 3;
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    return result;
}

int test_unordered_set_bytes_to_py_set(TestResultS &test_results, size_t size, size_t str_len) {
    std::unordered_set<std::vector<char>> cpp_set;
    for (size_t i = 0; i < size; ++i) {
        cpp_set.insert(unique_vector_char(str_len));
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_unordered_set_to_py_set(cpp_set);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (!op) {
        result = 1;
    } else {
        assert(op->ob_refcnt == 1);
        if (!Python_Cpp_Containers::py_set_check(op)) {
            result = 2;
        } else {
            if (compare_set(cpp_set, op)) {
                result = 3;
            }
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    return result;
}

int test_py_set_bytes_to_unordered_set(TestResultS &test_results, size_t size, size_t str_len) {
    std::unordered_set<std::vector<char>> cpp_set;
    int result = 0;
    std::string type = "<bytes>";
    PyObject *py_set = new_py_set_bytes(size, str_len);
    ExecClock exec_clock;
    int err = Python_Cpp_Containers::py_set_to_cpp_std_unordered_set(py_set, cpp_set);
    double exec_time = exec_clock.seconds();
    if (err) {
        result = 1;
    } else {
        if (compare_set(cpp_set, py_set)) {
            result = 2;
        }
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    return result;
}


// Create a new tuple of bytes
PyObject *
new_py_tuple_bytes(size_t size, size_t str_len) {
    PyObject *op = Python_Cpp_Containers::py_tuple_new(size);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::vector<char> str(str_len, ' ');
            int err = Python_Cpp_Containers::py_tuple_set(op, i, Python_Cpp_Containers::cpp_vector_char_to_py_bytes(str));
            if (err) {
                Py_DECREF(op);
                op = NULL;
            }
        }
    }
    return op;
}

// Create a new list of bytes
PyObject *
new_py_list_bytes(size_t size, size_t str_len) {
    PyObject *op = Python_Cpp_Containers::py_list_new(size);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::vector<char> str(str_len, ' ');
            int err = Python_Cpp_Containers::py_list_set(op, i, Python_Cpp_Containers::cpp_vector_char_to_py_bytes(str));
            if (err) {
                Py_DECREF(op);
                op = NULL;
            }
        }
    }
    return op;
}


// Create a new set of bytes
PyObject *
new_py_set_bytes(size_t size, size_t str_len) {
    PyObject *op = Python_Cpp_Containers::py_set_new(NULL);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::vector<char> str = unique_vector_char(str_len);
            int err = Python_Cpp_Containers::py_set_add(op, Python_Cpp_Containers::cpp_vector_char_to_py_bytes(str));
            if (err) {
                Py_DECREF(op);
                op = NULL;
            }
        }
    }
    return op;
}


// Create a new dict of unique bytes
PyObject *
new_py_dict_bytes(size_t size, size_t str_len) {
    PyObject *op = PyDict_New();
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::vector<char> key = unique_vector_char(str_len);
            PyObject *py_key = Python_Cpp_Containers::cpp_vector_char_to_py_bytes(key);
            std::vector<char> val = unique_vector_char(str_len);
            PyObject *py_val = Python_Cpp_Containers::cpp_vector_char_to_py_bytes(val);
            if (PyDict_SetItem(op, py_key, py_val)) {
                PyErr_Format(PyExc_ValueError, "Can not set an item in the Python dict.");
                Py_DECREF(op);
                Py_DECREF(py_key);
                Py_DECREF(py_val);
                op = NULL;
                return op;
            }
            // WARN: PyDict_SetItem increments key and value refcounts.
            Py_DECREF(py_key);
            Py_DECREF(py_val);
        }
    }
    return op;
}

int test_cpp_std_unordered_map_to_py_dict_bytes(TestResultS &test_results, size_t size, size_t str_len) {
    std::unordered_map<std::vector<char>, std::vector<char>> cpp_map;
    for (size_t i = 0; i < size; ++i) {
        cpp_map[unique_vector_char(str_len)] = std::vector<char>(str_len, ' ');
    }
    ExecClock exec_clock;
    PyObject *op = Python_Cpp_Containers::cpp_std_unordered_map_to_py_dict(cpp_map);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (! op) {
        result = 1;
    } else {
        assert(op->ob_refcnt ==  1);
        if (! PyDict_Check(op)) {
            result = 2;
        } else {
            if(compare_dict(cpp_map, op)) {
                result = 3;
            }
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    return result;
}

int test_py_dict_to_cpp_std_unordered_map_bytes(TestResultS &test_results, size_t size, size_t str_len) {
    PyObject *op = new_py_dict_bytes(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (! op) {
        result = 1;
    } else {
        std::unordered_map<std::vector<char>, std::vector<char>> cpp_map;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_dict_to_cpp_std_unordered_map(op, cpp_map);
        exec_time = exec_clock.seconds();
        if (err != 0) {
            result = 2;
        } else {
            // Compare dict
            if(compare_dict(cpp_map, op)) {
                result = 3;
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    return result;
}
