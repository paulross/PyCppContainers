# Python and C++ Containers

Python is well known for it's ability to handle *heterogeneous* data in containers such as lists.
But what if you need to convert to and from C++ containers such as ``std::vector<T>`` that require *homogeneous* data types?


This project is about converting all Python containers (``list``, ``dict``, ``set``, ``frozenset``, ``tuple``) containing
homogeneous types (``bool``, ``int``, ``float``, ``complex``, ``bytes``, ``str``) to and from their C++ equivalent.

For two way conversion for this set of containers:

| Python Container | C++ Equivalent    |
|-----------------|-----------------------|
| ``tuple``       | ``std::vector``       |
| ``list``        | ``std::vector``       |
| ``set``         | ``std::unordered_set`` |
| ``frozenset``   | ``std::unordered_set`` |
| ``dict``        | ``std::unordered_map`` |

Containing these objects:

| Python Object Type  | C++ Equivalent      |
|---------------------|--------------------------|
| ``True``, ``False`` | ``bool``                 |
| ``int``             | ``long``                 |
| ``float``           | ``double``               |
| ``complex``         | ``std::complex<double>`` |
| ``bytes``           | ``std::vector<char>``    |
| ``str``             | ``std::string``          |

These combinations would normally need 120 specific conversion
functions.

This project reduces that to just **six** hand maintained functions.
The 120 actual conversion functions are then created using a
mixture of templates, partial specialisation and code generation.

This approach means that new types and containers can be added with ease.

## Example

Suppose that you have a Python list of floats that needs to be passed to a C++ function that expects `std::vector<double>`.
That C++ function modifies that vector and you need the result as a new Python list of floats.
Your code will look like this:

```c++
static PyObject *
new_list(PyObject *arg) {
    // Declare the specific vector type
    std::vector<double> vec;
    // Call the generic function.
    // This returns non-zero if it can not convert arg to a std::vector<double> 
    if (!py_list_to_cpp_std_vector(arg, vec)) {
        // Send the vector to the C++ library function
        // ...
        // Convert the vector to a new Python list of float with a generic function.
        return cpp_std_vector_to_py_list(vec);
    }
    return NULL;
}

```


