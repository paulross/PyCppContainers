

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

