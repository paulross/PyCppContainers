
Performance
===================

Summary
-----------------

* Sequences of fundamental types are converted at around 100m objects/sec.
* Sequences of strings are converted at a memory rate of around 4000 Mb/sec.
* Dicts are about 8-10x slower.

Fundamental Types
^^^^^^^^^^^^^^^^^^^^^

Converting and copying of ``int``/``long`` and ``float``/``double`` takes about 0.01 µs per object (100m objects per second) for large containers.
This corresponds to around 800 Mb/s.
``boolean``/``bool`` is around 2x to 5x faster.

Strings of Different Lengths
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

With ``bytes``/``std::string`` converting and conversion takes about the following.
The performance appears appears linear (with some latency for small strings):

=============== ======================= =========================== ===================
String size     ~Time per object (µs)   ~Rate, million per second   ~Rate x Size Mb/s
=============== ======================= =========================== ===================
8               0.02                    50                          400
64              0.03                    30                          2000
512             0.1                     10                          5000
4096            1.0                     1                           4000
=============== ======================= =========================== ===================

Python Tuple to a C++ ``std::vector``
-----------------------------------------------

Here is an example of converting a Python tuple to a C++ ``std::vector<T>`` for up to 1m ``bool``, ``long`` and ``double`` types.
Time is per-object in µs.
So 1m float/long conversion takes about 10 to 20 ms.

.. image:: plots/test_py_tuple_to_vector.svg

C++ ``std::vector`` to a Python Tuple
-----------------------------------------------

This is the reverse of the above, the time to convert a C++ ``std::vector<T>`` to a Python  ``tuple`` for up to 1m ``bool``, ``long`` and ``double`` types.

.. image:: plots/test_vector_to_py_tuple.svg

Python Tuple of ``bytes`` to a C++ ``std::vector<std::string>>``
-----------------------------------------------------------------

This shows the conversion cost of various length strings.

.. image:: plots/test_vector_string_to_py_tuple.svg

C++ ``std::vector<std::string>>`` to a Python Tuple of ``bytes``
-----------------------------------------------------------------

This is the reverse of the above.

.. image:: plots/test_py_tuple_string_to_vector.svg

Python Dict of ``[float, float]`` to a C++ ``std::unordered_map<double, double>``
----------------------------------------------------------------------------------------------

This shows the conversion rate of a dict of floats to and from Python.
At 0.1 µs per item (10m objects/s) this rate is about one-tenth of the rate of converting a sequence.

.. image:: plots/test_dict_double.svg

Python Dict of ``[bytes, bytes]`` to a C++ ``std::unordered_map<std::string, std::string>``
------------------------------------------------------------------------------------------------------------

Similarly for dicts of bytes.
This corresponds, roughly, to a data rate of around 500 Mb/s.

.. image:: plots/test_dict_string.svg
