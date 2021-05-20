//
//  python_convert.hpp
//  PythonC++
//
// This contains hand crafted conversion of C++ <-> Python containers of homogeneous types.
// These are further instantiated by auto-generated code for a specific cartesian product of types and containers.
// That product is controlled by code_gen.py
// That auto-generated file is included by #include "auto_py_convert_internal.h" at the end of this file.p
//
// Usage:
//
//
//
//  Created by Paul Ross on 22/11/2018.
//  Copyright © 2018 Paul Ross. All rights reserved.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONVERT_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONVERT_H

#include <Python.h>

#include <string>
#include <vector>
#include <unordered_map>

namespace Python_Cpp_Homogeneous_Containers {

    // Tuple wrappers around PyTuple_New, PyTuple_SET_ITEM, PyTuple_GET_ITEM
    PyObject *py_tuple_new(size_t len);
    int py_tuple_set(PyObject *tuple_p, size_t pos, PyObject *op);
    PyObject *py_tuple_get(PyObject *tuple_p, size_t pos);

    // List wrappers around PyList_New, PyList_SET_ITEM, PyList_GET_ITEM
    PyObject *py_list_new(size_t len);
    int py_list_set(PyObject *list_p, size_t pos, PyObject *op);
    PyObject *py_list_get(PyObject *list_p, size_t pos);

    // This is a hand written generic function to convert a C++ vector to a Python tuple or list.
    // The template is instantiated with a C++ type and a conversion function to create a Python object from that type.
    //
    // Example of an instantiation of this template to create a function that will convert a C++ std::vector<T> to
    // a Python tuple of T:
    //
    //    template<typename T, PyObject *(*Convert)(const T &)>
    //    PyObject *
    //    generic_cpp_std_vector_to_py_tuple(const std::vector<T> &vec) {
    //        return generic_cpp_std_vector_to_py_unary<T, Convert, &py_tuple_new, &py_tuple_set, &py_tuple_get>(vec);
    //    }
    //
    // Example of an instantiation of this template to create a function that will convert a C++ std::vector<double> to
    // a Python tuple of floats:
    //
    //     template <>
    //     PyObject *
    //     std_vector_to_py_tuple<double>(const std::vector<double> &container) {
    //         return generic_cpp_std_vector_to_py_tuple<double, &py_float_from_double>(container);
    //     }
    //
    // Partial template specialisation: Need PyTuple_New, PyTuple_GET_ITEM, PyTuple_SET_ITEM.
    // Also error messages such as 'tuple'.
    template<typename T, PyObject *(*Convert)(const T &), PyObject *(*PyUnary_New)(size_t), int(*PyUnary_Set)(
            PyObject *, size_t, PyObject *), PyObject *(*PyUnary_Get)(PyObject *, size_t)>
    PyObject *
    generic_cpp_std_vector_to_py_unary(const std::vector<T> &vec) {
        assert(!PyErr_Occurred());
        PyObject *ret = PyTuple_New(vec.size());
        if (ret) {
            for (size_t i = 0; i < vec.size(); ++i) {
                PyObject *op = (*Convert)(vec[i]);
                if (!op) {
                    // Failure, clean up
                    for (size_t j = 0; j < i; ++j) {
                        // Inspection of PyTuple_New shows that the members are NULL on construction.
                        Py_XDECREF(PyTuple_GET_ITEM(ret, j));
                    }
                    goto except;
                }
                // This is a void function, always succeeds.
                PyTuple_SET_ITEM(ret, i, op); // Stolen reference.
            }
        } else {
            PyErr_Format(PyExc_ValueError, "Can not create Python tuple of size %ld", vec.size());
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

    template<typename T, PyObject *(*Convert)(const T &)>
    PyObject *
    generic_cpp_std_vector_to_py_tuple(const std::vector<T> &vec) {
        return generic_cpp_std_vector_to_py_unary<T, Convert, &py_tuple_new, &py_tuple_set, &py_tuple_get>(vec);
    }
    
    template<typename T, PyObject *(*Convert)(const T &)>
    PyObject *
    generic_cpp_std_vector_to_py_list(const std::vector<T> &vec) {
        return generic_cpp_std_vector_to_py_unary<T, Convert, &py_list_new, &py_list_set, &py_list_get>(vec);
    }
    
    
    // This is a hand written generic function to convert a Python tuple to a C++ vector.
    // The template is instantiated with a C++ type a check function and a conversion function to create a Python object
    // to that C++ type.
    //
    // Example of an instantiation of this template to create a function that will convert a Python tuple of floats to
    // a C++ std::vector<double>:
    //
    //  template <> int
    //  py_tuple_to_std_vector<double>(PyObject *op, std::vector<double> &container) {
    //      return generic_py_tuple_to_cpp_std_vector<double, &py_float_check, &py_float_as_double>(op, container);
    //  }
    //
    // Partial template specialisation: Need PyTuple_Check, PyTuple_GET_SIZE, PyTuple_GET_ITEM.
    // Also error messages.
    template<typename T, int (*Check)(PyObject *), T (*Convert)(PyObject *)>
    int generic_py_tuple_to_cpp_std_vector(PyObject *op, std::vector<T> &vec) {
        assert(!PyErr_Occurred());
        vec.clear();
        Py_INCREF(op); // Borrowed reference
        if (!PyTuple_Check(op)) {
            Py_DECREF(op);
            PyErr_Format(PyExc_ValueError, "Python object must be a tuple not a %s", op->ob_type->tp_name);
            return -1;
        }
        for (Py_ssize_t i = 0; i < PyTuple_GET_SIZE(op); ++i) {
            PyObject *value = PyTuple_GET_ITEM(op, i);
            if (!(*Check)(value)) {
                vec.clear();
                Py_DECREF(op);
                PyErr_Format(PyExc_ValueError, "Python value of type %s can not be converted", value->ob_type->tp_name);
                return -2;
            }
            vec.push_back((*Convert)(value));
            // Check !PyErr_Occurred() which could never happen as we check first.
        }
        Py_DECREF(op); // Borrowed reference
        assert(!PyErr_Occurred());
        return 0;
    }

    // This is a hand written generic function to convert a C++ unordered_map to a Python dict.
    // The template is instantiated with C++ type(s) and a conversion function(s) to create Python object(s) from those
    // types.
    //
    // Example:
    //
    //  template <>
    //  PyObject *
    //  std_unordered_map_to_py_dict<double, double>(const std::unordered_map<double, double> &map) {
    //      return generic_cpp_std_unordered_map_to_py_dict<
    //            double, double,
    //            &py_float_from_double, &py_float_from_double
    //      >(map);
    //  }
    // TODO: Here
    template<
            typename K,
            typename V,
            PyObject *(*Convert_K)(const K &),
            PyObject *(*Convert_V)(const V &)
    >
    PyObject *
    generic_cpp_std_unordered_map_to_py_dict(const std::unordered_map<K, V> &map) {
        PyObject *ret = PyDict_New();
        if (ret) {
            for (const auto &k_v: map) {
                PyObject *py_k = (*Convert_K)(k_v.first);
                // Failure, clean up
                PyObject *py_v = (*Convert_V)(k_v.second);
                if (!py_k || !py_v || !PyDict_SetItem(ret, py_k, py_v)) {
                    PyObject *keys = PyDict_Keys(ret);
                    for (Py_ssize_t i = 0; i < PyList_Size(keys); ++i) {
                        if (PyDict_DelItem(ret, PyList_GetItem(keys, i))) {
                            // Something terrible has happened, this might leak.
                            return NULL;
                        }
                    }
                    Py_DECREF(keys);
                    Py_DECREF(ret);
                }
            }
        }
        return ret;
    }

    template<
            typename K,
            typename V,
            int (*Check_K)(PyObject *),
            int (*Check_V)(PyObject *),
            K (*Convert_K)(PyObject *),
            V (*Convert_V)(PyObject *)
    >
    int generic_py_dict_to_cpp_std_unordered_map(PyObject *dict,
                                                 std::unordered_map<K, V> &map) {
        map.clear();

        Py_INCREF(dict); // Borrowed reference
        if (!PyDict_Check(dict)) {
            Py_DECREF(dict);
            return -1;
        }
        PyObject *key, *value;
        Py_ssize_t pos = 0;

        while (PyDict_Next(dict, &pos, &key, &value)) {
            if (!Check_K(key)) {
                map.clear();
                Py_DECREF(dict);
                return -2;
            }
            if (!Check_V(value)) {
                map.clear();
                Py_DECREF(dict);
                return -3;
            }
            map[Convert_K(key)] = Convert_V(value);
            // Check !PyErr_Occurred() which could never happen as we check first.
        }
        Py_DECREF(dict);
        return 0;
    }

} // namespace Python_Cpp_Homogeneous_Containers

// Now include the auto generated instantiations.

#include "auto_py_convert_internal.h"


#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONVERT_H
