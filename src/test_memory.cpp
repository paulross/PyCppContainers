//
// Created by Paul Ross on 25/05/2021.
//
// This just experiments with creating Python objects and observing the memory usage.
// The aim is to explore memory safe Python patterns.
//
// Many of these tests are based on test in test_functional or test_performance.
//

#include "test_memory.h"

#include <Python.h>

#include "get_rss.h"
#include "python_convert.h"
#include "test_common.h"

int test_memory_py_tuple(TestResultS &test_results, const std::string &type, size_t size) {
    assert(!PyErr_Occurred());
    int result = 0;
    double exec_time = -1.0;
    ExecClock exec_clock;
    PyObject *p_tuple = Python_Cpp_Homogeneous_Containers::py_tuple_new(size);
    PyObject *op = NULL;
    if (p_tuple) {
        for (size_t i = 0; i < size; ++i) {
            op = Python_Cpp_Homogeneous_Containers::py_float_from_double(static_cast<double>(i));
            if (!op) {
                // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                // e.g. tupledealloc(): https://github.com/python/cpython/blob/main/Objects/tupleobject.c#L268
                PyErr_Format(PyExc_ValueError, "Value of can not be converted.");
                result |= 1;
                goto except;
            }
            // This usually wraps a void function, always succeeds.
            if (Python_Cpp_Homogeneous_Containers::py_tuple_set(p_tuple, i, op)) { // Stolen reference.
                PyErr_Format(PyExc_RuntimeError, "Can not set unary value.");
                result |= 1 << 1;
                goto except;
            }
        }
    } else {
        PyErr_Format(PyExc_ValueError, "Can not create Python container of size %ld", size);
        result |= 1 << 2;
        goto except;
    }
    exec_time = exec_clock.seconds();
    assert(!PyErr_Occurred());
    assert(p_tuple);
    goto finally;
except:
    assert(PyErr_Occurred());
finally:
    Py_XDECREF(p_tuple);
    REPORT_TEST_OUTPUT;
    return result;
}

int test_memory_py_dict(TestResultS &test_results, const std::string &type, size_t size) {
    assert(!PyErr_Occurred());
    int result = 0;
    double exec_time = -1.0;
    ExecClock exec_clock;
    PyObject *p_container = PyDict_New();
    PyObject *py_k = NULL;
    PyObject *py_v = NULL;
    if (p_container) {
        for (size_t i = 0; i < size; ++i) {
            py_k = Python_Cpp_Homogeneous_Containers::py_float_from_double(static_cast<double>(i));
            if (! py_k) {
                // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                PyErr_Format(PyExc_ValueError, "C++ key of can not be converted.");
                goto except;
            }
            py_v = Python_Cpp_Homogeneous_Containers::py_float_from_double(static_cast<double>(i));
            if (! py_v) {
                // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                PyErr_Format(PyExc_ValueError, "C++ value of can not be converted.");
                goto except;
            }
            if (PyDict_SetItem(p_container, py_k, py_v)) {
                // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                PyErr_Format(PyExc_ValueError, "Can not set an item in the Python dict.");
                goto except;
            }
            // Oh this is nasty.
            // PyDict_SetItem() increfs the key and the value rather than stealing a reference.
            // insertdict(): https://github.com/python/cpython/blob/main/Objects/dictobject.c#L1074
            Py_DECREF(py_k);
            Py_DECREF(py_v);
        }
    } else {
        PyErr_Format(PyExc_ValueError, "Can not create Python container of size %ld", size);
        result |= 1 << 2;
        goto except;
    }
    exec_time = exec_clock.seconds();
    assert(!PyErr_Occurred());
    assert(p_container);
    goto finally;
except:
    assert(PyErr_Occurred());
finally:
    Py_XDECREF(p_container);
    REPORT_TEST_OUTPUT;
    return result;
}

// Similar to test_perf_vector_string_to_py_tuple()
// This is a long running test.
// min/max are inclusive.
int test_memory_vector_string_to_py_tuple(TestResultS &test_results, size_t str_len_min, size_t str_len_max,
                                          size_t size_min, size_t size_max) {
    int result = 0;
    for (size_t str_len = str_len_min; str_len <= str_len_max; str_len *= 2) {
        for (size_t size = size_min; size <= size_max; size *= 2) {
            result |= test_vector_string_to_py_tuple(test_results, size, str_len);
        }
    }
    return result;
}

// Similar to test_perf_py_tuple_string_to_vector()
// This is a long running test.
// min/max are inclusive.
int test_memory_py_tuple_string_to_vector(TestResultS &test_results, size_t str_len_min, size_t str_len_max,
                                        size_t size_min, size_t size_max) {
    int result = 0;
    for (size_t str_len = str_len_min; str_len <= str_len_max; str_len *= 2) {
        for (size_t size = size_min; size <= size_max; size *= 2) {
            result |= test_py_tuple_string_to_vector(test_results, size, str_len);
        }
    }
    return result;
}


void test_memory_all(TestResultS &test_results) {
    RSSSnapshot rss_overall("==== test_memory.cpp");
    {
        for (int i = 0; i < 10; ++i) {
            RSSSnapshot rss("test_memory_py_tuple");
            // Running this on its own give the following memory profile, values in MB and the delta:
            // Start, Python initialised:                        3.0
            // Start of test_memory_py_tuple():                  3.0
            // Before Py_XDECREF in test_memory_py_tuple():    117.7   +114.7
            // After Py_XDECREF in test_memory_py_tuple():       7.0   -110.7
            // Prior to Py_FinalizeEx()                          7.1     +0.1
            // After Py_FinalizeEx()                             6.1     -1.0
            //
            // Python floats are 24 bytes so 24MB allocated/deallocated.
            // Repeating this 1000 times gives the identical memory profile.
            test_memory_py_tuple(test_results, "<double>", 1 << 20);
            std::cout << rss << std::endl;
        }
    }
    {
        for (int i = 0; i < 10; ++i) {
            RSSSnapshot rss("test_memory_py_dict");
            // Running this on its own give the following memory profile, values in MB and the delta:
            // Start, Python initialised:                        3.1
            // Start of test_memory_py_dict():                   3.1
            // Before Py_XDECREF in test_memory_py_dict():      43.6    +40.6
            // After Py_XDECREF in test_memory_py_dict():       15.2    -28.4
            // Prior to Py_FinalizeEx()                         15.2
            // After Py_FinalizeEx()                            13.9     -1.3
            //
            // Python floats are 24 bytes so 24MB allocated/deallocated.
            // Repeating this 1000 times gives the identical memory profile.
            test_memory_py_dict(test_results, "<double>", 1 << 20);
            std::cout << rss << std::endl;
        }
    }
    {
        for (int i = 0; i < 100; ++i) {
            RSSSnapshot rss("test_memory_vector_string_to_py_tuple(1024, 2048, 512, 1<<16)");
            test_memory_vector_string_to_py_tuple(test_results, 1024, 2048, 512, 1 << 16);
            std::cout << rss << std::endl;
        }
    }
    std::cout << "====" << rss_overall << std::endl;
}
