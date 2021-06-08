Introduction
====================

Python is well known for it's ability to handle *heterogeneous* data in containers such as lists.
This project is about dealing with *homogeneous* data where you need to interact with C++ containers such as ``std::vector<T>``.

For example I might have a Python list of floats and I would like to pass it to a C++ library routine the expects a ``std::vector<double>``.
Or I have the result of a C++ computation that is a ``std::unordered_map<long, std::string>`` and I need to create a Python ``dict`` where the key is a Python ``int`` and the value a Python ``bytes`` object.

It becomes rather tedious to hand write the code for all possible containers and object types.

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
   * - ``dict``
     - ``std::unordered_map``

The number of conversion functions is worse than the cartesian product of the types and containers.
In the case of a dict the types can appear as either a key or a value.

For example for unary containers (``tuple``, ``list``, ``set``) there are three containers with four types and two functions (to give two way conversion) so 3 * 4 * 2 = 24 functions.

For ``dict`` there are four types but the key and the value can be either so 16 possible type pair combinations.
With two functions for each to give two way conversion this means 32 conversion functions.

Thus the combination of ``bool``, ``int``, ``float``, ``bytes`` and containers ``tuple``, ``list``, ``set`` and ``dict`` requires 56 conversion functions to write and debug.

The aim of this project is to reduce this amount of code to a manageable level.
It uses a mix of C++ templates and code generators to achieve this.
The result is a few small functions for objects and a pair of hand written templates for each container.
As lists and tuples are very similar the code is reduced even further.

The only code that needs to be maintained is for the two-way conversions for any type are:

* Two C++ templates that handle all the ``tuple`` and ``list`` conversions.
* Two C++ templates that handle all the ``set`` conversions.
* Two C++ templates that handle all the ``dict`` conversions.

This reduces 56 functions down to 6.