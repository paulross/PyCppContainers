***************
Usage
***************

Using This Project in your Python Extension
============================================


Code Generation
----------------------

If necessary run the code generator:


.. code-block:: shell

    cd src/py
    python code_gen.py

Which should give you something like:

.. code-block:: none

    Target directory "src/cpy"
    Writing declarations to "src/cpy/auto_py_convert_internal.h"
    Wrote 910 lines of code with 66 declarations.
    Writing definitions to  "src/cpy/auto_py_convert_internal.cpp"
    Wrote 653 lines of code with 64 definitions.

    Process finished with exit code 0


Build Configuration
--------------------------

You need to compile the following C++ files by adding them to your makefile or CMakeLists.txt:


.. code-block:: none

    src/cpy/auto_py_convert_internal.cpp
    src/cpy/python_container_convert.cpp
    src/cpy/python_object_convert.cpp


Source Inclusion
--------------------------

Your pre-processor needs access to the header files with the compiler flag:

.. code-block:: none

    -I src/cpy


Then in your Python extension include the line:

.. code-block:: c

    #include "python_convert.h"

An this gives you access to the whole API.


Examples
============

There are some examples of using this library in *src/ext/cPyCppContainers.cpp*.
This extension is built by *setup.py* and tested with *tests/unit/test_cPyCppContainers.py*.

Doubling the Values in a Python List of ``float`` Values
----------------------------------------------------------

Here is one of those examples in detail; doubling the values of a Python list of floats.
At the beginning of the extension we have:

.. code-block:: cpp

    #include "cpy/python_convert.h"

For convenience we use the namespace the conversion code is within:

.. code-block:: cpp

    using namespace Python_Cpp_Containers;

Here is the C++ function that we want to call that multiplies the values of a ``std::vector<double>`` in-place by 2.0:

.. code-block:: cpp

    /** Double the values of a vector in-place. */
    static void
    vector_double_x2(std::vector<double> &vec) {
        for (size_t i = 0; i < vec.size(); ++i) {
            vec[i] *= 2.0;
        }
    }

And here is the code that takes a Python list of floats, then calls the C++ function and finally converts the C++
``std::vector<double>`` back to a new Python list of floats:

.. code-block:: cpp

    /** Create a new list of floats with doubled values. */
    static PyObject *
    list_x2(PyObject *Py_UNUSED(module), PyObject *arg) {
        std::vector<double> vec;
        // py_list_to_cpp_std_vector() will return non-zero if the Python
        // argument can not be converted to a std::vector<double>
        // and a Python exception will be set.
        if (!py_list_to_cpp_std_vector(arg, vec)) {
            // Double the values in pure C++ code.
            vector_double_x2(vec);
            // cpp_std_vector_to_py_list() returns NULL on failure
            // and a Python exception will be set.
            return cpp_std_vector_to_py_list(vec);
        }
        return NULL;
    }

The vital piece of code is the declaration ``std::vector<double> vec;`` and that means:

* If a ``py_list_to_cpp_std_vector()`` implementation does not exist for ``double`` there will be a compile time error.
* Giving ``py_list_to_cpp_std_vector()`` anything other than a list of floats will create a Python runtime error.
* If ``cpp_std_vector_to_py_list()`` fails for any reason there will be a Python runtime error.


Reversing a ``tuple`` of ``bytes``
-------------------------------------------

Here is another example, we have a funcion to to reverse a ``tuple`` of ``bytes`` in C++

.. code-block:: cpp

    /** Returns a new vector reversed. */
    template<typename T>
    static std::vector<T>
    reverse_vector(const std::vector<T> &input){
        std::vector<T> output;
        for (size_t i = input.size(); i-- > 0;) {
            output.push_back(input[i]);
        }
        return output;
    }

    /** Reverse a tuple of bytes in C++. */
    static PyObject *
    tuple_reverse(PyObject *Py_UNUSED(module), PyObject *arg) {
        std::vector<std::string> vec;
        if (!py_tuple_to_cpp_std_vector(arg, vec)) {
            return cpp_std_vector_to_py_tuple(reverse_vector(vec));
        }
        return NULL;
    }




Python Tuples
==============

Converting a Python Tuple to a C++ ``std::vector``
------------------------------------------------------

Here is some demonstration code that takes a Python tuple of floats then converts that to C++ vector of doubles with a
single function call:

.. code-block:: cpp

    #include "python_convert.h"

    // Demonstration code.
    void test_example_py_tuple_to_vector_double(PyObject *op) {
        // Create the vector of the appropriate type.
        std::vector<double> cpp_vector;
        // Copy the tuple to a vector
        int err = Python_Cpp_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
        if (err != 0) {
            // Handle error
            // ...
        } else {
            // Use C++ vector.
            // ...
        }
    }

``Python_Cpp_Containers::py_tuple_to_cpp_std_vector`` has implementations for vectors of ``bool``, ``long``, ``double``
and ``std::string``.


Converting a C++ ``std::vector`` to a Python Tuple
------------------------------------------------------

Here is some demonstration code that creates a C++ vector of doubles then converts that to a Python tuple with a single
function call:

.. code-block:: cpp

    #include "python_convert.h"

    PyObject *test_example_vector_to_py_tuple_double() {
        // An imaginary function that creates a C++ std::vector<double>
        std::vector<double> cpp_vector = get_cpp_vector_doubles();
        // Convert to a Python tuple that contains floats
        PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
        if (! op) {
            // Handle error condition.
            // ...
        }
        return op;
    }

``Python_Cpp_Containers::cpp_std_vector_to_py_tuple`` has implementations for vectors of ``bool``, ``long``, ``double``
and ``std::string``.

Python Lists
===============


Converting a Python List to a C++ ``std::vector``
------------------------------------------------------

This is done with ``Python_Cpp_Containers::cpp_std_vector_to_py_list`` which is very similar to the code for tuples.
``Python_Cpp_Containers::cpp_std_vector_to_py_list`` has implementations for vectors of ``bool``, ``long``, ``double``
and ``std::string``.

Converting a C++ ``std::vector`` to a Python List
------------------------------------------------------

This is done with ``Python_Cpp_Containers::py_list_to_cpp_std_vector`` which is very similar to the code for tuples.
``Python_Cpp_Containers::py_list_to_cpp_std_vector`` has implementations for vectors of ``bool``, ``long``, ``double``
and ``std::string``.


Python Sets
==================

Converting a Python Set to a C++ ``std::unordered_set``
----------------------------------------------------------

This is done with ``Python_Cpp_Containers::cpp_std_unordered_set_to_py_set`` which is very similar to the code for
tuples and lists.
``Python_Cpp_Containers::cpp_std_unordered_set_to_py_set`` has implementations for the C++ types of ``bool``,
``long``, ``double`` and ``std::string``.

Converting a C++ ``std::unordered_set`` to a Python Set
----------------------------------------------------------

This is done with ``Python_Cpp_Containers::py_list_to_cpp_std_unordered_set`` which is very similar to the code for
tuples and lists.
``Python_Cpp_Containers::py_list_to_cpp_std_unordered_set`` has implementations for C++ types of ``bool``, ``long``,
``double`` and ``std::string``.


Python Dicts
==========================

Converting a Python ``dict`` to a C++ ``std::unordered_map``
-----------------------------------------------------------------

This is done with ``Python_Cpp_Containers::py_dict_to_cpp_std_unordered_map``.
This has implementations for all the combinations of C++ types of ``bool``, ``long``, ``double`` and ``std::string``
as keys and values so there are 16 combinations.

Here is an example of converting a Python dict of ``[int, bytes]`` to a C++ ``std::unordered_map<long, std::string>``:

.. code-block:: cpp

    #include "python_convert.h"

    void test_example_py_dict_to_cpp_std_unordered_map(PyObject *op) {
        std::unordered_map<long, std::string> cpp_map;
        int err = Python_Cpp_Containers::py_dict_to_cpp_std_unordered_map(op, cpp_map);
        if (err != 0) {
            // Handle error.
            // ...
        } else {
            // Do something with cpp_map
            // ...
        }
    }

Converting a C++ ``std::unordered_map`` to a Python ``dict``
-----------------------------------------------------------------

This is done with ``Python_Cpp_Containers::cpp_std_unordered_map_to_py_dict``.
This has implementations for all the combinations of C++ types of ``bool``, ``long``, ``double`` and ``std::string`` as
keys and values so there are 16 combinations.

Here is an example of converting a C++ ``std::unordered_map<long, std::string>`` to a Python dict of ``[int, bytes]``:

.. code-block:: cpp

    #include "python_convert.h"

    PyObject *test_example_cpp_std_unordered_map_to_py_dict() {
        // An imaginary function that creates a C++ std::unordered_map<long, std::string>
        std::unordered_map<long, std::string> cpp_map = get_cpp_map();
        // Convert to a Python dict.
        PyObject *op = Python_Cpp_Containers::cpp_std_unordered_map_to_py_dict(cpp_map);
        if (! op) {
            // Handle error.
            // ...
        }
        return op;
    }


Matrix Example
========================

Supposing there is a C++ library that provides matrix support for a ``std::vector<std::vector<double>>`` type and you
want it to work on a Python tuple of tuples of floats.

Firstly creating the C++ matrix from Python.

Converting a Python ``Tuple[Tuple[float]]`` to a C++ ``std::vector<std::vector<double>>``
-----------------------------------------------------------------------------------------------

.. code-block:: cpp

    #include "python_convert.h"

    // Demonstration code.
    void py_matrix_to_cpp_matrix(PyObject *op) {
        // Create the matrix of the appropriate type.
        std::vector<std::vector<double>> cpp_matrix;
        for (Py_ssize_t i = 0; i < Python_Cpp_Containers::py_tuple_len(op), ++i) {
            std::vector<double> cpp_vector;
            PyObject *row = Python_Cpp_Containers::py_tuple_get(op, i);
            int err = Python_Cpp_Containers::py_tuple_to_cpp_std_vector(row, cpp_vector);
            if (err != 0) {
                // Handle error
                // ...
                return;
            } else {
                cpp_matrix.push_back(cpp_vector);
            }
        }
        // Use the matrix
        some_function_that_uses_a_matrix(cpp_matrix);
    }

.. note:: Some error checking omitted.

Converting a C++ ``std::vector<std::vector<double>>`` to a Python ``Tuple[Tuple[float]]``
----------------------------------------------------------------------------------------------

And the reverse, given a C++ matrix this converts that to a Python tuple of tuples with a single function call:

.. code-block:: cpp

    #include "python_convert.h"

    PyObject *
    cpp_matrix_to_py_matrix() {
        // An imaginary function that creates a C++ std::vector<double>
        std::vector<std::vector<double>> cpp_matrix = get_cpp_matrix();
        PyObject *op = Python_Cpp_Containers::py_tuple_new(cpp_matrix.size());
        for (size_t i = 0; i < cpp_matrix.size(); ++i) {
            PyObject *row = Python_Cpp_Containers::cpp_std_vector_to_py_tuple(cpp_matrix[i]);
            if (! row) {
                // Handle error condition.
                // ...
                return NULL;
            }
            int err = Python_Cpp_Containers::py_tuple_set(op, i, row)
            if (err != 0) {
                // Handle error
                // ...
                return;
            }
        }
        return op;
    }

.. note:: Some error checking omitted.
