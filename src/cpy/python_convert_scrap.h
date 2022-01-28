//
// Created by Paul Ross on 26/01/2022.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONVER_SCRAP_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONVER_SCRAP_H

#include <Python.h>

#include <map>
#include <unordered_map>

//#include "python_convert.h"

/// Conversion functions for individual Python objects.
#include "python_object_convert.h"
/// Functions to handle Python containers.
//#include "python_container_convert.h"


namespace Python_Cpp_Containers {

    // C++ to Python
    // was generic_cpp_std_unordered_map_to_py_dict
    template<
            template<typename ...> class Map,
            typename K,
            typename V,
            PyObject *(*Convert_K)(const K &),
            PyObject *(*Convert_V)(const V &)
    >
    PyObject *
    generic_cpp_std_map_like_to_py_dict(const Map<K, V> &map) {
        PyObject *ret = PyDict_New();
        PyObject *py_k = NULL;
        PyObject *py_v = NULL;
        if (ret) {
            for (const auto &k_v: map) {
                py_k = (*Convert_K)(k_v.first);
                // NOTE: py_k->ob_refcnt may NOT be 1 for interned values.
                if (!py_k) {
                    // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                    PyErr_Format(PyExc_ValueError, "C++ key of can not be converted.");
                    goto except;
                }
                py_v = (*Convert_V)(k_v.second);
                // NOTE: py_v->ob_refcnt may NOT be 1 for interned values.
                if (!py_v) {
                    // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                    // However, we do need to decref the key as it has not been allocated to the dict.
                    Py_DECREF(py_k);
                    PyErr_Format(PyExc_ValueError, "C++ value of can not be converted.");
                    goto except;
                }
                if (PyDict_SetItem(ret, py_k, py_v)) {
                    // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                    // However, we do need to decref the key and the value as they have not been allocated to the dict.
                    Py_DECREF(py_k);
                    Py_DECREF(py_v);
                    PyErr_Format(PyExc_ValueError, "Can not set an item in the Python dict.");
                    goto except;
                }
                // Oh this is nasty.
                // PyDict_SetItem() increfs the key and the value rather than stealing a reference.
                // insertdict(): https://github.com/python/cpython/blob/main/Objects/dictobject.c#L1074
                // What is more we can NOT compare before and after refcounts, such as with an assert, as, with
                // interned values, if a context switch happens in PyDict_SetItem (is that possible?)
                // another thread may increment/decrement the interned values reference count unknown to us.
                // It is a mystery why this happens with dicts but not other containers.
                Py_DECREF(py_k);
                Py_DECREF(py_v);
            }
        } else {
            PyErr_Format(PyExc_ValueError, "Can not create Python dict");
            goto except;
        }
        assert(!PyErr_Occurred());
        goto finally;
    except:
        assert(PyErr_Occurred());
        Py_XDECREF(py_k);
        Py_XDECREF(py_v);
    finally:
        return ret;
    }

    // Base declaration
    template<template<typename ...> class Map, typename K, typename V>
    PyObject *
    cpp_std_map_like_to_py_dict(const std::unordered_map<K, V> &map);

    // Concrete instantiation for std::unordered_map<long, long>
    template<>
    PyObject *
    cpp_std_map_like_to_py_dict<std::unordered_map, long, long>(const std::unordered_map<long, long> &map) {
        return generic_cpp_std_map_like_to_py_dict<
                std::unordered_map,
                long, long,
                &cpp_long_to_py_long, &cpp_long_to_py_long
        >(map);
    }

    // Base declaration for std::map
    template<template<typename ...> class Map, typename K, typename V>
    PyObject *
    cpp_std_map_like_to_py_dict(const std::map<K, V> &map);

    // Concrete instantiation for std::map<long, long>
    template<>
    PyObject *
    cpp_std_map_like_to_py_dict<std::map, long, long>(const std::map<long, long> &map) {
        return generic_cpp_std_map_like_to_py_dict<
                std::map,
                long, long,
                &cpp_long_to_py_long, &cpp_long_to_py_long
        >(map);
    }

    // Python to C++
    // Was generic_py_dict_to_cpp_std_unordered_map
    template<
            template<typename ...> class Map,
            typename K,
            typename V,
            int (*Check_K)(PyObject *),
            int (*Check_V)(PyObject *),
            K (*Convert_K)(PyObject *),
            V (*Convert_V)(PyObject *)
    >
    int generic_py_dict_to_cpp_std_map_like(PyObject *dict, Map<K, V> &map) {
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

    // Base declaration for std::unordered_map
    template<template<typename ...> class Map, typename K, typename V>
    int
    py_dict_to_cpp_std_map_like(PyObject *op, std::unordered_map<K, V> &map);

    // Concrete instantiation for std::unordered_map<long, long>
    template<>
    int
    py_dict_to_cpp_std_map_like<std::unordered_map, long, long>(PyObject *op, std::unordered_map<long, long> &map) {
        return generic_py_dict_to_cpp_std_map_like<
                std::unordered_map,
                long, long,
                &py_long_check, &py_long_check,
                &py_long_to_cpp_long, &py_long_to_cpp_long
        >(op, map);
    }

    // Base declaration for std::map
    template<template<typename ...> class Map, typename K, typename V>
    int
    py_dict_to_cpp_std_map_like(PyObject *op, std::map<K, V> &map);

    // Concrete instantiation for std::map<long, long>
    template<>
    int
    py_dict_to_cpp_std_map_like<std::map, long, long>(PyObject *op, std::map<long, long> &map) {
        return generic_py_dict_to_cpp_std_map_like<
                std::map,
                long, long,
                &py_long_check, &py_long_check,
                &py_long_to_cpp_long, &py_long_to_cpp_long
        >(op, map);
    }

} //namespace Python_Cpp_Containers

#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONVER_SCRAP_H
