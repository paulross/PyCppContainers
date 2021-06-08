
Usage
==============

Python Tuples
----------------------

Converting a Python Tuple to a C++ ``std::vector``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here is some demonstration code that creates a C++ vector of doubles then converts that to a Python tuple with a singe function call:

.. code-block:: C++

    // Demonstration code.
    void test_example_vector_to_py_tuple_double() {
        // By way of example fill a vector with the values 0.0 to 1023.0
        std::vector<double> cpp_vector;
        for (size_t i = 0; i < 1024; ++i) {
            cpp_vector.push_back(static_cast<double>(i));
        }
        // Convert to a Python tuple that contains values 0.0 to 1023.0 as floats
        PyObject *op = Python_Cpp_Containers::cpp_std_vector_to_py_tuple(cpp_vector);
        if (! op) {
            // Handle error condition.
        } else {
            // Use Python tuple
            // ...
            // Give up the tuple when done.
            Py_DECREF(op);
        }
    }

``Python_Cpp_Containers::cpp_std_vector_to_py_tuple`` has implementations for vectors of ``bool``, ``long``, ``double`` and ``std::string``.

Converting a C++ ``std::vector`` to a Python Tuple
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here is some demonstration code that creates a Python tuple of floats then converts that to C++ vector of doubles with a singe function call:

.. code-block:: C++

    // Demonstration code.
    void test_example_py_tuple_to_vector_double() {
        PyObject *op = Python_Cpp_Containers::py_tuple_new(1024);
        if (! op) {
            // Handle error
        } else {
            // By way of example fill the tuple with the values 0.0 to 1023.0 as Python floats.
            for (size_t i = 0; i < 1024; ++i) {
                int err = Python_Cpp_Containers::py_tuple_set(
                        op,
                        i,
                        Python_Cpp_Containers::py_float_from_double(static_cast<double>(i))
                        );
                if (err != 0) {
                    // Handle insertion error
                }
            }
            // Create the vector of the appropriate type.
            std::vector<double> cpp_vector;
            // Convert the tuple to a vector
            int err = Python_Cpp_Containers::py_tuple_to_cpp_std_vector(op, cpp_vector);
            if (err != 0) {
                // Handle error
            } else {
                // Use vector.
                // ...
            }
            // Give up the tuple when done.
            Py_DECREF(op);
        }
    }

``Python_Cpp_Containers::py_tuple_to_cpp_std_vector`` has implementations for vectors of ``bool``, ``long``, ``double`` and ``std::string``.

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

    // Demonstration code
    void test_example_py_dict_to_cpp_std_unordered_map() {
        PyObject *op = PyDict_New();
        // Populate dict with [int, bytes]
        // ...
        std::unordered_map<long, std::string> cpp_map;
        int err = Python_Cpp_Containers::py_dict_to_cpp_std_unordered_map(op, cpp_map);
        if (err != 0) {
            // Handle error.
        } else {
            // Do something with cpp_map
            // ...
        }
        // Discard op if necessary
        Py_DECREF(op);
    }

Converting a C++ ``std::unordered_map`` to a Python ``dict``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is done with ``Python_Cpp_Containers::cpp_std_unordered_map_to_py_dict``.
This has implementations for all the combinations of C++ types of ``bool``, ``long``, ``double`` and ``std::string`` as keys and values so there are 16 combinations.

Here is an example of converting a C++ ``std::unordered_map<long, std::string>`` to a Python dict of ``[int, bytes]``:

.. code-block:: C++

    // Demonstration code
    void test_example_cpp_std_unordered_map_to_py_dict() {
        std::unordered_map<long, std::string> cpp_map;
        // Populate the map with some data.
        for (long i = 0; i < 128; ++i) {
            cpp_map[i] = std::string(4, ' ');
        }
        // Convert to a Python dict.
        PyObject *op = Python_Cpp_Containers::cpp_std_unordered_map_to_py_dict(cpp_map);
        if (! op) {
            // Handle error.
        } else {
            // Do something with op
            // ...
            // Discard if necessary.
            Py_DECREF(op);
        }
    }
