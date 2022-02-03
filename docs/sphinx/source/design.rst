.. moduleauthor:: Paul Ross <apaulross@gmail.com>
.. sectionauthor:: Paul Ross <apaulross@gmail.com>

.. PythonCppContainers Design

.. _PythonCppContainers.Design:

Design
==================

This library uses C++ templates but not in a particularly complex way.
There are six essential C++ templates and a Python script is used to to auto-generate the partial template specialisations and their instantiations.

``python_object_convert.h`` and ``python_object_convert.cpp``
-----------------------------------------------------------------

This is a hand written file that contains implementations of functions to convert Python types to their C++ equivalent.
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
It includes ``python_object_convert.h`` and ``python_container_convert.h``, declares the templates then includes ``auto_py_convert_internal.h``.


Conversion Templates
---------------------

Python Lists and Tuples
-----------------------

There are several levels of specialisation here as we want to support

Conversion From a ``std::vector<T>`` or a ``std::list<T>`` to a Python List or Tuple
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

    template<
            template<typename ...> class ListLike,
            typename T,
            PyObject *(*ConvertCppToPy)(const T &),
            PyObject *(*PyUnaryContainer_New)(size_t),
            int(*PyUnaryContainer_Set)(PyObject *, size_t, PyObject *)>
    PyObject *
    very_generic_cpp_std_list_like_to_py_unary(const ListLike<T> &list_like) {


.. list-table:: Convert a ``std::vector`` to a Python Tuple or List.
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

This template is then partially specified four ways for both tuples and lists from ``std::vector<T>`` and ``std::list<T>``:

.. code-block:: cpp

    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_like_to_py_tuple(const std::vector<T> &container) {
        return very_generic_cpp_std_list_like_to_py_unary<std::vector, T, ConvertCppToPy, &py_tuple_new, &py_tuple_set>(
                container);
    }

    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_like_to_py_tuple(const std::list<T> &container) {
        return very_generic_cpp_std_list_like_to_py_unary<std::list, T, ConvertCppToPy, &py_tuple_new, &py_tuple_set>(
                container);
    }

    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_like_to_py_list(const std::vector<T> &container) {
        return very_generic_cpp_std_list_like_to_py_unary<std::vector, T, ConvertCppToPy, &py_list_new, &py_list_set>(
                container);
    }

    template<typename T, PyObject *(*ConvertCppToPy)(const T &)>
    PyObject *
    generic_cpp_std_list_like_to_py_list(const std::list<T> &container) {
        return very_generic_cpp_std_list_like_to_py_unary<std::list, T, ConvertCppToPy, &py_list_new, &py_list_set>(
                container);
    }


Then these are specialised by auto-generated in ``auto_py_convert_internal.h`` code for the types ``bool``, ``long``, ``double``, ``std::vector<char>`` and ``std::string``.
Their declarations are:

.. code-block:: cpp

    // Base declaration
    template<typename T>
    PyObject *
    cpp_std_list_like_to_py_tuple(const std::vector<T> &container);

    // Instantiations
    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<bool>(const std::vector<bool> &container);

    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<long>(const std::vector<long> &container);

    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<double>(const std::vector<double> &container);

    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<std::vector<char>>(const std::vector<std::string> &container);

    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<std::string>(const std::vector<std::string> &container);

Their declarations are auto-generated in ``auto_py_convert_internal.cpp``:

.. code-block:: cpp

    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<bool>(const std::vector<bool> &container) {
        return generic_cpp_std_list_like_to_py_tuple<bool, &cpp_bool_to_py_bool>(container);
    }

    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<long>(const std::vector<long> &container) {
        return generic_cpp_std_list_like_to_py_tuple<long, &cpp_long_to_py_long>(container);
    }

    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<double>(const std::vector<double> &container) {
        return generic_cpp_std_list_like_to_py_tuple<double, &cpp_double_to_py_float>(container);
    }

    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<std::complex<double>>(const std::vector<std::complex<double>> &container) {
        return generic_cpp_std_list_like_to_py_tuple<std::complex<double>, &cpp_complex_to_py_complex>(container);
    }

    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<std::vector<char>>(const std::vector<std::vector<char>> &container) {
        return generic_cpp_std_list_like_to_py_tuple<std::vector<char>, &cpp_vector_char_to_py_bytes>(container);
    }

    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<std::string>(const std::vector<std::string> &container) {
        return generic_cpp_std_list_like_to_py_tuple<std::string, &cpp_string_to_py_unicode>(container);
    }

That is for ``std::vector``, for ``std::list`` the declarations and definitions are very similar in ``auto_py_convert_internal.h``:


.. code-block:: cpp

    // Base declaration
    template<typename T>
    PyObject *
    cpp_std_list_like_to_py_tuple(const std::list<T> &container);

    // Instantiations
    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<bool>(const std::list<bool> &container);

    // And so on...

And their declarations are auto-generated in ``auto_py_convert_internal.cpp``:

.. code-block:: cpp

    template <>
    PyObject *
    cpp_std_list_like_to_py_tuple<bool>(const std::list<bool> &container) {
        return generic_cpp_std_list_like_to_py_tuple<bool, &cpp_bool_to_py_bool>(container);
    }

    // And so on...


Conversion From a Python List or Tuple to a ``std::vector<T>``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

    template<typename T,
            int (*Check)(PyObject *),
            T (*Convert)(PyObject *),
            int(*PyUnary_Check)(PyObject *),
            Py_ssize_t(*PyUnary_Size)(PyObject *),
            PyObject *(*PyUnary_Get)(PyObject *, size_t)>
    int generic_py_unary_to_cpp_std_vector(PyObject *op, std::vector<T> &vec);


.. list-table:: Convert a ``std::vector`` to a Python Tuple or List.
   :widths: 30 30
   :header-rows: 1

   * - Type
     - Description
   * - ``typename T``
     - The C++ type of the object.
   * - ``int (*Check)(PyObject *)``
     - A pointer to a function returns true if Python object can be converted to type ``T``.
   * - ``int(*PyUnary_Check)(PyObject *)``
     - A pointer to a function that returns true if the given Python container of the  correct type (list or tuple respectively).
   * - ``Py_ssize_t(*PyUnary_Size)(PyObject *)``
     - A pointer to a function that returns the size of the Python container.
   * - ``PyObject *(*PyUnary_Get)(PyObject *, size_t)``
     - Gets a Python object in the Python container at the given position.

This template is then partially specified for both tuples and lists of type ``T``:

.. code-block:: cpp

    template<typename T, int (*Check)(PyObject *), T (*Convert)(PyObject *)>
    int generic_py_tuple_to_cpp_std_vector(PyObject *op, std::vector<T> &vec) {
        return generic_py_unary_to_cpp_std_vector<T,
                                                  Check,
                                                  Convert,
                                                  &py_tuple_check,
                                                  &py_tuple_len,
                                                  &py_tuple_get>(op, vec);
    }

    template<typename T, int (*Check)(PyObject *), T (*Convert)(PyObject *)>
    int generic_py_list_to_cpp_std_vector(PyObject *op, std::vector<T> &vec) {
        return generic_py_unary_to_cpp_std_vector<T,
                                                  Check,
                                                  Convert,
                                                  &py_list_check,
                                                  &py_list_len,
                                                  &py_list_get>(op, vec);
    }

Then these are specialised by auto-generated in ``auto_py_convert_internal.h`` code for the types ``bool``, ``long``, ``double`` and ``sts::string``.
Their declarations for tuple are (similarly for lists):

.. code-block:: cpp

    // Base declaration
    template<typename T>
    int
    py_tuple_to_cpp_std_vector(PyObject *tuple, std::vector<T> &container);

    // Instantiations
    template <>
    int
    py_tuple_to_cpp_std_vector<bool>(PyObject *tuple, std::vector<bool> &container);

    template <>
    int
    py_tuple_to_cpp_std_vector<long>(PyObject *tuple, std::vector<long> &container);

    template <>
    int
    py_tuple_to_cpp_std_vector<double>(PyObject *tuple, std::vector<double> &container);

    template <>
    int
    py_tuple_to_cpp_std_vector<std::string>(PyObject *tuple, std::vector<std::string> &container);

Their definitions for tuple are are auto-generated in ``auto_py_convert_internal.cpp`` (similarly for lists):

.. code-block:: cpp

    template <>
    int
    py_tuple_to_cpp_std_vector<bool>(PyObject *op, std::vector<bool> &container) {
        return generic_py_tuple_to_cpp_std_vector<bool, &py_bool_check, &py_bool_to_cpp_bool>(op, container);
    }

    template <>
    int
    py_tuple_to_cpp_std_vector<long>(PyObject *op, std::vector<long> &container) {
        return generic_py_tuple_to_cpp_std_vector<long, &py_long_check, &py_long_to_cpp_long>(op, container);
    }

    template <>
    int
    py_tuple_to_cpp_std_vector<double>(PyObject *op, std::vector<double> &container) {
        return generic_py_tuple_to_cpp_std_vector<double, &py_float_check, &py_float_to_cpp_double>(op, container);
    }

    template <>
    int
    py_tuple_to_cpp_std_vector<std::string>(PyObject *op, std::vector<std::string> &container) {
        return generic_py_tuple_to_cpp_std_vector<std::string, &py_bytes_check, &py_bytes_to_cpp_string>(op, container);
    }
