//
// Created by Paul Ross on 08/02/2022.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_CUSERDEFINED_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_CUSERDEFINED_H

#include "cpy/python_convert.h"
//#include "cpy/python_object_convert.h"

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


// Base declaration
template<typename T>
PyObject *
cpp_std_list_like_to_py_list(const std::vector<T> &container);

// Concrete declaration
template <>
PyObject *
cpp_std_list_like_to_py_list<CppCustomObject>(const std::vector<CppCustomObject> &container);

// Base declaration
template<typename T>
int
py_list_to_cpp_std_list_like(PyObject *op, std::vector<T> &container);

// Concrete declaration
template<>
int
py_list_to_cpp_std_list_like<CppCustomObject>(PyObject *op, std::vector<CppCustomObject> &container);


#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_CUSERDEFINED_H
