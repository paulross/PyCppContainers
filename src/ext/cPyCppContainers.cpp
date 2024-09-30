/**
 * Created by Paul Ross on 18/06/2021.
 */
#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include "structmember.h"

#include "cpy/python_convert.h"

using namespace Python_Cpp_Containers;

static PyObject *
new_bytes(PyObject *Py_UNUSED(module), PyObject *arg) {
    if (py_bytes_check(arg)) {
        std::vector<char> vec = py_bytes_to_cpp_vector_char(arg);
        return cpp_vector_char_to_py_bytes(vec);
    }
    return NULL;
}


static PyObject *
new_str(PyObject *Py_UNUSED(module), PyObject *arg) {
    if (py_unicode8_check(arg)) {
        std::string vec = py_unicode8_to_cpp_string(arg);
        return cpp_string_to_py_unicode8(vec);
    }
    return NULL;
}

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
    // py_list_to_cpp_std_list_like() will return non-zero if the Python
    // argument can not be converted to a std::vector<double>
    // and a Python exception will be set.
    if (!py_list_to_cpp_std_list_like(arg, vec)) {
        // Double the values in pure C++ code.
        vector_double_x2(vec);
        // cpp_std_list_like_to_py_list() returns NULL on failure
        // and a Python exception will be set.
        return cpp_std_list_like_to_py_list(vec);
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
    std::vector<std::vector<char>> vec;
    if (!py_tuple_to_cpp_std_list_like(arg, vec)) {
        return cpp_std_list_like_to_py_tuple(reverse_vector(vec));
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
    std::unordered_map<std::vector<char>, long> dict;
    if (!py_dict_to_cpp_std_map_like(arg, dict)) {
        for(auto &key_value: dict) {
            key_value.second += 1;
        }
        return cpp_std_map_like_to_py_dict(dict);
    }
    return NULL;
}

/**
 * Create a new list of T by copying into a vector and back.
 *
 * @param arg The Python list. This is const.
 * @return A new Python list of T.
 */
template<template<typename ...> class List, typename T>
static PyObject *
new_list(PyObject *arg) {
    List<T> vec;
    if (!py_list_to_cpp_std_list_like(arg, vec)) {
        return cpp_std_list_like_to_py_list(vec);
    }
    return NULL;
}

/**
 * Create a new list of bools by copying into a vector and back.
 *
 * @param arg The Python list. This is const.
 * @return A new Python list of bool.
 */
static PyObject *
new_list_vector_bool(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::vector, bool>(arg);
}

static PyObject *
new_list_vector_float(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::vector, double>(arg);
}

static PyObject *
new_list_vector_int(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::vector, long>(arg);
}

static PyObject *
new_list_vector_complex(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::vector, std::complex<double>>(arg);
}

static PyObject *
new_list_vector_bytes(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::vector, std::vector<char>>(arg);
}

static PyObject *
new_list_vector_str(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::vector, std::string>(arg);
}

static PyObject *
new_list_vector_str16(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::vector, std::u16string>(arg);
}

static PyObject *
new_list_vector_str32(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::vector, std::u32string>(arg);
}

static PyObject *
new_list_list_bool(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::list, bool>(arg);
}

static PyObject *
new_list_list_float(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::list, double>(arg);
}

static PyObject *
new_list_list_int(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::list, long>(arg);
}

static PyObject *
new_list_list_complex(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::list, std::complex<double>>(arg);
}

static PyObject *
new_list_list_bytes(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::list, std::vector<char>>(arg);
}

static PyObject *
new_list_list_str(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::list, std::string>(arg);
}

static PyObject *
new_list_list_str16(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::list, std::u16string>(arg);
}

static PyObject *
new_list_list_str32(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_list<std::list, std::u32string>(arg);
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
    if (!py_list_to_cpp_std_list_like(arg, vec)) {
        return cpp_std_list_like_to_py_list(vec);
    }
    return NULL;
}
#endif
/**
 * Create a new set of [K] by copying into a std::unordered_set and back.
 *
 * @param arg The Python set. This is const.
 * @return A new Python set of [K].
 */
template<typename K>
static PyObject *
new_set(PyObject *arg) {
    std::unordered_set<K> cpp_set;
    if (!py_set_to_cpp_std_unordered_set(arg, cpp_set)) {
        return cpp_std_unordered_set_to_py_set(cpp_set);
    }
    return NULL;
}

/**
 * Create a new set of [int] by copying into a std::unordered_set and back.
 *
 * @param arg The Python set. This is const.
 * @return A new Python set of [int].
 */
static PyObject *
new_set_int(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_set<long>(arg);
}

/**
 * Create a new set of [float] by copying into a std::unordered_set and back.
 *
 * @param arg The Python set. This is const.
 * @return A new Python set of [float].
 */
static PyObject *
new_set_float(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_set<double>(arg);
}

/**
 * Create a new set of [complex] by copying into a std::unordered_set and back.
 *
 * @param arg The Python set. This is const.
 * @return A new Python set of [complex].
 */
static PyObject *
new_set_complex(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_set<std::complex<double>>(arg);
}

/**
 * Create a new set of [bytes] by copying into a std::unordered_set and back.
 *
 * @param arg The Python set. This is const.
 * @return A new Python set of [bytes].
 */
static PyObject *
new_set_bytes(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_set<std::vector<char>>(arg);
}

/**
 * Create a new set of str by copying into a \c std::unordered_set and back.
 *
 * @param arg The Python set. This is const.
 * @return A new Python set of [str].
 */
static PyObject *
new_set_str(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_set<std::string>(arg);
}

/**
 * Create a new set of str with 16 bit characters by copying into a \c std::unordered_set and back.
 *
 * @param arg The Python set. This is const.
 * @return A new Python set of str16.
 */
static PyObject *
new_set_str16(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_set<std::u16string>(arg);
}

/**
 * Create a new set of str with 32 bit characters by copying into a \c std::unordered_set and back.
 *
 * @param arg The Python set. This is const.
 * @return A new Python set of str32.
 */
static PyObject *
new_set_str32(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_set<std::u32string>(arg);
}

/**
 * Create a new frozenset of [K] by copying into a \c std::unordered_set and back.
 *
 * @param arg The Python set. This is const.
 * @return A new Python frozenset of [K].
 */
template<typename K>
static PyObject *
new_frozenset(PyObject *arg) {
    std::unordered_set<K> cpp_set;
    if (!py_frozenset_to_cpp_std_unordered_set(arg, cpp_set)) {
        return cpp_std_unordered_set_to_py_frozenset(cpp_set);
    }
    return NULL;
}

/**
 * Create a new frozenset of [int] by copying into a std::unordered_set and back.
 *
 * @param arg The Python frozenset. This is const.
 * @return A new Python frozenset of [int].
 */
static PyObject *
new_frozenset_int(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_frozenset<long>(arg);
}

/**
 * Create a new frozenset of [float] by copying into a std::unordered_set and back.
 *
 * @param arg The Python frozenset. This is const.
 * @return A new Python frozenset of [float].
 */
static PyObject *
new_frozenset_float(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_frozenset<double>(arg);
}

/**
 * Create a new frozenset of [complex] by copying into a std::unordered_set and back.
 *
 * @param arg The Python frozenset. This is const.
 * @return A new Python frozenset of [complex].
 */
static PyObject *
new_frozenset_complex(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_frozenset<std::complex<double>>(arg);
}

/**
 * Create a new frozenset of [bytes] by copying into a std::unordered_set and back.
 *
 * @param arg The Python frozenset. This is const.
 * @return A new Python frozenset of [bytes].
 */
static PyObject *
new_frozenset_bytes(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_frozenset<std::vector<char>>(arg);
}

/**
 * Create a new frozenset of [str] by copying into a std::unordered_set and back.
 *
 * @param arg The Python frozenset. This is const.
 * @return A new Python frozenset of [str].
 */
static PyObject *
new_frozenset_str(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_frozenset<std::string>(arg);
}

/**
 * Create a new dict of [K, V] by copying into a std::unordered_map and back.
 *
 * @param arg The Python dict. This is const.
 * @return A new Python dict of [K, V].
 */
template<template<typename ...> class Map, typename K, typename V>
static PyObject *
new_dict(PyObject *arg) {
    Map<K, V> map;
    if (!py_dict_to_cpp_std_map_like(arg, map)) {
        return cpp_std_map_like_to_py_dict(map);
    }
    return NULL;
}

static PyObject *
new_dict_from_std_unordered_map_int_int(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::unordered_map, long, long>(arg);
}

static PyObject *
new_dict_from_std_unordered_map_float_float(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::unordered_map, double, double>(arg);
}

static PyObject *
new_dict_from_std_unordered_map_complex_complex(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::unordered_map, std::complex<double>, std::complex<double>>(arg);
}

static PyObject *
new_dict_from_std_unordered_map_bytes_bytes(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::unordered_map, std::vector<char>, std::vector<char>>(arg);
}

static PyObject *
new_dict_from_std_unordered_map_str_str(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::unordered_map, std::string, std::string>(arg);
}

static PyObject *
new_dict_from_std_unordered_map_str16_str16(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::unordered_map, std::u16string, std::u16string>(arg);
}

static PyObject *
new_dict_from_std_unordered_map_str32_str32(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::unordered_map, std::u32string, std::u32string>(arg);
}

static PyObject *
new_dict_from_std_unordered_map_int_str(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::unordered_map, long, std::string>(arg);
}

static PyObject *
new_dict_from_std_unordered_map_int_str16(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::unordered_map, long, std::u16string>(arg);
}

static PyObject *
new_dict_from_std_unordered_map_int_str32(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::unordered_map, long, std::u32string>(arg);
}

static PyObject *
new_dict_from_std_map_int_int(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::map, long, long>(arg);
}

static PyObject *
new_dict_from_std_map_float_float(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::map, double, double>(arg);
}

static PyObject *
new_dict_from_std_map_complex_complex(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::map, std::complex<double>, std::complex<double>>(arg);
}

static PyObject *
new_dict_from_std_map_bytes_bytes(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::map, std::vector<char>, std::vector<char>>(arg);
}

static PyObject *
new_dict_from_std_map_str_str(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::map, std::string, std::string>(arg);
}

static PyObject *
new_dict_from_std_map_str16_str16(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::map, std::u16string, std::u16string>(arg);
}

static PyObject *
new_dict_from_std_map_str32_str32(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::map, std::u32string, std::u32string>(arg);
}

static PyObject *
new_dict_from_std_map_int_str(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::map, long, std::string>(arg);
}

static PyObject *
new_dict_from_std_map_int_str16(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::map, long, std::u16string>(arg);
}

static PyObject *
new_dict_from_std_map_int_str32(PyObject *Py_UNUSED(module), PyObject *arg) {
    return new_dict<std::map, long, std::u32string>(arg);
}

/**
 * Create a new dict of [K, V]] by copying into a std::unordered_map.
 *
 * @param arg The Python dict. This is const.
 * @return None.
 */
template<typename K, typename V>
static PyObject *
new_dict_debug(PyObject *arg) {
    std::unordered_map<K, V> map;
    if (!py_dict_to_cpp_std_unordered_map(arg, map)) {
        Py_RETURN_NONE;
    }
    return NULL;
}

static PyObject *
new_dict_debug_int_int(PyObject *Py_UNUSED(module), PyObject *arg) {
//    return new_dict_debug<long, long>(arg);
    std::unordered_map<long, long> map;
    PyObject *key, *value;
    Py_ssize_t pos = 0;

    while (PyDict_Next(arg, &pos, &key, &value)) {
        if (!py_long_check(key)) {
            return NULL;
        }
        if (!py_long_check(value)) {
            return NULL;
        }
        map[py_long_to_cpp_long(key)] = py_long_to_cpp_long(value);
    }
    Py_RETURN_NONE;
}

static PyObject *
new_dict_debug_float_float(PyObject *Py_UNUSED(module), PyObject *dict) {
//    // Slow, O(N**2)
//    return new_dict_debug<double, double>(arg);

//    // Fast, O(N)
//    std::unordered_map<double, double> map;
//    PyObject *key, *value;
//    Py_ssize_t pos = 0;
//
//    while (PyDict_Next(arg, &pos, &key, &value)) {
//        if (!py_float_check(key)) {
//            return NULL;
//        }
//        if (!py_float_check(value)) {
//            return NULL;
//        }
//        map[py_float_to_cpp_double(key)] = py_float_to_cpp_double(value);
//    }
//    Py_RETURN_NONE;

    PyObject *ret;
    std::unordered_map<double, double> map;
    PyObject *key = NULL;
    PyObject *val = NULL;
    Py_ssize_t pos = 0;

    Py_INCREF(dict); // Borrowed reference
    if (!PyDict_Check(dict)) {
        PyErr_Format(PyExc_ValueError, "Python object must be a dict not a %s", dict->ob_type->tp_name);
        ret = NULL;
        goto except;
    }
//    // This is the line that causes the performance cost.
//    map.reserve(PyDict_Size(dict));
    while (PyDict_Next(dict, &pos, &key, &val)) {
        // key, val are borrowed references.
        if (!py_float_check(key)) {
            PyErr_Format(PyExc_ValueError, "Python dict key is wrong type of: %s", key->ob_type->tp_name);
            ret = NULL;
            goto except;
        }
        if (!py_float_check(val)) {
            PyErr_Format(PyExc_ValueError, "Python dict value is wrong type of: %s", val->ob_type->tp_name);
            ret = NULL;
            goto except;
        }
        map[py_float_to_cpp_double(key)] = py_float_to_cpp_double(val);
        // Check !PyErr_Occurred() which could never happen as we check first.
    }
    Py_INCREF(Py_None);
    ret = Py_None;
    assert(map.size() == static_cast<size_t>(PyDict_Size(dict)));
    assert(!PyErr_Occurred());
    goto finally;
except:
    map.clear();
    assert(PyErr_Occurred());
finally:
    Py_DECREF(dict); // Borrowed reference
    return ret;
}


#define SINGLE_ARGUMENT_METHOD(name, doc) { #name, name, METH_O, doc }

/**
 * The Python Extension methods.
 */
static PyMethodDef cPyCppContainersMethods[] = {
        SINGLE_ARGUMENT_METHOD(new_bytes, "Take a bytes and return a new str object."),
//        {"new_bytes", new_bytes, METH_O,
//                "Take a bytes and return a new str object."},
        {"new_str", new_str, METH_O,
                "Take a str and return a new str object."},
        {"list_x2", list_x2, METH_O,
                "Take a list of floats and return a new list with the values doubled."},
        {"tuple_reverse", tuple_reverse, METH_O,
                "Take a tuple of bytes and return a new tuple reversed."},
        {"dict_inc", dict_inc, METH_O,
                "Take a Python dict[bytes, int] and return a new dict with the values incremented by 1."},
        /* Copying functions. */
        /* Lists. */
        {"new_list_vector_float", new_list_vector_float, METH_O,
                "Take a list of floats and return a new list with the same values via a std::vector."},
        {"new_list_vector_bool", new_list_vector_bool, METH_O,
                "Take a list of booleans and return a new list with the same values via a std::vector."},
        {"new_list_vector_int", new_list_vector_int, METH_O,
                "Take a list of ints and return a new list with the same values via a std::vector."},
        {"new_list_vector_complex", new_list_vector_complex, METH_O,
                "Take a list of complex numbers and return a new list with the same values via a std::vector."},
        {"new_list_vector_bytes", new_list_vector_bytes, METH_O,
                "Take a list of bytes and return a new list with the same values via a std::vector."},
        {"new_list_vector_str", new_list_vector_str, METH_O,
                "Take a list of str and return a new list with the same values via a std::vector."},
        {"new_list_vector_str16", new_list_vector_str16, METH_O,
                "Take a list of str (16 bit characters) and return a new list with the same values via a std::vector."},
        {"new_list_vector_str32", new_list_vector_str32, METH_O,
                "Take a list of str (32 bit characters) and return a new list with the same values via a std::vector."},
        {"new_list_list_float", new_list_list_float, METH_O,
                "Take a list of floats and return a new list with the same values via a std::list."},
        {"new_list_list_bool", new_list_list_bool, METH_O,
                "Take a list of booleans and return a new list with the same values via a std::list."},
        {"new_list_list_int", new_list_list_int, METH_O,
                "Take a list of ints and return a new list with the same values via a std::list."},
        {"new_list_list_complex", new_list_list_complex, METH_O,
                "Take a list of complex numbers and return a new list with the same values via a std::list."},
        {"new_list_list_bytes", new_list_list_bytes, METH_O,
                "Take a list of bytes and return a new list with the same values via a std::list."},
        {"new_list_list_str", new_list_list_str, METH_O,
                "Take a list of str and return a new list with the same values via a std::list."},
        {"new_list_list_str16", new_list_list_str16, METH_O,
                "Take a list of str with 16 bit characters and return a new list with the same values via a std::list."},
        {"new_list_list_str32", new_list_list_str32, METH_O,
                "Take a list of str with 16 bit characters and return a new list with the same values via a std::list."},
        /* Sets. */
        {"new_set_int", new_set_int, METH_O,
                "Take a set of ints and return a new set with the same values."},
        {"new_set_float", new_set_float, METH_O,
                "Take a set of floats and return a new set with the same values."},
        {"new_set_complex", new_set_complex, METH_O,
                "Take a set of complex numbers and return a new set with the same values."},
        {"new_set_bytes", new_set_bytes, METH_O,
                "Take a set of bytes and return a new set with the same values."},
        {"new_set_str", new_set_str, METH_O,
                "Take a set of str and return a new set with the same values."},
        {"new_set_str16", new_set_str16, METH_O,
                "Take a set of str with 16 bit characters and return a new set with the same values."},
        {"new_set_str32", new_set_str32, METH_O,
                "Take a set of str with 32 bit characters and return a new set with the same values."},
        /* Frozen Sets. */
        {"new_frozenset_int", new_frozenset_int, METH_O,
                "Take a frozenset of ints and return a new frozenset with the same values."},
        {"new_frozenset_float", new_frozenset_float, METH_O,
                "Take a frozenset of floats and return a new frozenset with the same values."},
        {"new_frozenset_complex", new_frozenset_complex, METH_O,
                "Take a frozenset of complex numbers and return a new frozenset with the same values."},
        {"new_frozenset_bytes", new_frozenset_bytes, METH_O,
                "Take a frozenset of bytes and return a new frozenset with the same values."},
        {"new_frozenset_str", new_frozenset_str, METH_O,
                "Take a frozenset of str and return a new frozenset with the same values."},
#if 0
        // Example of failure as there is no template new_list<unsigned int>(arg)
        {"new_list_unsigned_int", new_list_unsigned_int, METH_O,
                "Take a list of unsigned ints and return a new list with the same values."},
#endif
        /* dicts */
        /* std::unordered_map */
        {"new_dict_from_std_unordered_map_int_int", new_dict_from_std_unordered_map_int_int, METH_O,
                "Take a dict of [int, int] using std::unordered_map and return a new dict with the same values."},
        {"new_dict_from_std_unordered_map_float_float", new_dict_from_std_unordered_map_float_float, METH_O,
                "Take a dict of [float, float] using std::unordered_map and return a new dict with the same values."},
        {"new_dict_from_std_unordered_map_complex_complex", new_dict_from_std_unordered_map_complex_complex, METH_O,
                "Take a dict of [complex, complex] using std::unordered_map and return a new dict with the same values."},
        {"new_dict_from_std_unordered_map_bytes_bytes", new_dict_from_std_unordered_map_bytes_bytes, METH_O,
                "Take a dict of [bytes, bytes] using std::unordered_map and return a new dict with the same values."},
        {"new_dict_from_std_unordered_map_str_str", new_dict_from_std_unordered_map_str_str, METH_O,
                "Take a dict of [str, str] using std::unordered_map and return a new dict with the same values."},
        {"new_dict_from_std_unordered_map_str16_str16", new_dict_from_std_unordered_map_str16_str16, METH_O,
                "Take a dict of [str16, str16] using std::unordered_map and return a new dict with the same values."},
        {"new_dict_from_std_unordered_map_str32_str32", new_dict_from_std_unordered_map_str32_str32, METH_O,
                "Take a dict of [str32, str32] using std::unordered_map and return a new dict with the same values."},
        {"new_dict_from_std_unordered_map_int_str", new_dict_from_std_unordered_map_int_str, METH_O,
                "Take a dict of [int, str] using std::unordered_map and return a new dict with the same values."},
        {"new_dict_from_std_unordered_map_int_str16", new_dict_from_std_unordered_map_int_str16, METH_O,
                "Take a dict of [int, str16] using std::unordered_map and return a new dict with the same values."},
        {"new_dict_from_std_unordered_map_int_str32", new_dict_from_std_unordered_map_int_str32, METH_O,
                "Take a dict of [int, str32] using std::unordered_map and return a new dict with the same values."},
        /* std::map */
        {"new_dict_from_std_map_int_int", new_dict_from_std_map_int_int, METH_O,
                "Take a dict of [int, int] using std::map and return a new dict with the same values."},
        {"new_dict_from_std_map_float_float", new_dict_from_std_map_float_float, METH_O,
                "Take a dict of [float, float] using std::map and return a new dict with the same values."},
        {"new_dict_from_std_map_complex_complex", new_dict_from_std_map_complex_complex, METH_O,
                "Take a dict of [complex, complex] using std::map and return a new dict with the same values."},
        {"new_dict_from_std_map_bytes_bytes", new_dict_from_std_map_bytes_bytes, METH_O,
                "Take a dict of [bytes, bytes] using std::map and return a new dict with the same values."},
        {"new_dict_from_std_map_str_str", new_dict_from_std_map_str_str, METH_O,
                "Take a dict of [str, str] using std::map and return a new dict with the same values."},
        {"new_dict_from_std_map_str16_str16", new_dict_from_std_map_str16_str16, METH_O,
                "Take a dict of [str16, str16] using std::map and return a new dict with the same values."},
        {"new_dict_from_std_map_str32_str32", new_dict_from_std_map_str32_str32, METH_O,
                "Take a dict of [str32, str32] using std::map and return a new dict with the same values."},
        {"new_dict_from_std_map_int_str", new_dict_from_std_map_int_str, METH_O,
                "Take a dict of [int, str] using std::map and return a new dict with the same values."},
        {"new_dict_from_std_map_int_str16", new_dict_from_std_map_int_str16, METH_O,
                "Take a dict of [int, str16] using std::map and return a new dict with the same values."},
        {"new_dict_from_std_map_int_str32", new_dict_from_std_map_int_str32, METH_O,
                "Take a dict of [int, str32] using std::map and return a new dict with the same values."},
        // Debug
        {"new_dict_debug_int_int", new_dict_debug_int_int, METH_O,
                "Debug a dict of [int, int]."},
        {"new_dict_debug_float_float", new_dict_debug_float_float, METH_O,
                "Debug a dict of [float, float]."},
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
    if (m == NULL) {
        return NULL;
    }
    if (
        PyModule_AddStringConstant(
                m,
                "PYTHON_CPP_CONTAINERS_VERSION",
                PYTHON_CPP_CONTAINERS_VERSION
        )
    ) {
        return NULL;
    }

    return m;
}
