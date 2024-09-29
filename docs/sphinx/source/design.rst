.. moduleauthor:: Paul Ross <apaulross@gmail.com>
.. sectionauthor:: Paul Ross <apaulross@gmail.com>

.. PythonCppContainers Design

.. _PythonCppContainers.Design:

Design
==================

This library uses C++ templates but not in a particularly complex way.
There are six essential C++ templates and a Python script is used to to auto-generate the partial template
specialisations and their instantiations.

As described in the previous chapter new types can be added pretty easily, alternatively the code generator can be
manipulated to do this.

Source Files ``python_object_convert.h`` and ``python_object_convert.cpp``
-----------------------------------------------------------------------------------

These are hand written files that contains implementations of functions to convert Python types to and from their
C++ equivalent.
There are three functions to each type:

* Convert a C++ value to a new Python object.
* Convert a Python object to a C++ value.
* Check that a Python object is of the expected type.

For example here are the three functions for Python ``int`` and C++ ``long``:

.. code-block:: c

    PyObject *cpp_long_to_py_long(const long &l);
    long py_long_to_cpp_long(PyObject *op);
    int py_long_check(PyObject *op);

The implementations of these are just one line wrappers around functions or macros in the Python C API.

``python_container_convert.h`` and ``python_container_convert.cpp``
---------------------------------------------------------------------------

This is a hand written file that contains implementations of functions to create and access Python unary containers
(``list``, ``tuple``, ``set``).
There are a number off functions to each container, for example a list:

* Check that a Python object is of the expected type.
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

``python_convert.h``
---------------------

This is a hand written file that contains templates that convert containers to and fro between Python  and C++.
It includes ``python_object_convert.h`` and ``python_container_convert.h``, declares the templates then
includes ``auto_py_convert_internal.h``.

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

.. list-table:: Convert a ``std::vector`` or ``std::list`` to a Python ``tuple`` or ``list``.
   :widths: 30 30
   :header-rows: 1

   * - Type
     - Description
   * - ``ListLike``
     - The C++ container, for example a ``std::vector`` or a ``std::list``.
   * - ``typename T``
     - The C++ type of each object in the container.
   * - ``PyObject *(*Convert)(const T &)``
     - A pointer to a function that takes a type ``T`` and returns a new Python ``PyObject*``.
   * - ``PyObject *(*PyUnary_New)(size_t)``
     - A pointer to a function that returns a new Python container of the given length.
   * - ``int(*PyUnary_Set)(PyObject *, size_t, PyObject *)>``
     - Sets a Python object in the Python container at the given position.

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
``bool``, ``long``, ``double``, ``std::vector<char>`` and ``std::string``.

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

This covers conversion From a Python ``list`` or ``tuple`` to a C++ ``std::vector<T>`` or ``std::list<T>``.
It follows a similar pattern as described above.

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

.. list-table:: Template to convert a ``std::vector`` or ``std::list`` to a Python ``tuple`` or ``list``.
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

This template is then partially specified with handwritten code.
Here is the handwritten code in ``python_convert.h`` for Python ``tuple`` to a C++ ``std::vector`` or ``std::list``.
They are basically one-liners, the interesting variation is for the ``std::vector`` where we exploit ``.reserve()``
to reduce reallocations.

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
        // Handwritten
    }

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
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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
        // Handwritten
    }

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

A hanbdwritten function  in ``python_convert.h`` provides the basis for specialisation:

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
        // Handwritten function.
    }

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
        // Handwritten function.
    }

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
