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

    venv/bin/python src/py/code_gen.py
    Target directory "src/cpy"
    Writing declarations to "src/cpy/auto_py_convert_internal.h"
    Wrote 1526 lines of code with 122 declarations.
    Writing definitions to  "src/cpy/auto_py_convert_internal.cpp"
    Wrote 1237 lines of code with 120 definitions.
    
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

Your pre-processor needs access to the header files with the compiler flag ``-I src/cpy``.

Then in your C++ code include:

.. code-block:: c

    #include "python_convert.h"

Which gives you access to the whole API in the namespace ``Python_Cpp_Containers``.


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

Testing
=======================

Testing With C++
-----------------------

Debug Build
^^^^^^^^^^^^^^^^^^^

Building the C++ code and running with ``main()`` will execute all functional tests when built as a debug build.
This takes a couple of minutes or so.

.. code-block:: text

    test_functional_all START
    ...
    Number of tests: 430
    REGEX_HEAD: "HEAD:\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)"
    REGEX_TEST: "TEST:\s+(\d+)\s+(\d+)\s+(\d+)\s+([0-9+-.]+)\s+([0-9+-.]+)\s+([0-9+-.]+)\s+([0-9+-.]+)\s+(\d+)\s+([0-9+-.]+)\s+(\S+)"
    REGEX_TAIL: "TAIL:\s+(.+)"
    HEAD: Fail   Scale  Repeat         Mean(s)     Std.Dev.(s)         Min.(s)         Max.(s)     Count      Rate(/s) Name
    TEST:    0    1024       1     0.000026474             N/A             N/A             N/A         1       37772.2 test_vector_to_py_tuple<<bool>>():[1024]
    ...
    TEST:    0   65536       1     0.084335436             N/A             N/A             N/A         1          11.9 test_vector_vector_char_to_py_tuple<std::string[2048]>():[65536]
    TAIL: Passed=430/430 Failed=0/430

    ====RSS(Mb): was:      5.633 now:    116.824 diff:   +111.191 Peak was:      5.633 now:    340.168 diff:   +334.535 main.cpp
    Total execution time: 142 (s)
    Bye, bye!

Release Build
^^^^^^^^^^^^^^^^^^^

With a release build this will run the performance tests as well.
This can require 10Gb of memory and can take 20 minutes or so.

.. code-block:: text

    test_functional_all START
    ...
    test_memory_all FINISH
    Number of tests: 2226
    REGEX_HEAD: "HEAD:\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)"
    REGEX_TEST: "TEST:\s+(\d+)\s+(\d+)\s+(\d+)\s+([0-9+-.]+)\s+([0-9+-.]+)\s+([0-9+-.]+)\s+([0-9+-.]+)\s+(\d+)\s+([0-9+-.]+)\s+(\S+)"
    REGEX_TAIL: "TAIL:\s+(.+)"
    HEAD: Fail   Scale  Repeat         Mean(s)     Std.Dev.(s)         Min.(s)         Max.(s)     Count      Rate(/s) Name
    TEST:    0    1024       1     0.000003310             N/A             N/A             N/A         1      302069.2 test_vector_to_py_tuple<<bool>>():[1024]
    ...
    TEST:    0   65536       1     0.029584157             N/A             N/A             N/A         1          33.8 test_vector_vector_char_to_py_tuple<std::string[2048]>():[65536]
    TAIL: Passed=9890/9890 Failed=0/9890

    ====RSS(Mb): was:      5.430 now:   2047.426 diff:  +2041.996 Peak was:      5.430 now:   7725.137 diff:  +7719.707 main.cpp
    Total execution time: 1e+03 (s)
    Bye, bye!


Testing With Python
-----------------------

Unit Tests
^^^^^^^^^^^^^^^^^^^

Running the basic unit tests on the ``cPyCppContainers`` extension that exercises all the code:

.. code-block:: shell

    $ pytest tests/

This takes two or three seconds.

Extra Tests
^^^^^^^^^^^^^^^^^^^

There are a couple of options that can be added:

* ``--runslow`` will run slow tests including performance test. Use the ``-s`` option to obtain the performance output.
* ``--pymemtrace`` will run memory tracing tests. This requires `pymemtrace <https://pypi.org/project/pymemtrace/>`_ to be installed.

For the full set of tests use:

.. code-block:: shell

    $ pytest tests/ -vs --runslow --pymemtrace

This can take around 30 minutes to complete.

Documentation
=======================

To create the documentation with ``Sphinx`` or ``doxygen``.

Sphinx
-----------------------

To build the HTML and PDF documentation from the project directory:

.. code-block:: shell

    $ cd docs/sphinx
    $ make html latexpdf
    $ open build/html/index.html
    $ open build/latex/PythonCppContainers.pdf

Doxygen
-----------------------

To build the HTML Doxygen documentation from the project directory:

.. code-block:: shell

    $ cd docs
    $ doxygen PythonCppContainers.dox
    $ open doxygen/html/index.html
