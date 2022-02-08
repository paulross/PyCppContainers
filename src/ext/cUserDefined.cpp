//
// Created by Paul Ross on 08/02/2022.
//

// https://docs.python.org/3/extending/newtypes_tutorial.html#adding-data-and-methods-to-the-basic-example
#include "custom3_Python3.9.0.c"

#include "cpy/python_object_convert.h"
#include "cpy/python_convert.h"

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


int py_custom_object_check(PyObject *op) {
    return Py_TYPE(op) == &CustomType;
}

CppCustomObject py_custom_object_to_cpp_custom_object(PyObject *op) {
    if (Py_TYPE(op) != &CustomType) {
        // TODO: throw
    }
    CustomObject *p = (CustomObject *) op;
    // py_unicode_to_cpp_string
    if (!Python_Cpp_Containers::py_unicode_check(p->first)) {
        // TODO: throw
    }
    if (!Python_Cpp_Containers::py_unicode_check(p->last)) {
        // TODO: throw
    }
    if (!Python_Cpp_Containers::py_long_check()p->number)) {
        // TODO: throw
    }
    return CppCustomObject(
            Python_Cpp_Containers::py_unicode_to_cpp_string(p->first),
            Python_Cpp_Containers::py_unicode_to_cpp_string(p->last),
            p->number
    );
}

PyObject *
cpp_custom_object_to_py_custom_object(const CppCustomObject &obj) {
    CustomObject *op = (CustomObject *) Custom_new(&CustomType, NULL, NULL);
    op->first = Python_Cpp_Containers::cpp_string_to_py_unicode(obj.first());
    op->last = Python_Cpp_Containers::cpp_string_to_py_unicode(obj.last());
    op->number = obj.number();
    return (PyObject *) op;
}

// Declaration
template<>
PyObject *
cpp_std_list_like_to_py_list<CppCustomObject>(const std::vector<CppCustomObject> &container);

// Implementation
template<>
PyObject *
cpp_std_list_like_to_py_list<CppCustomObject>(const std::vector<CppCustomObject> &container) {
    return generic_cpp_std_list_like_to_py_list<CppCustomObject, &cpp_custom_object_to_py_custom_object>(container);
}

// Declaration
template<>
int
py_list_to_cpp_std_list_like<CppCustomObject>(PyObject *op, std::vector<CppCustomObject> &container);

// Implementation
template<>
int
py_list_to_cpp_std_list_like<CppCustomObject>(PyObject *op, std::vector<CppCustomObject> &container) {
    return generic_py_list_to_cpp_std_list_like<CppCustomObject, &py_custom_object_check, &py_custom_object_to_cpp_custom_object>(
            op, container);
}
