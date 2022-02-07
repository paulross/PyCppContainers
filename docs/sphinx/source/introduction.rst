.. moduleauthor:: Paul Ross <apaulross@gmail.com>
.. sectionauthor:: Paul Ross <apaulross@gmail.com>

.. PythonCppContainers Introduction

.. _PythonCppContainers.Introduction:

*********************
Introduction
*********************

Python is well known for it's ability to handle *heterogeneous* data in containers such as lists.
But what if you need to interact with C++ containers such as ``std::vector<T>`` that require *homogeneous* data types?


This project is about converting Python containers (``list``, ``dict``, ``set``, ``frozenset``, ``tuple``) containing
homogeneous types (``bool``, ``int``, ``float``, ``complex``, ``bytes``, ``str``) to and from their C++ equivalent.


A Problematic Example
========================

Suppose that you have a Python list of floats and need to pass it to a C++ library that expects a ``std::vector<double>``.
If the result of that call modifies the C++ vector, or creates a new one, you need to return a Python list of floats
from the result.

Your code might look like this:

.. code-block:: cpp

    PyObject *example(PyObject *op) {
        std::vector<double> vec;
        // Populate the vector, function to be defined...
        write_to_vector(op, vec);
        // Do something in C++ with the vector
        // ...
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


There is no error handling here and all errors are runtime errors.

However if you need to support other object types, say lists of ``int``, ``str``, ``bytes`` then each one needs a pair of hand written functions.
It gets worse when you want to support other containers such as (``tuple``, ``list``, ``set``, ``frozenset``, ``dict``).
Then you have to write individual conversion functions for all the combinations of object types *and* containers.
This is tedious and error prone.

Why This Project
=========================

This project makes extensive use of C++ templates, partial template specialisation and code generation to reduce
dramatically the amount of hand maintained code.
It also converts many runtime errors to compile time errors.

This project supports two way conversion of this set of containers:

.. list-table:: Supported Containers.
   :widths: 50 50
   :header-rows: 1

   * - Python
     - C++ Equivalent
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

Which contain any of this set of types:

.. list-table:: Supported Object types.
   :widths: 30 30
   :header-rows: 1

   * - Python
     - C++ Equivalent
   * - ``True``, ``False``
     - ``bool``
   * - ``int``
     - ``long``
   * - ``float``
     - ``double``
   * - ``complex``
     - ``std::complex<double>``
   * - ``bytes``
     - ``std::vector<char>``
   * - ``str``
     - ``std::string``

The number of possible conversion functions is worse than the cartesian product of the types and containers as in the case of a
dict the types can appear as either a key or a value.

The tables above would normally require 120 conversion functions to be written, tested and documented [#]_ .

This project simplifies this by using a mix of C++ templates and code generators to reduce this number to just
**six** hand written templates for all 120 cases.

* Two C++ templates for Python ``tuple`` / ``list`` two way conversions for all types.
* Two C++ templates for Python ``set`` / ``frozenset`` two way conversions for all types.
* Two C++ templates for Python ``dict`` two way conversions for all type combinations.

These templates are fairly simple, comprehensible and, for simplicity, code generation is done with a Python script is used
to create the final, instantiated, 120 functions.

Hand Written Functions
=============================

There are only six non-trivial hand written functions along with a much larger of generated functions that successively
specialise these functions.

As an example, here how the function is developed that converts a Python list of ``float`` to a C++ ``std::vector<double>``.

Converting a Python tuple or list to a C++ ``std::vector<T>``
---------------------------------------------------------------------------------------

This generic function that converts unary Python indexed containers (``tuple`` and ``list``) to a C++ ``std::vector<T>``
or ``std::list<T>`` for any type has this signature:

.. code-block:: cpp

    template<
            template<typename ...> class ListLike,
            typename T,
            int (*PyObject_Check)(PyObject *),
            T (*PyObject_Convert)(PyObject *),
            int(*PyUnaryContainer_Check)(PyObject *),
            Py_ssize_t(*PyUnaryContainer_Size)(PyObject *),
            PyObject *(*PyUnaryContainer_Get)(PyObject *, size_t)>
    int even_more_generic_py_unary_to_cpp_std_list_like(PyObject *op, ListLike<T> &list_like) {

This template has these parameters:

.. list-table:: ``even_more_generic_py_unary_to_cpp_std_list_like()`` template parameters.
   :widths: 20 50
   :header-rows: 1

   * - Template Parameter
     - Notes
   * - ``ListLike``
     - The C++ container type, either a ``std::vector<T>`` or ``std::list<T>``.
   * - ``T``
     - The C++ type of the objects in the target C++ container.
   * - ``PyObject_Check``
     - A pointer to a function that checks that any ``PyObject *`` in the Python container is the correct type, for example that it is a ``bytes`` object.
   * - ``PyObject_Convert``
     - A pointer to a function that converts any ``PyObject *`` in the Python container to the C++ type, for example from ``bytes`` -> ``std::vector<char>``.
   * - ``PyUnaryContainer_Check``
     - A pointer to a function that checks that the ``PyObject *`` argument is the correct container type, for example a ``tuple``.
   * - ``PyUnaryContainer_Size``
     - A pointer to a function that returns the size of the Python container.
   * - ``PyUnaryContainer_Get``
     - A pointer to a function that gets a ``PyObject *`` from the Python container at a given index.

And the function has the following parameters.

.. list-table:: ``generic_py_unary_to_cpp_std_vector()`` parameters.
   :widths: 20 20 50
   :header-rows: 1

   * - Type
     - Name
     - Notes
   * - ``PyObject *``
     - ``op``
     - The Python container to read from.
   * - ``ListLike<T> &``
     - ``list_like``
     - The C++ list like container to write to.

The return value is zero on success or non zero if there is a runtime error.
These errors could be:

* ``PyObject *op`` is not a container of the required type.
* An member of the Python container can not be converted to the C++ type ``T`` (``PyObject_Check`` fails).

Partial Specialisation to Convert a Python list to a C++ ``std::vector<T>``
---------------------------------------------------------------------------------

This template can be partially specialised for converting Python *lists* of any type to C++ ``std::vector<T>`` or ``std::list<T>``.
This is hand written code but it is trivial by wrapping a single function call.
In the case of a ``std::vector`` we can use ``.reserve()`` to avoid excessive re-allocations.

Note the use of the function pointers to ``py_list_check``, ``py_list_len`` and ``py_list_get``.
These are thin wrappers around existing functions or macros in ``"Python.h"``.

.. code-block:: cpp

    template<typename T, int (*PyObject_Check)(PyObject *), T (*PyObject_Convert)(PyObject *)>
    int generic_py_list_to_cpp_std_list_like(PyObject *op, std::vector<T> &container) {
        // Reserve the vector, but only if it is a list. If not then ignore it as
        // even_more_generic_py_unary_to_cpp_std_list_like() will error
        if (py_list_check(op)) {
            container.reserve(py_list_len(op));
        }
        return even_more_generic_py_unary_to_cpp_std_list_like<
                std::vector, T, PyObject_Check, PyObject_Convert, &py_list_check, &py_list_len, &py_list_get
        >(op, container);
    }

Generated Functions
=============================

These are created by a script that takes the cartesian product of object types and container types and creates functions
for each container/object.
For example, to convert a Python ``list`` of ``float`` to a C++ ``std::vector<double>`` the following are created:

A base declaration in *auto_py_convert_internal.h*:

.. code-block:: cpp

    template<typename T>
    int
    py_list_to_cpp_std_list_like(PyObject *op, std::list<T> &container);

And a concrete declaration for each C++ target type ``T`` in *auto_py_convert_internal.h*:

.. code-block:: cpp

    template <>
    int
    py_list_to_cpp_std_list_like<double>(PyObject *op, std::list<double> &container);


And the concrete definition is in *auto_py_convert_internal.cpp*:

.. code-block:: cpp

    template <>
    int
    py_list_to_cpp_std_list_like<double>(PyObject *op, std::vector<double> &container) {
        return generic_py_list_to_cpp_std_list_like<double, &py_float_check, &py_float_to_cpp_double>(op, container);
    }


This is the function hierarchy for the code that converts Python lists and tuples to C++ ``std::vector<T>`` for all
object types.
Here is the function hierarchy for converting lists to C++ ``std::vector<T>``:

.. code-block:: none

                  very_generic_py_unary_to_cpp_std_list_like      <--- Hand written
                                           |
                            /--------------------------\
                            |                          |             Hand written partial
            generic_py_list_to_cpp_std_list_like    tuples...    <-- specialisation for std::vector
                            |                          |             and std::list
                            |                          |             (generally trivial).
                            |                          |
             py_list_to_cpp_std_list_like<T>          ...        <-- Generated
                            |                          |
            /-------------------------------\      /-------\
            |                               |      |       |         Generated declaration
    py_list_to_cpp_std_list_like<double>   ...    ...     ...    <-- and implementation
                                                                     (one liners)


Usage
------

Using the concrete function is as simple as this:

.. code-block:: cpp

    using namespace Python_Cpp_Containers;
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
    int err = py_list_to_cpp_std_vector(op, cpp_vector);
    // Handle error checking...

    // Now convert back.
    // Again this will be a compile time error if the C++ type is not supported.
    PyObject *new_op  = cpp_std_list_like_to_py_list(cpp_vector);
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
    generic_cpp_std_list_like_to_py_unary(const std::vector<T> &vec);

Alternatives
--------------------

If your use case can be solved by using any of the following then this project is not for you:

`numpy <https://numpy.org>`_

The `Buffer protocol <https://docs.python.org/3/c-api/buffer.html>`_

Python's `multiprocessing.shared_memory <https://docs.python.org/3/library/multiprocessing.shared_memory.html#module-multiprocessing.shared_memory>`_

.. rubric:: Footnotes
.. [#] There are four unary containers (``tuple``, ``list``, ``set``, ``frozenset``) and six types
    (``bool``, ``int``, ``float``, ``complex``, ``bytes``, ``str``).
    Each container/type combination requires two functions to give two way conversion from Python to C++ and back.
    Thus 4 (containers) * 6 (types) * 2 (way conversion) = 48 required functions.
    For ``dict`` there are six types either of which can be the key or the value so 36 possible variations (any 2 out of 6).
    With two way conversion this means another 72 functions.
    Thus is a total of 120 functions.
