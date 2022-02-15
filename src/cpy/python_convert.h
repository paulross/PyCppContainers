///
///  python_convert.hpp
///  PythonC++
///
/// This contains hand crafted conversion of C++ <-> Python containers of homogeneous types.
/// These are further instantiated by auto-generated code for a specific cartesian product of types and containers.
/// That product is controlled by code_gen.py
/// That auto-generated file is included by #include "auto_py_convert_internal.h" at the end of this file.
///
///
///
///  Created by Paul Ross on 22/11/2018.
///  Copyright © 2018 Paul Ross. All rights reserved.
///

#ifndef PYTHON_CPP_CONTAINERS_PYTHON_CONVERT_H
#define PYTHON_CPP_CONTAINERS_PYTHON_CONVERT_H

#include <Python.h>

#include <array>
#include <complex>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/// Conversion functions for individual Python objects.
#include "python_object_convert.h"
/// Functions to handle Python containers.
#include "python_container_convert.h"

#define PYTHON_CPP_CONTAINERS_VERSION "0.3.1"

namespace std {
    // We are adding to namespace std:: here.
    // See https://stackoverflow.com/questions/16122912/is-it-ok-to-specialize-stdnumeric-limitst-for-user-defined-number-like-class

    /**
     * Provide a hash function for \c std::vector<char>.
     * This just creates a \c std::string_view over the raw data and uses \c std::hash on that.
     */
    template<>
    struct hash<std::vector<char>> {
        size_t operator()(std::vector<char> const &item) const {
            size_t ret = 0;
            std::string_view sv(item.data(), item.size());
            ret = std::hash<std::string_view>{}(sv);
            return ret;
        }
    };

    /**
     * Provide a hash function for \c std::complex<double>.
     * This mimics the Python hash of complex, see \c complex_hash() typically at
     * https://github.com/python/cpython/blob/main/Objects/complexobject.c#L407
     * See also: Include/pyhash.h
     */
    template<>
    struct hash<std::complex<double>> {
        size_t operator()(std::complex<double> const &item) const {
            // From the Python hash code for complex values:
            //
            // _PyHASH_IMAG is 1000003UL /* 0xf4243 */
            // Py_uhash_t hashreal, hashimag, combined;
            //    hashreal = (Py_uhash_t)_Py_HashDouble((PyObject *) v, v->cval.real);
            //    if (hashreal == (Py_uhash_t)-1)
            //        return -1;
            //    hashimag = (Py_uhash_t)_Py_HashDouble((PyObject *)v, v->cval.imag);
            //    if (hashimag == (Py_uhash_t)-1)
            //        return -1;
            //    /* Note:  if the imaginary part is 0, hashimag is 0 now,
            //     * so the following returns hashreal unchanged.  This is
            //     * important because numbers of different types that
            //     * compare equal must have the same hash value, so that
            //     * hash(x + 0*j) must equal hash(x).
            //     */
            //    combined = hashreal + _PyHASH_IMAG * hashimag;
            //    if (combined == (Py_uhash_t)-1)
            //        combined = (Py_uhash_t)-2;
            //    return (Py_hash_t)combined;
            size_t hashreal, hashimag, combined;
            hashreal = std::hash<double>{}(item.real());
            if (hashreal == (size_t) -1) {
                return -1;
            }
            hashimag = std::hash<double>{}(item.imag());
            if (hashimag == (size_t) -1) {
                return -1;
            }
            combined = hashreal + 1000003UL * hashimag;
            if (combined == (size_t) -1) {
                combined = (size_t) -2;
            }
            return combined;
        }
    };

    // Add a complex number implementation of less<T> for std::map
    // See: https://stackoverflow.com/questions/26245189/using-stdcomplexdouble-as-a-stdmap-key
    // With the addition of a const qualifier for bool operator().
    template<typename T>
    struct less<std::complex<T>> {
        bool operator()(std::complex<T> const &a, std::complex<T> const &b) const {
            return std::array<T, 2>{a.real(), a.imag()} < std::array<T, 2>{b.real(), b.imag()};
        }
    };
}

namespace Python_Cpp_Containers {

    // TODO: Enumerate errors codes. Something like:
    enum class ErrorReturnValue : int {
        SUCCESS = 0,
        FAIL_CONTAINER_WRONG_TYPE,
        FAIL_CONTAINER_MEMBER_WRONG_TYPE,
        FAIL_CONTAINER_KEY_WRONG_TYPE,
        FAIL_CONTAINER_VALUE_WRONG_TYPE
    };

#pragma mark == Generic Container Conversion Code

#pragma mark -- Generic Tuple/List Container Conversion Code

    /**
     * This is a hand written generic function to convert a C++ \c std::vector to a Python \c tuple or \c list.
     * The template is instantiated with a C++ type and a conversion function to create a Python object from that type.
     *
     * Example of a partial specialisation of this template to create a function that will convert a C++
     * \c std::vector<T> to a Python \c tuple of \c T:
     *
     * \code
     *
     *      template<typename T, PyObject *(*Convert)(const T &)>
     *      PyObject *
     *      generic_cpp_std_vector_to_py_tuple(const std::vector<T> &vec) {
     *          return generic_cpp_std_vector_to_py_unary<T, Convert, &py_tuple_new, &py_tuple_set>(vec);
     *      }
     *
     * \endcode
     *
     * Example of a complete instantiation of this template to create a function that will convert a C++
     * \c std::vector<double> to a Python \c tuple of \c float.
     * We have to supply the conversion function, a function to create a new \c tuple and a function to set a value:
     *
     * \code
     *
     *      PyObject *std_vector_to_py_tuple(const std::vector<double> &container) {
     *          return generic_cpp_std_vector_to_py_tuple<double, &cpp_double_to_py_float, &py_tuple_new, &py_tuple_set>(container);
     *      }
     *
     * \endcode
     *
     * This is a partial template specialisation.
     * For complete specialisation we need \c PyTuple_New, \c PyTuple_GET_ITEM, \c PyTuple_SET_ITEM.
     *
     * @tparam T The C++ type of the objects in the vector.
     * @tparam ConvertCppToPy Function to convert the C++ \c T to a \c PyObject*.
     * @tparam PyUnaryContainer_New Function to create a new Python container of a given length given as a \c size_t.
     * @tparam PyUnaryContainer_Set Function to set a value in a Python container at a given position given as a \c size_t.
     * @param vec The C++ vector as input data.
     * @return The \c PyObject* as the output data containing the values of the C++ \c std::vector or NULL on failure in
     * which  case a \c PyErr... will be set.
     */
    template<
            template<typename ...> class ListLike,
            typename T,
            PyObject *(*ConvertCppToPy)(const T &),
            PyObject *(*PyUnaryContainer_New)(size_t),
            int(*PyUnaryContainer_Set)(PyObject *, size_t, PyObject *)>
    PyObject *
    very_generic_cpp_std_list_like_to_py_unary(const ListLike<T> &list_like) {
        assert(!PyErr_Occurred());
        PyObject *ret = PyUnaryContainer_New(list_like.size());
        if (ret) {
            size_t i = 0;
            for (const auto &val: list_like) {
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
            PyErr_Format(PyExc_ValueError, "Can not create Python container of size %ld", list_like.size());
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

    /**
     * This is a hand written generic function to convert a Python \c tuple or \c list to a C++ \c std::vector.
     * The template is instantiated with a C++ type a check function and a conversion function to create a Python object
     * to that C++ type.
     *
     * The given vector is cleared whether an error condition exists or not.
     *
     * Error handling notes:
     *
     * An assertion is made that no PyErr exists.
     * If PyUnary_Check(op) then this sets a Python ValueError.
     *
     * Example of an instantiation of this template to create a function that will convert a Python \c tuple of
     * \c float to a C++ \c std::vector<double>:
     *
     * \code
     *
     *      template <> int
     *      py_tuple_to_std_vector<double>(PyObject *op, std::vector<double> &container) {
     *          return generic_py_tuple_to_cpp_std_vector<double, &py_float_check, &py_float_to_cpp_double>(op, container);
     *      }
     *
     * \endcode
     *
     * This is a partial template specialisation.
     * For complete specialisation we need \c PyTuple_Check, \c PyTuple_GET_SIZE\c , \c PyTuple_GET_ITEM.
     *
     * @tparam T The C++ type of the objects in the vector.
     * @tparam PyObject_Check A function that takes a \c PyObject* and returns 1 if it is of the right type, 0 otherwise.
     * @tparam PyObject_Convert A function to convert a PyObject* to a C++ \c T.
     * @tparam PyUnaryContainer_Check A function that takes a PyObject* and returns 1 if it is of a suitable container,
     * 0 otherwise.
     * @tparam PyUnaryContainer_Size A function that returns the length of the Python container.
     * @tparam PyUnaryContainer_Get A function that gets a \c PyObject* from the Python container at a given index as a
     * \c size_t.
     * @param op The Python container of values that can be converted to C++ type \c T.
     * @param vec The C++ \c std::vector to populate. This will be empty on failure.
     * @return 0 on success, non-zero on failure.
     */
    template<
            template<typename ...> class ListLike,
            typename T,
            int (*PyObject_Check)(PyObject *),
            T (*PyObject_Convert)(PyObject *),
            int(*PyUnaryContainer_Check)(PyObject *),
            Py_ssize_t(*PyUnaryContainer_Size)(PyObject *),
            PyObject *(*PyUnaryContainer_Get)(PyObject *, size_t)>
    int very_generic_py_unary_to_cpp_std_list_like(PyObject *op, ListLike<T> &list_like) {
        assert(!PyErr_Occurred());
        int ret = 0;
        list_like.clear();
        Py_INCREF(op); // Borrow reference
        if (!PyUnaryContainer_Check(op)) {
            PyErr_Format(PyExc_ValueError, "Can not convert Python container of type %s", op->ob_type->tp_name);
            ret = -1;
            goto except;
        }
        for (Py_ssize_t i = 0; i < PyUnaryContainer_Size(op); ++i) {
            PyObject *value = PyUnaryContainer_Get(op, i);
            if (!value) {
                ret = -2;
                goto except;
            }
            if (!(*PyObject_Check)(value)) {
                list_like.clear();
                PyErr_Format(
                        PyExc_ValueError,
                        "Python value of type %s can not be converted",
                        value->ob_type->tp_name
                );
                ret = -3;
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

#pragma mark -- Specific Tuple Container Conversion Code

    // ---- Python Tuples
    // Handcrafted.
    /**
     * Partial specialisation of the template to convert from a C++ \c std::vector<T> to a Python \c tuple.
     *
     * Example complete specialisation for C++ \c long using this:
     *
     * \code
     *
     *      template <>
     *      PyObject *
     *      cpp_std_vector_to_py_tuple<long>(const std::vector<long> &container) {
     *          return generic_cpp_std_vector_to_py_tuple<long, &cpp_long_to_py_long>(container);
     *      }
     *
     * \endcode
     *
     * Then this can be used thus:
     *
     * \code
     *
     *      std::vector<long> cpp_vector;
     *      // Populate cpp_vector...
     *      //
     *      // Convert to a Python tuple of int.
     *      PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
     *      // If op == NULL then a Python error will be set.
     *
     * \endcode
     *
     * @tparam T C++ type of the objects in the container.
     * @tparam ConvertCppToPy Pointer to a conversion function to convert a C++ type \c T to an equivalent Python type.
     * @param container The C++ \c std::vector<T> as input.
     * @return A new Python tuple with the contents of the input or NULL on failure in which case a \c PyErr... will be
     * set.
     */
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_like_to_py_tuple(const std::vector<T> &container) {
        return very_generic_cpp_std_list_like_to_py_unary<std::vector, T, ConvertCppToPy, &py_tuple_new, &py_tuple_set>(
                container);
    }
    // Partial specialisations for std::list to Python tuple
    /**
     * Partial specialisation of the template to convert from a C++ \c std::list<T> to a Python \c tuple.
     *
     * Example complete specialisation for C++ \c long using this:
     *
     * \code
     *
     *      template <>
     *      PyObject *
     *      cpp_std_vector_to_py_tuple<long>(const std::list<long> &container) {
     *          return generic_cpp_std_vector_to_py_tuple<long, &cpp_long_to_py_long>(container);
     *      }
     *
     * \endcode
     *
     * Then this can be used thus:
     *
     * \code
     *
     *      std::list<long> cpp_list;
     *      // Populate cpp_list...
     *      //
     *      // Convert to a Python tuple of int.
     *      PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_tuple(cpp_list);
     *      // If op == NULL then a Python error will be set.
     *
     * \endcode
     *
     * @tparam T C++ type of the objects in the container.
     * @tparam ConvertCppToPy Pointer to a conversion function to convert a C++ type \c T to an equivalent Python type.
     * @param container The C++ \c std::list<T> as input.
     * @return A new Python tuple with the contents of the input or NULL on failure in which case a \c PyErr... will be
     * set.
     */
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_like_to_py_tuple(const std::list<T> &container) {
        return very_generic_cpp_std_list_like_to_py_unary<std::list, T, ConvertCppToPy, &py_tuple_new, &py_tuple_set>(
                container);
    }

    /**
     * Partial specialisation of the template to convert from a Python \c tuple to a C++ \c std::vector<T>.
     *
     * @tparam T C++ type of the objects in the container.
     * @tparam PyObject_Check Pointer to a function that checks the types of the objects in the tuple can be
     * converted to a C++ type \c T.
     * @tparam PyObject_Convert Pointer to a function that converts a Python object to a C++ type \c T.
     * @param op The Python \c tuple as input.
     * @param vec The C++ \c std::vector<T> as output. This will be empty on failure.
     * @return Zero on success, non-zero on failure.
     */
    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_tuple_to_cpp_std_list_like(PyObject *op, std::vector<T> &container) {
        // Reserve the vector, but only if it is a tuple.
        // If it is any other Python object then ignore it as py_tuple_len() may give undefined behaviour.
        // Leave it to very_generic_py_unary_to_cpp_std_list_like() to error
        if (py_tuple_check(op)) {
            container.reserve(py_tuple_len(op));
        }
        return very_generic_py_unary_to_cpp_std_list_like<
                std::vector, T, PyObject_Check, PyObject_Convert, &py_tuple_check, &py_tuple_len, &py_tuple_get
        >(op, container);
    }

    /**
     * Partial specialisation of the template to convert from a Python \c tuple to a C++ \c std::list<T>.
     *
     * @tparam T C++ type of the objects in the container.
     * @tparam PyObject_Check Pointer to a function that checks the types of the objects in the tuple can be
     * converted to a C++ type \c T.
     * @tparam PyObject_Convert Pointer to a function that converts a Python object to a C++ type \c T.
     * @param op The Python \c tuple as input.
     * @param vec The C++ \c std::list<T> as output. This will be empty on failure.
     * @return Zero on success, non-zero on failure.
     */
    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_tuple_to_cpp_std_list_like(PyObject *op, std::list<T> &container) {
        return very_generic_py_unary_to_cpp_std_list_like<
                std::list, T, PyObject_Check, PyObject_Convert, &py_tuple_check, &py_tuple_len, &py_tuple_get
        >(op, container);
    }

#pragma mark -- Specific List Container Conversion Code

    // ---- Python Lists
    // Handcrafted
    /**
     * Partial specialisation of the template to convert from a C++ \c std::vector<T> to a Python \c list.
     *
     * @tparam T C++ type of the objects in the container.
     * @tparam ConvertCppToPy Pointer to a conversion function to convert a C++ type \c T to an equivalent Python type.
     * @param vec The C++ \c std::vector<T> as input.
     * @return A new Python list with the contents of the input.
     */
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_like_to_py_list(const std::vector<T> &container) {
        return very_generic_cpp_std_list_like_to_py_unary<std::vector, T, ConvertCppToPy, &py_list_new, &py_list_set>(
                container);
    }

    /**
     * Partial specialisation of the template to convert from a C++ \c std::list<T> to a Python \c list.
     *
     * @tparam T C++ type of the objects in the container.
     * @tparam ConvertCppToPy Pointer to a conversion function to convert a C++ type \c T to an equivalent Python type.
     * @param vec The C++ \c std::list<T> as input.
     * @return A new Python list with the contents of the input.
     */
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_like_to_py_list(const std::list<T> &container) {
        return very_generic_cpp_std_list_like_to_py_unary<std::list, T, ConvertCppToPy, &py_list_new, &py_list_set>(
                container);
    }

    /**
     * Partial specialisation of the template to convert from a Python \c list to a C++ \c std::vector<T>.
     *
     * @tparam T C++ type of the objects in the container.
     * @tparam PyObject_Check Pointer to a function that checks the types of the objects in the list can be
     * converted to a C++ type \c T.
     * @tparam PyObject_Convert Pointer to a function that converts a Python object to a C++ type \c T.
     * @param op The Python list as input.
     * @param vec The C++ \c std::vector<T> as output. This will be empty on failure.
     * @return Zero on success, non-zero on failure.
     */
    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_list_to_cpp_std_list_like(PyObject *op, std::vector<T> &container) {
        // Reserve the vector, but only if it is a list.
        // If it is any other Python object then ignore it as py_tuple_len() may give undefined behaviour.
        // Leave it to very_generic_py_unary_to_cpp_std_list_like() to error
        if (py_list_check(op)) {
            container.reserve(py_list_len(op));
        }
        return very_generic_py_unary_to_cpp_std_list_like<
                std::vector, T, PyObject_Check, PyObject_Convert, &py_list_check, &py_list_len, &py_list_get
        >(op, container);
    }

    /**
     * Partial specialisation of the template to convert from a Python \c list to a C++ \c std::list<T>.
     *
     * @tparam T C++ type of the objects in the container.
     * @tparam PyObject_Check Pointer to a function that checks the types of the objects in the list can be
     * converted to a C++ type \c T.
     * @tparam PyObject_Convert Pointer to a function that converts a Python object to a C++ type \c T.
     * @param op The Python list as input.
     * @param vec The C++ \c std::list<T> as output. This will be empty on failure.
     * @return Zero on success, non-zero on failure.
     */
    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_list_to_cpp_std_list_like(PyObject *op, std::list<T> &container) {
        return very_generic_py_unary_to_cpp_std_list_like<
                std::list, T, PyObject_Check, PyObject_Convert, &py_list_check, &py_list_len, &py_list_get
        >(op, container);
    }

#pragma mark -- Generic Set/Frozen set Container Conversion Code

#pragma mark -- Specific Set Container Conversion Code

    /**
     * This is a hand written generic function to convert a C++ \c std::unordered_set<T> to a Python \c set or
     * \c frozenset.
     *
     * @tparam T The C++ type of the objects in the \c std::unordered_set.
     * @tparam ConvertCppToPy Function to convert the C++ \c <T> to a \c PyObject*.
     * @tparam PyContainer_New Function to create a new Python container.
     * @param set The C++ \c std::unordered_set as input data.
     * @return The PyObject* \c set or \c frozenset containing the values of the C++ \c std::unordered_set.
     */
    template<
            typename T,
            PyObject *(*ConvertCppToPy)(const T &),
            PyObject *(*PyContainer_New)(PyObject *)
    >
    PyObject *
    generic_cpp_std_unordered_set_to_py_set_or_frozenset(const std::unordered_set<T> &set) {
        assert(!PyErr_Occurred());
        PyObject *ret = (*PyContainer_New)(NULL);
        if (ret) {
            for (auto const &iter: set) {
                PyObject *op = (*ConvertCppToPy)(iter);
                if (!op) {
                    // Failure, do not need to decref the contents as that will be done when decref'ing the container.
                    PyErr_Format(PyExc_ValueError, "C++ value of can not be converted.");
                    goto except;
                }
#ifndef NDEBUG
                // Refcount may well be >> 1 for interned objects.
                Py_ssize_t op_ob_refcnt = op->ob_refcnt;
#endif
                // NOTE: PySet_Add does NOT increment the key refcount so steals it like list/tuple and unlike dict.
                // See set_add_entry(): https://github.com/python/cpython/blob/main/Objects/setobject.c#L103
                if (PySet_Add(ret, op)) { // Stolen reference.
                    PyErr_Format(PyExc_RuntimeError, "Can not set value into the set.");
                    goto except;
                }
#ifndef NDEBUG
                assert(op->ob_refcnt == op_ob_refcnt + 1 && "PySet_SetItem failed to increment value refcount.");
#endif
                Py_DECREF(op);
#ifndef NDEBUG
                assert(op->ob_refcnt == op_ob_refcnt && "Reference count incremented instead of stolen.");
#endif
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

    /**
     * Specific instantiation to convert a C++ \c std::unordered_set<T> to a Python \c set.
     *
     * @tparam T The C++ type of the objects in the \c std::unordered_set.
     * @tparam ConvertCppToPy Function to convert the C++ \c <T> to a \c PyObject*.
     * @param set The C++ \c std::unordered_set as input data.
     * @return The \c PyObject* set containing the values of the C++ \c std::unordered_set.
     */
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_unordered_set_to_py_set(const std::unordered_set<T> &set) {
        return generic_cpp_std_unordered_set_to_py_set_or_frozenset<T, ConvertCppToPy, &PySet_New>(set);
    }

    /**
     * Specific instantiation to convert a C++ \c std::unordered_set<T> to a Python \c frozenset.
     *
     * @tparam T The C++ type of the objects in the \c std::unordered_set.
     * @tparam ConvertCppToPy Function to convert the C++ \c <T> to a \c PyObject*.
     * @param set The C++ \c std::unordered_set as input data.
     * @return The \c PyObject* frozenset containing the values of the C++ \c std::unordered_set.
     */
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_unordered_set_to_py_frozenset(const std::unordered_set<T> &set) {
        return generic_cpp_std_unordered_set_to_py_set_or_frozenset<T, ConvertCppToPy, &PyFrozenSet_New>(set);
    }

    /**
     * This is a hand written generic function to convert a Python \c set or \c frozenset to a C++
     * \c std::unordered_set<T>.
     *
     * @tparam T The C++ type of the objects in the \c std::unordered_set.
     * @tparam PyContainer_Check A pointer to a function that checks that the Python container is the correct type.
     * @tparam PyObject_Check A pointer to a function that checks that a member of thePython container is the correct type.
     * @tparam PyObject_Convert A pointer to a function that converts a Python object to the C++ object of type \c T.
     * @param op The Python container,
     * @param set The C++ result.
     * @return Zero on success, non-zero on failure.
     */
    template<
            typename T,
            int (*PyContainer_Check)(PyObject *),
            int (*PyObject_Check)(PyObject *),
            T (*PyObject_Convert)(PyObject *)
    >
    int generic_py_set_or_frozenset_to_cpp_std_unordered_set(PyObject *op, std::unordered_set<T> &set) {
        assert(!PyErr_Occurred());
        int ret = 0;
        PyObject *py_iter = NULL;
        PyObject *py_item = NULL;
        set.clear();

        Py_INCREF(op); // Borrowed reference
        if (!(*PyContainer_Check)(op)) {
            PyErr_Format(PyExc_ValueError, "Python object must be a set not a %s", op->ob_type->tp_name);
            ret = -1;
            goto except;
        }
        // NOTE: It might be tempting to make the following call to pre-allocate space:
        // set.reserve(PySet_Size(op));
        // Do NOT do this.
        // std::unordered_set<double>.reserve() is very slow and O(N**2) for that type.
        // Possibly with other types as well.
        py_iter = PyObject_GetIter(op);
        if (!py_iter) {
            ret = -2;
            PyErr_Format(PyExc_ValueError, "Can not create Python iterator on type %s", op->ob_type->tp_name);
            goto except;
        }
        while ((py_item = PyIter_Next(py_iter))) {
            /* do something with item */
            if (!(*PyObject_Check)(py_item)) {
                set.clear();
                PyErr_Format(PyExc_ValueError, "Python value of type %s can not be converted",
                             py_item->ob_type->tp_name);
                ret = -3;
                goto except;
            }
            T cpp_item = (*PyObject_Convert)(py_item);
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

    /**
     * Specific instantiation to convert a Python \c set to a C++ \c std::unordered_set<T>.
     *
     * @tparam T The C++ type of the objects in the \c std::unordered_set.
     * @tparam PyObject_Check A pointer to a function that checks that a member of thePython container is the correct type.
     * @tparam PyObject_Convert A pointer to a function that converts a Python object to the C++ object of type \c T.
     * @param op The Python container,
     * @param set The C++ result.
     * @return Zero on success, non-zero on failure.
     */
    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_set_to_cpp_std_unordered_set(PyObject *op, std::unordered_set<T> &set) {
        return generic_py_set_or_frozenset_to_cpp_std_unordered_set<T, &py_set_check, PyObject_Check, PyObject_Convert>(
                op, set);
    }

    /**
     * Specific instantiation to convert a Python \c frozenset to a C++ \c std::unordered_set<T>.
     *
     * @tparam T The C++ type of the objects in the \c std::unordered_set.
     * @tparam PyObject_Check A pointer to a function that checks that a member of thePython container is the correct type.
     * @tparam PyObject_Convert A pointer to a function that converts a Python object to the C++ object of type \c T.
     * @param op The Python container,
     * @param set The C++ result.
     * @return Zero on success, non-zero on failure.
     */
    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_frozenset_to_cpp_std_unordered_set(PyObject *op, std::unordered_set<T> &set) {
        return generic_py_set_or_frozenset_to_cpp_std_unordered_set<T, &py_frozenset_check, PyObject_Check, PyObject_Convert>(
                op, set);
    }

#pragma mark -- Specific Dict Container Conversion Code

    /**
     * This is a hand written generic function to convert a C++ \c unordered_map to a Python \c dict.
     * The template is instantiated with C++ type(s) and a conversion function(s) to create Python object(s) from those
     * types.
     *
     * Example:
     *
     * \code
     *
     *  template <>
     *  PyObject *
     *  cpp_std_map_like_to_py_dict<std::unordered_map, double, double>(const std::unordered_map<double, double> &map) {
     *      return generic_cpp_std_map_like_to_py_dict<
     *            double, double,
     *            &cpp_double_to_py_float, &cpp_double_to_py_float
     *      >(map);
     *  }
     *
     * \endcode
     *
     * @tparam Map The container, either \c std::unordered_map or \c std::map.
     * @tparam K The C++ type of the key.
     * @tparam V The C++ type of the value.
     * @tparam Convert_K A function to convert a C++ type K to a \c PyObject*.
     * @tparam Convert_V A function to convert a C++ type V to a \c PyObject*.
     * @param map The C++ \c std::unordered_map that is to be converted to a Python \c dict.
     * @return The Python dictionary. \c NULL on failure.
     */
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

    /**
     *
     * This is a hand written generic function to convert a Python \c dict to a C++ \c std::unordered_map
     * or \c std::map.
     *
     * @tparam Map The container, either \c std::unordered_map or \c std::map.
     * @tparam K The C++ type of the key.
     * @tparam V The C++ type of the value.
     * @tparam Check_K A function to check that the type of a \c PyObject* is a C++ \c K.
     *  Returns 0 on success, non-zero on failure.
     * @tparam Check_V A function to check that the type of a \c PyObject* is a C++ \c V.
     *  Returns 0 on success, non-zero on failure.
     * @tparam Convert_K A function to convert a \c PyObject* to a C++ type \c K.
     * @tparam Convert_V A function to convert a \c PyObject* to a C++ type \c V.
     * @param dict The Python dictionary as input.
     * @param map The C++ \c std::unordered_map to populate. This will be empty on failure.
     * @return 0 on success. Non-zero on failure.
     */
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

} // namespace Python_Cpp_Containers

// Now include the auto generated instantiations.
#include "auto_py_convert_internal.h"

#endif // PYTHON_CPP_CONTAINERS_PYTHON_CONVERT_H
