//
// Created by Paul Ross on 26/01/2022.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONVER_SCRAP_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONVER_SCRAP_H

#include <Python.h>

#include <map>
#include <unordered_map>

#include "python_convert.h"

/// Conversion functions for individual Python objects.
#include "python_object_convert.h"
/// Functions to handle Python containers.
//#include "python_container_convert.h"


namespace Python_Cpp_Containers {

//template <typename, typename...> class Container
    template<
            template<typename ...> class Map,
            typename K,
            typename V,
            int (*Check_K)(PyObject *),
            int (*Check_V)(PyObject *),
            K (*Convert_K)(PyObject *),
            V (*Convert_V)(PyObject *)
    >
    int generic_py_dict_to_cpp_std_map(PyObject *dict, Map<K, V> &map) {
        int ret = 0;
        PyObject *key = NULL;
        PyObject *val = NULL;
        Py_ssize_t pos = 0;

        map.clear();
        Py_INCREF(dict); // Borrowed reference
        if (!PyDict_Check(dict)) {
            PyErr_Format(PyExc_ValueError, "Python object must be a dict not a %s", dict->ob_type->tp_name);
            ret = -1;
            goto except;
        }
        // NOTE: It might be tempting to make the following call to pre-allocate space:
        // map.reserve(PyDict_Size(dict));
        // Do NOT do this.
        // std::unordered_map<double, double>.reserve() is very slow and O(N**2) for those types.
        // Possibly with other types as well.
        while (PyDict_Next(dict, &pos, &key, &val)) {
            // key, val are borrowed references.
            if (!Check_K(key)) {
                PyErr_Format(PyExc_ValueError, "Python dict key is wrong type of: %s", key->ob_type->tp_name);
                ret = -2;
                goto except;
            }
            if (!Check_V(val)) {
                PyErr_Format(PyExc_ValueError, "Python dict value is wrong type of: %s", val->ob_type->tp_name);
                ret = -3;
                goto except;
            }
            map[Convert_K(key)] = Convert_V(val);
            // Check !PyErr_Occurred() which could never happen as we check first.
        }
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

//template <>
//int
//py_dict_to_cpp_std_map<long, long>(PyObject* op, std::unordered_map<long, long> &map);

    // Base instantiation for std::unordered_map
    template<template<typename ...> class Map, typename K, typename V>
    int
    py_dict_to_cpp_std_map(PyObject *op, std::unordered_map<K, V> &map);

    // Concrete instantiation for std::unordered_map<long, long>
    template<>
    int
    py_dict_to_cpp_std_map<std::unordered_map, long, long>(PyObject *op, std::unordered_map<long, long> &map) {
        return generic_py_dict_to_cpp_std_map<
                std::unordered_map,
                long, long,
                &py_long_check, &py_long_check,
                &py_long_to_cpp_long, &py_long_to_cpp_long
        >(op, map);
    }

    // Base instantiation for std::map
    template<template<typename ...> class Map, typename K, typename V>
    int
    py_dict_to_cpp_std_map(PyObject *op, std::map<K, V> &map);

    // Concrete instantiation for std::map<long, long>
    template<>
    int
    py_dict_to_cpp_std_map<std::map, long, long>(PyObject *op, std::map<long, long> &map) {
        return generic_py_dict_to_cpp_std_map<
                std::map,
                long, long,
                &py_long_check, &py_long_check,
                &py_long_to_cpp_long, &py_long_to_cpp_long
        >(op, map);
    }

} //namespace Python_Cpp_Containers

#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONVER_SCRAP_H
