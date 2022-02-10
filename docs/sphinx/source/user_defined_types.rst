.. moduleauthor:: Paul Ross <apaulross@gmail.com>
.. sectionauthor:: Paul Ross <apaulross@gmail.com>

.. User defined types

********************************
Adding User Defined Types
********************************


In CPython:

.. code-block:: c

    typedef struct {
        PyObject_HEAD
        PyObject *first; /* first name */
        PyObject *last;  /* last name */
        int number;
    } CustomObject;


Based on `the example in the Python documentation <https://docs.python.org/3/extending/newtypes_tutorial.html#adding-data-and-methods-to-the-basic-example>`_

This also has a method ``name()`` that combines the first and last names:

.. code-block::

    >>> import cUserDefined
    >>> custom_object = cUserDefined.Custom('First', 'Last', 21)
    >>> custom_object.name()
    'First Last'



Stuff
============================================================


The File ``cUserDefined.h``
---------------------------------------


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


.. code-block:: cpp

    #include "cpy/python_convert.h"

    namespace Python_Cpp_Containers {

        // Specialised declarations
        // C++ to Python
        template<>
        PyObject *
        cpp_std_list_like_to_py_list<CppCustomObject>(const std::vector<CppCustomObject> &container);

        // Python to C++
        template<>
        int
        py_list_to_cpp_std_list_like<CppCustomObject>(PyObject *op, std::vector<CppCustomObject> &container);

    } // namespace Python_Cpp_Containers


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

.. code-block:: cpp

    CppCustomObject py_custom_object_to_cpp_custom_object(PyObject *op) {
        if (!py_custom_object_check(op)) {
            // TODO: throw
        }
        CustomObject *p = (CustomObject *) op;
        return CppCustomObject(
                Python_Cpp_Containers::py_unicode_to_cpp_string(p->first),
                Python_Cpp_Containers::py_unicode_to_cpp_string(p->last),
                p->number
        );
    }

.. code-block:: cpp

    PyObject *
    cpp_custom_object_to_py_custom_object(const CppCustomObject &obj) {
        CustomObject *op = (CustomObject *) Custom_new(&CustomType, NULL, NULL);
        op->first = Python_Cpp_Containers::cpp_string_to_py_unicode(obj.first());
        op->last = Python_Cpp_Containers::cpp_string_to_py_unicode(obj.last());
        op->number = obj.number();
        return (PyObject *) op;
    }

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

.. code-block:: cpp

    static PyObject *
    reverse_names(PyObject *Py_UNUSED(module), PyObject *arg) {
        std::vector<CppCustomObject> input;
        if (! Python_Cpp_Containers::py_list_to_cpp_std_list_like(arg, input)) {
            std::vector<CppCustomObject> output;
            for (const auto &object: input) {
                output.emplace_back(CppCustomObject(object.last(), object.first(), object.number()));
            }
            return Python_Cpp_Containers::cpp_std_list_like_to_py_list(output);
        }
        return NULL;
    }

.. code-block:: cpp

    // Module functions
    static PyMethodDef cUserDefinedMethods[] = {
            {"reverse_names", reverse_names, METH_O,
                "Take a list of cUserDefined.Custom objects"
                " and return a new list with the name reversed."},
            {NULL, NULL, 0, NULL}        /* Sentinel */
    };


.. code-block::

    >>> import cUserDefined
    >>> list_of_names = [cUserDefined.Custom('First', 'Last', 21), cUserDefined.Custom('One', 'Two', 2487)]
    >>> list_of_names
    [<cUserDefined.Custom object at 0x10169c720>, <cUserDefined.Custom object at 0x10169c6f0>]
    >>> [v.name() for v in list_of_names]
    ['First Last', 'One Two']

Now reverse the names using C++:

.. code-block::

    >>> result = cUserDefined.reverse_names(list_of_names)

The objects returned are new objects (compare with above):

.. code-block::

    >>> result
    [<cUserDefined.Custom object at 0x1018ab4e0>, <cUserDefined.Custom object at 0x1018ab810>]

And their names are reversed:

.. code-block::

    >>> [v.name() for v in result]
    ['Last First', 'Two One']



FIXME:

.. code-block::

    >>> c = cUserDefined.Custom('Fred', 'Gürzenichstraße', 895)
    >>> c.Name()
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    AttributeError: 'cUserDefined.Custom' object has no attribute 'Name'
    >>> c.name()
    'Fred Gürzenichstraße'
    >>> l = [c]
    >>> m = cUserDefined.reverse_names(l)
    UnicodeDecodeError: 'utf-8' codec can't decode byte 0xfc in position 1: invalid start byte

    The above exception was the direct cause of the following exception:

    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    SystemError: <built-in function reverse_names> returned a result with an error set
