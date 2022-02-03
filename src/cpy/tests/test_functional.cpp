//
// Created by Paul Ross on 21/05/2021.
//

#include <Python.h>

#include "cpy/python_convert.h"
#include "test_functional.h"

/**
 * Demonstration code for converting a `std::vector<double>` to a Python tuple.
 */
void test_example_vector_to_py_tuple_double() {
    std::vector<double> cpp_vector;
    for (size_t i = 0; i < 1024; ++i) {
        cpp_vector.push_back(static_cast<double>(i));
    }
    PyObject *op = Python_Cpp_Containers::cpp_std_list_like_to_py_tuple(cpp_vector);
    if (! op) {
        // Handle error condition.
    } else {
        // Use the Python tuple
        Py_DECREF(op);
    }
}

/**
 * Demonstration code for converting a Python tuple off floats to a `std::vector<double>`.
 */
void test_example_py_tuple_to_vector_double() {
    PyObject *op = Python_Cpp_Containers::py_tuple_new(1024);
    if (! op) {
        // Handle error
    } else {
        for (size_t i = 0; i < 1024; ++i) {
            // Populate tuple.
            int err = Python_Cpp_Containers::py_tuple_set(
                    op,
                    i,
                    Python_Cpp_Containers::cpp_double_to_py_float(static_cast<double>(i))
                    );
            if (err != 0) {
                // Handle error
            }
        }
        std::vector<double> cpp_vector;
        int err = Python_Cpp_Containers::py_tuple_to_cpp_std_list_like(op, cpp_vector);
        if (err != 0) {
            // Handle error
        } else {
            // Use the C++ vector.
        }
        Py_DECREF(op);
    }
}

/**
 * Demonstration code to convert a std::unordered_map<long, std::string> to a Python dict.
 */
void test_example_cpp_std_unordered_map_to_py_dict() {
    std::unordered_map<long, std::vector<char>> cpp_map;
    // Populate the map with some data.
    for (long i = 0; i < 128; ++i) {
        cpp_map[i] = std::vector<char>(4, ' ');
    }
    // Convert to a Python dict.
    PyObject *op = Python_Cpp_Containers::cpp_std_map_like_to_py_dict(cpp_map);
    assert(PyDict_Check(op));
    if (! op) {
        // Handle error.
    } else {
        // Do something with op
        // ...
        // Discard if necessary.
        Py_DECREF(op);
    }
}

/**
 * Demonstration code to convert a std::map<long, std::string> to a Python dict.
 */
void test_example_cpp_std_map_to_py_dict() {
    std::map<long, std::vector<char>> cpp_map;
    // Populate the map with some data.
    for (long i = 0; i < 128; ++i) {
        cpp_map[i] = std::vector<char>(4, ' ');
    }
    // Convert to a Python dict.
    PyObject *op = Python_Cpp_Containers::cpp_std_map_like_to_py_dict(cpp_map);
    assert(PyDict_Check(op));
    if (! op) {
        // Handle error.
    } else {
        // Do something with op
        // ...
        // Discard if necessary.
        Py_DECREF(op);
    }
}

/**
 * Demonstration code to convert a Python dict[int, bytes] to a std::unordered_map<long, std::string>.
 */
void test_example_py_dict_to_cpp_std_unordered_map() {
    PyObject *op = PyDict_New();
    // Populate dict with [int, bytes]
    // ...
    std::unordered_map<long, std::vector<char>> cpp_map;
    int err = Python_Cpp_Containers::py_dict_to_cpp_std_map_like(op, cpp_map);
    if (err != 0) {
        // Handle error.
    } else {
        // Do something with cpp_map
        // ...
    }
    // Discard op if necessary
    Py_DECREF(op);
}

void test_functional_tuple(TestResultS &test_results) {
    // Tuples.
    test_vector_to_py_tuple<bool, &Python_Cpp_Containers::py_bool_to_cpp_bool>(test_results, "<bool>", 1024);
    test_vector_to_py_tuple<long, &Python_Cpp_Containers::py_long_to_cpp_long>(test_results, "<long>", 1024);
    test_vector_to_py_tuple<double, &Python_Cpp_Containers::py_float_to_cpp_double>(test_results, "<double>", 1024);
    test_vector_to_py_tuple<std::complex<double>, &Python_Cpp_Containers::py_complex_to_cpp_complex>(test_results,
                                                                                                     "std::complex<double>",
                                                                                                     1024);
    test_py_tuple_to_vector<bool, &Python_Cpp_Containers::cpp_bool_to_py_bool>(
            test_results, "<bool>", 1024);
    test_py_tuple_to_vector<long, &Python_Cpp_Containers::cpp_long_to_py_long>(
            test_results, "<long>", 1024);
    test_py_tuple_to_vector<double, &Python_Cpp_Containers::cpp_double_to_py_float>(
            test_results, "<double>", 1024);
    test_py_tuple_to_vector<std::complex<double>, &Python_Cpp_Containers::cpp_complex_to_py_complex>(
            test_results, "std::complex<double>", 1024);
    test_vector_to_py_tuple_round_trip<bool>(test_results, "<bool>", 1024);
    test_vector_to_py_tuple_round_trip<long>(test_results, "<long>", 1024);
    test_vector_to_py_tuple_round_trip<double>(test_results, "<double>", 1024);
    test_vector_to_py_tuple_round_trip<std::complex<double>>(test_results, "<std::complex<double>>", 1024);
    test_py_tuple_to_vector_round_trip<bool, &Python_Cpp_Containers::cpp_bool_to_py_bool>(test_results,
                                                                                          "<bool>", 1024);
    test_py_tuple_to_vector_round_trip<long, &Python_Cpp_Containers::cpp_long_to_py_long>(test_results,
                                                                                          "<long>", 1024);
    test_py_tuple_to_vector_round_trip<double, &Python_Cpp_Containers::cpp_double_to_py_float>(
            test_results,
            "<double>", 1024);
    test_py_tuple_to_vector_round_trip<std::complex<double>, &Python_Cpp_Containers::cpp_complex_to_py_complex>(
            test_results,
            "<std::complex<double>>", 1024);
    test_vector_vector_char_to_py_tuple(test_results, 1024, 32);
    test_py_tuple_bytes_to_vector(test_results, 1024, 32);
    test_vector_string_to_py_tuple(test_results, 1024, 32);
    test_py_tuple_str_to_vector(test_results, 1024, 32);
}

void test_functional_list(TestResultS &test_results) {
    // Lists
    test_vector_to_py_list<bool>(test_results, "<bool>", 1024);
    test_vector_to_py_list<long>(test_results, "<long>", 1024);
    test_vector_to_py_list<double>(test_results, "<double>", 1024);
    test_vector_to_py_list<std::complex<double>>(test_results, "std::complex<double>", 1024);
    test_py_list_to_vector<bool, &Python_Cpp_Containers::cpp_bool_to_py_bool, &Python_Cpp_Containers::py_bool_to_cpp_bool>(
            test_results, "<bool>", 1024);
    test_py_list_to_vector<long, &Python_Cpp_Containers::cpp_long_to_py_long, &Python_Cpp_Containers::py_long_to_cpp_long>(
            test_results, "<long>", 1024);
    test_py_list_to_vector<double, &Python_Cpp_Containers::cpp_double_to_py_float, &Python_Cpp_Containers::py_float_to_cpp_double>(
            test_results, "<double>", 1024);
    test_py_list_to_vector<std::complex<double>, &Python_Cpp_Containers::cpp_complex_to_py_complex, &Python_Cpp_Containers::py_complex_to_cpp_complex>(
            test_results, "std::complex<double>", 1024);
    test_vector_to_py_list_round_trip<bool>(test_results, "<bool>", 1024);
    test_vector_to_py_list_round_trip<long>(test_results, "<long>", 1024);
    test_vector_to_py_list_round_trip<double>(test_results, "<double>", 1024);
    test_vector_to_py_list_round_trip<std::complex<double>>(test_results, "std::complex<double>", 1024);
    test_py_list_to_vector_round_trip<bool, &Python_Cpp_Containers::cpp_bool_to_py_bool>(test_results,
                                                                                         "<bool>", 1024);
    test_py_list_to_vector_round_trip<long, &Python_Cpp_Containers::cpp_long_to_py_long>(test_results,
                                                                                         "<long>", 1024);
    test_py_list_to_vector_round_trip<double, &Python_Cpp_Containers::cpp_double_to_py_float>(
            test_results,
            "<double>", 1024);
    test_py_list_to_vector_round_trip<std::complex<double>, &Python_Cpp_Containers::cpp_complex_to_py_complex>(
            test_results,
            "std::complex<double>", 1024);
    test_vector_vector_char_to_py_list(test_results, 1024, 32);
    test_py_list_bytes_to_vector(test_results, 1024, 32);
    test_vector_string_to_py_list(test_results, 1024, 32);
    test_py_list_str_to_vector(test_results, 1024, 32);
}

void test_functional_set(TestResultS &test_results) {
    // sets
    test_unordered_set_to_py_set<long, &Python_Cpp_Containers::py_long_to_cpp_long, &Python_Cpp_Containers::cpp_long_to_py_long>(
            test_results, "<long>", 1024);
    test_py_set_to_unordered_set<long, &Python_Cpp_Containers::py_long_to_cpp_long, &Python_Cpp_Containers::cpp_long_to_py_long>(
            test_results, "<long>", 1024);
    test_unordered_set_to_py_set<double, &Python_Cpp_Containers::py_float_to_cpp_double, &Python_Cpp_Containers::cpp_double_to_py_float>(
            test_results, "<double>", 1024);
    test_py_set_to_unordered_set<double, &Python_Cpp_Containers::py_float_to_cpp_double, &Python_Cpp_Containers::cpp_double_to_py_float>(
            test_results, "<double>", 1024);
    test_unordered_set_to_py_set<std::complex<double>, &Python_Cpp_Containers::py_complex_to_cpp_complex,
            &Python_Cpp_Containers::cpp_complex_to_py_complex>(
            test_results, "<std::complex<double>>", 1024);
    test_py_set_to_unordered_set<std::complex<double>, &Python_Cpp_Containers::py_complex_to_cpp_complex,
            &Python_Cpp_Containers::cpp_complex_to_py_complex>(
            test_results, "<std::complex<double>>", 1024);
    // Test set of bytes
    test_py_set_bytes_to_unordered_set(test_results, 1024, 32);
    test_unordered_set_bytes_to_py_set(test_results, 1024, 32);
    test_unordered_set_string_to_py_set(test_results, 1024, 32);
    test_py_set_string_to_unordered_set(test_results, 1024, 32);
}

void test_functional_dict_with_std_unordred_map(TestResultS &test_results) {
    // Dicts
    test_cpp_std_unordered_map_to_py_dict<
            long,
            long,
            &Python_Cpp_Containers::cpp_long_to_py_long,
            &Python_Cpp_Containers::cpp_long_to_py_long,
            &Python_Cpp_Containers::py_long_to_cpp_long,
            &Python_Cpp_Containers::py_long_to_cpp_long
    >(test_results, "<long>", 258);
    test_py_dict_to_cpp_std_unordered_map<
            long,
            long,
            &Python_Cpp_Containers::cpp_long_to_py_long,
            &Python_Cpp_Containers::cpp_long_to_py_long,
            &Python_Cpp_Containers::py_long_to_cpp_long,
            &Python_Cpp_Containers::py_long_to_cpp_long
    >(test_results, "<long>", 1024);
    test_cpp_std_unordered_map_to_py_dict<
            double,
            double,
            &Python_Cpp_Containers::cpp_double_to_py_float,
            &Python_Cpp_Containers::cpp_double_to_py_float,
            &Python_Cpp_Containers::py_float_to_cpp_double,
            &Python_Cpp_Containers::py_float_to_cpp_double
    >(test_results, "<double>", 1024);
    test_py_dict_to_cpp_std_unordered_map<
            double,
            double,
            &Python_Cpp_Containers::cpp_double_to_py_float,
            &Python_Cpp_Containers::cpp_double_to_py_float,
            &Python_Cpp_Containers::py_float_to_cpp_double,
            &Python_Cpp_Containers::py_float_to_cpp_double
    >(test_results, "<double>", 1024);
    test_cpp_std_unordered_map_to_py_dict<
            std::complex<double>,
            std::complex<double>,
            &Python_Cpp_Containers::cpp_complex_to_py_complex,
            &Python_Cpp_Containers::cpp_complex_to_py_complex,
            &Python_Cpp_Containers::py_complex_to_cpp_complex,
            &Python_Cpp_Containers::py_complex_to_cpp_complex
    >(test_results, "<std::complex<double>>", 1024);
    test_py_dict_to_cpp_std_unordered_map<
            std::complex<double>,
            std::complex<double>,
            &Python_Cpp_Containers::cpp_complex_to_py_complex,
            &Python_Cpp_Containers::cpp_complex_to_py_complex,
            &Python_Cpp_Containers::py_complex_to_cpp_complex,
            &Python_Cpp_Containers::py_complex_to_cpp_complex
    >(test_results, "<std::complex<double>>", 1024);
    test_cpp_std_unordered_map_to_py_dict_bytes(test_results, 1024, 32);
    test_py_dict_to_cpp_std_unordered_map_bytes(test_results, 1024, 32);
    test_cpp_std_unordered_map_to_py_dict_string(test_results, 1024, 32);
    test_py_dict_to_cpp_std_unordered_map_string(test_results, 1024, 32);
}

void test_functional_dict_with_std_map(TestResultS &test_results) {
    // Dicts
    test_cpp_std_map_to_py_dict<
            long,
            long,
            &Python_Cpp_Containers::cpp_long_to_py_long,
            &Python_Cpp_Containers::cpp_long_to_py_long,
            &Python_Cpp_Containers::py_long_to_cpp_long,
            &Python_Cpp_Containers::py_long_to_cpp_long
    >(test_results, "<long>", 258);
    test_py_dict_to_cpp_std_map<
            long,
            long,
            &Python_Cpp_Containers::cpp_long_to_py_long,
            &Python_Cpp_Containers::cpp_long_to_py_long,
            &Python_Cpp_Containers::py_long_to_cpp_long,
            &Python_Cpp_Containers::py_long_to_cpp_long
    >(test_results, "<long>", 1024);
    test_cpp_std_map_to_py_dict<
            double,
            double,
            &Python_Cpp_Containers::cpp_double_to_py_float,
            &Python_Cpp_Containers::cpp_double_to_py_float,
            &Python_Cpp_Containers::py_float_to_cpp_double,
            &Python_Cpp_Containers::py_float_to_cpp_double
    >(test_results, "<double>", 1024);
    test_py_dict_to_cpp_std_map<
            double,
            double,
            &Python_Cpp_Containers::cpp_double_to_py_float,
            &Python_Cpp_Containers::cpp_double_to_py_float,
            &Python_Cpp_Containers::py_float_to_cpp_double,
            &Python_Cpp_Containers::py_float_to_cpp_double
    >(test_results, "<double>", 1024);
    test_cpp_std_map_to_py_dict<
            std::complex<double>,
            std::complex<double>,
            &Python_Cpp_Containers::cpp_complex_to_py_complex,
            &Python_Cpp_Containers::cpp_complex_to_py_complex,
            &Python_Cpp_Containers::py_complex_to_cpp_complex,
            &Python_Cpp_Containers::py_complex_to_cpp_complex
    >(test_results, "<std::complex<double>>", 1024);
    test_py_dict_to_cpp_std_map<
            std::complex<double>,
            std::complex<double>,
            &Python_Cpp_Containers::cpp_complex_to_py_complex,
            &Python_Cpp_Containers::cpp_complex_to_py_complex,
            &Python_Cpp_Containers::py_complex_to_cpp_complex,
            &Python_Cpp_Containers::py_complex_to_cpp_complex
    >(test_results, "<std::complex<double>>", 1024);
    test_cpp_std_map_to_py_dict_bytes(test_results, 1024, 32);
    test_py_dict_to_cpp_std_map_bytes(test_results, 1024, 32);
    test_cpp_std_map_to_py_dict_string(test_results, 1024, 32);
    test_py_dict_to_cpp_std_map_string(test_results, 1024, 32);
}

void test_functional_all(TestResultS &test_results) {
    std::cout << __FUNCTION__ << " START" << std::endl;
    RSSSnapshot rss_overall("==== test_functional.cpp");
    // Test that the demonstration code works, no record of the result is kept.
    test_example_vector_to_py_tuple_double();
    test_example_py_tuple_to_vector_double();
    test_example_cpp_std_unordered_map_to_py_dict();
    test_example_cpp_std_map_to_py_dict();
    test_example_py_dict_to_cpp_std_unordered_map();

    // Functional tests that add to the test results.
    test_functional_tuple(test_results);
    test_functional_list(test_results);
    test_functional_set(test_results);
    test_functional_dict_with_std_unordred_map(test_results);
    test_functional_dict_with_std_map(test_results);

    std::cout << "==== " << rss_overall << std::endl;
    std::cout << __FUNCTION__ << " FINISH" << std::endl;
}
