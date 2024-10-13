//
// Created by Paul Ross on 23/05/2021.
//
#include "test_common.h"

#pragma mark Comparison template specialisations.

// Specific instantiations of templates.
template<>
int
compare_tuple<bool>(const std::vector<bool> &cpp_vector, PyObject *op) {
    return compare_tuple<
            bool,
            &Python_Cpp_Containers::cpp_bool_to_py_bool,
            &Python_Cpp_Containers::py_bool_to_cpp_bool>(cpp_vector, op);
}

template<>
int
compare_tuple<long>(const std::vector<long> &cpp_vector, PyObject *op) {
    return compare_tuple<
            long,
            &Python_Cpp_Containers::cpp_long_to_py_long,
            &Python_Cpp_Containers::py_long_to_cpp_long>(cpp_vector, op);
}

template<>
int
compare_tuple<double>(const std::vector<double> &cpp_vector, PyObject *op) {
    return compare_tuple<
            double,
            &Python_Cpp_Containers::cpp_double_to_py_float,
            &Python_Cpp_Containers::py_float_to_cpp_double>(cpp_vector, op);
}

template<>
int
compare_tuple<std::complex<double>>(const std::vector<std::complex<double>> &cpp_vector, PyObject *op) {
    return compare_tuple<
            std::complex<double>,
            &Python_Cpp_Containers::cpp_complex_to_py_complex,
            &Python_Cpp_Containers::py_complex_to_cpp_complex>(cpp_vector, op);
}

template<>
int
compare_tuple<std::vector<char>>(const std::vector<std::vector<char>> &cpp_vector, PyObject *op) {
    return compare_tuple<
            std::vector<char>,
            &Python_Cpp_Containers::cpp_vector_char_to_py_bytes,
            &Python_Cpp_Containers::py_bytes_to_cpp_vector_char>(cpp_vector, op);
}

template<>
int
compare_tuple<std::string>(const std::vector<std::string> &cpp_vector, PyObject *op) {
    return compare_tuple<
            std::string,
            &Python_Cpp_Containers::cpp_string_to_py_unicode8,
            &Python_Cpp_Containers::py_unicode8_to_cpp_string>(cpp_vector, op);
}

template<>
int
compare_tuple<std::u16string>(const std::vector<std::u16string> &cpp_vector, PyObject *op) {
    return compare_tuple<
            std::u16string,
            &Python_Cpp_Containers::cpp_u16string_to_py_unicode16,
            &Python_Cpp_Containers::py_unicode16_to_cpp_u16string>(cpp_vector, op);
}

template<>
int
compare_tuple<std::u32string>(const std::vector<std::u32string> &cpp_vector, PyObject *op) {
    return compare_tuple<
            std::u32string,
            &Python_Cpp_Containers::cpp_u32string_to_py_unicode32,
            &Python_Cpp_Containers::py_unicode32_to_cpp_u32string>(cpp_vector, op);
}

template<>
int
compare_list<bool>(const std::vector<bool> &cpp_vector, PyObject *op) {
    return compare_list<
            bool,
            &Python_Cpp_Containers::cpp_bool_to_py_bool,
            &Python_Cpp_Containers::py_bool_to_cpp_bool>(cpp_vector, op);
}

template<>
int
compare_list<long>(const std::vector<long> &cpp_vector, PyObject *op) {
    return compare_list<
            long,
            &Python_Cpp_Containers::cpp_long_to_py_long,
            &Python_Cpp_Containers::py_long_to_cpp_long>(cpp_vector, op);
}

template<>
int
compare_list<double>(const std::vector<double> &cpp_vector, PyObject *op) {
    return compare_list<
            double,
            &Python_Cpp_Containers::cpp_double_to_py_float,
            &Python_Cpp_Containers::py_float_to_cpp_double>(cpp_vector, op);
}

template<>
int
compare_list<std::complex<double>>(const std::vector<std::complex<double>> &cpp_vector, PyObject *op) {
    return compare_list<
            std::complex<double>,
            &Python_Cpp_Containers::cpp_complex_to_py_complex,
            &Python_Cpp_Containers::py_complex_to_cpp_complex>(cpp_vector, op);
}

template<>
int
compare_list<std::vector<char>>(const std::vector<std::vector<char>> &cpp_vector, PyObject *op) {
    return compare_list<
            std::vector<char>,
            &Python_Cpp_Containers::cpp_vector_char_to_py_bytes,
            &Python_Cpp_Containers::py_bytes_to_cpp_vector_char
    >(cpp_vector, op);
}

template<>
int
compare_list<std::string>(const std::vector<std::string> &cpp_vector, PyObject *op) {
    return compare_list<
            std::string,
            &Python_Cpp_Containers::cpp_string_to_py_unicode8,
            &Python_Cpp_Containers::py_unicode8_to_cpp_string>(cpp_vector, op);
}

template<>
int
compare_list<std::u16string>(const std::vector<std::u16string> &cpp_vector, PyObject *op) {
    return compare_list<
            std::u16string,
            &Python_Cpp_Containers::cpp_u16string_to_py_unicode16,
            &Python_Cpp_Containers::py_unicode16_to_cpp_u16string>(cpp_vector, op);
}

template<>
int
compare_list<std::u32string>(const std::vector<std::u32string> &cpp_vector, PyObject *op) {
    return compare_list<
            std::u32string,
            &Python_Cpp_Containers::cpp_u32string_to_py_unicode32,
            &Python_Cpp_Containers::py_unicode32_to_cpp_u32string>(cpp_vector, op);
}

template<>
int
compare_set<std::vector<char>>(const std::unordered_set<std::vector<char>> &cpp_set, PyObject *op) {
    return compare_set<
            std::vector<char>,
            &Python_Cpp_Containers::cpp_vector_char_to_py_bytes,
            &Python_Cpp_Containers::py_bytes_to_cpp_vector_char>(cpp_set, op);
}

template<>
int
compare_set<std::string>(const std::unordered_set<std::string> &cpp_set, PyObject *op) {
    return compare_set<
            std::string,
            &Python_Cpp_Containers::cpp_string_to_py_unicode8,
            &Python_Cpp_Containers::py_unicode8_to_cpp_string>(cpp_set, op);
}

template<>
int
compare_set<std::u16string>(const std::unordered_set<std::u16string> &cpp_set, PyObject *op) {
    return compare_set<
            std::u16string,
            &Python_Cpp_Containers::cpp_u16string_to_py_unicode16,
            &Python_Cpp_Containers::py_unicode16_to_cpp_u16string>(cpp_set, op);
}

template<>
int
compare_set<std::u32string>(const std::unordered_set<std::u32string> &cpp_set, PyObject *op) {
    return compare_set<
            std::u32string,
            &Python_Cpp_Containers::cpp_u32string_to_py_unicode32,
            &Python_Cpp_Containers::py_unicode32_to_cpp_u32string>(cpp_set, op);
}

template<>
int
compare_dict<
        std::unordered_map, std::vector<char>, std::vector<char>
>(const std::unordered_map<std::vector<char>, std::vector<char>> &cpp_map, PyObject *op) {
    return compare_dict<
            std::unordered_map,
            std::vector<char>,
            std::vector<char>,
            &Python_Cpp_Containers::cpp_vector_char_to_py_bytes,
            &Python_Cpp_Containers::cpp_vector_char_to_py_bytes,
            &Python_Cpp_Containers::py_bytes_to_cpp_vector_char,
            &Python_Cpp_Containers::py_bytes_to_cpp_vector_char
    >(cpp_map, op);
}

template<>
int
compare_dict<
        std::unordered_map, std::string, std::string
>(const std::unordered_map<std::string, std::string> &cpp_map, PyObject *op) {
    return compare_dict<
            std::unordered_map,
            std::string,
            std::string,
            &Python_Cpp_Containers::cpp_string_to_py_unicode8,
            &Python_Cpp_Containers::cpp_string_to_py_unicode8,
            &Python_Cpp_Containers::py_unicode8_to_cpp_string,
            &Python_Cpp_Containers::py_unicode8_to_cpp_string
    >(cpp_map, op);
}

template<>
int
compare_dict<
        std::unordered_map, std::u16string, std::u16string
>(const std::unordered_map<std::u16string, std::u16string> &cpp_map, PyObject *op) {
    return compare_dict<
            std::unordered_map,
            std::u16string,
            std::u16string,
            &Python_Cpp_Containers::cpp_u16string_to_py_unicode16,
            &Python_Cpp_Containers::cpp_u16string_to_py_unicode16,
            &Python_Cpp_Containers::py_unicode16_to_cpp_u16string,
            &Python_Cpp_Containers::py_unicode16_to_cpp_u16string
    >(cpp_map, op);
}

template<>
int
compare_dict<
        std::unordered_map, std::u32string, std::u32string
>(const std::unordered_map<std::u32string, std::u32string> &cpp_map, PyObject *op) {
    return compare_dict<
            std::unordered_map,
            std::u32string,
            std::u32string,
            &Python_Cpp_Containers::cpp_u32string_to_py_unicode32,
            &Python_Cpp_Containers::cpp_u32string_to_py_unicode32,
            &Python_Cpp_Containers::py_unicode32_to_cpp_u32string,
            &Python_Cpp_Containers::py_unicode32_to_cpp_u32string
    >(cpp_map, op);
}

template<>
int
compare_dict<
        std::map, std::vector<char>, std::vector<char>
>(const std::map<std::vector<char>, std::vector<char>> &cpp_map, PyObject *op) {
    return compare_dict<
            std::map,
            std::vector<char>,
            std::vector<char>,
            &Python_Cpp_Containers::cpp_vector_char_to_py_bytes,
            &Python_Cpp_Containers::cpp_vector_char_to_py_bytes,
            &Python_Cpp_Containers::py_bytes_to_cpp_vector_char,
            &Python_Cpp_Containers::py_bytes_to_cpp_vector_char
    >(cpp_map, op);
}

template<>
int
compare_dict<
        std::map, std::string, std::string
>(const std::map<std::string, std::string> &cpp_map, PyObject *op) {
    return compare_dict<
            std::map,
            std::string,
            std::string,
            &Python_Cpp_Containers::cpp_string_to_py_unicode8,
            &Python_Cpp_Containers::cpp_string_to_py_unicode8,
            &Python_Cpp_Containers::py_unicode8_to_cpp_string,
            &Python_Cpp_Containers::py_unicode8_to_cpp_string
    >(cpp_map, op);
}

template<>
int
compare_dict<
        std::map, std::u16string, std::u16string
>(const std::map<std::u16string, std::u16string> &cpp_map, PyObject *op) {
    return compare_dict<
            std::map,
            std::u16string,
            std::u16string,
            &Python_Cpp_Containers::cpp_u16string_to_py_unicode16,
            &Python_Cpp_Containers::cpp_u16string_to_py_unicode16,
            &Python_Cpp_Containers::py_unicode16_to_cpp_u16string,
            &Python_Cpp_Containers::py_unicode16_to_cpp_u16string
    >(cpp_map, op);
}

template<>
int
compare_dict<
        std::map, std::u32string, std::u32string
>(const std::map<std::u32string, std::u32string> &cpp_map, PyObject *op) {
    return compare_dict<
            std::map,
            std::u32string,
            std::u32string,
            &Python_Cpp_Containers::cpp_u32string_to_py_unicode32,
            &Python_Cpp_Containers::cpp_u32string_to_py_unicode32,
            &Python_Cpp_Containers::py_unicode32_to_cpp_u32string,
            &Python_Cpp_Containers::py_unicode32_to_cpp_u32string
    >(cpp_map, op);
}

/**
 * Tests converting a C++ \c std::vector<std::vector<char>> to a Python \c tuple.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_vector_vector_char_to_py_tuple(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    std::vector<std::vector<char>> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
//        cpp_vector.push_back(unique_vector_char(str_len));
        cpp_vector.push_back(std::vector<char>(str_len, ' '));
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_list_like_to_py_tuple(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (!op) {
        result |= 1;
    } else {
        assert(op->ob_refcnt == 1);
        if (compare_tuple(cpp_vector, op)) {
            result = 2;
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a Python \c tuple of \c bytes to a C++ \c std::vector<std::vector<char>>.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_py_tuple_bytes_to_vector(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    PyObject * op = new_py_tuple_bytes(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result = 1;
    } else {
        std::vector<std::vector<char>> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_tuple_to_cpp_std_list_like(op, cpp_vector);
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
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a C++ \c std::vector<std::string> to a Python \c tuple.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_vector_string_to_py_tuple(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    assert(!PyErr_Occurred());
    std::vector<std::string> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
//        cpp_vector.push_back(unique_vector_char(str_len));
        cpp_vector.push_back(std::string(str_len, ' '));
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_list_like_to_py_tuple(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (!op) {
        result |= 1;
    } else {
        assert(op->ob_refcnt == 1);
        if (compare_tuple(cpp_vector, op)) {
            result = 2;
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a Python \c tuple of \c str to a C++ \c std::vector<std::string>.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_py_tuple_str_to_vector(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    assert(!PyErr_Occurred());
    PyObject * op = new_py_tuple_string(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result = 1;
    } else {
        std::vector<std::string> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_tuple_to_cpp_std_list_like(op, cpp_vector);
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
    RSS_SNAPSHOT_REPORT;
//    assert(!PyErr_Occurred());
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a C++ \c std::vector<std::string> to a Python \c tuple.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_vector_u16string_to_py_tuple(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    assert(!PyErr_Occurred());
    std::vector<std::u16string> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
//        cpp_vector.push_back(unique_vector_char(str_len));
        cpp_vector.push_back(std::u16string(str_len, ' '));
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_list_like_to_py_tuple(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (!op) {
        result |= 1;
    } else {
        assert(op->ob_refcnt == 1);
        if (compare_tuple(cpp_vector, op)) {
            result = 2;
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a Python \c tuple of \c str to a C++ \c std::vector<std::string>.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_py_tuple_str16_to_vector(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    assert(!PyErr_Occurred());
    PyObject * op = new_py_tuple_string16(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result = 1;
    } else {
        std::vector<std::u16string> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_tuple_to_cpp_std_list_like(op, cpp_vector);
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
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a C++ \c std::vector<std::u32string> to a Python \c tuple.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_vector_u32string_to_py_tuple(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    assert(!PyErr_Occurred());
    std::vector<std::u32string> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
//        cpp_vector.push_back(unique_vector_char(str_len));
        cpp_vector.push_back(std::u32string(str_len, U'1'));
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_list_like_to_py_tuple(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (!op) {
        result |= 1;
    } else {
        assert(op->ob_refcnt == 1);
        if (compare_tuple(cpp_vector, op)) {
            result = 2;
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a Python \c tuple of \c str to a C++ \c std::vector<std::u32string>.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_py_tuple_str32_to_vector(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    assert(!PyErr_Occurred());
    PyObject * op = new_py_tuple_string32(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result = 1;
    } else {
        std::vector<std::u32string> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_tuple_to_cpp_std_list_like(op, cpp_vector);
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
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a C++ \c std::vector<std::vector<char>> to a Python \c list.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_vector_vector_char_to_py_list(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    std::vector<std::vector<char>> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
//        cpp_vector.push_back(unique_vector_char(str_len));
        cpp_vector.push_back(std::vector<char>(str_len, ' '));
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_list_like_to_py_list(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (!op) {
        result |= 1;
    } else {
        assert(op->ob_refcnt == 1);
        if (compare_list(cpp_vector, op)) {
            result = 2;
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a Python \c list to a C++ \c std::vector<std::vector<char>>.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_py_list_bytes_to_vector(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    PyObject * op = new_py_list_bytes(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result = 1;
    } else {
        std::vector<std::vector<char>> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_list_to_cpp_std_list_like(op, cpp_vector);
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
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a C++ \c std::vector<std::string> to a Python \c list.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_vector_string_to_py_list(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    assert(!PyErr_Occurred());
    std::vector<std::string> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
//        cpp_vector.push_back(unique_vector_char(str_len));
        cpp_vector.push_back(std::string(str_len, ' '));
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_list_like_to_py_list(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (!op) {
        result |= 1;
    } else {
        assert(op->ob_refcnt == 1);
        if (compare_list(cpp_vector, op)) {
            result = 2;
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    assert(!PyErr_Occurred());
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a Python \c list to a C++ \c std::vector<std::string>.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_py_list_str_to_vector(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    assert(!PyErr_Occurred());
    PyObject * op = new_py_list_string(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result = 1;
    } else {
        std::vector<std::string> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_list_to_cpp_std_list_like(op, cpp_vector);
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
    RSS_SNAPSHOT_REPORT;
    assert(!PyErr_Occurred());
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a C++ \c std::vector<std::u16string> to a Python \c list.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_vector_u16string_to_py_list(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    assert(!PyErr_Occurred());
    std::vector<std::u16string> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
//        cpp_vector.push_back(unique_vector_char(str_len));
        cpp_vector.push_back(std::u16string(str_len, u' '));
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_list_like_to_py_list(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (!op) {
        result |= 1;
    } else {
        assert(op->ob_refcnt == 1);
        if (compare_list(cpp_vector, op)) {
            result = 2;
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    assert(!PyErr_Occurred());
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a Python \c list to a C++ \c std::vector<std::u16string>.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_py_list_str16_to_vector(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    assert(!PyErr_Occurred());
    PyObject * op = new_py_list_string16(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result = 1;
    } else {
        std::vector<std::u16string> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_list_to_cpp_std_list_like(op, cpp_vector);
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
    RSS_SNAPSHOT_REPORT;
    if (result) {
        assert(PyErr_Occurred());
    } else {
        assert(!PyErr_Occurred());
    }
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a C++ \c std::vector<std::u32string> to a Python \c list.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_vector_u32string_to_py_list(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    assert(!PyErr_Occurred());
    std::vector<std::u32string> cpp_vector;
    for (size_t i = 0; i < size; ++i) {
//        cpp_vector.push_back(unique_vector_char(str_len));
        cpp_vector.push_back(std::u32string(str_len, U' '));
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_list_like_to_py_list(cpp_vector);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (!op) {
        result |= 1;
    } else {
        assert(op->ob_refcnt == 1);
        if (compare_list(cpp_vector, op)) {
            result = 2;
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    assert(!PyErr_Occurred());
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Tests converting a Python \c list to a C++ \c std::vector<std::u32string>.
 *
 * @param test_results The test results to update.
 * @param size Size of the \c std::vector to create.
 * @param str_len Length of each entry in the \c std::vector.
 * @return 0 on success, non-zero on failure.
 */
int test_py_list_str32_to_vector(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    assert(!PyErr_Occurred());
    PyObject * op = new_py_list_string32(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result = 1;
    } else {
        std::vector<std::u32string> cpp_vector;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_list_to_cpp_std_list_like(op, cpp_vector);
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
    RSS_SNAPSHOT_REPORT;
    if (result) {
        assert(PyErr_Occurred());
    } else {
        assert(!PyErr_Occurred());
    }
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_unordered_set_bytes_to_py_set(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    std::unordered_set<std::vector<char>> cpp_set;
    for (size_t i = 0; i < size; ++i) {
        cpp_set.insert(unique_vector_char(str_len));
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_unordered_set_to_py_set(cpp_set);
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
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_py_set_bytes_to_unordered_set(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    std::unordered_set<std::vector<char>> cpp_set;
    int result = 0;
    std::string type = "<bytes>";
    PyObject * py_set = new_py_set_bytes(size, str_len);
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
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_unordered_set_string_to_py_set(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    std::unordered_set<std::string> cpp_set;
    for (size_t i = 0; i < size; ++i) {
        cpp_set.insert(unique_string(str_len));
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_unordered_set_to_py_set(cpp_set);
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
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_py_set_string_to_unordered_set(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    std::unordered_set<std::string> cpp_set;
    int result = 0;
    std::string type = "<bytes>";
    PyObject * py_set = new_py_set_string(size, str_len);
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
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_unordered_set_u16string_to_py_set(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    std::unordered_set<std::u16string> cpp_set;
    for (size_t i = 0; i < size; ++i) {
        cpp_set.insert(unique_u16string(str_len));
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_unordered_set_to_py_set(cpp_set);
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
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_py_set_string16_to_unordered_set(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    std::unordered_set<std::u16string> cpp_set;
    int result = 0;
    std::string type = "<bytes>";
    PyObject * py_set = new_py_set_u16string(size, str_len);
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
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_unordered_set_u32string_to_py_set(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    std::unordered_set<std::u32string> cpp_set;
    for (size_t i = 0; i < size; ++i) {
        cpp_set.insert(unique_u32string(str_len));
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_unordered_set_to_py_set(cpp_set);
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
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_py_set_string32_to_unordered_set(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    std::unordered_set<std::u32string> cpp_set;
    int result = 0;
    std::string type = "<bytes>";
    PyObject * py_set = new_py_set_u32string(size, str_len);
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
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

/**
 * Create a new Python \c tuple of \c bytes.
 *
 * @param size Length of the \c tuple.
 * @param str_len Length of each \c bytes object. Each byte is just ' '.
 * @return New reference to a \c tuple or \c NULL on failure.
 */
PyObject *
new_py_tuple_bytes(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = Python_Cpp_Containers::py_tuple_new(size);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::vector<char> str(str_len, ' ');
            int err = Python_Cpp_Containers::py_tuple_set(op, i,
                                                          Python_Cpp_Containers::cpp_vector_char_to_py_bytes(str));
            if (err) {
                PyErr_Format(PyExc_SystemError,
                             "Python_Cpp_Containers::py_tuple_set() failed returning %d.", err
                );
                Py_DECREF(op);
                op = NULL;
            }
        }
    }
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c tuple of \c str.
 *
 * @param size Length of the \c tuple.
 * @param str_len Length of each \c str object. Each byte is just ' '.
 * @return New reference to a \c tuple or \c NULL on failure.
 */
PyObject *
new_py_tuple_string(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = Python_Cpp_Containers::py_tuple_new(size);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::string str(str_len, ' ');
            int err = Python_Cpp_Containers::py_tuple_set(op, i, Python_Cpp_Containers::cpp_string_to_py_unicode8(str));
            if (err) {
                PyErr_Format(PyExc_SystemError,
                             "Python_Cpp_Containers::py_tuple_set() failed returning %d.", err
                );
                Py_DECREF(op);
                op = NULL;
            }
        }
    }
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c tuple of \c 16 bit unicode str.
 *
 * @param size Length of the \c tuple.
 * @param str_len Length of each \c str object. Each character is just u' '.
 * @return New reference to a \c tuple or \c NULL on failure.
 */
PyObject *
new_py_tuple_string16(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = Python_Cpp_Containers::py_tuple_new(size);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::u16string str(str_len, u' ');
            int err = Python_Cpp_Containers::py_tuple_set(op, i,
                                                          Python_Cpp_Containers::cpp_u16string_to_py_unicode16(str));
            if (err) {
                PyErr_Format(PyExc_SystemError,
                             "Python_Cpp_Containers::py_tuple_set() failed returning %d.", err
                );
                Py_DECREF(op);
                op = NULL;
            }
        }
    }
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c tuple of \c 32 bit unicode str.
 *
 * @param size Length of the \c tuple.
 * @param str_len Length of each \c str object. Each character is just U' '.
 * @return New reference to a \c tuple or \c NULL on failure.
 */
PyObject *
new_py_tuple_string32(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = Python_Cpp_Containers::py_tuple_new(size);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::u32string str(str_len, U' ');
            int err = Python_Cpp_Containers::py_tuple_set(op, i,
                                                          Python_Cpp_Containers::cpp_u32string_to_py_unicode32(str));
            if (err) {
                PyErr_Format(PyExc_SystemError,
                             "Python_Cpp_Containers::py_tuple_set() failed returning %d.", err
                );
                Py_DECREF(op);
                op = NULL;
            }
        }
    }
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c list of \c bytes.
 *
 * @param size Length of the \c list.
 * @param str_len Length of each \c bytes object. Each byte is just ' '.
 * @return New reference to a \c list or \c NULL on failure.
 */
PyObject *
new_py_list_bytes(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = Python_Cpp_Containers::py_list_new(size);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::vector<char> str(str_len, ' ');
            int err = Python_Cpp_Containers::py_list_set(op, i,
                                                         Python_Cpp_Containers::cpp_vector_char_to_py_bytes(str));
            if (err) {
                PyErr_Format(PyExc_SystemError,
                             "Python_Cpp_Containers::py_list_set() failed returning %d.", err
                );
                Py_DECREF(op);
                op = NULL;
            }
        }
    }
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c list of \c str.
 *
 * @param size Length of the \c list.
 * @param str_len Length of each \c str object. Each byte is just ' '.
 * @return New reference to a \c list or \c NULL on failure.
 */
PyObject *
new_py_list_string(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = Python_Cpp_Containers::py_list_new(size);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::string str(str_len, ' ');
            int err = Python_Cpp_Containers::py_list_set(op, i, Python_Cpp_Containers::cpp_string_to_py_unicode8(str));
            if (err) {
                PyErr_Format(PyExc_SystemError,
                             "Python_Cpp_Containers::py_list_set() failed returning %d.", err
                );
                Py_DECREF(op);
                op = NULL;
            }
        }
    }
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c list of \c str with 16 bit characters.
 *
 * @param size Length of the \c list.
 * @param str_len Length of each \c str object. Each character is just u' '.
 * @return New reference to a \c list or \c NULL on failure.
 */
PyObject *
new_py_list_string16(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = Python_Cpp_Containers::py_list_new(size);
    int err;
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::u16string str(str_len, u' ');
            err = Python_Cpp_Containers::py_list_set(
                    op, i, Python_Cpp_Containers::cpp_u16string_to_py_unicode16(str)
            );
            if (err) {
                PyErr_Format(PyExc_SystemError,
                             "Python_Cpp_Containers::py_list_set() failed returning %d.", err
                );
                Py_DECREF(op);
                op = NULL;
                break;
            }
        }
    }
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c list of \c str with 32 bit characters.
 *
 * @param size Length of the \c list.
 * @param str_len Length of each \c str object. Each character is just U' '.
 * @return New reference to a \c list or \c NULL on failure.
 */
PyObject *
new_py_list_string32(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = Python_Cpp_Containers::py_list_new(size);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::u32string str(str_len, U' ');
            int err = Python_Cpp_Containers::py_list_set(
                    op, i, Python_Cpp_Containers::cpp_u32string_to_py_unicode32(str)
            );
            if (err) {
                PyErr_Format(PyExc_SystemError,
                             "Python_Cpp_Containers::py_list_set() failed returning %d.", err
                );
                Py_DECREF(op);
                op = NULL;
            }
        }
    }
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c set of \c bytes.
 *
 * @param size Length of the \c set.
 * @param str_len Length of each \c bytes object. Each object will be unique.
 * @return New reference to a \c set or \c NULL on failure.
 */
PyObject *
new_py_set_bytes(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = PySet_New(NULL);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::vector<char> str = unique_vector_char(str_len);
            int err = PySet_Add(op, Python_Cpp_Containers::cpp_vector_char_to_py_bytes(str));
            if (err) {
                PyErr_Format(PyExc_SystemError, "PySet_Add failed returning %d.", err);
                Py_DECREF(op);
                op = NULL;
            }
        }
    }
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c set of \c str.
 *
 * @param size Length of the \c set.
 * @param str_len Length of each \c str object. Each object will be unique.
 * @return New reference to a \c set or \c NULL on failure.
 */
PyObject *
new_py_set_string(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = PySet_New(NULL);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::string str = unique_string(str_len);
            int err = PySet_Add(op, Python_Cpp_Containers::cpp_string_to_py_unicode8(str));
            if (err) {
                PyErr_Format(PyExc_SystemError, "PySet_Add failed returning %d.", err);
                Py_DECREF(op);
                op = NULL;
            }
        }
        assert((size_t) PySet_Size(op) == size);
    }
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c set of \c str 16 bit.
 *
 * @param size Length of the \c set.
 * @param str_len Length of each \c str object. Each object will be unique.
 * @return New reference to a \c set or \c NULL on failure.
 */
PyObject *
new_py_set_u16string(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = PySet_New(NULL);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::u16string str = unique_u16string(str_len);
            int err = PySet_Add(op, Python_Cpp_Containers::cpp_u16string_to_py_unicode16(str));
            if (err) {
                PyErr_Format(PyExc_SystemError, "PySet_Add failed returning %d.", err);
                Py_DECREF(op);
                op = NULL;
            }
        }
        assert((size_t) PySet_Size(op) == size);
    }
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c set of \c str 32 bit.
 *
 * @param size Length of the \c set.
 * @param str_len Length of each \c str object. Each object will be unique.
 * @return New reference to a \c set or \c NULL on failure.
 */
PyObject *
new_py_set_u32string(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = PySet_New(NULL);
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::u32string str = unique_u32string(str_len);
            int err = PySet_Add(op, Python_Cpp_Containers::cpp_u32string_to_py_unicode32(str));
            if (err) {
                PyErr_Format(PyExc_SystemError, "PySet_Add failed returning %d.", err);
                Py_DECREF(op);
                op = NULL;
            }
        }
        assert((size_t) PySet_Size(op) == size);
    }
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c dict of \c bytes for both the key and the value.
 *
 * @param size Length of the \c dict.
 * @param str_len Length of each \c bytes object to be the key and value. Each key and value will be unique.
 * @return New reference to a \c dict or \c NULL on failure.
 */
PyObject *
new_py_dict_bytes(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = PyDict_New();
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::vector<char> key = unique_vector_char(str_len);
            PyObject * py_key = Python_Cpp_Containers::cpp_vector_char_to_py_bytes(key);
            std::vector<char> val = unique_vector_char(str_len);
            PyObject * py_val = Python_Cpp_Containers::cpp_vector_char_to_py_bytes(val);
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
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c dict of \c str for both the key and the value.
 *
 * @param size Length of the \c dict.
 * @param str_len Length of each \c str object to be the key and value. Each key and value will be unique.
 * @return New reference to a \c dict or \c NULL on failure.
 */
PyObject *
new_py_dict_string(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = PyDict_New();
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::string key = unique_string(str_len);
            PyObject * py_key = Python_Cpp_Containers::cpp_string_to_py_unicode8(key);
            std::string val = unique_string(str_len);
            PyObject * py_val = Python_Cpp_Containers::cpp_string_to_py_unicode8(val);
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
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c dict of \c str (16bit) for both the key and the value.
 *
 * @param size Length of the \c dict.
 * @param str_len Length of each \c str object to be the key and value. Each key and value will be unique.
 * @return New reference to a \c dict or \c NULL on failure.
 */
PyObject *
new_py_dict_string16(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = PyDict_New();
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::u16string key = unique_u16string(str_len);
            PyObject * py_key = Python_Cpp_Containers::cpp_u16string_to_py_unicode16(key);
            std::u16string val = unique_u16string(str_len);
            PyObject * py_val = Python_Cpp_Containers::cpp_u16string_to_py_unicode16(val);
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
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

/**
 * Create a new Python \c dict of \c str (32bit) for both the key and the value.
 *
 * @param size Length of the \c dict.
 * @param str_len Length of each \c str object to be the key and value. Each key and value will be unique.
 * @return New reference to a \c dict or \c NULL on failure.
 */
PyObject *
new_py_dict_string32(size_t size, size_t str_len) {
    assert(!PyErr_Occurred());
    PyObject * op = PyDict_New();
    if (op) {
        for (size_t i = 0; i < size; ++i) {
            std::u32string key = unique_u32string(str_len);
            PyObject * py_key = Python_Cpp_Containers::cpp_u32string_to_py_unicode32(key);
            std::u32string val = unique_u32string(str_len);
            PyObject * py_val = Python_Cpp_Containers::cpp_u32string_to_py_unicode32(val);
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
    if (op) {
        assert(!PyErr_Occurred());
    } else {
        assert(PyErr_Occurred());
    }
    return op;
}

template<
        template<typename ...> class MapLike
>
int test_cpp_std_map_like_to_py_dict_bytes(TestResultS &test_results, size_t size, size_t str_len,
                                           const std::string &container_type) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    MapLike<std::vector<char>, std::vector<char>> cpp_map;
    for (size_t i = 0; i < size; ++i) {
        cpp_map[unique_vector_char(str_len)] = std::vector<char>(str_len, ' ');
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_map_like_to_py_dict(cpp_map);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (!op) {
        result = 1;
    } else {
        assert(op->ob_refcnt == 1);
        if (!PyDict_Check(op)) {
            result = 2;
        } else {
            if (compare_dict(cpp_map, op)) {
                result = 3;
            }
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_CONTAINER_TYPE_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_cpp_std_unordered_map_to_py_dict_bytes(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_cpp_std_map_like_to_py_dict_bytes<std::unordered_map>(test_results, size, str_len,
                                                                            "std::unordered_map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}


int test_cpp_std_map_to_py_dict_bytes(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_cpp_std_map_like_to_py_dict_bytes<std::map>(test_results, size, str_len,
                                                                  "std::map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}


template<
        template<typename ...> class MapLike
>
int test_py_dict_to_cpp_std_map_like_bytes(TestResultS &test_results, size_t size, size_t str_len,
                                           const std::string &container_type) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    PyObject * op = new_py_dict_bytes(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result = 1;
    } else {
        MapLike<std::vector<char>, std::vector<char>> cpp_map;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_dict_to_cpp_std_map_like(op, cpp_map);
        exec_time = exec_clock.seconds();
        if (err != 0) {
            result = 2;
        } else {
            // Compare dict
            if (compare_dict(cpp_map, op)) {
                result = 3;
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_CONTAINER_TYPE_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_py_dict_to_cpp_std_unordered_map_bytes(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_py_dict_to_cpp_std_map_like_bytes<std::unordered_map>(test_results, size, str_len,
                                                                            "std::unordered_map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_py_dict_to_cpp_std_map_bytes(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_py_dict_to_cpp_std_map_like_bytes<std::map>(test_results, size, str_len,
                                                                  "std::map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

template<
        template<typename ...> class MapLike
>
int test_cpp_std_map_like_to_py_dict_string(TestResultS &test_results, size_t size, size_t str_len,
                                            const std::string &container_type) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    MapLike<std::string, std::string> cpp_map;
    for (size_t i = 0; i < size; ++i) {
        cpp_map[unique_string(str_len)] = std::string(str_len, ' ');
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_map_like_to_py_dict(cpp_map);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (!op) {
        result = 1;
    } else {
        assert(op->ob_refcnt == 1);
        if (!PyDict_Check(op)) {
            result = 2;
        } else {
            if (compare_dict(cpp_map, op)) {
                result = 3;
            }
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_CONTAINER_TYPE_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

template<
        template<typename ...> class MapLike
>
int test_cpp_std_map_like_to_py_dict_string16(TestResultS &test_results, size_t size, size_t str_len,
                                              const std::string &container_type) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    MapLike<std::u16string, std::u16string> cpp_map;
    for (size_t i = 0; i < size; ++i) {
        cpp_map[unique_u16string(str_len)] = std::u16string(str_len, u' ');
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_map_like_to_py_dict(cpp_map);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (!op) {
        result = 1;
    } else {
        assert(op->ob_refcnt == 1);
        if (!PyDict_Check(op)) {
            result = 2;
        } else {
            if (compare_dict(cpp_map, op)) {
                result = 3;
            }
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_CONTAINER_TYPE_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

template<
        template<typename ...> class MapLike
>
int test_cpp_std_map_like_to_py_dict_string32(TestResultS &test_results, size_t size, size_t str_len,
                                              const std::string &container_type) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    MapLike<std::u32string, std::u32string> cpp_map;
    for (size_t i = 0; i < size; ++i) {
        cpp_map[unique_u32string(str_len)] = std::u32string(str_len, u' ');
    }
    ExecClock exec_clock;
    PyObject * op = Python_Cpp_Containers::cpp_std_map_like_to_py_dict(cpp_map);
    double exec_time = exec_clock.seconds();
    int result = 0;
    if (!op) {
        result = 1;
    } else {
        assert(op->ob_refcnt == 1);
        if (!PyDict_Check(op)) {
            result = 2;
        } else {
            if (compare_dict(cpp_map, op)) {
                result = 3;
            }
        }
        assert(op->ob_refcnt == 1);
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_CONTAINER_TYPE_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_cpp_std_unordered_map_to_py_dict_string(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_cpp_std_map_like_to_py_dict_string<std::unordered_map>(test_results, size, str_len,
                                                                             "std::unordered_map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_cpp_std_unordered_map_to_py_dict_string16(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_cpp_std_map_like_to_py_dict_string16<std::unordered_map>(test_results, size, str_len,
                                                                               "std::unordered_map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_cpp_std_unordered_map_to_py_dict_string32(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_cpp_std_map_like_to_py_dict_string32<std::unordered_map>(test_results, size, str_len,
                                                                               "std::unordered_map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_cpp_std_map_to_py_dict_string(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_cpp_std_map_like_to_py_dict_string<std::map>(test_results, size, str_len, "std::map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_cpp_std_map_to_py_dict_string16(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_cpp_std_map_like_to_py_dict_string16<std::map>(test_results, size, str_len, "std::map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_cpp_std_map_to_py_dict_string32(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_cpp_std_map_like_to_py_dict_string32<std::map>(test_results, size, str_len, "std::map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

template<
        template<typename ...> class MapLike
>
int test_py_dict_to_cpp_std_map_like_string(TestResultS &test_results, size_t size, size_t str_len,
                                            const std::string &container_type) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    PyObject * op = new_py_dict_string(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result = 1;
    } else {
        MapLike<std::string, std::string> cpp_map;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_dict_to_cpp_std_map_like(op, cpp_map);
        exec_time = exec_clock.seconds();
        if (err != 0) {
            result = 2;
        } else {
            // Compare dict
            if (compare_dict(cpp_map, op)) {
                result = 3;
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_CONTAINER_TYPE_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

template<
        template<typename ...> class MapLike
>
int test_py_dict_to_cpp_std_map_like_string16(TestResultS &test_results, size_t size, size_t str_len,
                                              const std::string &container_type) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    PyObject * op = new_py_dict_string16(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result = 1;
    } else {
        MapLike<std::u16string, std::u16string> cpp_map;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_dict_to_cpp_std_map_like(op, cpp_map);
        exec_time = exec_clock.seconds();
        if (err != 0) {
            result = 2;
        } else {
            // Compare dict
            if (compare_dict(cpp_map, op)) {
                result = 3;
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_CONTAINER_TYPE_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

template<
        template<typename ...> class MapLike
>
int test_py_dict_to_cpp_std_map_like_string32(TestResultS &test_results, size_t size, size_t str_len,
                                              const std::string &container_type) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    PyObject * op = new_py_dict_string32(size, str_len);
    int result = 0;
    double exec_time = -1.0;
    if (!op) {
        result = 1;
    } else {
        MapLike<std::u32string, std::u32string> cpp_map;
        ExecClock exec_clock;
        int err = Python_Cpp_Containers::py_dict_to_cpp_std_map_like(op, cpp_map);
        exec_time = exec_clock.seconds();
        if (err != 0) {
            result = 2;
        } else {
            // Compare dict
            if (compare_dict(cpp_map, op)) {
                result = 3;
            }
        }
        Py_DECREF(op);
    }
    REPORT_TEST_OUTPUT_WITH_CONTAINER_TYPE_STRING_LENGTH;
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_py_dict_to_cpp_std_unordered_map_string(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_py_dict_to_cpp_std_map_like_string<std::unordered_map>(test_results, size, str_len,
                                                                             "std::unordered_map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_py_dict_to_cpp_std_unordered_map_u16string(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_py_dict_to_cpp_std_map_like_string16<std::unordered_map>(test_results, size, str_len,
                                                                               "std::unordered_map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_py_dict_to_cpp_std_unordered_map_u32string(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_py_dict_to_cpp_std_map_like_string32<std::unordered_map>(test_results, size, str_len,
                                                                               "std::unordered_map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_py_dict_to_cpp_std_map_string(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_py_dict_to_cpp_std_map_like_string<std::map>(test_results, size, str_len, "std::map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_py_dict_to_cpp_std_map_string16(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_py_dict_to_cpp_std_map_like_string16<std::map>(test_results, size, str_len, "std::map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}

int test_py_dict_to_cpp_std_map_string32(TestResultS &test_results, size_t size, size_t str_len) {
    TEST_FOR_PY_ERR_ON_ENTRY;
    RSS_SNAPSHOT_WITHOUT_TYPE;
    int result = test_py_dict_to_cpp_std_map_like_string32<std::map>(test_results, size, str_len, "std::map");
    RSS_SNAPSHOT_REPORT;
    TEST_FOR_PY_ERR_ON_EXIT;
    return result;
}
