#include <iostream>

#include <Python.h>

#include "python_convert.h"

void test_vector_double_to_py_tuple() {
    std::cout << "Starting: " << __FUNCTION__ << "()" << std::endl;
    size_t SIZE = 3;
    std::vector<double> cpp_vector;
    for (size_t i = 0; i < SIZE; ++i) {
        cpp_vector.push_back(static_cast<double>(i));
    }
    PyObject *op = Python_Cpp_Homogeneous_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    assert(op);
    assert(PyTuple_CheckExact(op));
    assert((unsigned long)PyTuple_Size(op) == cpp_vector.size());
    for (size_t i = 0; i < SIZE; ++i) {
        double value = PyFloat_AsDouble(PyTuple_GetItem(op, i));
        assert(value == cpp_vector[i]);
    }
    Py_DECREF(op);
    std::cout << "    Done: " << __FUNCTION__ << "()" << std::endl;
}

void test_vector_long_to_py_tuple() {
    std::cout << "Starting: " << __FUNCTION__ << "()" << std::endl;
    size_t SIZE = 3;
    std::vector<long> cpp_vector;
    for (size_t i = 0; i < SIZE; ++i) {
        cpp_vector.push_back(static_cast<long>(i));
    }
    PyObject *op = Python_Cpp_Homogeneous_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
    assert(op);
    assert(PyTuple_CheckExact(op));
    assert((unsigned long)PyTuple_Size(op) == cpp_vector.size());
    for (size_t i = 0; i < SIZE; ++i) {
        long value = PyLong_AsLong(PyTuple_GetItem(op, i));
        assert(value == cpp_vector[i]);
    }
    Py_DECREF(op);
    std::cout << "    Done: " << __FUNCTION__ << "()" << std::endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    Py_Initialize();

    test_vector_double_to_py_tuple();
    test_vector_long_to_py_tuple();
    return 0;
}
