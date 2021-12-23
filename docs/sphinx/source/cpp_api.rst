****************************
C++ API
****************************

Python Containers to C++
============================


.. code-block:: cpp

    #include "python_convert.h"

All these APIs are in the namespace ``Python_Cpp_Containers``.

Python ``tuple`` to ``std::vector``
---------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename T>
    int
    py_tuple_to_cpp_std_vector(PyObject *op, std::vector<T> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 30 20 50
   :header-rows: 1

   * - Argument ``op``
     - Argument ``container``
     - Return value
   * - A Python ``tuple`` containing values convertable to type ``<T>``.
     - The ``std::vector`` to write to.
     - 0 on success, non-zero on failure in which case the container will be empty.
       The causes of failure can be; ``op`` is not a tuple or a member of the ``op`` can not be converted to type ``<T>``.

Example
^^^^^^^^^^^^^^^

Process a tuple of Python ``float``:

.. code-block:: cpp

    void tuple_float_to_cpp(PyObject *arg) {
        std::vector<double> vec;
        if (! py_tuple_to_cpp_std_vector(arg, vec)) {
            // Handle error...
        }
        // Use vec...
    }

Python ``list`` to ``std::vector``
---------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename T>
    int
    py_list_to_cpp_std_vector(PyObject *op, std::vector<T> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 30 20 50
   :header-rows: 1

   * - Argument ``op``
     - Argument ``container``
     - Return value
   * - A Python ``list`` containing values convertable to type ``<T>``.
     - The ``std::vector`` to write to.
     - 0 on success, non-zero on failure in which case the container will be empty.
       The causes of failure can be; ``op`` is not a list or a member of the ``op`` can not be converted to type ``<T>``.

Example
^^^^^^^^^^^^^^^

Process a list of Python ``float``:

.. code-block:: cpp

    void list_float_to_cpp(PyObject *arg) {
        std::vector<double> vec;
        if (! py_list_to_cpp_std_vector(arg, vec)) {
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

Python ``dict`` to ``std::unordered_map``
---------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename K, typename V>
    int
    py_dict_to_cpp_std_unordered_map(PyObject *op, std::unordered_map<K, V> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 30 30
   :header-rows: 1

   * - Argument ``op``
     - Argument ``container``
     - Return value
   * - A Python ``dict`` containing keys convertable to type ``<K>`` and values convertable to type ``<V>``.
     - The ``std::unordered_map`` to write to.
     - 0 on success, non-zero on failure.

Example
^^^^^^^^^^^^^^^

Process a dict of Python ``[int, float]``:

.. code-block:: cpp

    void dict_int_float_to_cpp(PyObject *arg) {
        std::unordered_map<long, double> map;
        if (! py_dict_to_cpp_std_unordered_map(arg, map)) {
            // Handle error...
        }
        // Use map...
    }

C++ Containers to Python
============================

CPP ``std::vector`` to Python ``tuple``
---------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename T>
    PyObject *
    cpp_std_vector_to_py_tuple(const std::vector<T> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 50
   :header-rows: 1

   * - Argument ``container``
     - Return value
   * - A ``std::vector`` of type ``<T>`` convertable to an appropriate Python type.
     - The new Python container, ``NULL`` on failure in which case a ``PyErr`` will be set.

Example
^^^^^^^^^^^^^^^

Create a tuple of Python ``float``:

.. code-block:: cpp

    PyObject *vector_double_to_tuple() {
        std::vector<double> vec;
        // Populate vec
        // ...
        return cpp_std_vector_to_py_tuple(vec);
    }


CPP ``std::vector`` to Python ``list``
---------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename T>
    PyObject *
    cpp_std_vector_to_py_list(const std::vector<T> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 50
   :header-rows: 1

   * - Argument ``container``
     - Return value
   * - A ``std::vector`` of type ``<T>`` convertable to an appropriate Python type.
     - The new Python container, ``NULL`` on failure in which case a ``PyErr`` will be set.

Example
^^^^^^^^^^^^^^^

Create a list of Python ``float``:

.. code-block:: cpp

    PyObject *vector_double_to_list() {
        std::vector<double> vec;
        // Populate vec
        // ...
        return cpp_std_vector_to_py_list(vec);
    }

CPP ``std::unordered_set`` to Python ``set``
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

CPP ``std::unordered_set`` to Python ``frozenset``
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

C++ ``std::unordered_map`` to a Python ``dict``
-----------------------------------------------------

API
^^^^

.. code-block:: cpp

    template<typename K, typename V>
    PyObject *
    cpp_std_unordered_map_to_py_dict(const std::unordered_map<K, V> &container);

Arguments
^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 50
   :header-rows: 1

   * - Argument ``container``
     - Return value
   * - A ``std::unordered_map`` of type ``<K, V>`` convertable to appropriate Python types.
     - The new Python container, ``NULL`` on failure in which case a ``PyErr`` will be set.

Example
^^^^^^^^^^^^^^^

Create a dict of Python ``[int, float]``:

.. code-block:: cpp

    PyObject *map_double_to_list() {
        std::unordered_map<long, double> map;
        // Populate map
        // ...
        return cpp_std_unordered_map_to_py_dict(map);
    }
