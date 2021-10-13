*********************
Introduction
*********************

Python is well known for it's ability to handle *heterogeneous* data in containers such as lists.
But what if you need to interact with C++ containers such as ``std::vector<T>`` that require *homogeneous* data types?


This project is about converting Python containers (``list``, ``dict``, ``set``, ``tuple``) containing homogeneous types
to and from their C++ equivalent.

A Problematic Example
========================

Suppose that you have a Python list of floats and need to pass it to a C++ library that expects a ``std::vector<double>``.

To convert that Python list to a C++ ``std::vector<double>`` might look like this:

.. code-block:: cpp

    PyObject *example(PyObject *op) {
        std::vector<double> vec;
        // Populate the vector, function to be defined...
        write_to_vector(op, vec);
        // Do something in C++ with the vector...
    }

If the result of that call modifies the C++ vector, or creates a new one, you need to return a Python list of floats
from the result.
Perhaps by adding code such as:

.. code-block:: cpp

    PyObject *example(PyObject *op) {
        // Do something in C++ with the vector...
        // Convert the vector back to a Python list.
        // Function to be defined...
        return read_from_vector(vec);
    }

What should the implementation of ``write_to_vector()`` and ``read_from_vector()`` look like?

The answer seems fairly simple; firstly ``write_to_vector`` converting a Python list to a C++ ``std::vector<double>``:

.. code-block:: cpp

    void write_to_vector(PyObject *op, std::vector<double> &vec) {
        vec.clear();
        for (Py_ssize_t i = 0; i < PyList_Size(op); ++i) {
            vec.push_back(PyFloat_AsDouble(PyList_GET_ITEM(op, i)));
        }
    }

And the inverse, ``read_from_vector`` creating a new Python list from a C++ ``std::vector<double>``:

.. code-block:: cpp

    PyObject *read_from_vector(const std::vector<double> &vec) {
        PyObject *ret = PyList_New(vec.size());
        for (size_t i = 0; i < vec.size(); ++i) {
            PyList_SET_ITEM(ret, i, PyFloat_FromDouble(vec[i]));
        }
        return ret;
    }

This is fine, except notice the absence of error handling above, and all errors are runtime errors.
And runtime errors are much harder to deal with than compile time errors.

TODO:

Until you want to support other object types, say ``int``, ``bytes``.
It gets worse when you want to support other containers such as (``tuple``, ``set``, ``dict``).
Then you have to write individual conversion functions for all the combinations of object types *and* containers.

The problem with this approach is that functions have to be written
for every combination of interesting types (``float``, ``int``, ``bytes``) **and** every container of interest
(``tuple``, ``list``, ``set``, ``dict``).
This is tedious and error prone.

Also, notice the absence of error handling above, and all errors are runtime errors.

Why This Project
=========================

Instead this project makes extensive use of C++ templates, partial template specialisation and code generation to reduce
dramatically the amount of hand maintained code.
It also converts many runtime errors to compile time errors.

If we want to support a fairly basic set of types:

.. list-table:: Supported Object types.
   :widths: 30 30
   :header-rows: 1

   * - Python Type
     - C++ Type
   * - ``True``, ``False``
     - ``bool``
   * - ``int``
     - ``long``
   * - ``float``
     - ``double``
   * - ``bytes``
     - ``std::string``

And a basic set of containers:

.. list-table:: Supported Containers.
   :widths: 50 50
   :header-rows: 1

   * - Python Type
     - C++ Type
   * - ``tuple``
     - ``std::vector``
   * - ``list``
     - ``std::vector``
   * - ``set``
     - ``std::unordered_set``
   * - ``frozenset``
     - ``std::unordered_set``
   * - ``dict``
     - ``std::unordered_map``

The number of conversion functions is worse than the cartesian product of the types and containers.
In the case of a dict the types can appear as either a key or a value.

For example for unary containers (``tuple``, ``list``, ``set``, ``frozenset``) there are five containers with four types and two functions (to give two way conversion).
Thus 4 * 4 * 2 = 32 functions.

For ``dict`` there are four types but the key and the value can be either so 16 possible type pair combinations.
With two functions for each to give two way conversion this means 32 conversion functions.

Thus the combination of ``bool``, ``int``, ``float``, ``bytes`` and containers ``tuple``, ``list``, ``set`` and ``dict`` requires 56 conversion functions to write and debug.

The aim of this project is to reduce this amount of code to a manageable level.
It uses a mix of C++ templates and code generators to achieve this.
The result is a few small functions for objects and a pair of hand written templates for each container.
As lists and tuples are very similar the code is reduced even further.

The only hand written code that needs to be maintained is for the two-way conversions for any type are:

* Two C++ templates that handle all the ``tuple`` and ``list`` conversions.
* Two C++ templates that handle all the ``set`` and ``frozenset`` conversions.
* Two C++ templates that handle all the ``dict`` conversions.

This reduces 64 functions down to 6.


Hand Written Functions
=============================

There are only six non-trivial hand written functions along with a much larger of generated functions that successively
specialise these functions.
As an example, here how the function is developed that converts a Python list of ``float`` to a C++ ``std::vector<double>``.

Converting a Python tuple or list to a C++ ``std::vector<T>``
---------------------------------------------------------------------------------------

This generic function that works with unary Python containers (``tuple`` and ``list``) has a signature that looks like this:

.. code-block:: cpp

    template<typename T,
            int (*PyObject_Check)(PyObject *),
            T (*PyObject_Convert)(PyObject *),
            int(*PyUnaryContainer_Check)(PyObject *),
            Py_ssize_t(*PyUnaryContainer_Size)(PyObject *),
            PyObject *(*PyUnaryContainer_Get)(PyObject *, size_t)>
    int
    generic_py_unary_to_cpp_std_vector(PyObject *op, std::vector<T> &vec);

This template has these parameters:

.. list-table:: ``generic_py_unary_to_cpp_std_vector()`` template parameters.
   :widths: 20 50
   :header-rows: 1

   * - Template Parameter
     - Notes
   * - ``PyObject_Check``
     - A pointer to a function that checks that any ``PyObject *`` in the Python container is the correct type, for example that it is a ``bytes`` object.
   * - ``PyObject_Convert``
     - A pointer to a function that converts any ``PyObject *`` in the Python container to the C++ type, for example from ``bytes`` -> ``std::string``.
   * - ``PyUnaryContainer_Check``
     - A pointer to a function that checks that the ``PyObject *`` argument is the correct container type, for example a ``tuple``.
   * - ``PyUnaryContainer_Size``
     - A pointer to a function that returns the size of the Python container.
   * - ``PyUnaryContainer_Get``
     - A pointer to a function that gets a ``PyObject *`` from the Python container at a given index.

The function has the following parameters.

.. list-table:: ``generic_py_unary_to_cpp_std_vector()`` parameters.
   :widths: 20 20 50
   :header-rows: 1

   * - Type
     - Name
     - Notes
   * - ``PyObject *``
     - ``op``
     - The Python container to read from.
   * - ``std::vector<T>``
     - ``vec``
     - The C++ to write to.


Partial Specialisation to Convert a Python list to a C++ ``std::vector<T>``
---------------------------------------------------------------------------------

This template can be partially specialised for converting Python *lists* of any type to C++ ``std::vector<T>``.
This is hand written code but is just has a single function call.
Note the use of the function pointers to ``py_list_check``, ``py_list_len`` and ``py_list_get``.


.. code-block:: cpp

    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_list_to_cpp_std_vector(PyObject *op, std::vector<T> &vec) {
        return generic_py_unary_to_cpp_std_vector<T, PyObject_Check, PyObject_Convert,
            &py_list_check, &py_list_len, &py_list_get>(op, vec);
    }


Generated Functions
=============================

These are created by a script that takes the cartesian product of object types and container types and creates functions for each container/object.
For example, to convert a Python ``list`` of ``float`` to a C++ ``std::vector<double>`` the following are created:

A base declaration in *auto_py_convert_internal.h*:

.. code-block:: cpp

    template<typename T>
    int
    py_list_to_cpp_std_vector(PyObject *op, std::vector<T> &container);

And a concrete declaration for each C++ target type ``T`` in *auto_py_convert_internal.h*:

.. code-block:: cpp

    template <>
    int
    py_list_to_cpp_std_vector<double>(PyObject *op, std::vector<double> &container);


And the concrete definition is in *auto_py_convert_internal.cpp*:

.. code-block:: cpp

    template <>
    int
    py_list_to_cpp_std_vector<double>(PyObject *op, std::vector<double> &container) {
        return generic_py_list_to_cpp_std_vector<double, &py_float_check, &py_float_to_cpp_double>(
            op, container
        );
    }


This is the function hierarchy:

.. code-block::

                                    py_unary_to_cpp_vector                  <--- Hand written
                                              |
                            /---------------------------------\
                            |                                 |                 Hand written partial
            generic_py_list_to_cpp_std_vector       similarly for tuples    <-- specialisation
                            |                                 |                 (one liners).
                            |                                 |
                py_list_to_cpp_std_vector<T>                 ...            <-- Generated
                            |                                 |
            /-------------------------------\             /-------\
            |                               |             |       |             Generated declaration
    py_list_to_cpp_std_vector<double>      ...           ...     ...        <-- and implementation
                                                                                (one liners)


Usage
------

Using the concrete function is as simple as this:

.. code-block:: cpp

    // Create a PyObject* representing a list of Python floats.
    PyObject *op = PyList_New(3);
    PyList_SetItem(op, 0, PyFloat_FromDouble(21.0));
    PyList_SetItem(op, 1, PyFloat_FromDouble(42.0));
    PyList_SetItem(op, 2, PyFloat_FromDouble(3.0));

    // Create the output vector...
    std::vector<double> cpp_vector;

    // Template specialisation will automatically invoke the appropriate
    // function call.
    // It will be a compile time error if the container/type function
    // is not available.
    // At run time this will return zero on success, non-zero on failure,
    // for example if op is not a Python tuple or members of op can not be
    // converted to C++ doubles.
    int err = Python_Cpp_Containers::py_list_to_cpp_std_vector(op, cpp_vector);
    // Handle error checking...

    // Now convert back.
    // Again this will be a compile time error if the C++ type is not supported.
    PyObject *new_op  = Python_Cpp_Containers::cpp_std_vector_to_py_list(cpp_vector);
    // new_op is a Python list of floats.
    // new_op will be null on failure and a Python exception will have been set.







Converting a C++ ``std::vector<T>`` to a Python tuple or list
--------------------------------------------------------------------------------------------------------------------

The generic function signature looks like this:


.. code-block:: cpp

    template<typename T,
            PyObject *(*ConvertCppToPy)(const T &),
            PyObject *(*PyUnaryContainer_New)(size_t),
            int(*PyUnaryContainer_Set)(PyObject *, size_t, PyObject *)>
    PyObject *
    generic_cpp_std_vector_to_py_unary(const std::vector<T> &vec);








