//
// Created by Paul Ross on 21/05/2021.
//

#include <Python.h>

#include "cpy/python_convert.h"
#include "test_functional.h"

// Demonstration code.
void test_example_vector_to_py_tuple_double() {
    std::vector<double> cpp_vector;
    for (size_t i = 0; i < 1024; ++i) {
        cpp_vector.push_back(static_cast<double>(i));
    }
    PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    if (! op) {
        // Handle error condition.
    } else {
        // Use Python tuple
        Py_DECREF(op);
    }
}

// Demonstration code.
void test_example_py_tuple_to_vector_double() {
    PyObject *op = Python_Cpp_Containers::py_tuple_new(1024);
    if (! op) {
        // Handle error
    } else {
        for (size_t i = 0; i < 1024; ++i) {
            int err = Python_Cpp_Containers::py_tuple_set(
                    op,
                    i,
                    Python_Cpp_Containers::py_float_from_double(static_cast<double>(i))
                    );
            if (err != 0) {
                // Handle error
            }
        }
        std::vector<double> cpp_vector;
        int err = Python_Cpp_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
        if (err != 0) {
            // Handle error
        } else {
            // Use vector.
        }
        Py_DECREF(op);
    }
}

// Demonstration code
void test_example_cpp_std_unordered_map_to_py_dict() {
    std::unordered_map<long, std::string> cpp_map;
    // Populate the map with some data.
    for (long i = 0; i < 128; ++i) {
        cpp_map[i] = std::string(4, ' ');
    }
    // Convert to a Python dict.
    PyObject *op = Python_Cpp_Containers::cpp_std_unordered_map_to_py_dict(cpp_map);
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

// Demonstration code
void test_example_py_dict_to_cpp_std_unordered_map() {
    PyObject *op = PyDict_New();
    // Populate dict with [int, bytes]
    // ...
    std::unordered_map<long, std::string> cpp_map;
    int err = Python_Cpp_Containers::py_dict_to_cpp_std_unordered_map(op, cpp_map);
    if (err != 0) {
        // Handle error.
    } else {
        // Do something with cpp_map
        // ...
    }
    // Discard op if necessary
    Py_DECREF(op);
}

void test_functional_all(TestResultS &test_results) {
    RSSSnapshot rss_overall("==== test_functional.cpp");
    test_example_vector_to_py_tuple_double();
    test_example_py_tuple_to_vector_double();
    test_example_cpp_std_unordered_map_to_py_dict();
    test_example_py_dict_to_cpp_std_unordered_map();
    {
        RSSSnapshot rss("test_vector_to_py_tuple<bool>");
        test_vector_to_py_tuple<bool, &Python_Cpp_Containers::py_bool_as_bool>(test_results, "<bool>",
                                                                                           1024);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_vector_to_py_tuple<long>");
        test_vector_to_py_tuple<long, &Python_Cpp_Containers::py_long_as_long>(test_results, "<long>",
                                                                                           1024);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_vector_to_py_tuple<double>");
        test_vector_to_py_tuple<double, &Python_Cpp_Containers::py_float_as_double>(test_results,
                                                                                                "<double>", 1024);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_py_tuple_to_vector<bool>");
        test_py_tuple_to_vector<bool, &Python_Cpp_Containers::py_bool_from_bool, &Python_Cpp_Containers::py_bool_as_bool>(
                test_results, "<bool>", 1024);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_py_tuple_to_vector<long>");
        test_py_tuple_to_vector<long, &Python_Cpp_Containers::py_long_from_long, &Python_Cpp_Containers::py_long_as_long>(
                test_results, "<long>", 1024);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_py_tuple_to_vector<double>");
        test_py_tuple_to_vector<double, &Python_Cpp_Containers::py_float_from_double, &Python_Cpp_Containers::py_float_as_double>(
                test_results, "<double>", 1024);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_vector_to_py_tuple_round_trip<bool>");
        test_vector_to_py_tuple_round_trip<bool>(test_results, "<bool>", 1024);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_vector_to_py_tuple_round_trip<long>");
        test_vector_to_py_tuple_round_trip<long>(test_results, "<long>", 1024);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_vector_to_py_tuple_round_trip<double>");
        test_vector_to_py_tuple_round_trip<double>(test_results, "<double>", 1024);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_py_tuple_to_vector_round_trip<bool>");
        test_py_tuple_to_vector_round_trip<bool, &Python_Cpp_Containers::py_bool_from_bool>(test_results,
                                                                                                        "<bool>", 1024);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_py_tuple_to_vector_round_trip<long>");
        test_py_tuple_to_vector_round_trip<long, &Python_Cpp_Containers::py_long_from_long>(test_results,
                                                                                                        "<long>", 1024);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_py_tuple_to_vector_round_trip<double>");
        test_py_tuple_to_vector_round_trip<double, &Python_Cpp_Containers::py_float_from_double>(
                test_results,
                "<double>", 1024);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_vector_string_to_py_tuple");
        test_vector_string_to_py_tuple(test_results, 1024, 32);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_py_tuple_string_to_vector");
        test_py_tuple_string_to_vector(test_results, 1024, 32);
        std::cout << rss << std::endl;
    }
    // Dicts
    {
        RSSSnapshot rss("test_cpp_std_unordered_map_to_py_dict<double, double>");
        test_cpp_std_unordered_map_to_py_dict<
                double,
                double,
                &Python_Cpp_Containers::py_float_from_double,
                &Python_Cpp_Containers::py_float_from_double
        >(test_results, "<double>", 1024);
        std::cout << rss << std::endl;
    }
    {
        RSSSnapshot rss("test_py_dict_to_cpp_std_unordered_map<double, double>");
        test_py_dict_to_cpp_std_unordered_map<
                double,
                double,
                &Python_Cpp_Containers::py_float_from_double,
                &Python_Cpp_Containers::py_float_from_double
        >(test_results, "<double>", 1024);
        std::cout << rss << std::endl;
    }
    std::cout << "====" << rss_overall << std::endl;
}
