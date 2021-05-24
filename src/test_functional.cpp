//
// Created by Paul Ross on 21/05/2021.
//

#include <Python.h>

#include "python_convert.h"
#include "test_functional.h"


void test_functional_all(TestResultS &test_results) {
    test_vector_to_py_tuple<bool, &Python_Cpp_Homogeneous_Containers::py_bool_as_bool>(test_results, "<bool>", 1024);
    test_vector_to_py_tuple<long, &Python_Cpp_Homogeneous_Containers::py_long_as_long>(test_results, "<long>", 1024);
    test_vector_to_py_tuple<double, &Python_Cpp_Homogeneous_Containers::py_float_as_double>(test_results, "<double>", 1024);
    test_py_tuple_to_vector<bool, &Python_Cpp_Homogeneous_Containers::py_bool_from_bool, &Python_Cpp_Homogeneous_Containers::py_bool_as_bool>(
            test_results, "<bool>", 1024);
    test_py_tuple_to_vector<long, &Python_Cpp_Homogeneous_Containers::py_long_from_long, &Python_Cpp_Homogeneous_Containers::py_long_as_long>(
            test_results, "<long>", 1024);
    test_py_tuple_to_vector<double, &Python_Cpp_Homogeneous_Containers::py_float_from_double, &Python_Cpp_Homogeneous_Containers::py_float_as_double>(
            test_results, "<double>", 1024);
    test_vector_to_py_tuple_round_trip<bool>(test_results, "<bool>", 1024);
    test_vector_to_py_tuple_round_trip<long>(test_results, "<long>", 1024);
    test_vector_to_py_tuple_round_trip<double>(test_results, "<double>", 1024);
    test_py_tuple_to_vector_round_trip<bool, &Python_Cpp_Homogeneous_Containers::py_bool_from_bool>(test_results,
                                                                                                    "<bool>", 1024);
    test_py_tuple_to_vector_round_trip<long, &Python_Cpp_Homogeneous_Containers::py_long_from_long>(test_results,
                                                                                                    "<long>", 1024);
    test_py_tuple_to_vector_round_trip<double, &Python_Cpp_Homogeneous_Containers::py_float_from_double>(test_results,
                                                                                                         "<double>", 1024);
    test_vector_string_to_py_tuple(test_results, 1024, 32);
    test_py_tuple_string_to_vector(test_results, 1024, 32);
    // Dicts
    test_generic_cpp_std_unordered_map_to_py_dict<
            double,
            double,
            &Python_Cpp_Homogeneous_Containers::py_float_from_double,
            &Python_Cpp_Homogeneous_Containers::py_float_from_double
    >(test_results, "<double>", 1024);
    test_generic_py_dict_to_cpp_std_unordered_map<
            double,
            double,
            &Python_Cpp_Homogeneous_Containers::py_float_from_double,
            &Python_Cpp_Homogeneous_Containers::py_float_from_double
    >(test_results, "<double>", 1024);
}
