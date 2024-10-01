//
// Created by Paul Ross on 08/02/2022.
//

#ifndef PY_CPP_CONTAINERS_CUSERDEFINED_H
#define PY_CPP_CONTAINERS_CUSERDEFINED_H

#include <string>
#include <utility>

class CppCustomObject {
public:
    CppCustomObject() {};
    CppCustomObject(
            std::string first,
            std::string last,
            long number) : m_first(std::move(first)), m_last(std::move(last)), m_number(number) {}

//    CppCustomObject(const CppCustomObject&) = default;
//    CppCustomObject(CppCustomObject&&) = default;
//    CppCustomObject& operator=(const CppCustomObject&) = default;
//    CppCustomObject& operator=(CppCustomObject&&) = default;
//    virtual ~CppCustomObject() = default;

    // Accessors
    const std::string &first() const { return m_first; }
    const std::string &last() const { return m_last; }
    long number() const { return m_number; }
    std::string name() { return m_first + " " + m_last; }
    // Other methods here...
private:
    std::string m_first;
    std::string m_last;
    long m_number;
};

#include "cpy/python_convert.h"

//// Base declaration
//template<typename T>
//PyObject *
//cpp_std_list_like_to_py_list(const std::vector<T> &container);

//// Base declaration
//template<typename T>
//int
//py_list_to_cpp_std_list_like(PyObject *op, std::vector<T> &container);

namespace Python_Cpp_Containers {

    // Specialised declarations
    template<>
    PyObject *
    cpp_std_list_like_to_py_list<CppCustomObject>(const std::vector<CppCustomObject> &container);

    template<>
    int
    py_list_to_cpp_std_list_like<CppCustomObject>(PyObject *op, std::vector<CppCustomObject> &container);

    // Add dict support
    // Specialised declarations
    template<>
    PyObject *
    cpp_std_map_like_to_py_dict<std::map, long, CppCustomObject>(const std::map<long, CppCustomObject> &map);

    template <>
    int
    py_dict_to_cpp_std_map_like<std::map, long, CppCustomObject>(PyObject* op, std::map<long, CppCustomObject> &map);

} // namespace Python_Cpp_Containers

#endif //PY_CPP_CONTAINERS_CUSERDEFINED_H
