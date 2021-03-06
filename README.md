# Python and C++ Containers

Python is well known for it's ability to handle *heterogeneous* data in containers such as lists.
But what if you need to convert to and from C++ containers such as ``std::vector<T>`` that require *homogeneous* data types?


This C++ project is about converting between C++ containers and Python's (`tuple`  ``list``, ``set``, ``frozenset``, ``dict``) containing
homogeneous types (``bool``, ``int``, ``float``, ``complex``, ``bytes``, ``str``) to and from their C++ equivalents.

Two-way conversion for this set of containers:

| C++ Container              | Python Equivalent |
|----------------------------|-------------------|
| `std::vector<T>`           | `list`            |
| `std::vector<T>`           | `tuple`           |
| `std::list<T>`             | `list`            |
| `std::list<T>`             | `tuple`           |
| `std::unordered_set<T>`    | `set`             |
| `std::unordered_set<T>`    | `frozenset`       |
| `std::unordered_map<K, V>` | `dict`            |
| `std::map<K, V>`           | `dict`            |

Containing these objects:

| C++ Type                 | Python Equivalent  |
|--------------------------|---------------------|
| ``bool``                 | ``True``, ``False`` |
| ``long``                 | ``int``             |
| ``double``               | ``float``           |
| ``std::complex<double>`` | ``complex``         |
| ``std::vector<char>``    | ``bytes``           |
| ``std::string``          | ``str``             |

These combinations would normally need 216 specific conversion
functions.

This project reduces that to just **six** hand maintained functions.
The 216 actual conversion functions are then created automatically
using a mixture of templates, partial specialisation and code generation.
This approach means that new types and containers can be added with ease.

## Using This Library

### C++ To Python

TODO:

Suppose that you have a Python list of floats that needs to be passed to a C++ function that expects `std::vector<double>`.
Then that C++ function modifies that vector and you need the result as a new Python list of floats.
With this library your code will be as simple as this:

```c++
static PyObject *
your_function_name(void) {
    std::vector<double> container = some_cpp_function_that_creates_a_vector();
    // Convert the vector back to a new Python list of float
    // with a generic function.
    return cpp_std_list_like_to_py_list(container);
}
```

Some other variations, firstly create a Python `tuple` rather than a `list`:

```c++
static PyObject *
your_function_name(void) {
    std::vector<double> container = some_cpp_function_that_creates_a_vector();
    return cpp_std_list_like_to_py_tuple(container);
}
```

Or work with a `std::list` rather than a `std::vector`:

```c++
static PyObject *
your_function_name(void) {
    std::list<double> container = some_cpp_function_that_creates_a_list();
    return cpp_std_list_like_to_py_list(container);
}
```

Or work with a `std::vector<std::string>>`:

```c++
static PyObject *
your_function_name(void) {
    std::vector<std::string> container = some_cpp_function_that_creates_a_vector();
    return cpp_std_list_like_to_py_list(container);
}
```

Note `cpp_std_list_like_to_py_list(container)` will select the correct type conversion or will give
a compile time error if there is a type mismatch.

### Python to C++

```c++
static PyObject *
your_function_name(PyObject *arg) {
    // Declare the specific vector type
    std::vector<double> vec;
    // Call the generic function to convert a list to a std::vector.
    // This returns non-zero if it can not convert arg to a
    // std::vector<double> 
    if (!py_list_to_cpp_std_list_like(arg, vec)) {
        // Send the std::vector<double> to the C++ library.
        // ...
        Py_RETURN_NONE;
    }
    return NULL;
}
```

# Usage

## Code Generation

If necessary run the code generator:


```shell
cd src/py
python code_gen.py
```

Which should give you something like:

```shell
venv/bin/python src/py/code_gen.py
Target directory "src/cpy"
Writing declarations to "src/cpy/auto_py_convert_internal.h"
Wrote 2654 lines of code with 220 declarations.
Writing definitions to "src/cpy/auto_py_convert_internal.cpp"
Wrote 2384 lines of code with 216 definitions.

Process finished with exit code 0
```

## C++ Build Configuration

You need to compile the following C++ files by adding them to your makefile or CMakeLists.txt:

```text
src/cpy/auto_py_convert_internal.cpp
src/cpy/python_container_convert.cpp
src/cpy/python_object_convert.cpp
```

### Source Inclusion

Your pre-processor needs access to the header files with the compiler flag ``-I src/cpy``.

Then in your C++ code include:

```c++
#include "python_convert.h"
```

Which gives you access to the whole API in the namespace ``Python_Cpp_Containers``.

## Python Extension Example

There are some examples of using this library in *src/ext/cPyCppContainers.cpp*.
This extension is built by *setup.py* and tested with *tests/unit/test_cPyCppContainers.py*.

To build this extension:

```shell
$ python setup.py develop
```

And to use it:

```python
import cPyCppContainer
```

There are a number of functions there that exploit this C++ library.
For example this C function create a C++ ``std::vector<double>`` from a Python list of
floats then creates a new Python list of floats from that C++ container ('round-tripping').

```c++
static PyObject *
new_list_float(PyObject *arg) {
    std::vector<double> vec;
    if (!py_list_to_cpp_std_list_like(arg, vec)) {
        return cpp_std_list_like_to_py_list(vec);
    }
    return NULL;
}
```

This can be called from Python thus:

```python
import cPyCppContainers
cPyCppContainers.new_list_float([1.0, 2.0])
[1.0, 2.0]
```

If the Python list contains non-floats an exception will be raised:

```python
cPyCppContainers.new_list_float([1.0, 2])
Traceback (most recent call last):
File "<stdin>", line 1, in <module>
ValueError: Python value of type int can not be converted
```

### Testing

To test the cPyCppContainers extension which exercises much of the C++ code:

```shell
$ pytest tests/
```

This takes a few seconds.
There are a couple of options that can be added:

* ``--runslow`` will run slow tests including performance test. Use the ``-s`` option to obtain the performance output.
* ``--pymemtrace`` will run memory tracing tests. This requires [pymemtrace](https://pypi.org/project/pymemtrace/) to be installed.

So for the full set of tests:

``` shell
$ pytest -vs --runslow --pymemtrace tests/
```

This can take around 30 minutes to complete.

# Credits

Many thanks to my employer [Paige](https://www.paige.ai) for letting me opensource this project.
