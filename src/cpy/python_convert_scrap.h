//
// Created by Paul Ross on 26/01/2022.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONVER_SCRAP_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONVER_SCRAP_H

#include <Python.h>

#include <list>
#include <map>
#include <unordered_map>
#include <vector>

//#include "python_convert.h"

/// Conversion functions for individual Python objects.
#include "python_object_convert.h"
/// Functions to handle Python containers.
#include "python_container_convert.h"


namespace Python_Cpp_Containers {

    // ==== C++ to Python
    template<
            template<typename ...> class ListLike,
            typename T,
            PyObject *(*ConvertCppToPy)(const T &),
            PyObject *(*PyUnaryContainer_New)(size_t),
            int(*PyUnaryContainer_Set)(PyObject *, size_t, PyObject *)>
    PyObject *
    generic_cpp_std_list_like_to_py_list_like(const ListLike<T> &list_like) {
        assert(!PyErr_Occurred());
        PyObject *ret = PyUnaryContainer_New(list_like.size());
        if (ret) {
            size_t i = 0;
            for (const auto &val : list_like) {
                PyObject *op = (*ConvertCppToPy)(val);
                if (!op) {
                    // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                    // e.g. tupledealloc(): https://github.com/python/cpython/blob/main/Objects/tupleobject.c#L268
                    PyErr_Format(PyExc_ValueError, "C++ value of can not be converted.");
                    goto except;
                }
#ifndef NDEBUG
                // Refcount may well be >> 1 for interned objects.
                Py_ssize_t op_ob_refcnt = op->ob_refcnt;
#endif
                // PyUnaryContainer_Set usually wraps a void function, always succeeds returning non-zero.
                if (PyUnaryContainer_Set(ret, i++, op)) { // Stolen reference.
                    PyErr_Format(PyExc_RuntimeError, "Can not set unary value.");
                    goto except;
                }
#ifndef NDEBUG
                assert(op->ob_refcnt == op_ob_refcnt && "Reference count incremented instead of stolen.");
#endif
            }
        } else {
            PyErr_Format(PyExc_ValueError, "Can not create Python container of size %ld", vec.size());
            goto except;
        }
        assert(!PyErr_Occurred());
        assert(ret);
        goto finally;
    except:
        Py_XDECREF(ret);
        assert(PyErr_Occurred());
        ret = NULL;
    finally:
        return ret;
    }

    // ---- Python Tuples
    // Partial specialisations for std::vector to Python tuple
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_vector_to_py_tuple(const std::vector<T> &container) {
        return generic_cpp_std_list_like_to_py_list_like<std::vector, T, ConvertCppToPy, &py_tuple_new, &py_tuple_set>(container);
    }
    // Partial specialisations for std::list to Python tuple
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_to_py_tuple(const std::list<T> &container) {
        return generic_cpp_std_list_like_to_py_list_like<std::list, T, ConvertCppToPy, &py_tuple_new, &py_tuple_set>(container);
    }

    // Base declaration for std::vector -> tuple
    template<typename T>
    PyObject *
    cpp_std_list_like_to_py_tuple(const std::vector<T> &container);

    // Instantiations for vector -> tuple
    // Declaration for vector -> tuple
//    template <>
//    PyObject *
//    cpp_std_vector_to_py_tuple<long>(const std::vector<long> &container);

    // Definition for std::vector -> tuple
    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<long>(const std::vector<long> &container) {
        return generic_cpp_std_vector_to_py_tuple<long, &cpp_long_to_py_long>(container);
    }

    // Base declaration for std::list -> tuple
    template<typename T>
    PyObject *
    cpp_std_list_like_to_py_tuple(const std::list<T> &container);

    // Definition for std::list -> tuple
    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<long>(const std::list<long> &container) {
        return generic_cpp_std_list_to_py_tuple<long, &cpp_long_to_py_long>(container);
    }

    // ---- Python Lists
    // Partial specialisations for std::vector to Python list
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_vector_to_py_list(const std::vector<T> &container) {
        return generic_cpp_std_list_like_to_py_list_like<std::vector, T, ConvertCppToPy, &py_list_new, &py_list_set>(container);
    }
    // Partial specialisations for std::list to Python list
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_to_py_list(const std::list<T> &container) {
        return generic_cpp_std_list_like_to_py_list_like<std::list, T, ConvertCppToPy, &py_list_new, &py_list_set>(container);
    }

    // Base declaration for std::vector -> list
    template<typename T>
    PyObject *
    cpp_std_list_like_to_py_list(const std::vector<T> &container);

    // Instantiations for vector -> list
    // Declaration for vector -> list
//    template <>
//    PyObject *
//    cpp_std_vector_to_py_list<long>(const std::vector<long> &container);

    // Definition for std::vector -> list
    template <>
    PyObject *
    cpp_std_list_like_to_py_list<long>(const std::vector<long> &container) {
        return generic_cpp_std_vector_to_py_list<long, &cpp_long_to_py_long>(container);
    }

    // Base declaration for std::list -> list
    template<typename T>
    PyObject *
    cpp_std_list_like_to_py_list(const std::list<T> &container);

    // Definition for std::list -> list
    template <>
    PyObject *
    cpp_std_list_like_to_py_list<long>(const std::list<long> &container) {
        return generic_cpp_std_list_to_py_list<long, &cpp_long_to_py_long>(container);
    }

    // Unary Python to C++
    template<typename T,
            template<typename ...> class ListLike,
            int (*PyObject_Check)(PyObject *),
            T (*PyObject_Convert)(PyObject *),
            int(*PyUnaryContainer_Check)(PyObject *),
            Py_ssize_t(*PyUnaryContainer_Size)(PyObject *),
            PyObject *(*PyUnaryContainer_Get)(PyObject *, size_t)>
    int generic_py_unary_to_cpp_list_like(PyObject *op, ListLike<T> &list_like) {
        assert(!PyErr_Occurred());
        int ret = 0;
        list_like.clear();
        Py_INCREF(op); // Borrow reference
        if (!PyUnaryContainer_Check(op)) {
            PyErr_Format(PyExc_ValueError, "Can not convert Python container of type %s", op->ob_type->tp_name);
            ret = -1;
            goto except;
        }
        // We would like to reserve a length for vectors, we can't do that for std::list
        // Ah could we do that in the specialisation?
//        list_like.reserve(PyUnaryContainer_Size(op));
        for (Py_ssize_t i = 0; i < PyUnaryContainer_Size(op); ++i) {
            PyObject *value = PyUnaryContainer_Get(op, i);
            if (!(*PyObject_Check)(value)) {
                list_like.clear();
                PyErr_Format(
                        PyExc_ValueError,
                        "Python value of type %s can not be converted",
                        value->ob_type->tp_name
                );
                ret = -2;
                goto except;
            }
            list_like.push_back((*PyObject_Convert)(value));
            // Check !PyErr_Occurred() which could never happen as we check first.
        }
        assert(!PyErr_Occurred());
        goto finally;
    except:
        assert(PyErr_Occurred());
        list_like.clear();
    finally:
        Py_DECREF(op); // Return borrowed reference
        return ret;
    }

    // Hand crafted partial specialisations
    // Python tuple to std::vector
    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_tuple_to_cpp_std_vector(PyObject *op, std::vector<T> &vec) {
        // Specialisation to reserve vector capacity. not available for std::list
        // We only do this if op is a tuple because py_tuple_len might error.
        // generic_py_unary_to_cpp_list_like() will set an error if op is not a tuple.
        if (py_tuple_check(op)) {
            vec.reserve(py_tuple_len(op));
        }
        return generic_py_unary_to_cpp_list_like<
                std::vector, T, PyObject_Check, PyObject_Convert, &py_tuple_check, &py_tuple_len, &py_tuple_get
        >(op, vec);
    }

    // Python list to std::vector
    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_list_to_cpp_std_vector(PyObject *op, std::vector<T> &vec) {
        // Specialisation to reserve vector capacity. not available for std::list
        // We only do this if op is a list because py_list_len might error.
        // generic_py_unary_to_cpp_list_like() will set an error if op is not a tuple.
        if (py_list_check(op)) {
            vec.reserve(py_list_len(op));
        }
        return generic_py_unary_to_cpp_list_like<
                std::vector, T, PyObject_Check, PyObject_Convert, &py_list_check, &py_list_len, &py_list_get
        >(op, vec);
    }

    // Python tuple to std::list
    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_tuple_to_cpp_std_list(PyObject *op, std::list<T> &vec) {
        return generic_py_unary_to_cpp_list_like<
                std::list, T, PyObject_Check, PyObject_Convert, &py_tuple_check, &py_tuple_len, &py_tuple_get
        >(op, vec);
    }

    // Python list to std::list
    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_list_to_cpp_std_list(PyObject *op, std::list<T> &vec) {
        return generic_py_unary_to_cpp_list_like<
                std::list, T, PyObject_Check, PyObject_Convert, &py_list_check, &py_list_len, &py_list_get
        >(op, vec);
    }

    // Auto generated
    // Python to C++ std::vector
    // Base declaration
    template<typename T>
    int
    py_list_to_cpp_list_like(PyObject *op, std::vector<T> &container);
    // Instantiation declaration in .h file
//    template <>
//    int
//    py_list_to_cpp_list_like<long>(PyObject *op, std::vector<long> &container);
    // Instantiation declaration in .cpp file
    template <>
    int
    py_list_to_cpp_list_like<long>(PyObject *op, std::vector<long> &container) {
        return generic_py_list_to_cpp_list_like<long, &py_long_check, &py_long_to_cpp_long>(op, container);
    }

    // Python to C++ std::list
    // Base declaration
    template<typename T>
    int
    py_list_to_cpp_list_like(PyObject *op, std::list<T> &container);
    // Instantiation declaration in .h file
//    template <>
//    int
//    py_list_to_cpp_list_like<long>(PyObject *op, std::list<long> &container);
    // Instantiation declaration in .cpp file
    template <>
    int
    py_list_to_cpp_list_like<long>(PyObject *op, std::list<long> &container) {
        return generic_py_list_to_cpp_list_like<long, &py_long_check, &py_long_to_cpp_long>(op, container);
    }


    // ======== Dictionaries
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
