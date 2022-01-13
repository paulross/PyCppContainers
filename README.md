# Python and C++ Containers

Python is well known for it's ability to handle *heterogeneous* data in containers such as lists.
But what if you need to convert to and from C++ containers such as ``std::vector<T>`` that require *homogeneous* data types?


This project is about converting Python containers (``list``, ``dict``, ``set``, ``frozenset``, ``tuple``) containing
homogeneous types (``bool``, ``int``, ``float``, ``complex``, ``bytes``, ``str``) to and from their C++ equivalent.

This project gives two way conversion for this set of containers:

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
This project reduces that to just **six** functions using a
mixture of templates and code generation.
New types and containers can be added with ease.
