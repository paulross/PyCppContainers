.. moduleauthor:: Paul Ross <apaulross@gmail.com>
.. sectionauthor:: Paul Ross <apaulross@gmail.com>

.. PyCppContainers Design

.. _PyCppContainers.Design:

Design
==================

This library uses C++ templates but not in a particularly complex way.
There are six essential C++ templates and a Python script is used to to auto-generate the partial template
specialisations and their instantiations.

As described in the previous chapter new types can be added pretty easily, alternatively the code generator can be
manipulated to do this.

Essentially there are functions to make these conversions between Python and C++:

- Objects that can be members of containers. Examples are float/double, strings and user defined types.
  See :ref:`PyCppContainers.user_define_types` for more information on the latter.
- Containers. Examples are Python lists to and from C++ ``std::list<T>``.

Object Conversion Source Files
------------------------------

The are in ``python_object_convert.h`` and ``python_object_convert.cpp``.

There are hand written files that contains implementations of functions to convert Python types to and from their
C++ equivalent.
There are three functions to each type:

* Check that a Python object is of the expected type.
* Convert a Python object to a C++ value.
* Convert a C++ value to a new Python object.

For example here are the three functions for Python ``int`` and C++ ``long``:

.. code-block:: c

    int py_long_check(PyObject *op);
    long py_long_to_cpp_long(PyObject *op);
    PyObject *cpp_long_to_py_long(const long &l);

The implementations of these are just one line wrappers around functions or macros in the Python C API:

.. code-block:: c

    #include "Python.h"

    int py_long_check(PyObject *op) {
        return PyLong_Check(op);
    }

    long py_long_to_cpp_long(PyObject *op) {
        assert(py_long_check(op));
        return PyLong_AsLong(op);
    }

    PyObject *cpp_long_to_py_long(const long &l) {
        return PyLong_FromLong(l);
    }

The implementations for more complex types, such as string conversion, are a little more complicated but not greatly so.

Container Conversion Source Files
---------------------------------

These are in ``python_container_convert.h`` and ``python_container_convert.cpp``.

This is a hand written file that contains implementations of functions to create and access Python unary containers
(such as ``list``, ``tuple``, ``set``).
There are a number of functions to each container, for example a ``list``:

* Check that each Python container is of the expected type.
* Create a new Python container.
* Find the length of a Python container.
* Set a value in a Python container.
* Get a value from a Python container.

For example here are the three functions for Python lists:

.. code-block:: c

    int py_list_check(PyObject *op);
    PyObject *py_list_new(size_t len);
    Py_ssize_t py_list_len(PyObject *list_p);
    int py_list_set(PyObject *list_p, size_t pos, PyObject *op);
    PyObject *py_list_get(PyObject *list_p, size_t pos);

The implementations of these are just one line wrappers around functions or macros in the Python C API.
For example:

.. code-block:: c

    // List wrappers around PyList_Check, PyList_New, PyList_SET_ITEM, PyList_GET_ITEM
    int py_list_check(PyObject *op) {
        return PyList_Check(op);
    }
    PyObject *py_list_new(size_t len) {
        return PyList_New(len);
    }
    Py_ssize_t py_list_len(PyObject *op) {
        return PyList_Size(op);
    }
    int py_list_set(PyObject *list_p, size_t pos, PyObject *op) {
        PyList_SET_ITEM(list_p, pos, op);
        return 0;
    }
    PyObject *py_list_get(PyObject *list_p, size_t pos) {
        return PyList_GET_ITEM(list_p, pos);
    }

``python_convert.h``
---------------------

This is the top level file that gives access to the whole library.
Is is a hand written file that contains templates that convert containers to and fro between Python  and C++.
It includes ``python_object_convert.h`` and ``python_container_convert.h``, that declares the templates then
includes ``auto_py_convert_internal.h`` the auto generated file of template specialisations.

Python ``list`` and ``tuple``
-----------------------------------

There are several levels of specialisation here as we want to support conversion from Python ``list`` and ``tuple``
to and from ``std::vector`` and ``std::list``.

These functions are described in detail and, for brevity, the functions that handle sets and dicts that follow the
same pattern are describe in less detail.

Conversion From C++ to Python
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This provides conversion From a ``std::vector<T>`` or a ``std::list<T>`` to a Python List or Tuple.
Firstly there is a highly generic handwritten function in ``python_convert.h``:

.. code-block:: cpp

    template<
            template<typename ...> class ListLike,
            typename T,
            PyObject *(*ConvertCppToPy)(const T &),
            PyObject *(*PyUnaryContainer_New)(size_t),
            int(*PyUnaryContainer_Set)(PyObject *, size_t, PyObject *)>
    PyObject *
    very_generic_cpp_std_list_like_to_py_unary(const ListLike<T> &list_like) {
        // Handwritten code...
    }

The template types are:

.. list-table:: Convert a ``std::vector`` or ``std::list`` to a Python ``tuple`` or ``list``.
   :widths: 30 30
   :header-rows: 1

   * - Type
     - Description
   * - ``ListLike``
     - The C++ container, for example a ``std::vector`` or a ``std::list``.
   * - ``typename T``
     - The C++ type of each object in the container.
   * - ``PyObject *(*ConvertCppToPy)(const T &)``
     - A pointer to a function that takes a type ``T`` and returns a new Python ``PyObject*``.
   * - ``PyObject *(*PyUnaryContainer_New)(size_t)``
     - A pointer to a function that returns a new Python container of the given length.
   * - ``int(*PyUnaryContainer_Set)(PyObject *, size_t, PyObject *)>``
     - Sets a Python object in the Python container at the given position.

And the parameters are:

.. list-table:: Function to convert a ``std::vector`` or ``std::list`` to a Python ``tuple`` or ``list``.
   :widths: 30 30
   :header-rows: 1

   * - Parameter
     - Description
   * - ``list_like``
     - The C++ container.

This returns a new PyObject or NULL on failure.

The hand written implementation looks like this:

.. code-block:: cpp

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
                    // Failure, do not need to decref the contents as that will be done
                    // when decref'ing the container. e.g. tupledealloc():
                    // https://github.com/python/cpython/blob/main/Objects/tupleobject.c#L268
                    PyErr_Format(PyExc_ValueError, "C++ value of can not be converted.");
                    goto except;
                }
    #ifndef NDEBUG
                // Refcount may well be >> 1 for interned objects.
                Py_ssize_t op_ob_refcnt = op->ob_refcnt;
    #endif
                // PyUnaryContainer_Set usually wraps a void function,
                // always succeeds returning non-zero.
                if (PyUnaryContainer_Set(ret, i++, op)) { // Stolen reference.
                    PyErr_Format(PyExc_RuntimeError, "Can not set unary value.");
                    goto except;
                }
    #ifndef NDEBUG
                assert(op->ob_refcnt == op_ob_refcnt
                       && "Reference count incremented instead of stolen.");
    #endif
            }
        } else {
            PyErr_Format(
                PyExc_ValueError,
                "Can not create Python container of size %ld",
                list_like.size()
            );
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

This template is then partially specified four ways for both Python ``tuple`` and ``list`` from both C++
``std::vector<T>`` and ``std::list<T>``.
This is handwritten code in ``python_convert.h`` but they are, effectively, just one-liners:

.. code-block:: cpp

    // C++ std::vector<T> to a Python tuple
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_like_to_py_tuple(const std::vector<T> &container) {
        return very_generic_cpp_std_list_like_to_py_unary<
            std::vector, T, ConvertCppToPy, &py_tuple_new, &py_tuple_set
        >(container);
    }

    // C++ std::list<T> to a Python tuple
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_like_to_py_tuple(const std::list<T> &container) {
        return very_generic_cpp_std_list_like_to_py_unary<
            std::list, T, ConvertCppToPy, &py_tuple_new, &py_tuple_set
        >(container);
    }

    // C++ std::vector<T> to a Python list
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_like_to_py_list(const std::vector<T> &container) {
        return very_generic_cpp_std_list_like_to_py_unary<
            std::vector, T, ConvertCppToPy, &py_list_new, &py_list_set
        >(container);
    }

    // C++ std::list<T> to a Python list
    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_like_to_py_list(const std::list<T> &container) {
        return very_generic_cpp_std_list_like_to_py_unary<
            std::list, T, ConvertCppToPy, &py_list_new, &py_list_set
        >(container);
    }

Then these are specialised by auto-generated code in ``auto_py_convert_internal.h`` for the specific types
``bool``, ``long``, ``double``, ``std::vector<char>``, ``std::string`` and so on.

For brevity only the declarations and definitions are shown for the type ``long``.
For example to create a Python ``tuple`` from  a C++ ``std::vector`` the base declaration for any type ``T`` is:

.. code-block:: cpp

    // Base declaration
    template<typename T>
    PyObject *
    cpp_std_list_like_to_py_tuple(const std::vector<T> &container);

And the declaration for type ``long`` in ``auto_py_convert_internal.h`` is:

.. code-block:: cpp

    // Instantiations
    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<long>(const std::vector<long> &container);

The definitions are auto-generated in ``auto_py_convert_internal.cpp``, for example for C++ type ``long``.
These are just one-liners:

.. code-block:: cpp

    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<long>(const std::vector<long> &container) {
        return generic_cpp_std_list_like_to_py_tuple<long, &cpp_long_to_py_long>(container);
    }


That is for ``std::vector``, for ``std::list`` the declarations and definitions are very similar.
Firstly in ``auto_py_convert_internal.h``, again just showing for ``long``:

.. code-block:: cpp

    // Base declaration
    template<typename T>
    PyObject *
    cpp_std_list_like_to_py_tuple(const std::list<T> &container);

    // Instantiations
    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<long>(const std::list<long> &container);

    // And so on...

And the declarations auto-generated in ``auto_py_convert_internal.cpp``:

.. code-block:: cpp

    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<long>(const std::list<long> &container) {
        return generic_cpp_std_list_like_to_py_tuple<long, &cpp_long_to_py_long>(container);
    }

    // And so on...

Conversion From Python to C++
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The conversion from a Python ``list`` or ``tuple`` to a C++ ``std::vector<T>`` or ``std::list<T>`` follows a similar
pattern as described above.

Firstly there is a highly generic handwritten function in ``python_convert.h``:

.. code-block:: cpp

    template<
            template<typename ...> class ListLike,
            typename T,
            int (*PyObject_Check)(PyObject *),
            T (*PyObject_Convert)(PyObject *),
            int(*PyUnaryContainer_Check)(PyObject *),
            Py_ssize_t(*PyUnaryContainer_Size)(PyObject *),
            PyObject *(*PyUnaryContainer_Get)(PyObject *, size_t)>
    int very_generic_py_unary_to_cpp_std_list_like(PyObject *op, ListLike<T> &list_like) {
        // Handwritten code
    }

Template parameters are:

.. list-table:: Template to convert a Python ``tuple`` or ``list`` to a ``std::vector`` or ``std::list``.
   :widths: 30 30
   :header-rows: 1

   * - Type
     - Description
   * - ``ListLike``
     - The C++ container, for example a ``std::vector`` or a ``std::list``.
   * - ``typename T``
     - The C++ type of the object.
   * - ``int (*PyObject_Check)(PyObject *)``
     - A pointer to a function returns true if Python object can be converted to a C++ object of type ``T``.
   * - ``T (*PyObject_Convert)(PyObject *)``
     - A pointer to a function to convert a Python object to a C++ object of type ``T``.
   * - ``int(*PyUnaryContainer_Check)(PyObject *)``
     - A pointer to a function returns true if the Python container is of the relevant type (``list`` or ``tuple`` in this case).
   * - ``Py_ssize_t(*PyUnaryContainer_Size)(PyObject *)``
     - A pointer to a function that returns the size of the Python container.
   * - ``PyObject *(*PyUnaryContainer_Get)(PyObject *, size_t)``
     - Gets a Python object in the Python container at the given position.

Parameters are:

.. list-table:: Function to convert a ``std::vector`` or ``std::list`` to a Python ``tuple`` or ``list``.
   :widths: 30 30
   :header-rows: 1

   * - Parameter
     - Description
   * - ``op``
     - The Python container.
   * - ``list_like``
     - The C++ container. This will be empty on failure.

This returns zero on success, non-zero on failure.
Failure reasons can be:

* The Python object is not the expected container type.
* A Python object in the container is ``NULL``.
* A Python object in the container can not be converted to a C++ type ``T``.

The implementation looks like this:

.. code-block:: cpp

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
        Py_INCREF(op); // Increment borrowed reference
        if (!PyUnaryContainer_Check(op)) {
            PyErr_Format(
                PyExc_ValueError,
                "Can not convert Python container of type %s",
                op->ob_type->tp_name
            );
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
        Py_DECREF(op); // Decrement borrowed reference
        return ret;
    }

This template is then partially specified with handwritten code.
Here is the handwritten code in ``python_convert.h`` for Python ``tuple`` to a C++ ``std::vector`` or ``std::list``.
They are basically one-liners, the interesting variation is for the ``std::vector`` where we exploit ``.reserve()``
to reduce reallocation.

.. code-block:: cpp

    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_tuple_to_cpp_std_list_like(PyObject *op, std::vector<T> &container) {
        // Reserve the vector, but only if it is a tuple. If not then ignore it as
        // very_generic_py_unary_to_cpp_std_list_like() will error
        if (py_tuple_check(op)) {
            container.reserve(py_tuple_len(op));
        }
        return very_generic_py_unary_to_cpp_std_list_like<
            std::vector, T, PyObject_Check, PyObject_Convert,
            &py_tuple_check, &py_tuple_len, &py_tuple_get
        >(op, container);
    }

    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_tuple_to_cpp_std_list_like(PyObject *op, std::list<T> &container) {
        return very_generic_py_unary_to_cpp_std_list_like<
            std::list, T, PyObject_Check, PyObject_Convert,
            &py_tuple_check, &py_tuple_len, &py_tuple_get
        >(op, container);
    }

The declarations for Python ``tuple`` to a C++ ``std::vector`` are auto-generated in ``auto_py_convert_internal.h``.
Here shown just for ``long``:

.. code-block:: cpp

    // Base declaration
    template<typename T>
    int
    py_tuple_to_cpp_std_list_like(PyObject *op, std::vector<T> &container);

    // Instantiations
    template <>
    int
    py_tuple_to_cpp_std_list_like<long>(PyObject *op, std::vector<long> &container);

The definitions are auto-generated in ``auto_py_convert_internal.cpp``, here shown just for ``long``:

.. code-block:: cpp

    template <>
    int
    py_tuple_to_cpp_std_list_like<long>(PyObject *op, std::list<long> &container) {
        return generic_py_tuple_to_cpp_std_list_like<
            long, &py_long_check, &py_long_to_cpp_long
        >(op, container);
    }

Python ``set`` and ``frozenset``
----------------------------------------

Here is the handwritten code in ``python_convert.h`` supports the conversion too and from a Python ``set``
or ``frozenset`` to and from a a C++ ``std::unordered_set``.

Conversion From C++ to Python
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

    template<
            typename T,
            PyObject *(*ConvertCppToPy)(const T &),
            PyObject *(*PyContainer_New)(PyObject *)
    >
    PyObject *
    generic_cpp_std_unordered_set_to_py_set_or_frozenset(const std::unordered_set<T> &set) {
        // Handwritten implementation. Omitted for simplicity.
    }

The template types are:

.. list-table:: Convert a ``std::unordered_set`` to a Python ``set`` or ``frozenset``.
   :widths: 30 30
   :header-rows: 1

   * - Type
     - Description
   * - ``typename T``
     - The C++ type of each object in the container.
   * - ``PyObject *(*ConvertCppToPy)(const T &)``
     - A pointer to a function that takes a type ``T`` and returns a new Python ``PyObject*``.
   * - ``PyObject *(*PyUnaryContainer_New)(size_t)``
     - A pointer to a function that returns a new Python container.

And the parameters are:

.. list-table:: Function to convert a ``std::vector`` or ``std::list`` to a Python ``tuple`` or ``list``.
   :widths: 30 30
   :header-rows: 1

   * - Parameter
     - Description
   * - ``set``
     - The C++ container.

This returns a new PyObject or NULL on failure.

Here is the handwritten specialisations in ``python_convert.h`` supports the conversion too and from a Python ``set``
and ``frozenset``.
They are basically one-liners.

.. code-block:: cpp

    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_unordered_set_to_py_set(const std::unordered_set<T> &set) {
        return generic_cpp_std_unordered_set_to_py_set_or_frozenset<
            T, ConvertCppToPy, &PySet_New
        >(set);
    }

    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_unordered_set_to_py_frozenset(const std::unordered_set<T> &set) {
        return generic_cpp_std_unordered_set_to_py_set_or_frozenset<
            T, ConvertCppToPy, &PyFrozenSet_New
        >(set);
    }

Then declarations are auto-generated in ``auto_py_convert_internal.h``, here shown just for a Python
``set`` containing ``long``:

.. code-block:: cpp

    // Base declaration
    template<typename T>
    PyObject *
    cpp_std_unordered_set_to_py_set(const std::unordered_set<T> &container);

    // Instantiations
    template <>
    PyObject *
    cpp_std_unordered_set_to_py_set<long>(const std::unordered_set<long> &container);

    // And so on..

The definitions are auto-generated in ``auto_py_convert_internal.cpp``, here shown just for a Python
``set`` containing ``long``:

.. code-block:: cpp

    template <>
    PyObject *
    cpp_std_unordered_set_to_py_set<long>(const std::unordered_set<long> &container) {
        return generic_cpp_std_unordered_set_to_py_set<long, &cpp_long_to_py_long>(container);
    }

    // And so on..

Conversion From Python to C++
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

    template<
            typename T,
            int (*PyContainer_Check)(PyObject *),
            int (*PyObject_Check)(PyObject *),
            T (*PyObject_Convert)(PyObject *)
    >
    int generic_py_set_or_frozenset_to_cpp_std_unordered_set(
        PyObject *op, std::unordered_set<T> &set
    ) {
        // Handwritten. Omitted for simplicity.
    }

Template parameters are:

.. list-table:: Template to convert a Python ``set`` or ``frozenset`` to a ``std::unordered)set``.
   :widths: 30 30
   :header-rows: 1

   * - Type
     - Description
   * - ``typename T``
     - The C++ type of the object.
   * - ``int(*PyUnaryContainer_Check)(PyObject *)``
     - A pointer to a function returns true if the Python container is of the relevant type (``set`` or ``frozenset`` in this case).
   * - ``int (*PyObject_Check)(PyObject *)``
     - A pointer to a function returns true if Python object can be converted to a C++ object of type ``T``.
   * - ``T (*PyObject_Convert)(PyObject *)``
     - A pointer to a function to convert a Python object to a C++ object of type ``T``.

Parameters are:

.. list-table:: Function to convert a Python ``set`` or ``frozenset`` to a ``std::unordered)set``.
   :widths: 30 30
   :header-rows: 1

   * - Parameter
     - Description
   * - ``op``
     - The Python container.
   * - ``set``
     - The C++ container. This will be empty on failure.

This returns zero on success, non-zero on failure.
Failure reasons can be:

* The Python object is not the expected container type.
* A Python object in the container is ``NULL``.
* A Python object in the container can not be converted to a C++ type ``T``.

Here are the specialisations for ``set`` and ``frozenset``:

.. code-block:: cpp

    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_set_to_cpp_std_unordered_set(PyObject *op, std::unordered_set<T> &set) {
        return generic_py_set_or_frozenset_to_cpp_std_unordered_set<
            T, &py_set_check, PyObject_Check, PyObject_Convert
        >(op, set);
    }

    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_frozenset_to_cpp_std_unordered_set(PyObject *op, std::unordered_set<T> &set) {
        return generic_py_set_or_frozenset_to_cpp_std_unordered_set<
            T, &py_frozenset_check, PyObject_Check, PyObject_Convert
        >(op, set);
    }


The declarations are auto-generated in ``auto_py_convert_internal.h``, here shown just for a Python
``set`` containing ``long``:

.. code-block:: cpp

    // Base declaration
    template<typename T>
    int
    py_set_to_cpp_std_unordered_set(
        PyObject *op, std::unordered_set<T> &container
    );

    // Instantiations
    template <>
    int
    py_set_to_cpp_std_unordered_set<long>(
        PyObject *op, std::unordered_set<long> &container
    );

    // And so on..

The definitions are auto-generated in ``auto_py_convert_internal.cpp``, here shown just for a Python
``set`` containing ``long``:

.. code-block:: cpp

    template <>
    int
    py_set_to_cpp_std_unordered_set<long>(
        PyObject *op, std::unordered_set<long> &container
    ) {
        return generic_py_set_to_cpp_std_unordered_set<
            long, &py_long_check, &py_long_to_cpp_long
        >(op, container);
    }

    // And so on..

Python ``dict``
-----------------------

This supports the two-way conversion from a Python ``dict`` to and from a C++ ``std::unordered_map`` or a ``std::map``.

Conversion From C++ to Python
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A handwritten function  in ``python_convert.h`` provides the basis for specialisation:

.. code-block:: cpp

    template<
            template<typename ...> class Map,
            typename K,
            typename V,
            PyObject *(*Convert_K)(const K &),
            PyObject *(*Convert_V)(const V &)
    >
    PyObject *
    generic_cpp_std_map_like_to_py_dict(const Map<K, V> &map) {
        // Handwritten function. Omitted for simplicity.
    }

The template types are:

.. list-table:: Convert a ``std::map`` or ``std::unordered_map`` to a Python ``dict``.
   :widths: 30 30
   :header-rows: 1

   * - Type
     - Description
   * - ``Map``
     - The C++ container, for example a ``std::map`` or a ``std::unordered_map``.
   * - ``typename K``
     - The C++ type of the keys in the container.
   * - ``typename V``
     - The C++ type of the values in the container.
   * - ``PyObject *(*Convert_K)(const T &)``
     - A pointer to a function that takes a type ``K`` and returns a new Python ``PyObject *``.
   * - ``PyObject *(*Convert_V)(const T &)``
     - A pointer to a function that takes a type ``V`` and returns a new Python ``PyObject *``.

And the parameters are:

.. list-table:: Function to convert a ``std::map`` or ``std::unordered_map`` to a Python ``dict``.
   :widths: 30 30
   :header-rows: 1

   * - Parameter
     - Description
   * - ``map``
     - The C++ container.

This returns a new PyObject or NULL on failure.

The specialised declarations are auto-generated in ``auto_py_convert_internal.h``, here shown just for a Python
``dict`` from a ``std::unordered_map`` or a ``std::map`` containing ``long, long``:

.. code-block:: cpp

    // Base declaration
    template<template<typename ...> class Map, typename K, typename V>
    PyObject *
    cpp_std_map_like_to_py_dict(const Map<K, V> &map);

    // Instantiations
    template <>
    PyObject *
    cpp_std_map_like_to_py_dict<std::unordered_map, long, long>(
        const std::unordered_map<long, long> &map
    );

    template <>
    PyObject *
    cpp_std_map_like_to_py_dict<std::map, long, long>(
        const std::map<long, long> &map
    );

The definitions are auto-generated in ``auto_py_convert_internal.cpp``, here shown just for a Python
``dict`` from a ``std::unordered_map`` containing ``long, long``:

.. code-block:: cpp

    template <>
    PyObject *
    cpp_std_map_like_to_py_dict<std::unordered_map, long, long>(
        const std::unordered_map<long, long> &map
    ) {
        return generic_cpp_std_map_like_to_py_dict<
            std::unordered_map,
            long, long,
            &cpp_long_to_py_long, &cpp_long_to_py_long
        >(map);
    }

Conversion From Python to C++
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The reverse, converting from Python to C++, is accomplished by a single handwritten template in ``python_convert.h``:

.. code-block:: cpp

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
        // Handwritten function. Omitted for simplicity.
    }

Template parameters are:

.. list-table:: Template to convert a Python ``dict`` to a ``std::map`` or a ``std::unordered_map``.
   :widths: 30 30
   :header-rows: 1

   * - Type
     - Description
   * - ``Map``
     - The C++ container, for example a ``std::map`` or a ``std::unordered_map``.
   * - ``typename K``
     - The C++ type of the keys.
   * - ``typename V``
     - The C++ type of the values.
   * - ``int (*Check_K)(PyObject *)``
     - A pointer to a function returns true if Python object can be converted to a C++ object of type ``K``.
   * - ``int (*Check_V)(PyObject *)``
     - A pointer to a function returns true if Python object can be converted to a C++ object of type ``V``.
   * - ``T (*Convert_K)(PyObject *)``
     - A pointer to a function to convert a Python object to a C++ object of type ``K``.
   * - ``T (*Convert_V)(PyObject *)``
     - A pointer to a function to convert a Python object to a C++ object of type ``V``.

Parameters are:

.. list-table:: Function to convert a ``std::vector`` or ``std::list`` to a Python ``tuple`` or ``list``.
   :widths: 30 30
   :header-rows: 1

   * - Parameter
     - Description
   * - ``dict``
     - The Python container.
   * - ``map``
     - The C++ container. This will be empty on failure.

This returns zero on success, non-zero on failure.
Failure reasons can be:

* The Python object is not the expected container type.
* A Python object in the container is ``NULL``.
* A Python object in the container can not be converted to a C++ type ``K`` or ``V``.

The declarations are auto-generated in ``auto_py_convert_internal.h``, here shown just for a Python
``dict`` from a ``std::unordered_map`` or ``std::map`` containing ``long, long``:

.. code-block:: cpp

    // Base declaration
    template<template<typename ...> class Map, typename K, typename V>
    int
    py_dict_to_cpp_std_map_like(PyObject *op, Map<K, V> &map);

    // Instantiations
    template <>
    int
    py_dict_to_cpp_std_map_like<std::unordered_map, long, long>(
        PyObject* op, std::unordered_map<long, long> &map
    );

    template <>
    int
    py_dict_to_cpp_std_map_like<std::map, long, long>(
        PyObject* op, std::map<long, long> &map
    );

The definitions are auto-generated in ``auto_py_convert_internal.cpp``, here shown just for a Python
``dict`` from a ``std::unordered_map`` containing ``long, long``:

.. code-block:: cpp

    template <>
    int
    py_dict_to_cpp_std_map_like<std::unordered_map, long, long>(
        PyObject* op, std::unordered_map<long, long> &map
    ) {
        return generic_py_dict_to_cpp_std_map_like<
            std::unordered_map,
            long, long,
            &py_long_check, &py_long_check,
            &py_long_to_cpp_long, &py_long_to_cpp_long
        >(op, map);
    }

Code Generation
----------------------

If necessary run the code generator:

.. code-block:: shell

    cd src/py
    python code_gen.py

Which should give you something like:

.. code-block:: shell

    venv/bin/python src/py/code_gen.py
    Version: 0.4.0
    Target directory "src/cpy"
    Writing declarations to "src/cpy/auto_py_convert_internal.h"
    Wrote 4125 lines of code with 356 declarations.
    Writing definitions to  "src/cpy/auto_py_convert_internal.cpp"
    Wrote 3971 lines of code with 352 definitions.

    Process finished with exit code 0
