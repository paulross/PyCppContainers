
Usage
==============

Python Tuples
----------------------

Converting a Python Tuple to a C++ ``std::vector``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here is some demonstration code that takes a Python tuple of floats then converts that to C++ vector of doubles with a singe function call:

.. code-block:: C++

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

``Python_Cpp_Containers::py_tuple_to_cpp_std_vector`` has implementations for vectors of ``bool``, ``long``, ``double`` and ``std::string``.


Converting a C++ ``std::vector`` to a Python Tuple
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here is some demonstration code that creates a C++ vector of doubles then converts that to a Python tuple with a single function call:

.. code-block:: C++

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

``Python_Cpp_Containers::cpp_std_vector_to_py_tuple`` has implementations for vectors of ``bool``, ``long``, ``double`` and ``std::string``.

Python Lists
----------------------

Converting a Python List to a C++ ``std::vector``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is done with ``Python_Cpp_Containers::cpp_std_vector_to_py_list`` which is very similar to the code for tuples.
``Python_Cpp_Containers::cpp_std_vector_to_py_list`` has implementations for vectors of ``bool``, ``long``, ``double`` and ``std::string``.

Converting a C++ ``std::vector`` to a Python List
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is done with ``Python_Cpp_Containers::py_list_to_cpp_std_vector`` which is very similar to the code for tuples.
``Python_Cpp_Containers::py_list_to_cpp_std_vector`` has implementations for vectors of ``bool``, ``long``, ``double`` and ``std::string``.


Python Sets
----------------------

Converting a Python Set to a C++ ``std::unordered_set``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is done with ``Python_Cpp_Containers::cpp_std_unordered_set_to_py_set`` which is very similar to the code for tuples and lists.
``Python_Cpp_Containers::cpp_std_unordered_set_to_py_set`` has implementations for the C++ types of ``bool``, ``long``, ``double`` and ``std::string``.

Converting a C++ ``std::unordered_set`` to a Python Set
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is done with ``Python_Cpp_Containers::py_list_to_cpp_std_unordered_set`` which is very similar to the code for tuples and lists.
``Python_Cpp_Containers::py_list_to_cpp_std_unordered_set`` has implementations for C++ types of ``bool``, ``long``, ``double`` and ``std::string``.


Python Dicts
----------------------

Converting a Python ``dict`` to a C++ ``std::unordered_map``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is done with ``Python_Cpp_Containers::py_dict_to_cpp_std_unordered_map``.
This has implementations for all the combinations of C++ types of ``bool``, ``long``, ``double`` and ``std::string`` as keys and values so there are 16 combinations.

Here is an example of converting a Python dict of ``[int, bytes]`` to a C++ ``std::unordered_map<long, std::string>``:

.. code-block:: C++

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
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is done with ``Python_Cpp_Containers::cpp_std_unordered_map_to_py_dict``.
This has implementations for all the combinations of C++ types of ``bool``, ``long``, ``double`` and ``std::string`` as keys and values so there are 16 combinations.

Here is an example of converting a C++ ``std::unordered_map<long, std::string>`` to a Python dict of ``[int, bytes]``:

.. code-block:: C++

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


Matrices
----------------------

Supposing there is a C++ library that provides matrix support with ``std::vector<std::vector<double>>`` and it is desired to convert these to tuples of tuples of floats.

Converting a Python Tuple[Tuple[float]] to a C++ ``std::vector<std::vector<double>>``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. note:: Some error checking omitted.

.. code-block:: C++

    // Demonstration code.
    void test_example_py_tuple_to_vector_double(PyObject *op) {
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

Converting a C++ ``std::vector<std::vector<double>>`` to a Python Tuple[Tuple[float]]
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here is some demonstration code that creates a C++ vector of doubles then converts that to a Python tuple with a single function call:

.. note:: Some error checking omitted.

.. code-block:: C++

    PyObject *test_example_vector_to_py_tuple_double() {
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
