***************************************
Using this Library in Your C++ Code
***************************************

The Basics
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


Errors
-------------------

If using this library in C++ there will be a linker error if you specify a template type that is not supported.
For example here is some code that tries to copy a Python list of unsigned integers.
The two conversion functions are not defined for ``unsigned int``.

.. code-block:: cpp

    static PyObject *
    new_list_unsigned_int(PyObject *Py_UNUSED(module), PyObject *arg) {
        std::vector<unsigned int> vec;
        if (!py_list_to_cpp_std_vector(arg, vec)) {
            return cpp_std_vector_to_py_list(vec);
        }
        return NULL;
    }

A C++ tool chain will complain with a linker error such as:

.. code-block:: none

    Undefined symbols for architecture x86_64:
      "_object* Python_Cpp_Containers::cpp_std_vector_to_py_list<unsigned int>(std::__1::vector<unsigned int, std::__1::allocator<unsigned int> > const&)", referenced from:
          new_list_unsigned_int(_object*, _object*) in cPyCppContainers.cpp.o
      "int Python_Cpp_Containers::py_list_to_cpp_std_vector<unsigned int>(_object*, std::__1::vector<unsigned int, std::__1::allocator<unsigned int> >&)", referenced from:
          new_list_unsigned_int(_object*, _object*) in cPyCppContainers.cpp.o
    ld: symbol(s) not found for architecture x86_64

If you are building a Python extension this will, most likely, build but importing the extension will fail immediately with something like:

.. code-block:: python

    >>> import cPyCppContainers
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    ImportError: dlopen(cPyCppContainers.cpython-39-darwin.so, 2): Symbol not found: __ZN21Python_Cpp_Containers25cpp_std_vector_to_py_listIjEEP7_objectRKNSt3__16vectorIT_NS3_9allocatorIS5_EEEE
      Referenced from: cPyCppContainers.cpython-39-darwin.so
      Expected in: flat namespace
     in cPyCppContainers.cpython-39-darwin.so


Examples
============

There are some examples of using this library in *src/ext/cPyCppContainers.cpp*.
This extension is built by *setup.py* and tested with *tests/unit/test_cPyCppContainers.py*.

To build this extension:

.. code-block:: bash

    $ python setup.py develop

And to use it:

.. code-block:: python

    import cPyCppContainer


Using C++ to Double the Values in a Python List of ``float``
-----------------------------------------------------------------

Here is one of those examples in detail; doubling the values of a Python list of floats.

At the beginning of the extension C/C++ code we have:

.. code-block:: cpp

    #include "cpy/python_convert.h"

For convenience we use the namespace that the conversion code is within:

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

Using the Extension
^^^^^^^^^^^^^^^^^^^^^^^^^^

Once the extension is built you can use it thus:

.. code-block:: python

    >>> import cPyCppContainers
    >>> cPyCppContainers.list_x2([1.0, 2.0, 4.0])
    [2.0, 4.0, 8.0]

You can verify that the returned list is a new one rather than modifying the input in-place:
.. code-block:: python

    >>> a = [1.0, 2.0, 4.0]
    >>> b = cPyCppContainers.list_x2(a)
    >>> hex(id(a))
    '0x1017150c0'
    >>> hex(id(b))
    '0x101810dc0'

If the values are not floats or the container is not a list a ``ValueError`` is raised:

.. code-block:: python

    >>> cPyCppContainers.list_x2([1, 2, 4])
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    ValueError: Python value of type int can not be converted
    >>> cPyCppContainers.list_x2((1.0, 2.0, 4.0))
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    ValueError: Can not convert Python container of type tuple


Reversing a ``tuple`` of ``bytes`` in  C++
-------------------------------------------

Here is another example, suppose that we have a function to to reverse a ``tuple`` of ``bytes`` in C++:

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

Here is the extension code that call this:

.. code-block:: cpp

    /** Reverse a tuple of bytes in C++. */
    static PyObject *
    tuple_reverse(PyObject *Py_UNUSED(module), PyObject *arg) {
        std::vector<std::string> vec;
        if (!py_tuple_to_cpp_std_vector(arg, vec)) {
            return cpp_std_vector_to_py_tuple(reverse_vector(vec));
        }
        return NULL;
    }

Once again the declaration ``std::vector<std::string> vec;`` ensures that the correct instantiations of conversion functions are called.

When the extension is built it can be used like this:

.. code-block:: python

    >>> import cPyCppContainers
    >>> cPyCppContainers.tuple_reverse((b'ABC', b'XYZ'))
    (b'XYZ', b'ABC')


Incrementing ``dict`` values in  C++
-------------------------------------------

Here is an example of taking a Python ``dict`` of ``[bytes, int]`` and creating a new ``dict`` with the values increased by one.
The C++ code in the extension is this:

.. code-block:: cpp

    /** Creates a new dict[bytes, int] with the values incremented by 1 in C++ */
    static PyObject *
    dict_inc(PyObject *Py_UNUSED(module), PyObject *arg) {
        std::unordered_map<std::string, long> dict;
        /* Copy the Python structure to the C++ one. */
        if (!py_dict_to_cpp_std_unordered_map(arg, dict)) {
            /* Increment. */
            for(auto &key_value: dict) {
                key_value.second += 1;
            }
            /* Copy the C++ structure to a new Python dict. */
            return cpp_std_unordered_map_to_py_dict(dict);
        }
        return NULL;
    }

Once the extension is built this can be used thus:

.. code-block::

    >>> import cPyCppContainers
    >>> cPyCppContainers.dict_inc({b'A' : 65, b'Z' : 90})
    {b'Z': 91, b'A': 66}

There are several other examples in *src/ext/cPyCppContainers.cpp* with tests in *tests/unit/test_cPyCppContainers.py*.
