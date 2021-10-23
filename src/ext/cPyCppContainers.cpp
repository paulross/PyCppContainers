/**
 * Created by Paul Ross on 18/06/2021.
 */
#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include "structmember.h"

#include "cpy/python_convert.h"

using namespace Python_Cpp_Containers;

/**
 * Double the values of a vector in-place.
 *
 * @param vec The vector to double.
 */
static void
vector_double_x2(std::vector<double> &vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] *= 2.0;
    }
}

/**
 * Create a new list of floats with doubled values.
 *
 * @param _unused_module
 * @param arg The Python list of floats. This is const.
 * @return A new Python list of floats with the values doubled.
 */
static PyObject *
list_x2(PyObject *Py_UNUSED(module), PyObject *arg) {
    std::vector<double> vec;
    // py_list_to_cpp_std_vector() will return non-zero if the Python
    // argument can not be converted to a std::vector<double>
    // and a Python exception will be set.
    if (!py_list_to_cpp_std_vector(arg, vec)) {
        // Double the values in pure C++ code.
        vector_double_x2(vec);
        // cpp_std_vector_to_py_list() returns NULL on failure
        // and a Python exception will be set.
        return cpp_std_vector_to_py_list(vec);
    }
    return NULL;
}

/**
 * Returns a new vector reversed.
 *
 * @tparam T The type of the members of the vector.
 * @param input The vector to be reversed.
 * @return A new vector reversed.
 */
template<typename T>
static std::vector<T>
reverse_vector(const std::vector<T> &input){
    std::vector<T> output;
    for (size_t i = input.size(); i-- > 0;) {
        output.push_back(input[i]);
    }
    return output;
}

/**
 * Reverse a tuple of bytes in C++.
 *
 * @param _unused_module
 * @param arg The Python tuple of bytes to be reversed.
 * @return A new tuple of bytes reversed.
 */
static PyObject *
tuple_reverse(PyObject *Py_UNUSED(module), PyObject *arg) {
    std::vector<std::string> vec;
    if (!py_tuple_to_cpp_std_vector(arg, vec)) {
        return cpp_std_vector_to_py_tuple(reverse_vector(vec));
    }
    return NULL;
}

/**
 * Creates a new dict[bytes, int] with the values incremented by 1 in C++.
 *
 * @param _unused_module
 * @param arg The Python dictionary of [bytes, int] to increment in C++. This is const.
 * @return A new Python dict of [bytes, int] with the values incremented.
 */
static PyObject *
dict_inc(PyObject *Py_UNUSED(module), PyObject *arg) {
    std::unordered_map<std::string, long> dict;
    if (!py_dict_to_cpp_std_unordered_map(arg, dict)) {
        for(auto& key_value: dict) {
            key_value.second += 1;
        }
        return cpp_std_unordered_map_to_py_dict(dict);
    }
    return NULL;
}

/**
 * The Python Extension methods.
 */
static PyMethodDef cPyCppContainersMethods[] = {
        {"list_x2", list_x2, METH_O,
                "Take a list of floats and return a new list with the values doubled."},
        {"tuple_reverse", tuple_reverse, METH_O,
                "Take a tuple of bytes and return a new tuple reversed."},
        {"dict_inc", dict_inc, METH_O,
                "Take a Python dict[bytes, int] and return a new dict with the values incremented by 1."},
        {NULL, NULL, 0, NULL}        /* Sentinel */
};

/**
 * The Python extension definition.
 */
static struct PyModuleDef cPyCppContainersmodule = {
        PyModuleDef_HEAD_INIT,
        "cPyCppContainers",
        "Example extension module that converts Python containers to and from their C++ equivalents.",
        -1,
        cPyCppContainersMethods,
        NULL,
        NULL,
        NULL,
        NULL
};

/**
 * The Python module initialisation.
 */
PyMODINIT_FUNC
PyInit_cPyCppContainers(void) {
    PyObject *m;

    m = PyModule_Create(&cPyCppContainersmodule);
    if (m == NULL)
        return NULL;

    return m;
}

