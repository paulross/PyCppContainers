.. moduleauthor:: Paul Ross <apaulross@gmail.com>
.. sectionauthor:: Paul Ross <apaulross@gmail.com>

.. PythonCppContainers C++ API

.. _PythonCppContainers.Cpp_API:

****************************
C++ API
****************************

Include File and Namespace
============================

.. code-block:: cpp

    #include "python_convert.h"

All these APIs are in the namespace ``Python_Cpp_Containers``.

Python Containers to C++
============================

Error Indication
--------------------------

All of the conversion functions from Python to C++ return an integer which is zero on success, non-zero otherwise.
Reasons for failure can be:

* The ``PyObject *`` is not the expected Python container, for example passing  a Python tuple when a list is expected.
* A member of the Python container can not be converted to C++ type ``<T>``.

In the error case a ``PyErr_...`` will be set.

Python ``tuple`` to ``std::vector`` or ``std::list``
-----------------------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename T>
    int
    py_tuple_to_cpp_std_list_like(PyObject *op, std::vector<T> &container);

    template<typename T>
    int
    py_tuple_to_cpp_std_list_like(PyObject *op, std::list<T> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 30 20 50
   :header-rows: 1

   * - Argument ``op``
     - Argument ``container``
     - Return value
   * - A Python ``tuple`` containing values convertable to type ``<T>``.
     - The ``std::vector`` or ``std::list`` to write to.
     - 0 on success, non-zero on failure in which case the container will be empty.
       The causes of failure can be; ``op`` is not a tuple or a member of the ``op`` can not be converted to type ``<T>``.

Example
^^^^^^^^^^^^^^^

Process a tuple of Python ``float``:

.. code-block:: cpp

    void tuple_float_to_cpp(PyObject *arg) {
        std::vector<double> vec;
        if (! py_tuple_to_cpp_std_list_like(arg, vec)) {
            // Handle error...
        }
        // Use vec...
    }

Python ``list`` to ``std::vector`` or ``std::list``
--------------------------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename T>
    int
    py_list_to_cpp_std_list_like(PyObject *op, std::vector<T> &container);

    template<typename T>
    int
    py_list_to_cpp_std_list_like(PyObject *op, std::list<T> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 30 20 50
   :header-rows: 1

   * - Argument ``op``
     - Argument ``container``
     - Return value
   * - A Python ``list`` containing values convertable to type ``<T>``.
     - The ``std::vector`` or ``std::list`` to write to.
     - 0 on success, non-zero on failure in which case the container will be empty.
       The causes of failure can be; ``op`` is not a list or a member of the ``op`` can not be converted to type ``<T>``.

Example
^^^^^^^^^^^^^^^

Process a list of Python ``float``:

.. code-block:: cpp

    void list_float_to_cpp(PyObject *arg) {
        std::list<double> list;
        if (! py_list_to_cpp_std_list_like(arg, list)) {
            // Handle error...
        }
        // Use vec...
    }

Python ``set`` to ``std::unordered_set``
---------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename T>
    int
    py_set_to_cpp_std_unordered_set(PyObject *op, std::unordered_set<T> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 30 30
   :header-rows: 1

   * - Argument ``op``
     - Argument ``container``
     - Return value
   * - A Python ``set`` containing values convertable to type ``<T>``.
     - The ``std::unordered_set`` to write to.
     - 0 on success, non-zero on failure.

Example
^^^^^^^^^^^^^^^

Process a set of Python ``float``:

.. code-block:: cpp

    void set_float_to_cpp(PyObject *arg) {
        std::unordered_set<double> set;
        if (! py_set_to_cpp_std_unordered_set(arg, set)) {
            // Handle error...
        }
        // Use set...
    }

Python ``frozenset`` to ``std::unordered_set``
------------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename T>
    int
    py_frozenset_to_cpp_std_unordered_set(PyObject *op, std::unordered_set<T> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 30 30
   :header-rows: 1

   * - Argument ``op``
     - Argument ``container``
     - Return value
   * - A Python ``frozenset`` containing values convertable to type ``<T>``.
     - The ``std::unordered_set`` to write to.
     - 0 on success, non-zero on failure.

Example
^^^^^^^^^^^^^^^

Process a frozenset of Python ``float``:

.. code-block:: cpp

    void frozenset_float_to_cpp(PyObject *arg) {
        std::unordered_set<double> frozenset;
        if (! py_frozenset_to_cpp_std_unordered_set(arg, frozenset)) {
            // Handle error...
        }
        // Use frozenset...
    }

Python ``dict`` to ``std::unordered_map`` or ``std::map``
--------------------------------------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename K, typename V>
    int
    py_dict_to_cpp_std_map_like(PyObject *op, std::unordered_map<K, V> &container);

    template<typename K, typename V>
    int
    py_dict_to_cpp_std_map_like(PyObject *op, std::map<K, V> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 30 30
   :header-rows: 1

   * - Argument ``op``
     - Argument ``container``
     - Return value
   * - A Python ``dict`` containing keys convertable to type ``<K>`` and values convertable to type ``<V>``.
     - The ``std::unordered_map`` or ``std::map`` to write to.
     - 0 on success, non-zero on failure.

Example
^^^^^^^^^^^^^^^

Process a dict of Python ``[int, float]``:

.. code-block:: cpp

    void dict_int_float_to_cpp(PyObject *arg) {
        std::unordered_map<long, double> map;
        if (! py_dict_to_cpp_std_map_like(arg, map)) {
            // Handle error...
        }
        // Use map...
    }

C++ Containers to Python
============================

Error Indication
--------------------------

All of the conversion functions from C++ to Python return an ``PyObject *``.
If this is non-NULL it is a *new reference* and it is te responsibility of the caller to dispose off it.

On failure these functions will return NULL
Reasons for failure can be:

* The new Python container can not be created with the CPython API, perhaps for memory reasons.
* A C++ object can not be converted to a Python object. I can not imagine how this would be the case.
* The converted C++ object can not be can  not be inserted into the Python container. I can not imagine how this would be the case.

In the failure case a ``PyErr_...`` will be set.

C++ ``std::vector`` or ``std::list`` to Python ``tuple``
------------------------------------------------------------------------------

API
^^^^

To convert to a Python ``tuple``:

.. code-block:: cpp

    template<typename T>
    PyObject *
    cpp_std_list_like_to_py_tuple(const std::vector<T> &container);

    template<typename T>
    PyObject *
    cpp_std_list_like_to_py_tuple(const std::list<T> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 50
   :header-rows: 1

   * - Argument ``container``
     - Return value
   * - A ``std::vector`` or ``std::list`` of type ``<T>`` convertable to an appropriate Python type.
     - The new Python container, ``NULL`` on failure in which case a ``PyErr`` will be set.

Example
^^^^^^^^^^^^^^^

Create a tuple of Python ``float``:

.. code-block:: cpp

    PyObject *vector_double_to_tuple() {
        std::vector<double> vec;
        // Populate vec
        // ...
        return cpp_std_list_like_to_py_tuple(vec);
    }


C++ ``std::vector`` or ``std::list`` to Python ``list``
----------------------------------------------------------------

API
^^^^

.. code-block:: cpp

To convert to a Python ``list``:

.. code-block:: cpp

    template<typename T>
    PyObject *
    cpp_std_list_like_to_py_list(const std::vector<T> &container);

    template<typename T>
    PyObject *
    cpp_std_list_like_to_py_list(const std::list<T> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 50
   :header-rows: 1

   * - Argument ``container``
     - Return value
   * - A ``std::vector`` or ``std::list`` of type ``<T>`` convertable to an appropriate Python type.
     - The new Python container, ``NULL`` on failure in which case a ``PyErr`` will be set.

Example
^^^^^^^^^^^^^^^

Create a list of Python ``float``:

.. code-block:: cpp

    PyObject *vector_double_to_list() {
        std::vector<double> vec;
        // Populate vec
        // ...
        return cpp_std_list_like_to_py_list(vec);
    }

C++ ``std::unordered_set`` to Python ``set``
---------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename T>
    PyObject *
    cpp_std_unordered_set_to_py_set(const std::unordered_set<T> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 50
   :header-rows: 1

   * - Argument ``container``
     - Return value
   * - A ``std::unordered_set`` of type ``<T>`` convertable to an appropriate Python type.
     - The new Python container, ``NULL`` on failure in which case a ``PyErr`` will be set.

Example
^^^^^^^^^^^^^^^

Create a set of Python ``float``:

.. code-block:: cpp

    PyObject *vector_double_to_list() {
        std::unordered_set<double> set;
        // Populate set
        // ...
        return cpp_std_unordered_set_to_py_set(set);
    }

C++ ``std::unordered_set`` to Python ``frozenset``
----------------------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename T>
    PyObject *
    cpp_std_unordered_set_to_py_frozenset(const std::unordered_set<T> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 50
   :header-rows: 1

   * - Argument ``container``
     - Return value
   * - A ``std::unordered_set`` of type ``<T>`` convertable to an appropriate Python type.
     - The new Python container, ``NULL`` on failure in which case a ``PyErr`` will be set.

Example
^^^^^^^^^^^^^^^

Create a frozenset of Python ``float``:

.. code-block:: cpp

    PyObject *vector_double_to_list() {
        std::unordered_set<double> set;
        // Populate set
        // ...
        return cpp_std_unordered_set_to_py_frozenset(set);
    }

C++ ``std::unordered_map`` or ``std::map`` to a Python ``dict``
-----------------------------------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename K, typename V>
    PyObject *
    cpp_std_map_like_to_py_dict(const std::unordered_map<K, V> &container);

    template<typename K, typename V>
    PyObject *
    cpp_std_map_like_to_py_dict(const std::map<K, V> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 50
   :header-rows: 1

   * - Argument ``container``
     - Return value
   * - A ``std::unordered_map`` or ``std::map`` of type ``<K, V>`` convertable to appropriate Python types.
     - The new Python container, ``NULL`` on failure in which case a ``PyErr`` will be set.

Example
^^^^^^^^^^^^^^^

Create a dict of Python ``[int, float]``:

.. code-block:: cpp

    PyObject *map_double_to_list() {
        std::unordered_map<long, double> map;
        // Populate map
        // ...
        return cpp_std_map_like_to_py_dict(map);
    }
