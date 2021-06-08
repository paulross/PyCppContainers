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

#include <complex>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace Python_Cpp_Homogeneous_Containers {
#pragma mark == Object Conversion Code

    // Conversion functions.

#pragma mark -- Boolean/bool Conversion Code

    // Bool/bool
    PyObject *py_bool_from_bool(bool const &b);
    bool py_bool_as_bool(PyObject *op);
    int py_bool_check(PyObject *op);

#pragma mark -- Long Integer/long Conversion Code

    // Long/long
    PyObject *py_long_from_long(const long &l);
    long py_long_as_long(PyObject *op);
    int py_long_check(PyObject *op);

#pragma mark -- Float/double Conversion Code

    // Float/double
    PyObject *py_float_from_double(const double &d);
    double py_float_as_double(PyObject *op);
    int py_float_check(PyObject *op);

#pragma mark -- Complex Conversion Code

    // Complex/complex
    PyObject *py_complex_from_complex(const std::complex<double> &c);
    std::complex<double> py_complex_as_complex(PyObject *op);
    int py_complex_check(PyObject *op);

#pragma mark -- Bytes/std::string Conversion Code

    // Bytes to/from string
    PyObject *py_bytes_from_string(const std::string &s);
    std::string py_bytes_as_string(PyObject *op);
    int py_bytes_check(PyObject *op);

#pragma mark == Container Check, Create, Len, Set, Get

#pragma mark -- Tuple Check, Create, Len, Set, Get

    // Tuple wrappers around PyTuple_Check, PyTuple_New, PyTuple_Size, PyTuple_SET_ITEM, PyTuple_GET_ITEM
    int py_tuple_check(PyObject *op);
    PyObject *py_tuple_new(size_t len);
    Py_ssize_t py_tuple_len(PyObject *op);
    int py_tuple_set(PyObject *tuple_p, size_t pos, PyObject *op);
    PyObject *py_tuple_get(PyObject *tuple_p, size_t pos);

#pragma mark -- List Check, Create, Len, Set, Get

    // List wrappers around PyList_Check, PyList_New, PyList_Size, PyList_SET_ITEM, PyList_GET_ITEM
    int py_list_check(PyObject *op);
    PyObject *py_list_new(size_t len);
    Py_ssize_t py_list_len(PyObject *op);
    int py_list_set(PyObject *list_p, size_t pos, PyObject *op);
    PyObject *py_list_get(PyObject *list_p, size_t pos);

#pragma mark == Generic Container Conversion Code

#pragma mark -- Generic Tuple/List Container Conversion Code

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
    template<typename T,
            PyObject *(*Convert)(const T &),
            PyObject *(*PyUnary_New)(size_t),
            int(*PyUnary_Set)(PyObject *, size_t, PyObject *)>
    PyObject *
    generic_cpp_std_vector_to_py_unary(const std::vector<T> &vec) {
        assert(!PyErr_Occurred());
        PyObject *ret = PyUnary_New(vec.size());
        if (ret) {
            for (size_t i = 0; i < vec.size(); ++i) {
                PyObject *op = (*Convert)(vec[i]);
                if (!op) {
                    // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                    // e.g. tupledealloc(): https://github.com/python/cpython/blob/main/Objects/tupleobject.c#L268
                    PyErr_Format(PyExc_ValueError, "C++ value of can not be converted.");
                    goto except;
                }
                // Refcount may well be >> 1 for interned objects.
                Py_ssize_t op_ob_refcnt = op->ob_refcnt;
                // This usually wraps a void function, always succeeds.
                if (PyUnary_Set(ret, i, op)) { // Stolen reference.
                    PyErr_Format(PyExc_RuntimeError, "Can not set unary value.");
                    goto except;
                }
                assert(op->ob_refcnt == op_ob_refcnt && "Reference count incremented instead of stolen.");
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
    template<typename T,
            int (*Check)(PyObject *),
            T (*Convert)(PyObject *),
            int(*PyUnary_Check)(PyObject *),
            Py_ssize_t(*PyUnary_Size)(PyObject *),
            PyObject *(*PyUnary_Get)(PyObject *, size_t)>
    int generic_py_unary_to_cpp_std_vector(PyObject *op, std::vector<T> &vec) {
        assert(!PyErr_Occurred());
        int ret = 0;
        vec.clear();
        Py_INCREF(op); // Borrowed reference
        if (!PyUnary_Check(op)) {
            PyErr_Format(PyExc_ValueError, "Python object must be a tuple/list not a %s", op->ob_type->tp_name);
            ret = -1;
            goto except;
        }
        for (Py_ssize_t i = 0; i < PyUnary_Size(op); ++i) {
            PyObject *value = PyUnary_Get(op, i);
            if (!(*Check)(value)) {
                vec.clear();
                PyErr_Format(PyExc_ValueError, "Python value of type %s can not be converted", value->ob_type->tp_name);
                ret = -2;
                goto except;
            }
            vec.push_back((*Convert)(value));
            // Check !PyErr_Occurred() which could never happen as we check first.
        }
        assert(!PyErr_Occurred());
        goto finally;
    except:
        assert(PyErr_Occurred());
    finally:
        Py_DECREF(op); // Borrowed reference
        return ret;
    }

#pragma mark -- Specific Tuple Container Conversion Code

    template<typename T, PyObject *(*Convert)(const T &)>
    PyObject *
    generic_cpp_std_vector_to_py_tuple(const std::vector<T> &vec) {
        return generic_cpp_std_vector_to_py_unary<T, Convert, &py_tuple_new, &py_tuple_set>(vec);
    }

    template<typename T, int (*Check)(PyObject *), T (*Convert)(PyObject *)>
    int generic_py_tuple_to_cpp_std_vector(PyObject *op, std::vector<T> &vec) {
        return generic_py_unary_to_cpp_std_vector<T, Check, Convert, &py_tuple_check, &py_tuple_len, &py_tuple_get>(op,
                                                                                                                   vec);
    }

#pragma mark -- Specific List Container Conversion Code

    template<typename T, PyObject *(*Convert)(const T &)>
    PyObject *
    generic_cpp_std_vector_to_py_list(const std::vector<T> &vec) {
        return generic_cpp_std_vector_to_py_unary<T, Convert, &py_list_new, &py_list_set>(vec);
    }

    template<typename T, int (*Check)(PyObject *), T (*Convert)(PyObject *)>
    int generic_py_list_to_cpp_std_vector(PyObject *op, std::vector<T> &vec) {
        return generic_py_unary_to_cpp_std_vector<T, Check, Convert, &py_list_check, &py_list_len, &py_list_get>(op,
                                                                                                                 vec);
    }

#pragma mark -- Specific Set Container Conversion Code

    // This is a hand written generic function to convert a C++ unordered_set to a Python set.
    template<typename T, PyObject *(*Convert)(const T &)>
    PyObject *
    generic_cpp_std_unordered_set_to_py_set(const std::unordered_set<T> &set) {
        assert(!PyErr_Occurred());
        PyObject *ret = PySet_New(NULL);
        if (ret) {
            for (auto const &iter: set) {
                PyObject *op = (*Convert)(iter);
                if (!op) {
                    // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                    PyErr_Format(PyExc_ValueError, "C++ value of can not be converted.");
                    goto except;
                }
                // Refcount may well be >> 1 for interned objects.
                Py_ssize_t op_ob_refcnt = op->ob_refcnt;
                // This usually wraps a void function, always succeeds.
                if (PySet_Add(ret, op)) { // Stolen reference.
                    PyErr_Format(PyExc_RuntimeError, "Can not set value into the set.");
                    goto except;
                }
                assert(op->ob_refcnt == op_ob_refcnt && "Reference count incremented instead of stolen.");
            }
        } else {
            PyErr_Format(PyExc_ValueError, "Can not create Python set");
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

    template<typename T, int (*Check)(PyObject *), T (*Convert)(PyObject *)>
    int generic_py_set_to_cpp_std_unordered_set(PyObject *op, std::unordered_set<T> &set) {
        assert(!PyErr_Occurred());
        int ret = 0;
        PyObject *py_iter = NULL;
        PyObject *py_item = NULL;

        set.clear();
        Py_INCREF(op); // Borrowed reference
        if (!PySet_Check(op)) {
            PyErr_Format(PyExc_ValueError, "Python object must be a set not a %s", op->ob_type->tp_name);
            ret = -1;
            goto except;
        }
        py_iter = PyObject_GetIter(op);
        if (! py_iter) {
            ret = -2;
            PyErr_Format(PyExc_ValueError, "Can not create Python iterator on type %s", op->ob_type->tp_name);
            goto except;
        }
        while ((py_item = PyIter_Next(py_iter))) {
            /* do something with item */
            if (!(*Check)(py_item)) {
                set.clear();
                PyErr_Format(PyExc_ValueError, "Python value of type %s can not be converted",
                             py_item->ob_type->tp_name);
                ret = -3;
                goto except;
            }
            T cpp_item = (*Convert)(py_item);
            if (set.count(cpp_item) != 0) {
                // Something horribly wrong.
                PyErr_Format(PyExc_ValueError,
                             "Python values of type %s are distinct in the Python set but conversion makes"
                             "them unique in C++ set (previous value already seen in C++ set)",
                             py_item->ob_type->tp_name);
                ret = -4;
                goto except;
            }
            set.insert(cpp_item);
            /* release reference when done */
            Py_DECREF(py_item);
            py_item = NULL; // NOTE: There is a decref in finally: label so must do this otherwise a double decref.
        }
        assert(!PyErr_Occurred());
        goto finally;
    except:
        set.clear();
        assert(PyErr_Occurred());
    finally:
        Py_DECREF(op); // Borrowed reference
        Py_XDECREF(py_item);
        Py_XDECREF(py_iter);
        return ret;
    }

#pragma mark -- Specific Dict Container Conversion Code

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
        PyObject *py_k = NULL;
        PyObject *py_v = NULL;
        if (ret) {
            for (const auto &k_v: map) {
                py_k = (*Convert_K)(k_v.first);
                if (! py_k) {
                    // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                    PyErr_Format(PyExc_ValueError, "C++ key of can not be converted.");
                    goto except;
                }
                // Refcount may well be >> 1 for interned objects.
                Py_ssize_t py_k_ob_refcnt = py_k->ob_refcnt;
                py_v = (*Convert_V)(k_v.second);
                if (! py_v) {
                    // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                    PyErr_Format(PyExc_ValueError, "C++ value of can not be converted.");
                    goto except;
                }
                // Refcount may well be >> 1 for interned objects.
                Py_ssize_t py_v_ob_refcnt = py_v->ob_refcnt;
                if (PyDict_SetItem(ret, py_k, py_v)) {
                    // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                    PyErr_Format(PyExc_ValueError, "Can not set an item in the Python dict.");
                    goto except;
                }
                // Oh this is nasty.
                // PyDict_SetItem() increfs the key and the value rather than stealing a reference.
                // insertdict(): https://github.com/python/cpython/blob/main/Objects/dictobject.c#L1074
                assert(py_k->ob_refcnt == py_k_ob_refcnt + 1 && "PyDict_SetItem failed to increment key refcount.");
                Py_DECREF(py_k);
                assert(py_k->ob_refcnt == py_k_ob_refcnt);
                assert(py_v->ob_refcnt == py_v_ob_refcnt + 1 && "PyDict_SetItem failed to increment value refcount.");
                Py_DECREF(py_v);
                assert(py_v->ob_refcnt == py_v_ob_refcnt);
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
        while (PyDict_Next(dict, &pos, &key, &val)) {
            // key, val are borrowed references.
            if (!Check_K(key)) {
                PyErr_Format(PyExc_ValueError, "Python dict key is wrong type of %s", key->ob_type->tp_name);
                ret = -2;
                goto except;
            }
            if (!Check_V(val)) {
                PyErr_Format(PyExc_ValueError, "Python dict value is wrong type of %s", val->ob_type->tp_name);
                ret = -3;
                goto except;
            }
            map[Convert_K(key)] = Convert_V(val);
            // Check !PyErr_Occurred() which could never happen as we check first.
        }
        assert(!PyErr_Occurred());
        goto finally;
    except:
        map.clear();
        assert(PyErr_Occurred());
    finally:
        Py_DECREF(dict); // Borrowed reference
        return ret;
    }

} // namespace Python_Cpp_Homogeneous_Containers

// Now include the auto generated instantiations.

#include "auto_py_convert_internal.h"


#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_PYTHON_CONVERT_H
