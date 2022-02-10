.. moduleauthor:: Paul Ross <apaulross@gmail.com>
.. sectionauthor:: Paul Ross <apaulross@gmail.com>

.. User defined types

********************************
User Defined Types
********************************

This code also supports conversion of containers of user defined types between Python and C++.


User Defined Types in a C Extension
============================================

This is based on `the example in the Python documentation <https://docs.python.org/3/extending/newtypes_tutorial.html#adding-data-and-methods-to-the-basic-example>`_
This is varied slightly ffor the example in that:

- The extension code is in the file ``cUserDefined.cpp``.
- The module name is ``cUserDefined`` (rather than the ``custom`` module in the original example).

In this example a ``CustomObject`` class is created:

.. code-block:: c

    typedef struct {
        PyObject_HEAD
        PyObject *first; /* first name */
        PyObject *last;  /* last name */
        int number;
    } CustomObject;


This also has a method ``name()`` that combines the first and last names.

.. code-block::

    >>> import cUserDefined
    >>> custom_object = cUserDefined.Custom('François', 'Truffaut', 21468)
    >>> custom_object.name()
    'François Truffaut'


The C++ Equivalent in the File ``cUserDefined.h``
---------------------------------------------------

This would look something like this:

.. code-block:: cpp

    #include <string>

    class CppCustomObject {
    public:
        CppCustomObject(
            const std::string &first,
            const std::string &last,
            long number) : m_first(first), m_last(last), m_number(number) {}
        // Accessors
        const std::string &first() const { return m_first; }
        const std::string &last() const { return m_last; }
        long number() const { return m_number; }
        // Other methods here...
    private:
        std::string m_first;
        std::string m_last;
        long m_number;
    };


Adding Conversion Code in ``cUserDefined.cpp``
---------------------------------------------------

In the extension add the verification and conversion code between the Python ``CustomObject`` and the C++ ``CppCustomObject``.
First verify the Python type and its contents:

.. code-block:: cpp

    #include "cpy/python_object_convert.h"

    int py_custom_object_check(PyObject *op) {
        if (Py_TYPE(op) != &CustomType) {
            return 0;
        }
        CustomObject *p = (CustomObject *) op;
        if (!Python_Cpp_Containers::py_unicode_check(p->first)) {
            return 0;
        }
        if (!Python_Cpp_Containers::py_unicode_check(p->last)) {
            return 0;
        }
        return 1;
    }

The code to convert from a Python ``CustomObject`` to a C++ ``CppCustomObject``:

.. code-block:: cpp

    CppCustomObject py_custom_object_to_cpp_custom_object(PyObject *op) {
        // Check type, could throw here.
        assert(py_custom_object_check(op));
        CustomObject *p = (CustomObject *) op;
        return CppCustomObject(
                Python_Cpp_Containers::py_unicode_to_cpp_string(p->first),
                Python_Cpp_Containers::py_unicode_to_cpp_string(p->last),
                p->number
        );
    }

The code to convert from a C++ ``CppCustomObject`` to a Python ``CustomObject``:

.. code-block:: cpp

    PyObject *
    cpp_custom_object_to_py_custom_object(const CppCustomObject &obj) {
        CustomObject *op = (CustomObject *) Custom_new(&CustomType, NULL, NULL);
        if (op) {
            op->first = Python_Cpp_Containers::cpp_string_to_py_unicode(obj.first());
            op->last = Python_Cpp_Containers::cpp_string_to_py_unicode(obj.last());
            op->number = obj.number();
        }
        return (PyObject *) op;
    }

In the file, ``cUserDefined.h``, include this project's header file and then in this project's namespace declare
the specialisations to convert to and from lists of these objects:

.. code-block:: cpp

    #include "cpy/python_convert.h"

    namespace Python_Cpp_Containers {

        // Specialised declarations
        // C++ to Python
        template<>
        PyObject *
        cpp_std_list_like_to_py_list<CppCustomObject>(
            const std::vector<CppCustomObject> &container
        );

        // Python to C++
        template<>
        int
        py_list_to_cpp_std_list_like<CppCustomObject>(
            PyObject *op, std::vector<CppCustomObject> &container
        );

    } // namespace Python_Cpp_Containers


In the file, ``cUserDefined.cpp`` implement the specialisations, these are just one-liners.
Firstly from  C++ to Python:

.. code-block:: cpp

    namespace Python_Cpp_Containers {
        // Specialised implementations
        template<>
        PyObject *
        cpp_std_list_like_to_py_list<CppCustomObject>(const std::vector<CppCustomObject> &container) {
            return generic_cpp_std_list_like_to_py_list<
                    CppCustomObject, &cpp_custom_object_to_py_custom_object
            >(container);
        }
    } // namespace Python_Cpp_Containers

Then from Python to C++:

.. code-block:: cpp

    namespace Python_Cpp_Containers {
        template<>
        int
        py_list_to_cpp_std_list_like<CppCustomObject>(PyObject *op, std::vector<CppCustomObject> &container) {
            return generic_py_list_to_cpp_std_list_like<
                    CppCustomObject, &py_custom_object_check, &py_custom_object_to_cpp_custom_object
            >(op, container);
        }

    } // namespace Python_Cpp_Containers

Now you have all the code needed to convert lists of these objects between C++ and Python.

Using the Conversion Functions
------------------------------------------

Here is a fairly trivial example that takes a list of Python ``CustomObject`` and creates a list of C++
``CppCustomObject`` with the first name and last name reversed.
Then it converts that list C++ ``CppCustomObject`` back to a new list of of Python ``CustomObject``.

In ``cUserDefined.cpp``:

.. code-block:: cpp

    static PyObject *
    reverse_list_names(PyObject *Py_UNUSED(module), PyObject *arg) {
        std::vector<CppCustomObject> input;
        // Convert to a C++ vector
        if (! Python_Cpp_Containers::py_list_to_cpp_std_list_like(arg, input)) {
            // Create a new C++ vector with names reversed.
            std::vector<CppCustomObject> output;
            for (const auto &object: input) {
                // Note reversing names.
                output.emplace_back(
                    CppCustomObject(object.last(), object.first(), object.number())
                );
            }
            // Convert to a new Python list.
            return Python_Cpp_Containers::cpp_std_list_like_to_py_list(output);
        }
        return NULL;
    }

Add this function to the module, in ``cUserDefined.cpp``:

.. code-block:: cpp

    // Module functions
    static PyMethodDef cUserDefinedMethods[] = {
            {"reverse_list_names", reverse_list_names, METH_O,
                "Take a list of cUserDefined.Custom objects"
                " and return a new list with the name reversed."},
            {NULL, NULL, 0, NULL}        /* Sentinel */
    };

Build the module and try it out:

.. code-block::

    >>> import cUserDefined
    >>> list_of_names = [cUserDefined.Custom('First', 'Last', 21), cUserDefined.Custom('François', 'Truffaut', 21468)]
    >>> list_of_names
    [<cUserDefined.Custom object at 0x103d43450>, <cUserDefined.Custom object at 0x103f520f0>]
    >>> [v.name() for v in list_of_names]
    ['First Last', 'François Truffaut']

Now reverse the names using C++, the objects returned are new objects (compare with above):

.. code-block::

    >>> result = cUserDefined.reverse_list_names(list_of_names)
    >>> result
    [<cUserDefined.Custom object at 0x103d43720>, <cUserDefined.Custom object at 0x103f52e40>]

And the names are reversed:

.. code-block::

    >>> [v.name() for v in result]
    ['Last First', 'Truffaut François']

Supporting ``dict[int, cUserDefined.Custom]``
---------------------------------------------------

.. code-block:: cpp

    namespace Python_Cpp_Containers {
        // Specialised declarations
        // C++ to Python
        template<>
        PyObject *
        cpp_std_map_like_to_py_dict<std::map, long, CppCustomObject>(
            const std::map<long, CppCustomObject> &map
        );

        // Python to C++
        template <>
        int
        py_dict_to_cpp_std_map_like<std::map, long, CppCustomObject>(
            PyObject* op, std::map<long, CppCustomObject> &map
        );
    } // namespace Python_Cpp_Containers


.. code-block:: cpp

    namespace Python_Cpp_Containers {
        // Specialised definitions
        // C++ to Python
        template<>
        PyObject *
        cpp_std_map_like_to_py_dict<std::map, long, CppCustomObject>(
            const std::map<long, CppCustomObject> &map
        ) {
            return generic_cpp_std_map_like_to_py_dict<
                    std::map, long, CppCustomObject,
                    &cpp_long_to_py_long,
                    &cpp_custom_object_to_py_custom_object
                >(map);
        }

        // Python to C++
        template <>
        int
        py_dict_to_cpp_std_map_like<std::map, long, CppCustomObject>(
            PyObject* op, std::map<long, CppCustomObject> &map
        ) {
            return generic_py_dict_to_cpp_std_map_like<
                    std::map,
                    long, CppCustomObject,
                    &py_long_check, &py_custom_object_check,
                    &py_long_to_cpp_long,
                    &py_custom_object_to_cpp_custom_object
            >(op, map);
        }

    } // namespace Python_Cpp_Containers


.. code-block:: cpp

    static PyObject *
    reverse_dict_names(PyObject *Py_UNUSED(module), PyObject *arg) {
        std::map<long, CppCustomObject> input;
        if (! Python_Cpp_Containers::py_dict_to_cpp_std_map_like(arg, input)) {
            std::map<long, CppCustomObject> output;
            for (const auto &iter: input) {
                output.emplace(
                    std::make_pair(
                        iter.first,
                        CppCustomObject(
                            iter.second.last(), iter.second.first(), iter.second.number()
                        )
                    )
                );
            }
            return Python_Cpp_Containers::cpp_std_map_like_to_py_dict(output);
        }
        return NULL;
    }


.. code-block::

    >>> import cUserDefined
    >>> d = {0 : cUserDefined.Custom('First', 'Last', 17953), 1: cUserDefined.Custom('François', 'Truffaut', 21468),}
    >>> d
    {0: <cUserDefined.Custom object at 0x10e0ec6f0>, 1: <cUserDefined.Custom object at 0x10e0ec450>}


.. code-block::

    >>> e = cUserDefined.reverse_dict_names(d)
    >>> e
    {0: <cUserDefined.Custom object at 0x10e2fb4e0>, 1: <cUserDefined.Custom object at 0x10e2fb1b0>}


.. code-block::

    >>> {k: v.name() for k, v in e.items()}
    {0: 'Last First', 1: 'Truffaut François'}
