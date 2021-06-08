
Performance
===================

Python Tuple to a C++ ``std::vector``
-----------------------------------------------

Here is an example of converting a Python tuple to a C++ ``std::vector<T>`` for up to 1m ``bool``, ``long`` and ``double`` types.
Time is per-object in µs.
So 1m float/long conversion takes about 0.02 seconds.

.. image:: plots/test_py_tuple_to_vector.svg

C++ ``std::vector`` to a Python Tuple
-----------------------------------------------

This is the reverse of the above, the time to convert a C++ ``std::vector<T>`` to a Python  ``tuple`` for up to 1m ``bool``, ``long`` and ``double`` types.

.. image:: plots/test_vector_to_py_tuple.svg

Python Tuple of ``bytes`` to a C++ ``std::vector``
------------------------------------------------------------

.. image:: plots/test_vector_string_to_py_tuple.svg

Python Dict of ``[float, float]`` to a C++ ``std::unordered_map<double, double>``
----------------------------------------------------------------------------------------------

.. image:: plots/test_dict_double.svg

Python Dict of ``[bytes, bytes]`` to a C++ ``std::unordered_map<std::string, std::string>``
------------------------------------------------------------------------------------------------------------

.. image:: plots/test_dict_string.svg
