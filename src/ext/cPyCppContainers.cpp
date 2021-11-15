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
        for(auto &key_value: dict) {
            key_value.second += 1;
        }
        return cpp_std_unordered_map_to_py_dict(dict);
    }
    return NULL;
}

/**
 * Create a new list of T by copying into a vector and back.
 *
 * @param arg The Python list. This is const.
 * @return A new Python list of T.
 */
template<typename T>
static PyObject *
new_list(PyObject *arg) {
    std::vector<T> vec;
    if (!py_list_to_cpp_std_vector(arg, vec)) {
        return cpp_std_vector_to_py_list(vec);
    }
    return NULL;
}

/**
 * Create a new list of floats by copying into a vector and back.
 *
 * @param arg The Python list. This is const.
 * @return A new Python list of float.
 */
static PyObject *
new_list_float(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<double>(arg);
}

static PyObject *
new_list_bool(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<bool>(arg);
}

static PyObject *
new_list_int(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<long>(arg);
}

static PyObject *
new_list_bytes(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::string>(arg);
}


#if 0
/*
 * Note how this works in C++ compilation (linker fails)
 * However setup.py works just fine but this gives an ImportError with Symbol not found.
 * This need documenting.
 * C++ linker failure:
Undefined symbols for architecture x86_64:
  "_object* Python_Cpp_Containers::cpp_std_vector_to_py_list<unsigned int>(std::__1::vector<unsigned int, std::__1::allocator<unsigned int> > const&)", referenced from:
      new_list_unsigned_int(_object*, _object*) in cPyCppContainers.cpp.o
  "int Python_Cpp_Containers::py_list_to_cpp_std_vector<unsigned int>(_object*, std::__1::vector<unsigned int, std::__1::allocator<unsigned int> >&)", referenced from:
      new_list_unsigned_int(_object*, _object*) in cPyCppContainers.cpp.o
ld: symbol(s) not found for architecture x86_64

 Failure in Python:
>>> import cPyCppContainers
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ImportError: dlopen(/Users/engun/CLionProjects/PythonCppHomogeneousContainers/cPyCppContainers.cpython-39-darwin.so, 2): Symbol not found: __ZN21Python_Cpp_Containers25cpp_std_vector_to_py_listIjEEP7_objectRKNSt3__16vectorIT_NS3_9allocatorIS5_EEEE
  Referenced from: /Users/engun/CLionProjects/PythonCppHomogeneousContainers/cPyCppContainers.cpython-39-darwin.so
  Expected in: flat namespace
 in /Users/engun/CLionProjects/PythonCppHomogeneousContainers/cPyCppContainers.cpython-39-darwin.so
*/
static PyObject *
new_list_unsigned_int(PyObject *Py_UNUSED(module), PyObject *arg) {
    std::vector<unsigned int> vec;
    if (!py_list_to_cpp_std_vector(arg, vec)) {
        return cpp_std_vector_to_py_list(vec);
    }
    return NULL;
}
#endif

/**
 * Create a new dict of [K, V]] by copying into a std::unordered_map and back.
 *
 * @param arg The Python dict. This is const.
 * @return A new Python dict of [K, V].
 */
template<typename K, typename V>
static PyObject *
new_dict(PyObject *arg) {
    std::unordered_map<K, V> map;
    if (!py_dict_to_cpp_std_unordered_map(arg, map)) {
        return cpp_std_unordered_map_to_py_dict(map);
    }
    return NULL;
}

/**
 * Create a new dict of [int, int] by copying into a std::unordered_map and back.
 *
 * @param arg The Python dict. This is const.
 * @return A new Python dict of [int, int].
 */
static PyObject *
new_dict_int_int(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<long, long>(arg);
}

/**
 * Create a new dict of [float, float] by copying into a std::unordered_map and back.
 *
 * @param arg The Python dict. This is const.
 * @return A new Python dict of [float, float].
 */
static PyObject *
new_dict_float_float(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<double, double>(arg);
}

static PyObject *
new_dict_bytes_bytes(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::string, std::string>(arg);
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
        /* Copying functions. */
        /* Lists. */
        {"new_list_float", new_list_float, METH_O,
                "Take a list of floats and return a new list with the same values."},
        {"new_list_bool", new_list_bool, METH_O,
                "Take a list of booleans and return a new list with the same values."},
        {"new_list_int", new_list_int, METH_O,
                "Take a list of ints and return a new list with the same values."},
        {"new_list_bytes", new_list_bytes, METH_O,
                "Take a list of ints and return a new list with the same values."},
#if 0
        // Example of failure as there is no template new_list<unsigned int>(arg)
        {"new_list_unsigned_int", new_list_unsigned_int, METH_O,
                "Take a list of unsigned ints and return a new list with the same values."},
#endif
        /* dicts */
        {"new_dict_int_int", new_dict_int_int, METH_O,
                "Take a dict of [int, int] and return a new dict with the same values."},
        {"new_dict_float_float", new_dict_float_float, METH_O,
                "Take a dict of [float, float] and return a new dict with the same values."},
        {"new_dict_bytes_bytes", new_dict_bytes_bytes, METH_O,
                "Take a dict of [bytes, bytes] and return a new dict with the same values."},
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

