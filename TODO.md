#  Various Things To Do

# Supported Types and Containers

## Supported Types

| Python            | C++               | Notes                             |
| ----------------- |:----------------- | :-------------------------------- |
| `True`, `False`   | `bool`            |                                   |
| `int`             | `long`            | Overflow?                         |
| `float`           | `double`          |                                   |
| `complex`         | `std::complex`    | Not for dicts/sets as Python complex is hashable but std::complex is not. Do not support for the moment. |
| `str`             | `std::string`     | Just support `bytes` initially?   |
| `bytes`           | `std::string`     |                                   |
| `bytearray`       | N/A               |                                   |
| `datetime`        | `<chrono>` ???    | Leave for the moment. C++20.      |

So the initial number of supported types is four.
All are hashable so they are all candidates for dictionary keys.

## Supported Containers

| Python        | C++                   | Notes                     |
| ------------- |:--------------------- | :------------------------ |
| `tuple`       | `std::vector`         |                           |
| `list`        | `std::vector`         |                           |
| `set`         | `std::unordered_set`  |                           |
| `frozenset`   | N/A                   |                           |
| `dict`        | `std::unordered_map`  |                           |

There are four supported containers.

## Type and Container Combinations

There are three unary containers and one pair container.

Total unary containers: 3 containers * 4 types * 2 way conversion = 24 functions.

Dict: 1 container * 4**2 types * 2 way conversion = 32 functions.

Total 56 functions.

Supported by two hand coded templates in `python_convert.h` for each container, eight in total.

### Hand Coded Unary Container Functions

The functions that support Python `tuple` <-> C++ `std::vector` and  Python `list` <-> C++ `std::vector` are near identical.

The functions that support Python `set` <-> C++ `std::unordered_set` are very similar to the Python `tuple` <-> C++ `std::vector`.

# Code and Testing

## General

* Use `goto` `except:` and `finally:` throughout `python_convert.h`

## Code Generation

* Make a `code_gen_common.py` that holds `CPP_TYPE_TO_FUNCS` and `UNARY_COLLECTIONS`. This controls the  extent of the code generation.
* Have a flag to control `dict` conversion generation.

## Testing

* ~~Convert the current tests in `main()` to returning a value, 0 for pass.~~
* ~~Add test performance capture [TestFramework].~~
~~* Performance tests need to have some scale element to show time growth with size.~~
* Round tripping.
~~* Random strings, something like `A...Z[rand() % 26]`. No static integer as string, incremented on every call.~~
* Move test generation to `code_gen_test.py` that creates `auto_test...` `.h/.cpp`
* Create performance tests `code_gen_perf.py` that creates `auto_perf...` `.h/.cpp`
* Add dict functional tests.
* Add set tests.

## Source Code Layout

* Move the code into `cpy/`, `py/` and `cpp/` directories.

# Documentation

* `README.md`
* All the rest.
* Add to Python Extension Patterns?

# CPython Interface Example

Suppose we have a C++ function to create a cross product from two vectors.
So given [1, 2, 3] and [4, 5] it returns:

```text
[
    [4, 8, 12],
    [5, 10, 15],
]
```

Create a module that takes two Python lists and returns a Python list of lists.

# Other

* Get `cmake` to create a `Makefile`. `cmake -G "Unix Makefiles"` ?
