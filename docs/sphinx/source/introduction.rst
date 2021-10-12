Introduction
====================

Python is well known for it's ability to handle *heterogeneous* data in containers such as lists.
But what if you need to interact with C++ containers such as ``std::vector<T>`` that require *homogeneous* data types?


This project is about:

* Converting Python containers (``list``, ``dict``, ``set``, ``tuple``) containing homogeneous types to their C++ equivalent.
* Converting C++ containers (``std::vector<T>``, ``std::unordered_set<T>``, ``std::unordered_map<Key, T>``) to the Python equivalent container containing homogeneous Python types.

A Basic Example
----------------

Supposes you have a Python list of floats and need to pass it to a C++ library that expects a ``std::vector<double>``.
If the result of that call modifies that C++ vector, or creates a new one, you need to return a Python list of floats from the result.
Your code might look something like this:

.. code-block:: cpp

    PyObject *example(PyObject *op) {
        std::vector<double> vec;
        // Populate the vector, function to be defined...
        py_list_to_cpp_std_vector(op, vec);
        // Do something in C++ with the vector.
        // ...
        // Convert the vector back to a Python list. Function to be defined...
        return cpp_std_vector_to_py_list(vec);
    }

What should the implementation of ``py_list_to_cpp_std_vector()`` and ``cpp_std_vector_to_py_list()`` look like?
The answer seems simple, firstly converting a Python list to a C++ ``std::vector<double>``:

.. code-block:: cpp

    void py_list_to_cpp_std_vector(PyObject *op, std::vector<double> &vec) {
        vec.clear();
        for (Py_ssize_t i = 0; i < PyList_Size(op); ++i) {
            PyObject *value = PyList_GET_ITEM(op, i);
            vec.push_back(PyFloat_AsDouble(value));
        }
    }

And the inverse, creating a new Python list from a C++ ``std::vector<double>``:

.. code-block:: cpp

    PyObject *cpp_std_vector_to_py_list(const std::vector<double> &vec) {
        PyObject *ret = PyList_New(vec.size());
        for (size_t i = 0; i < vec.size(); ++i) {
            PyList_SET_ITEM(ret, i, PyFloat_FromDouble(vec[i]));
        }
        return ret;
    }



Why This Project
---------------------

It is tedious and error prone to hand write the code for all possible containers and object types.
Instead this project makes extensive use of C++ templates, partial template specialisation and code generation to reduce quite dramatically reduce the amount of hand maintained code.

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

The only code that needs to be maintained is for the two-way conversions for any type are:

* Two C++ templates that handle all the ``tuple`` and ``list`` conversions.
* Two C++ templates that handle all the ``set`` and ``frozenset`` conversions.
* Two C++ templates that handle all the ``dict`` conversions.

This reduces 64 functions down to 6.