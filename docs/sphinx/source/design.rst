

Design
==================




``python_convert.h``
---------------------

This is a hand written file that contains:

* Functions to convert objects to and fro between Python and C++.
  See "Conversion of Objects" below.
* Function to create and  access Python containers such as ``tuples``, ``lists`` etc.
  See "Creating and Accessing Python Containers" below.
* Templates that convert containers to and fro between Python  and C++.
  These are described in detail below.

Conversion of Objects
^^^^^^^^^^^^^^^^^^^^^^^^^^

These are wrappers around existing Python C API functions.
There are the following functions for each supported object type:

* Check that a Python ``PyObject *`` is of the correct object type.
* Convert a Python ``PyObject *`` to a C++ fundamental type.
* Create a new Python ``PyObject *`` from a C++ fundamental type.

Their implementations are in ``python_convert.cpp``

For example for Python floats to and from a C++ ``double`` there will  be these function  implementations:

.. code-block:: C++

    PyObject *py_float_from_double(const double &d) {
        return PyFloat_FromDouble(d);
    }
    double py_float_as_double(PyObject *op) {
        assert(py_float_check(op));
        return PyFloat_AsDouble(op);
    }
    int py_float_check(PyObject *op) {
        return PyFloat_Check(op);
    }

Creating and Accessing Python Containers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

These are wrappers around existing Python C API functions.
There are the following functions for each supported object type:

* Check that a Python ``PyObject *`` is of the correct container type.
* Create a new Python ``PyObject *`` container.
* Set a new ``PyObject *`` in the container.
* Get a new ``PyObject *`` from the container.

Their implementations are in ``python_convert.cpp``

For example for a Python tuple there will be these function implementations:

.. code-block:: C++

    // Tuple check, create, set, get functions.
    int py_tuple_check(PyObject *op) {
        return PyTuple_Check(op);
    }
    PyObject *py_tuple_new(size_t len) {
        return PyTuple_New(len);
    }
    Py_ssize_t py_tuple_len(PyObject *op) {
        return PyTuple_Size(op);
    }
    int py_tuple_set(PyObject *tuple_p, size_t pos, PyObject *op) {
        PyTuple_SET_ITEM(tuple_p, pos, op);
        return 0;
    }
    PyObject *py_tuple_get(PyObject *tuple_p, size_t pos) {
        return PyTuple_GET_ITEM(tuple_p, pos);
    }

Conversion Templates
---------------------

Python Lists and Tuples
-----------------------

Conversion From a ``std::vector<T>`` to a Python List or Tuple
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: C++

    template<typename T,
            PyObject *(*Convert)(const T &),
            PyObject *(*PyUnary_New)(size_t),
            int(*PyUnary_Set)(PyObject *, size_t, PyObject *)>
    PyObject *
    generic_cpp_std_vector_to_py_unary(const std::vector<T> &vec) {


.. list-table:: Convert a ``std::vector`` to a Python Tuple or List.
   :widths: 30 30
   :header-rows: 1

   * - Type
     - Description
   * - ``typename T``
     - The C++ type of the object.
   * - ``PyObject *(*Convert)(const T &)``
     - A pointer to a function that takes a type ``T`` and returns a new Python object.
   * - ``PyObject *(*PyUnary_New)(size_t)``
     - A pointer to a function that returns a new Python container of the given length.
   * - ``int(*PyUnary_Set)(PyObject *, size_t, PyObject *)>``
     - Sets a Python object in the Python container at the given position.

This template is then partially specified for both tuples and lists of type ``T``:

.. code-block:: C++

    template<typename T, PyObject *(*Convert)(const T &)>
    PyObject *
    generic_cpp_std_vector_to_py_tuple(const std::vector<T> &vec) {
        return generic_cpp_std_vector_to_py_unary<T,
                                                  Convert,
                                                  &py_tuple_new,
                                                  &py_tuple_set>(vec);
    }

    template<typename T, PyObject *(*Convert)(const T &)>
    PyObject *
    generic_cpp_std_vector_to_py_list(const std::vector<T> &vec) {
        return generic_cpp_std_vector_to_py_unary<T,
                                                  Convert,
                                                  &py_list_new,
                                                  &py_list_set>(vec);
    }

Conversion From a Python List or Tuple to a ``std::vector<T>``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: C++

    template<typename T,
            int (*Check)(PyObject *),
            T (*Convert)(PyObject *),
            int(*PyUnary_Check)(PyObject *),
            Py_ssize_t(*PyUnary_Size)(PyObject *),
            PyObject *(*PyUnary_Get)(PyObject *, size_t)>
    int generic_py_unary_to_cpp_std_vector(PyObject *op, std::vector<T> &vec) {


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

.. code-block:: C++

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

