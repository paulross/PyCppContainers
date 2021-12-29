# Source Code for Python Cpp Homogenous Containers

In this `src/` directory are:

- `cpp` Pure C++ code, no Python API is used.
- `cpy` C/C++ code that `#inculde`s `Python.h`.
- `ext` Python extensions in C/C++ using Python APIs by `#inculde`ing `Python.h`.
- `py` Pure Python code.

## `cpp/` Files of Note

Code to get the Resident Set Size (RSS).

C++ code that creates a test framework.

## `cpy/` Files and Directories of Note

In the `test/` directory are all the C++ test files including functional and performance tests.

`auto_py_convert_internal.h` and `auto_py_convert_internal.cpp` is the C++ code that is generated by `code_gen.py`.
These C++ files should *not* be edited.

`python_container_convert.h` and `python_container_convert.cpp` contain the handwritten C++ code that provides functions to interact with Python containers such as tuples.
Namely:

- Check if a Python container is a particular type.
- Create a new Python container.
- Find the size of the Python container.
- Set a `PyObject*` into a Python container.
- Get a `PyObject*` from a Python container.

These are all very simple functions that wrap existing Python API functions or macros.

`python_convert.h` contains the C++ code that converts all combinations of Python containers and objects, such as floats, to and from their C/C++ equivalents.
There are just six handwritten C++ template functions here.

`python_object_convert.h` and `python_object_convert.cpp` contain the handwritten C++ code that converts Python objects, such as floats, to and from their C/C++ equivalents.
Namely:

- Check if a Python object is a particular type.
- Convert a `PyObject*` into a C++ type.
- Convert a C++ type into a `PyObject*`.

These are all very simple functions that wrap existing Python API functions or macros.

## `ext/` Files of Note

Here is `cPyCppContainers.cpp` which provides examples of interfacing between C++ and Python with this code.
This extension is used for the round trip performance tests. 

## `py/` Files of Note

This contains the Python scripts that generate C++ code into the `cpy/` directory. 
`code_gen.py` is the main script.