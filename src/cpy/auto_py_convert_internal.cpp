//============================ Definition file ============================
//#########################################################################
//####### Auto-generated code - do not edit. Seriously, do NOT edit. ######
//#########################################################################
//
// Version: 0.3.2
//
// Conversion from homogeneous data structures in Python and C++
// 
// Unary conversions
// tuple:
// UnaryFunctions(python_container='tuple', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::vector<bool>
// UnaryFunctions(python_container='tuple', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::vector<long>
// UnaryFunctions(python_container='tuple', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::vector<double>
// UnaryFunctions(python_container='tuple', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::vector<std::complex<double>>
// UnaryFunctions(python_container='tuple', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::vector<std::vector<char>>
// UnaryFunctions(python_container='tuple', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::vector<std::string>
// 
// tuple:
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<bool>
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<long>
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<double>
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<std::complex<double>>
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<std::vector<char>>
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<std::string>
// 
// list:
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<bool>
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<long>
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<double>
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<std::complex<double>>
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<std::vector<char>>
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<std::string>
// 
// list:
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<bool>
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<long>
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<double>
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<std::complex<double>>
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<std::vector<char>>
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<std::string>
// 
// set:
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<bool>
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<long>
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<double>
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<std::complex<double>>
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<std::vector<char>>
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<std::string>
// 
// frozenset:
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<bool>
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<long>
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<double>
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<std::complex<double>>
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<std::vector<char>>
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<std::string>
// 
// 
// Mapping conversions
// dict <-> std::unordered_map<bool, bool>
// dict <-> std::unordered_map<bool, long>
// dict <-> std::unordered_map<bool, double>
// dict <-> std::unordered_map<bool, std::complex<double>>
// dict <-> std::unordered_map<bool, std::vector<char>>
// dict <-> std::unordered_map<bool, std::string>
// dict <-> std::unordered_map<long, bool>
// dict <-> std::unordered_map<long, long>
// dict <-> std::unordered_map<long, double>
// dict <-> std::unordered_map<long, std::complex<double>>
// dict <-> std::unordered_map<long, std::vector<char>>
// dict <-> std::unordered_map<long, std::string>
// dict <-> std::unordered_map<double, bool>
// dict <-> std::unordered_map<double, long>
// dict <-> std::unordered_map<double, double>
// dict <-> std::unordered_map<double, std::complex<double>>
// dict <-> std::unordered_map<double, std::vector<char>>
// dict <-> std::unordered_map<double, std::string>
// dict <-> std::unordered_map<std::complex<double>, bool>
// dict <-> std::unordered_map<std::complex<double>, long>
// dict <-> std::unordered_map<std::complex<double>, double>
// dict <-> std::unordered_map<std::complex<double>, std::complex<double>>
// dict <-> std::unordered_map<std::complex<double>, std::vector<char>>
// dict <-> std::unordered_map<std::complex<double>, std::string>
// dict <-> std::unordered_map<std::vector<char>, bool>
// dict <-> std::unordered_map<std::vector<char>, long>
// dict <-> std::unordered_map<std::vector<char>, double>
// dict <-> std::unordered_map<std::vector<char>, std::complex<double>>
// dict <-> std::unordered_map<std::vector<char>, std::vector<char>>
// dict <-> std::unordered_map<std::vector<char>, std::string>
// dict <-> std::unordered_map<std::string, bool>
// dict <-> std::unordered_map<std::string, long>
// dict <-> std::unordered_map<std::string, double>
// dict <-> std::unordered_map<std::string, std::complex<double>>
// dict <-> std::unordered_map<std::string, std::vector<char>>
// dict <-> std::unordered_map<std::string, std::string>
// 
#include "python_convert.h"

namespace Python_Cpp_Containers {

//**************** Unary collections <-> Python collections ***************
//---------------------- std::vector -> Python tuple ----------------------
template <>
PyObject *
cpp_std_list_like_to_py_tuple<bool>(const std::vector<bool> &container) {
    return generic_cpp_std_list_like_to_py_tuple<bool, &cpp_bool_to_py_bool>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_tuple<long>(const std::vector<long> &container) {
    return generic_cpp_std_list_like_to_py_tuple<long, &cpp_long_to_py_long>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_tuple<double>(const std::vector<double> &container) {
    return generic_cpp_std_list_like_to_py_tuple<double, &cpp_double_to_py_float>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::complex<double>>(const std::vector<std::complex<double>> &container) {
    return generic_cpp_std_list_like_to_py_tuple<std::complex<double>, &cpp_complex_to_py_complex>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::vector<char>>(const std::vector<std::vector<char>> &container) {
    return generic_cpp_std_list_like_to_py_tuple<std::vector<char>, &cpp_vector_char_to_py_bytes>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::string>(const std::vector<std::string> &container) {
    return generic_cpp_std_list_like_to_py_tuple<std::string, &cpp_string_to_py_unicode>(container);
}

//-------------------- END: std::vector -> Python tuple -------------------

//---------------------- Python tuple -> std::vector ----------------------
template <>
int
py_tuple_to_cpp_std_list_like<bool>(PyObject *op, std::vector<bool> &container) {
    return generic_py_tuple_to_cpp_std_list_like<bool, &py_bool_check, &py_bool_to_cpp_bool>(op, container);
}

template <>
int
py_tuple_to_cpp_std_list_like<long>(PyObject *op, std::vector<long> &container) {
    return generic_py_tuple_to_cpp_std_list_like<long, &py_long_check, &py_long_to_cpp_long>(op, container);
}

template <>
int
py_tuple_to_cpp_std_list_like<double>(PyObject *op, std::vector<double> &container) {
    return generic_py_tuple_to_cpp_std_list_like<double, &py_float_check, &py_float_to_cpp_double>(op, container);
}

template <>
int
py_tuple_to_cpp_std_list_like<std::complex<double>>(PyObject *op, std::vector<std::complex<double>> &container) {
    return generic_py_tuple_to_cpp_std_list_like<std::complex<double>, &py_complex_check, &py_complex_to_cpp_complex>(op, container);
}

template <>
int
py_tuple_to_cpp_std_list_like<std::vector<char>>(PyObject *op, std::vector<std::vector<char>> &container) {
    return generic_py_tuple_to_cpp_std_list_like<std::vector<char>, &py_bytes_check, &py_bytes_to_cpp_vector_char>(op, container);
}

template <>
int
py_tuple_to_cpp_std_list_like<std::string>(PyObject *op, std::vector<std::string> &container) {
    return generic_py_tuple_to_cpp_std_list_like<std::string, &py_unicode_check, &py_unicode_to_cpp_string>(op, container);
}

//-------------------- END: Python tuple -> std::vector -------------------

//----------------------- std::list -> Python tuple -----------------------
template <>
PyObject *
cpp_std_list_like_to_py_tuple<bool>(const std::list<bool> &container) {
    return generic_cpp_std_list_like_to_py_tuple<bool, &cpp_bool_to_py_bool>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_tuple<long>(const std::list<long> &container) {
    return generic_cpp_std_list_like_to_py_tuple<long, &cpp_long_to_py_long>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_tuple<double>(const std::list<double> &container) {
    return generic_cpp_std_list_like_to_py_tuple<double, &cpp_double_to_py_float>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::complex<double>>(const std::list<std::complex<double>> &container) {
    return generic_cpp_std_list_like_to_py_tuple<std::complex<double>, &cpp_complex_to_py_complex>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::vector<char>>(const std::list<std::vector<char>> &container) {
    return generic_cpp_std_list_like_to_py_tuple<std::vector<char>, &cpp_vector_char_to_py_bytes>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::string>(const std::list<std::string> &container) {
    return generic_cpp_std_list_like_to_py_tuple<std::string, &cpp_string_to_py_unicode>(container);
}

//--------------------- END: std::list -> Python tuple --------------------

//----------------------- Python tuple -> std::list -----------------------
template <>
int
py_tuple_to_cpp_std_list_like<bool>(PyObject *op, std::list<bool> &container) {
    return generic_py_tuple_to_cpp_std_list_like<bool, &py_bool_check, &py_bool_to_cpp_bool>(op, container);
}

template <>
int
py_tuple_to_cpp_std_list_like<long>(PyObject *op, std::list<long> &container) {
    return generic_py_tuple_to_cpp_std_list_like<long, &py_long_check, &py_long_to_cpp_long>(op, container);
}

template <>
int
py_tuple_to_cpp_std_list_like<double>(PyObject *op, std::list<double> &container) {
    return generic_py_tuple_to_cpp_std_list_like<double, &py_float_check, &py_float_to_cpp_double>(op, container);
}

template <>
int
py_tuple_to_cpp_std_list_like<std::complex<double>>(PyObject *op, std::list<std::complex<double>> &container) {
    return generic_py_tuple_to_cpp_std_list_like<std::complex<double>, &py_complex_check, &py_complex_to_cpp_complex>(op, container);
}

template <>
int
py_tuple_to_cpp_std_list_like<std::vector<char>>(PyObject *op, std::list<std::vector<char>> &container) {
    return generic_py_tuple_to_cpp_std_list_like<std::vector<char>, &py_bytes_check, &py_bytes_to_cpp_vector_char>(op, container);
}

template <>
int
py_tuple_to_cpp_std_list_like<std::string>(PyObject *op, std::list<std::string> &container) {
    return generic_py_tuple_to_cpp_std_list_like<std::string, &py_unicode_check, &py_unicode_to_cpp_string>(op, container);
}

//--------------------- END: Python tuple -> std::list --------------------

//----------------------- std::vector -> Python list ----------------------
template <>
PyObject *
cpp_std_list_like_to_py_list<bool>(const std::vector<bool> &container) {
    return generic_cpp_std_list_like_to_py_list<bool, &cpp_bool_to_py_bool>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_list<long>(const std::vector<long> &container) {
    return generic_cpp_std_list_like_to_py_list<long, &cpp_long_to_py_long>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_list<double>(const std::vector<double> &container) {
    return generic_cpp_std_list_like_to_py_list<double, &cpp_double_to_py_float>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_list<std::complex<double>>(const std::vector<std::complex<double>> &container) {
    return generic_cpp_std_list_like_to_py_list<std::complex<double>, &cpp_complex_to_py_complex>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_list<std::vector<char>>(const std::vector<std::vector<char>> &container) {
    return generic_cpp_std_list_like_to_py_list<std::vector<char>, &cpp_vector_char_to_py_bytes>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_list<std::string>(const std::vector<std::string> &container) {
    return generic_cpp_std_list_like_to_py_list<std::string, &cpp_string_to_py_unicode>(container);
}

//-------------------- END: std::vector -> Python list --------------------

//----------------------- Python list -> std::vector ----------------------
template <>
int
py_list_to_cpp_std_list_like<bool>(PyObject *op, std::vector<bool> &container) {
    return generic_py_list_to_cpp_std_list_like<bool, &py_bool_check, &py_bool_to_cpp_bool>(op, container);
}

template <>
int
py_list_to_cpp_std_list_like<long>(PyObject *op, std::vector<long> &container) {
    return generic_py_list_to_cpp_std_list_like<long, &py_long_check, &py_long_to_cpp_long>(op, container);
}

template <>
int
py_list_to_cpp_std_list_like<double>(PyObject *op, std::vector<double> &container) {
    return generic_py_list_to_cpp_std_list_like<double, &py_float_check, &py_float_to_cpp_double>(op, container);
}

template <>
int
py_list_to_cpp_std_list_like<std::complex<double>>(PyObject *op, std::vector<std::complex<double>> &container) {
    return generic_py_list_to_cpp_std_list_like<std::complex<double>, &py_complex_check, &py_complex_to_cpp_complex>(op, container);
}

template <>
int
py_list_to_cpp_std_list_like<std::vector<char>>(PyObject *op, std::vector<std::vector<char>> &container) {
    return generic_py_list_to_cpp_std_list_like<std::vector<char>, &py_bytes_check, &py_bytes_to_cpp_vector_char>(op, container);
}

template <>
int
py_list_to_cpp_std_list_like<std::string>(PyObject *op, std::vector<std::string> &container) {
    return generic_py_list_to_cpp_std_list_like<std::string, &py_unicode_check, &py_unicode_to_cpp_string>(op, container);
}

//-------------------- END: Python list -> std::vector --------------------

//------------------------ std::list -> Python list -----------------------
template <>
PyObject *
cpp_std_list_like_to_py_list<bool>(const std::list<bool> &container) {
    return generic_cpp_std_list_like_to_py_list<bool, &cpp_bool_to_py_bool>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_list<long>(const std::list<long> &container) {
    return generic_cpp_std_list_like_to_py_list<long, &cpp_long_to_py_long>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_list<double>(const std::list<double> &container) {
    return generic_cpp_std_list_like_to_py_list<double, &cpp_double_to_py_float>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_list<std::complex<double>>(const std::list<std::complex<double>> &container) {
    return generic_cpp_std_list_like_to_py_list<std::complex<double>, &cpp_complex_to_py_complex>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_list<std::vector<char>>(const std::list<std::vector<char>> &container) {
    return generic_cpp_std_list_like_to_py_list<std::vector<char>, &cpp_vector_char_to_py_bytes>(container);
}

template <>
PyObject *
cpp_std_list_like_to_py_list<std::string>(const std::list<std::string> &container) {
    return generic_cpp_std_list_like_to_py_list<std::string, &cpp_string_to_py_unicode>(container);
}

//--------------------- END: std::list -> Python list ---------------------

//------------------------ Python list -> std::list -----------------------
template <>
int
py_list_to_cpp_std_list_like<bool>(PyObject *op, std::list<bool> &container) {
    return generic_py_list_to_cpp_std_list_like<bool, &py_bool_check, &py_bool_to_cpp_bool>(op, container);
}

template <>
int
py_list_to_cpp_std_list_like<long>(PyObject *op, std::list<long> &container) {
    return generic_py_list_to_cpp_std_list_like<long, &py_long_check, &py_long_to_cpp_long>(op, container);
}

template <>
int
py_list_to_cpp_std_list_like<double>(PyObject *op, std::list<double> &container) {
    return generic_py_list_to_cpp_std_list_like<double, &py_float_check, &py_float_to_cpp_double>(op, container);
}

template <>
int
py_list_to_cpp_std_list_like<std::complex<double>>(PyObject *op, std::list<std::complex<double>> &container) {
    return generic_py_list_to_cpp_std_list_like<std::complex<double>, &py_complex_check, &py_complex_to_cpp_complex>(op, container);
}

template <>
int
py_list_to_cpp_std_list_like<std::vector<char>>(PyObject *op, std::list<std::vector<char>> &container) {
    return generic_py_list_to_cpp_std_list_like<std::vector<char>, &py_bytes_check, &py_bytes_to_cpp_vector_char>(op, container);
}

template <>
int
py_list_to_cpp_std_list_like<std::string>(PyObject *op, std::list<std::string> &container) {
    return generic_py_list_to_cpp_std_list_like<std::string, &py_unicode_check, &py_unicode_to_cpp_string>(op, container);
}

//--------------------- END: Python list -> std::list ---------------------

//-------------------- std::unordered_set -> Python set -------------------
template <>
PyObject *
cpp_std_unordered_set_to_py_set<bool>(const std::unordered_set<bool> &container) {
    return generic_cpp_std_unordered_set_to_py_set<bool, &cpp_bool_to_py_bool>(container);
}

template <>
PyObject *
cpp_std_unordered_set_to_py_set<long>(const std::unordered_set<long> &container) {
    return generic_cpp_std_unordered_set_to_py_set<long, &cpp_long_to_py_long>(container);
}

template <>
PyObject *
cpp_std_unordered_set_to_py_set<double>(const std::unordered_set<double> &container) {
    return generic_cpp_std_unordered_set_to_py_set<double, &cpp_double_to_py_float>(container);
}

template <>
PyObject *
cpp_std_unordered_set_to_py_set<std::complex<double>>(const std::unordered_set<std::complex<double>> &container) {
    return generic_cpp_std_unordered_set_to_py_set<std::complex<double>, &cpp_complex_to_py_complex>(container);
}

template <>
PyObject *
cpp_std_unordered_set_to_py_set<std::vector<char>>(const std::unordered_set<std::vector<char>> &container) {
    return generic_cpp_std_unordered_set_to_py_set<std::vector<char>, &cpp_vector_char_to_py_bytes>(container);
}

template <>
PyObject *
cpp_std_unordered_set_to_py_set<std::string>(const std::unordered_set<std::string> &container) {
    return generic_cpp_std_unordered_set_to_py_set<std::string, &cpp_string_to_py_unicode>(container);
}

//----------------- END: std::unordered_set -> Python set -----------------

//-------------------- Python set -> std::unordered_set -------------------
template <>
int
py_set_to_cpp_std_unordered_set<bool>(PyObject *op, std::unordered_set<bool> &container) {
    return generic_py_set_to_cpp_std_unordered_set<bool, &py_bool_check, &py_bool_to_cpp_bool>(op, container);
}

template <>
int
py_set_to_cpp_std_unordered_set<long>(PyObject *op, std::unordered_set<long> &container) {
    return generic_py_set_to_cpp_std_unordered_set<long, &py_long_check, &py_long_to_cpp_long>(op, container);
}

template <>
int
py_set_to_cpp_std_unordered_set<double>(PyObject *op, std::unordered_set<double> &container) {
    return generic_py_set_to_cpp_std_unordered_set<double, &py_float_check, &py_float_to_cpp_double>(op, container);
}

template <>
int
py_set_to_cpp_std_unordered_set<std::complex<double>>(PyObject *op, std::unordered_set<std::complex<double>> &container) {
    return generic_py_set_to_cpp_std_unordered_set<std::complex<double>, &py_complex_check, &py_complex_to_cpp_complex>(op, container);
}

template <>
int
py_set_to_cpp_std_unordered_set<std::vector<char>>(PyObject *op, std::unordered_set<std::vector<char>> &container) {
    return generic_py_set_to_cpp_std_unordered_set<std::vector<char>, &py_bytes_check, &py_bytes_to_cpp_vector_char>(op, container);
}

template <>
int
py_set_to_cpp_std_unordered_set<std::string>(PyObject *op, std::unordered_set<std::string> &container) {
    return generic_py_set_to_cpp_std_unordered_set<std::string, &py_unicode_check, &py_unicode_to_cpp_string>(op, container);
}

//----------------- END: Python set -> std::unordered_set -----------------

//----------------- std::unordered_set -> Python frozenset ----------------
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<bool>(const std::unordered_set<bool> &container) {
    return generic_cpp_std_unordered_set_to_py_frozenset<bool, &cpp_bool_to_py_bool>(container);
}

template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<long>(const std::unordered_set<long> &container) {
    return generic_cpp_std_unordered_set_to_py_frozenset<long, &cpp_long_to_py_long>(container);
}

template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<double>(const std::unordered_set<double> &container) {
    return generic_cpp_std_unordered_set_to_py_frozenset<double, &cpp_double_to_py_float>(container);
}

template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<std::complex<double>>(const std::unordered_set<std::complex<double>> &container) {
    return generic_cpp_std_unordered_set_to_py_frozenset<std::complex<double>, &cpp_complex_to_py_complex>(container);
}

template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<std::vector<char>>(const std::unordered_set<std::vector<char>> &container) {
    return generic_cpp_std_unordered_set_to_py_frozenset<std::vector<char>, &cpp_vector_char_to_py_bytes>(container);
}

template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<std::string>(const std::unordered_set<std::string> &container) {
    return generic_cpp_std_unordered_set_to_py_frozenset<std::string, &cpp_string_to_py_unicode>(container);
}

//-------------- END: std::unordered_set -> Python frozenset --------------

//----------------- Python frozenset -> std::unordered_set ----------------
template <>
int
py_frozenset_to_cpp_std_unordered_set<bool>(PyObject *op, std::unordered_set<bool> &container) {
    return generic_py_frozenset_to_cpp_std_unordered_set<bool, &py_bool_check, &py_bool_to_cpp_bool>(op, container);
}

template <>
int
py_frozenset_to_cpp_std_unordered_set<long>(PyObject *op, std::unordered_set<long> &container) {
    return generic_py_frozenset_to_cpp_std_unordered_set<long, &py_long_check, &py_long_to_cpp_long>(op, container);
}

template <>
int
py_frozenset_to_cpp_std_unordered_set<double>(PyObject *op, std::unordered_set<double> &container) {
    return generic_py_frozenset_to_cpp_std_unordered_set<double, &py_float_check, &py_float_to_cpp_double>(op, container);
}

template <>
int
py_frozenset_to_cpp_std_unordered_set<std::complex<double>>(PyObject *op, std::unordered_set<std::complex<double>> &container) {
    return generic_py_frozenset_to_cpp_std_unordered_set<std::complex<double>, &py_complex_check, &py_complex_to_cpp_complex>(op, container);
}

template <>
int
py_frozenset_to_cpp_std_unordered_set<std::vector<char>>(PyObject *op, std::unordered_set<std::vector<char>> &container) {
    return generic_py_frozenset_to_cpp_std_unordered_set<std::vector<char>, &py_bytes_check, &py_bytes_to_cpp_vector_char>(op, container);
}

template <>
int
py_frozenset_to_cpp_std_unordered_set<std::string>(PyObject *op, std::unordered_set<std::string> &container) {
    return generic_py_frozenset_to_cpp_std_unordered_set<std::string, &py_unicode_check, &py_unicode_to_cpp_string>(op, container);
}

//-------------- END: Python frozenset -> std::unordered_set --------------

//************* END: Unary collections <-> Python collections *************

//**************** std::std::unordered_map <-> Python dict ****************
//------------- Converts a std::std::unordered_map<bool, bool> ------------
//--------------- to a Python dict of { bool : bool, ...}    --------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, bool>(const std::unordered_map<bool, bool> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        bool, bool,
        &cpp_bool_to_py_bool, &cpp_bool_to_py_bool
    >(map);
}

//-------------- Converts a Python dict of {bool : bool, ...} -------------
//---------------- to a std::std::unordered_map<bool, bool> ---------------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, bool>(PyObject* op, std::unordered_map<bool, bool> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        bool, bool,
        &py_bool_check, &py_bool_check,
        &py_bool_to_cpp_bool, &py_bool_to_cpp_bool
    >(op, map);
}

//------------- Converts a std::std::unordered_map<bool, long> ------------
//--------------- to a Python dict of { bool : long, ...}    --------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, long>(const std::unordered_map<bool, long> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        bool, long,
        &cpp_bool_to_py_bool, &cpp_long_to_py_long
    >(map);
}

//-------------- Converts a Python dict of {bool : long, ...} -------------
//---------------- to a std::std::unordered_map<bool, long> ---------------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, long>(PyObject* op, std::unordered_map<bool, long> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        bool, long,
        &py_bool_check, &py_long_check,
        &py_bool_to_cpp_bool, &py_long_to_cpp_long
    >(op, map);
}

//------------ Converts a std::std::unordered_map<bool, double> -----------
//-------------- to a Python dict of { bool : double, ...}    -------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, double>(const std::unordered_map<bool, double> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        bool, double,
        &cpp_bool_to_py_bool, &cpp_double_to_py_float
    >(map);
}

//------------- Converts a Python dict of {bool : double, ...} ------------
//--------------- to a std::std::unordered_map<bool, double> --------------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, double>(PyObject* op, std::unordered_map<bool, double> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        bool, double,
        &py_bool_check, &py_float_check,
        &py_bool_to_cpp_bool, &py_float_to_cpp_double
    >(op, map);
}

//----- Converts a std::std::unordered_map<bool, std::complex<double>> ----
//------- to a Python dict of { bool : std::complex<double>, ...}    ------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, std::complex<double>>(const std::unordered_map<bool, std::complex<double>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        bool, std::complex<double>,
        &cpp_bool_to_py_bool, &cpp_complex_to_py_complex
    >(map);
}

//------ Converts a Python dict of {bool : std::complex<double>, ...} -----
//-------- to a std::std::unordered_map<bool, std::complex<double>> -------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, std::complex<double>>(PyObject* op, std::unordered_map<bool, std::complex<double>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        bool, std::complex<double>,
        &py_bool_check, &py_complex_check,
        &py_bool_to_cpp_bool, &py_complex_to_cpp_complex
    >(op, map);
}

//------ Converts a std::std::unordered_map<bool, std::vector<char>> ------
//-------- to a Python dict of { bool : std::vector<char>, ...}    --------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, std::vector<char>>(const std::unordered_map<bool, std::vector<char>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        bool, std::vector<char>,
        &cpp_bool_to_py_bool, &cpp_vector_char_to_py_bytes
    >(map);
}

//------- Converts a Python dict of {bool : std::vector<char>, ...} -------
//--------- to a std::std::unordered_map<bool, std::vector<char>> ---------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, std::vector<char>>(PyObject* op, std::unordered_map<bool, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        bool, std::vector<char>,
        &py_bool_check, &py_bytes_check,
        &py_bool_to_cpp_bool, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//--------- Converts a std::std::unordered_map<bool, std::string> ---------
//----------- to a Python dict of { bool : std::string, ...}    -----------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, std::string>(const std::unordered_map<bool, std::string> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        bool, std::string,
        &cpp_bool_to_py_bool, &cpp_string_to_py_unicode
    >(map);
}

//---------- Converts a Python dict of {bool : std::string, ...} ----------
//------------ to a std::std::unordered_map<bool, std::string> ------------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, std::string>(PyObject* op, std::unordered_map<bool, std::string> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        bool, std::string,
        &py_bool_check, &py_unicode_check,
        &py_bool_to_cpp_bool, &py_unicode_to_cpp_string
    >(op, map);
}

//------------- Converts a std::std::unordered_map<long, bool> ------------
//--------------- to a Python dict of { long : bool, ...}    --------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, bool>(const std::unordered_map<long, bool> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        long, bool,
        &cpp_long_to_py_long, &cpp_bool_to_py_bool
    >(map);
}

//-------------- Converts a Python dict of {long : bool, ...} -------------
//---------------- to a std::std::unordered_map<long, bool> ---------------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, bool>(PyObject* op, std::unordered_map<long, bool> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        long, bool,
        &py_long_check, &py_bool_check,
        &py_long_to_cpp_long, &py_bool_to_cpp_bool
    >(op, map);
}

//------------- Converts a std::std::unordered_map<long, long> ------------
//--------------- to a Python dict of { long : long, ...}    --------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, long>(const std::unordered_map<long, long> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        long, long,
        &cpp_long_to_py_long, &cpp_long_to_py_long
    >(map);
}

//-------------- Converts a Python dict of {long : long, ...} -------------
//---------------- to a std::std::unordered_map<long, long> ---------------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, long>(PyObject* op, std::unordered_map<long, long> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        long, long,
        &py_long_check, &py_long_check,
        &py_long_to_cpp_long, &py_long_to_cpp_long
    >(op, map);
}

//------------ Converts a std::std::unordered_map<long, double> -----------
//-------------- to a Python dict of { long : double, ...}    -------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, double>(const std::unordered_map<long, double> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        long, double,
        &cpp_long_to_py_long, &cpp_double_to_py_float
    >(map);
}

//------------- Converts a Python dict of {long : double, ...} ------------
//--------------- to a std::std::unordered_map<long, double> --------------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, double>(PyObject* op, std::unordered_map<long, double> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        long, double,
        &py_long_check, &py_float_check,
        &py_long_to_cpp_long, &py_float_to_cpp_double
    >(op, map);
}

//----- Converts a std::std::unordered_map<long, std::complex<double>> ----
//------- to a Python dict of { long : std::complex<double>, ...}    ------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, std::complex<double>>(const std::unordered_map<long, std::complex<double>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        long, std::complex<double>,
        &cpp_long_to_py_long, &cpp_complex_to_py_complex
    >(map);
}

//------ Converts a Python dict of {long : std::complex<double>, ...} -----
//-------- to a std::std::unordered_map<long, std::complex<double>> -------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, std::complex<double>>(PyObject* op, std::unordered_map<long, std::complex<double>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        long, std::complex<double>,
        &py_long_check, &py_complex_check,
        &py_long_to_cpp_long, &py_complex_to_cpp_complex
    >(op, map);
}

//------ Converts a std::std::unordered_map<long, std::vector<char>> ------
//-------- to a Python dict of { long : std::vector<char>, ...}    --------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, std::vector<char>>(const std::unordered_map<long, std::vector<char>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        long, std::vector<char>,
        &cpp_long_to_py_long, &cpp_vector_char_to_py_bytes
    >(map);
}

//------- Converts a Python dict of {long : std::vector<char>, ...} -------
//--------- to a std::std::unordered_map<long, std::vector<char>> ---------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, std::vector<char>>(PyObject* op, std::unordered_map<long, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        long, std::vector<char>,
        &py_long_check, &py_bytes_check,
        &py_long_to_cpp_long, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//--------- Converts a std::std::unordered_map<long, std::string> ---------
//----------- to a Python dict of { long : std::string, ...}    -----------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, std::string>(const std::unordered_map<long, std::string> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        long, std::string,
        &cpp_long_to_py_long, &cpp_string_to_py_unicode
    >(map);
}

//---------- Converts a Python dict of {long : std::string, ...} ----------
//------------ to a std::std::unordered_map<long, std::string> ------------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, std::string>(PyObject* op, std::unordered_map<long, std::string> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        long, std::string,
        &py_long_check, &py_unicode_check,
        &py_long_to_cpp_long, &py_unicode_to_cpp_string
    >(op, map);
}

//------------ Converts a std::std::unordered_map<double, bool> -----------
//-------------- to a Python dict of { double : bool, ...}    -------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, bool>(const std::unordered_map<double, bool> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        double, bool,
        &cpp_double_to_py_float, &cpp_bool_to_py_bool
    >(map);
}

//------------- Converts a Python dict of {double : bool, ...} ------------
//--------------- to a std::std::unordered_map<double, bool> --------------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, bool>(PyObject* op, std::unordered_map<double, bool> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        double, bool,
        &py_float_check, &py_bool_check,
        &py_float_to_cpp_double, &py_bool_to_cpp_bool
    >(op, map);
}

//------------ Converts a std::std::unordered_map<double, long> -----------
//-------------- to a Python dict of { double : long, ...}    -------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, long>(const std::unordered_map<double, long> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        double, long,
        &cpp_double_to_py_float, &cpp_long_to_py_long
    >(map);
}

//------------- Converts a Python dict of {double : long, ...} ------------
//--------------- to a std::std::unordered_map<double, long> --------------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, long>(PyObject* op, std::unordered_map<double, long> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        double, long,
        &py_float_check, &py_long_check,
        &py_float_to_cpp_double, &py_long_to_cpp_long
    >(op, map);
}

//----------- Converts a std::std::unordered_map<double, double> ----------
//------------- to a Python dict of { double : double, ...}    ------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, double>(const std::unordered_map<double, double> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        double, double,
        &cpp_double_to_py_float, &cpp_double_to_py_float
    >(map);
}

//------------ Converts a Python dict of {double : double, ...} -----------
//-------------- to a std::std::unordered_map<double, double> -------------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, double>(PyObject* op, std::unordered_map<double, double> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        double, double,
        &py_float_check, &py_float_check,
        &py_float_to_cpp_double, &py_float_to_cpp_double
    >(op, map);
}

//---- Converts a std::std::unordered_map<double, std::complex<double>> ---
//------ to a Python dict of { double : std::complex<double>, ...}    -----
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, std::complex<double>>(const std::unordered_map<double, std::complex<double>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        double, std::complex<double>,
        &cpp_double_to_py_float, &cpp_complex_to_py_complex
    >(map);
}

//----- Converts a Python dict of {double : std::complex<double>, ...} ----
//------- to a std::std::unordered_map<double, std::complex<double>> ------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, std::complex<double>>(PyObject* op, std::unordered_map<double, std::complex<double>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        double, std::complex<double>,
        &py_float_check, &py_complex_check,
        &py_float_to_cpp_double, &py_complex_to_cpp_complex
    >(op, map);
}

//----- Converts a std::std::unordered_map<double, std::vector<char>> -----
//------- to a Python dict of { double : std::vector<char>, ...}    -------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, std::vector<char>>(const std::unordered_map<double, std::vector<char>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        double, std::vector<char>,
        &cpp_double_to_py_float, &cpp_vector_char_to_py_bytes
    >(map);
}

//------ Converts a Python dict of {double : std::vector<char>, ...} ------
//-------- to a std::std::unordered_map<double, std::vector<char>> --------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, std::vector<char>>(PyObject* op, std::unordered_map<double, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        double, std::vector<char>,
        &py_float_check, &py_bytes_check,
        &py_float_to_cpp_double, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//-------- Converts a std::std::unordered_map<double, std::string> --------
//---------- to a Python dict of { double : std::string, ...}    ----------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, std::string>(const std::unordered_map<double, std::string> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        double, std::string,
        &cpp_double_to_py_float, &cpp_string_to_py_unicode
    >(map);
}

//--------- Converts a Python dict of {double : std::string, ...} ---------
//----------- to a std::std::unordered_map<double, std::string> -----------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, std::string>(PyObject* op, std::unordered_map<double, std::string> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        double, std::string,
        &py_float_check, &py_unicode_check,
        &py_float_to_cpp_double, &py_unicode_to_cpp_string
    >(op, map);
}

//----- Converts a std::std::unordered_map<std::complex<double>, bool> ----
//------- to a Python dict of { std::complex<double> : bool, ...}    ------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, bool>(const std::unordered_map<std::complex<double>, bool> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::complex<double>, bool,
        &cpp_complex_to_py_complex, &cpp_bool_to_py_bool
    >(map);
}

//------ Converts a Python dict of {std::complex<double> : bool, ...} -----
//-------- to a std::std::unordered_map<std::complex<double>, bool> -------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, bool>(PyObject* op, std::unordered_map<std::complex<double>, bool> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::complex<double>, bool,
        &py_complex_check, &py_bool_check,
        &py_complex_to_cpp_complex, &py_bool_to_cpp_bool
    >(op, map);
}

//----- Converts a std::std::unordered_map<std::complex<double>, long> ----
//------- to a Python dict of { std::complex<double> : long, ...}    ------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, long>(const std::unordered_map<std::complex<double>, long> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::complex<double>, long,
        &cpp_complex_to_py_complex, &cpp_long_to_py_long
    >(map);
}

//------ Converts a Python dict of {std::complex<double> : long, ...} -----
//-------- to a std::std::unordered_map<std::complex<double>, long> -------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, long>(PyObject* op, std::unordered_map<std::complex<double>, long> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::complex<double>, long,
        &py_complex_check, &py_long_check,
        &py_complex_to_cpp_complex, &py_long_to_cpp_long
    >(op, map);
}

//---- Converts a std::std::unordered_map<std::complex<double>, double> ---
//------ to a Python dict of { std::complex<double> : double, ...}    -----
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, double>(const std::unordered_map<std::complex<double>, double> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::complex<double>, double,
        &cpp_complex_to_py_complex, &cpp_double_to_py_float
    >(map);
}

//----- Converts a Python dict of {std::complex<double> : double, ...} ----
//------- to a std::std::unordered_map<std::complex<double>, double> ------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, double>(PyObject* op, std::unordered_map<std::complex<double>, double> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::complex<double>, double,
        &py_complex_check, &py_float_check,
        &py_complex_to_cpp_complex, &py_float_to_cpp_double
    >(op, map);
}

// Converts a std::std::unordered_map<std::complex<double>, std::complex<double>> 
// to a Python dict of { std::complex<double> : std::complex<double>, ...}    
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, std::complex<double>>(const std::unordered_map<std::complex<double>, std::complex<double>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::complex<double>, std::complex<double>,
        &cpp_complex_to_py_complex, &cpp_complex_to_py_complex
    >(map);
}

// Converts a Python dict of {std::complex<double> : std::complex<double>, ...} 
// to a std::std::unordered_map<std::complex<double>, std::complex<double>> 
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, std::complex<double>>(PyObject* op, std::unordered_map<std::complex<double>, std::complex<double>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::complex<double>, std::complex<double>,
        &py_complex_check, &py_complex_check,
        &py_complex_to_cpp_complex, &py_complex_to_cpp_complex
    >(op, map);
}

// Converts a std::std::unordered_map<std::complex<double>, std::vector<char>> 
// to a Python dict of { std::complex<double> : std::vector<char>, ...}    
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, std::vector<char>>(const std::unordered_map<std::complex<double>, std::vector<char>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::complex<double>, std::vector<char>,
        &cpp_complex_to_py_complex, &cpp_vector_char_to_py_bytes
    >(map);
}

// Converts a Python dict of {std::complex<double> : std::vector<char>, ...} 
//- to a std::std::unordered_map<std::complex<double>, std::vector<char>> -
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, std::vector<char>>(PyObject* op, std::unordered_map<std::complex<double>, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::complex<double>, std::vector<char>,
        &py_complex_check, &py_bytes_check,
        &py_complex_to_cpp_complex, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//- Converts a std::std::unordered_map<std::complex<double>, std::string> -
//--- to a Python dict of { std::complex<double> : std::string, ...}    ---
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, std::string>(const std::unordered_map<std::complex<double>, std::string> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::complex<double>, std::string,
        &cpp_complex_to_py_complex, &cpp_string_to_py_unicode
    >(map);
}

//-- Converts a Python dict of {std::complex<double> : std::string, ...} --
//---- to a std::std::unordered_map<std::complex<double>, std::string> ----
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, std::string>(PyObject* op, std::unordered_map<std::complex<double>, std::string> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::complex<double>, std::string,
        &py_complex_check, &py_unicode_check,
        &py_complex_to_cpp_complex, &py_unicode_to_cpp_string
    >(op, map);
}

//------ Converts a std::std::unordered_map<std::vector<char>, bool> ------
//-------- to a Python dict of { std::vector<char> : bool, ...}    --------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, bool>(const std::unordered_map<std::vector<char>, bool> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::vector<char>, bool,
        &cpp_vector_char_to_py_bytes, &cpp_bool_to_py_bool
    >(map);
}

//------- Converts a Python dict of {std::vector<char> : bool, ...} -------
//--------- to a std::std::unordered_map<std::vector<char>, bool> ---------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, bool>(PyObject* op, std::unordered_map<std::vector<char>, bool> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::vector<char>, bool,
        &py_bytes_check, &py_bool_check,
        &py_bytes_to_cpp_vector_char, &py_bool_to_cpp_bool
    >(op, map);
}

//------ Converts a std::std::unordered_map<std::vector<char>, long> ------
//-------- to a Python dict of { std::vector<char> : long, ...}    --------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, long>(const std::unordered_map<std::vector<char>, long> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::vector<char>, long,
        &cpp_vector_char_to_py_bytes, &cpp_long_to_py_long
    >(map);
}

//------- Converts a Python dict of {std::vector<char> : long, ...} -------
//--------- to a std::std::unordered_map<std::vector<char>, long> ---------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, long>(PyObject* op, std::unordered_map<std::vector<char>, long> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::vector<char>, long,
        &py_bytes_check, &py_long_check,
        &py_bytes_to_cpp_vector_char, &py_long_to_cpp_long
    >(op, map);
}

//----- Converts a std::std::unordered_map<std::vector<char>, double> -----
//------- to a Python dict of { std::vector<char> : double, ...}    -------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, double>(const std::unordered_map<std::vector<char>, double> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::vector<char>, double,
        &cpp_vector_char_to_py_bytes, &cpp_double_to_py_float
    >(map);
}

//------ Converts a Python dict of {std::vector<char> : double, ...} ------
//-------- to a std::std::unordered_map<std::vector<char>, double> --------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, double>(PyObject* op, std::unordered_map<std::vector<char>, double> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::vector<char>, double,
        &py_bytes_check, &py_float_check,
        &py_bytes_to_cpp_vector_char, &py_float_to_cpp_double
    >(op, map);
}

// Converts a std::std::unordered_map<std::vector<char>, std::complex<double>> 
// to a Python dict of { std::vector<char> : std::complex<double>, ...}    
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, std::complex<double>>(const std::unordered_map<std::vector<char>, std::complex<double>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::vector<char>, std::complex<double>,
        &cpp_vector_char_to_py_bytes, &cpp_complex_to_py_complex
    >(map);
}

// Converts a Python dict of {std::vector<char> : std::complex<double>, ...} 
//- to a std::std::unordered_map<std::vector<char>, std::complex<double>> -
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, std::complex<double>>(PyObject* op, std::unordered_map<std::vector<char>, std::complex<double>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::vector<char>, std::complex<double>,
        &py_bytes_check, &py_complex_check,
        &py_bytes_to_cpp_vector_char, &py_complex_to_cpp_complex
    >(op, map);
}

// Converts a std::std::unordered_map<std::vector<char>, std::vector<char>> 
//-- to a Python dict of { std::vector<char> : std::vector<char>, ...}    -
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, std::vector<char>>(const std::unordered_map<std::vector<char>, std::vector<char>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::vector<char>, std::vector<char>,
        &cpp_vector_char_to_py_bytes, &cpp_vector_char_to_py_bytes
    >(map);
}

//- Converts a Python dict of {std::vector<char> : std::vector<char>, ...} 
//--- to a std::std::unordered_map<std::vector<char>, std::vector<char>> --
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, std::vector<char>>(PyObject* op, std::unordered_map<std::vector<char>, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::vector<char>, std::vector<char>,
        &py_bytes_check, &py_bytes_check,
        &py_bytes_to_cpp_vector_char, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//--- Converts a std::std::unordered_map<std::vector<char>, std::string> --
//----- to a Python dict of { std::vector<char> : std::string, ...}    ----
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, std::string>(const std::unordered_map<std::vector<char>, std::string> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::vector<char>, std::string,
        &cpp_vector_char_to_py_bytes, &cpp_string_to_py_unicode
    >(map);
}

//---- Converts a Python dict of {std::vector<char> : std::string, ...} ---
//------ to a std::std::unordered_map<std::vector<char>, std::string> -----
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, std::string>(PyObject* op, std::unordered_map<std::vector<char>, std::string> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::vector<char>, std::string,
        &py_bytes_check, &py_unicode_check,
        &py_bytes_to_cpp_vector_char, &py_unicode_to_cpp_string
    >(op, map);
}

//--------- Converts a std::std::unordered_map<std::string, bool> ---------
//----------- to a Python dict of { std::string : bool, ...}    -----------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, bool>(const std::unordered_map<std::string, bool> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::string, bool,
        &cpp_string_to_py_unicode, &cpp_bool_to_py_bool
    >(map);
}

//---------- Converts a Python dict of {std::string : bool, ...} ----------
//------------ to a std::std::unordered_map<std::string, bool> ------------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, bool>(PyObject* op, std::unordered_map<std::string, bool> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::string, bool,
        &py_unicode_check, &py_bool_check,
        &py_unicode_to_cpp_string, &py_bool_to_cpp_bool
    >(op, map);
}

//--------- Converts a std::std::unordered_map<std::string, long> ---------
//----------- to a Python dict of { std::string : long, ...}    -----------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, long>(const std::unordered_map<std::string, long> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::string, long,
        &cpp_string_to_py_unicode, &cpp_long_to_py_long
    >(map);
}

//---------- Converts a Python dict of {std::string : long, ...} ----------
//------------ to a std::std::unordered_map<std::string, long> ------------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, long>(PyObject* op, std::unordered_map<std::string, long> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::string, long,
        &py_unicode_check, &py_long_check,
        &py_unicode_to_cpp_string, &py_long_to_cpp_long
    >(op, map);
}

//-------- Converts a std::std::unordered_map<std::string, double> --------
//---------- to a Python dict of { std::string : double, ...}    ----------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, double>(const std::unordered_map<std::string, double> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::string, double,
        &cpp_string_to_py_unicode, &cpp_double_to_py_float
    >(map);
}

//--------- Converts a Python dict of {std::string : double, ...} ---------
//----------- to a std::std::unordered_map<std::string, double> -----------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, double>(PyObject* op, std::unordered_map<std::string, double> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::string, double,
        &py_unicode_check, &py_float_check,
        &py_unicode_to_cpp_string, &py_float_to_cpp_double
    >(op, map);
}

//- Converts a std::std::unordered_map<std::string, std::complex<double>> -
//--- to a Python dict of { std::string : std::complex<double>, ...}    ---
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, std::complex<double>>(const std::unordered_map<std::string, std::complex<double>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::string, std::complex<double>,
        &cpp_string_to_py_unicode, &cpp_complex_to_py_complex
    >(map);
}

//-- Converts a Python dict of {std::string : std::complex<double>, ...} --
//---- to a std::std::unordered_map<std::string, std::complex<double>> ----
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, std::complex<double>>(PyObject* op, std::unordered_map<std::string, std::complex<double>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::string, std::complex<double>,
        &py_unicode_check, &py_complex_check,
        &py_unicode_to_cpp_string, &py_complex_to_cpp_complex
    >(op, map);
}

//--- Converts a std::std::unordered_map<std::string, std::vector<char>> --
//----- to a Python dict of { std::string : std::vector<char>, ...}    ----
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, std::vector<char>>(const std::unordered_map<std::string, std::vector<char>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::string, std::vector<char>,
        &cpp_string_to_py_unicode, &cpp_vector_char_to_py_bytes
    >(map);
}

//---- Converts a Python dict of {std::string : std::vector<char>, ...} ---
//------ to a std::std::unordered_map<std::string, std::vector<char>> -----
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, std::vector<char>>(PyObject* op, std::unordered_map<std::string, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::string, std::vector<char>,
        &py_unicode_check, &py_bytes_check,
        &py_unicode_to_cpp_string, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//------ Converts a std::std::unordered_map<std::string, std::string> -----
//-------- to a Python dict of { std::string : std::string, ...}    -------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, std::string>(const std::unordered_map<std::string, std::string> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::unordered_map,
        std::string, std::string,
        &cpp_string_to_py_unicode, &cpp_string_to_py_unicode
    >(map);
}

//------- Converts a Python dict of {std::string : std::string, ...} ------
//--------- to a std::std::unordered_map<std::string, std::string> --------
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, std::string>(PyObject* op, std::unordered_map<std::string, std::string> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::unordered_map,
        std::string, std::string,
        &py_unicode_check, &py_unicode_check,
        &py_unicode_to_cpp_string, &py_unicode_to_cpp_string
    >(op, map);
}

//************** END: std::std::unordered_map <-> Python dict *************

//********************* std::std::map <-> Python dict *********************
//------------------ Converts a std::std::map<bool, bool> -----------------
//--------------- to a Python dict of { bool : bool, ...}    --------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, bool>(const std::map<bool, bool> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        bool, bool,
        &cpp_bool_to_py_bool, &cpp_bool_to_py_bool
    >(map);
}

//-------------- Converts a Python dict of {bool : bool, ...} -------------
//--------------------- to a std::std::map<bool, bool> --------------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, bool>(PyObject* op, std::map<bool, bool> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        bool, bool,
        &py_bool_check, &py_bool_check,
        &py_bool_to_cpp_bool, &py_bool_to_cpp_bool
    >(op, map);
}

//------------------ Converts a std::std::map<bool, long> -----------------
//--------------- to a Python dict of { bool : long, ...}    --------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, long>(const std::map<bool, long> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        bool, long,
        &cpp_bool_to_py_bool, &cpp_long_to_py_long
    >(map);
}

//-------------- Converts a Python dict of {bool : long, ...} -------------
//--------------------- to a std::std::map<bool, long> --------------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, long>(PyObject* op, std::map<bool, long> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        bool, long,
        &py_bool_check, &py_long_check,
        &py_bool_to_cpp_bool, &py_long_to_cpp_long
    >(op, map);
}

//----------------- Converts a std::std::map<bool, double> ----------------
//-------------- to a Python dict of { bool : double, ...}    -------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, double>(const std::map<bool, double> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        bool, double,
        &cpp_bool_to_py_bool, &cpp_double_to_py_float
    >(map);
}

//------------- Converts a Python dict of {bool : double, ...} ------------
//-------------------- to a std::std::map<bool, double> -------------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, double>(PyObject* op, std::map<bool, double> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        bool, double,
        &py_bool_check, &py_float_check,
        &py_bool_to_cpp_bool, &py_float_to_cpp_double
    >(op, map);
}

//---------- Converts a std::std::map<bool, std::complex<double>> ---------
//------- to a Python dict of { bool : std::complex<double>, ...}    ------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, std::complex<double>>(const std::map<bool, std::complex<double>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        bool, std::complex<double>,
        &cpp_bool_to_py_bool, &cpp_complex_to_py_complex
    >(map);
}

//------ Converts a Python dict of {bool : std::complex<double>, ...} -----
//------------- to a std::std::map<bool, std::complex<double>> ------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, std::complex<double>>(PyObject* op, std::map<bool, std::complex<double>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        bool, std::complex<double>,
        &py_bool_check, &py_complex_check,
        &py_bool_to_cpp_bool, &py_complex_to_cpp_complex
    >(op, map);
}

//----------- Converts a std::std::map<bool, std::vector<char>> -----------
//-------- to a Python dict of { bool : std::vector<char>, ...}    --------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, std::vector<char>>(const std::map<bool, std::vector<char>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        bool, std::vector<char>,
        &cpp_bool_to_py_bool, &cpp_vector_char_to_py_bytes
    >(map);
}

//------- Converts a Python dict of {bool : std::vector<char>, ...} -------
//-------------- to a std::std::map<bool, std::vector<char>> --------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, std::vector<char>>(PyObject* op, std::map<bool, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        bool, std::vector<char>,
        &py_bool_check, &py_bytes_check,
        &py_bool_to_cpp_bool, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//-------------- Converts a std::std::map<bool, std::string> --------------
//----------- to a Python dict of { bool : std::string, ...}    -----------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, std::string>(const std::map<bool, std::string> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        bool, std::string,
        &cpp_bool_to_py_bool, &cpp_string_to_py_unicode
    >(map);
}

//---------- Converts a Python dict of {bool : std::string, ...} ----------
//----------------- to a std::std::map<bool, std::string> -----------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, std::string>(PyObject* op, std::map<bool, std::string> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        bool, std::string,
        &py_bool_check, &py_unicode_check,
        &py_bool_to_cpp_bool, &py_unicode_to_cpp_string
    >(op, map);
}

//------------------ Converts a std::std::map<long, bool> -----------------
//--------------- to a Python dict of { long : bool, ...}    --------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, bool>(const std::map<long, bool> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        long, bool,
        &cpp_long_to_py_long, &cpp_bool_to_py_bool
    >(map);
}

//-------------- Converts a Python dict of {long : bool, ...} -------------
//--------------------- to a std::std::map<long, bool> --------------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, bool>(PyObject* op, std::map<long, bool> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        long, bool,
        &py_long_check, &py_bool_check,
        &py_long_to_cpp_long, &py_bool_to_cpp_bool
    >(op, map);
}

//------------------ Converts a std::std::map<long, long> -----------------
//--------------- to a Python dict of { long : long, ...}    --------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, long>(const std::map<long, long> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        long, long,
        &cpp_long_to_py_long, &cpp_long_to_py_long
    >(map);
}

//-------------- Converts a Python dict of {long : long, ...} -------------
//--------------------- to a std::std::map<long, long> --------------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, long>(PyObject* op, std::map<long, long> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        long, long,
        &py_long_check, &py_long_check,
        &py_long_to_cpp_long, &py_long_to_cpp_long
    >(op, map);
}

//----------------- Converts a std::std::map<long, double> ----------------
//-------------- to a Python dict of { long : double, ...}    -------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, double>(const std::map<long, double> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        long, double,
        &cpp_long_to_py_long, &cpp_double_to_py_float
    >(map);
}

//------------- Converts a Python dict of {long : double, ...} ------------
//-------------------- to a std::std::map<long, double> -------------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, double>(PyObject* op, std::map<long, double> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        long, double,
        &py_long_check, &py_float_check,
        &py_long_to_cpp_long, &py_float_to_cpp_double
    >(op, map);
}

//---------- Converts a std::std::map<long, std::complex<double>> ---------
//------- to a Python dict of { long : std::complex<double>, ...}    ------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, std::complex<double>>(const std::map<long, std::complex<double>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        long, std::complex<double>,
        &cpp_long_to_py_long, &cpp_complex_to_py_complex
    >(map);
}

//------ Converts a Python dict of {long : std::complex<double>, ...} -----
//------------- to a std::std::map<long, std::complex<double>> ------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, std::complex<double>>(PyObject* op, std::map<long, std::complex<double>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        long, std::complex<double>,
        &py_long_check, &py_complex_check,
        &py_long_to_cpp_long, &py_complex_to_cpp_complex
    >(op, map);
}

//----------- Converts a std::std::map<long, std::vector<char>> -----------
//-------- to a Python dict of { long : std::vector<char>, ...}    --------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, std::vector<char>>(const std::map<long, std::vector<char>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        long, std::vector<char>,
        &cpp_long_to_py_long, &cpp_vector_char_to_py_bytes
    >(map);
}

//------- Converts a Python dict of {long : std::vector<char>, ...} -------
//-------------- to a std::std::map<long, std::vector<char>> --------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, std::vector<char>>(PyObject* op, std::map<long, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        long, std::vector<char>,
        &py_long_check, &py_bytes_check,
        &py_long_to_cpp_long, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//-------------- Converts a std::std::map<long, std::string> --------------
//----------- to a Python dict of { long : std::string, ...}    -----------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, std::string>(const std::map<long, std::string> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        long, std::string,
        &cpp_long_to_py_long, &cpp_string_to_py_unicode
    >(map);
}

//---------- Converts a Python dict of {long : std::string, ...} ----------
//----------------- to a std::std::map<long, std::string> -----------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, std::string>(PyObject* op, std::map<long, std::string> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        long, std::string,
        &py_long_check, &py_unicode_check,
        &py_long_to_cpp_long, &py_unicode_to_cpp_string
    >(op, map);
}

//----------------- Converts a std::std::map<double, bool> ----------------
//-------------- to a Python dict of { double : bool, ...}    -------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, bool>(const std::map<double, bool> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        double, bool,
        &cpp_double_to_py_float, &cpp_bool_to_py_bool
    >(map);
}

//------------- Converts a Python dict of {double : bool, ...} ------------
//-------------------- to a std::std::map<double, bool> -------------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, bool>(PyObject* op, std::map<double, bool> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        double, bool,
        &py_float_check, &py_bool_check,
        &py_float_to_cpp_double, &py_bool_to_cpp_bool
    >(op, map);
}

//----------------- Converts a std::std::map<double, long> ----------------
//-------------- to a Python dict of { double : long, ...}    -------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, long>(const std::map<double, long> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        double, long,
        &cpp_double_to_py_float, &cpp_long_to_py_long
    >(map);
}

//------------- Converts a Python dict of {double : long, ...} ------------
//-------------------- to a std::std::map<double, long> -------------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, long>(PyObject* op, std::map<double, long> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        double, long,
        &py_float_check, &py_long_check,
        &py_float_to_cpp_double, &py_long_to_cpp_long
    >(op, map);
}

//---------------- Converts a std::std::map<double, double> ---------------
//------------- to a Python dict of { double : double, ...}    ------------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, double>(const std::map<double, double> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        double, double,
        &cpp_double_to_py_float, &cpp_double_to_py_float
    >(map);
}

//------------ Converts a Python dict of {double : double, ...} -----------
//------------------- to a std::std::map<double, double> ------------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, double>(PyObject* op, std::map<double, double> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        double, double,
        &py_float_check, &py_float_check,
        &py_float_to_cpp_double, &py_float_to_cpp_double
    >(op, map);
}

//--------- Converts a std::std::map<double, std::complex<double>> --------
//------ to a Python dict of { double : std::complex<double>, ...}    -----
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, std::complex<double>>(const std::map<double, std::complex<double>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        double, std::complex<double>,
        &cpp_double_to_py_float, &cpp_complex_to_py_complex
    >(map);
}

//----- Converts a Python dict of {double : std::complex<double>, ...} ----
//------------ to a std::std::map<double, std::complex<double>> -----------
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, std::complex<double>>(PyObject* op, std::map<double, std::complex<double>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        double, std::complex<double>,
        &py_float_check, &py_complex_check,
        &py_float_to_cpp_double, &py_complex_to_cpp_complex
    >(op, map);
}

//---------- Converts a std::std::map<double, std::vector<char>> ----------
//------- to a Python dict of { double : std::vector<char>, ...}    -------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, std::vector<char>>(const std::map<double, std::vector<char>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        double, std::vector<char>,
        &cpp_double_to_py_float, &cpp_vector_char_to_py_bytes
    >(map);
}

//------ Converts a Python dict of {double : std::vector<char>, ...} ------
//------------- to a std::std::map<double, std::vector<char>> -------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, std::vector<char>>(PyObject* op, std::map<double, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        double, std::vector<char>,
        &py_float_check, &py_bytes_check,
        &py_float_to_cpp_double, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//------------- Converts a std::std::map<double, std::string> -------------
//---------- to a Python dict of { double : std::string, ...}    ----------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, std::string>(const std::map<double, std::string> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        double, std::string,
        &cpp_double_to_py_float, &cpp_string_to_py_unicode
    >(map);
}

//--------- Converts a Python dict of {double : std::string, ...} ---------
//---------------- to a std::std::map<double, std::string> ----------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, std::string>(PyObject* op, std::map<double, std::string> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        double, std::string,
        &py_float_check, &py_unicode_check,
        &py_float_to_cpp_double, &py_unicode_to_cpp_string
    >(op, map);
}

//---------- Converts a std::std::map<std::complex<double>, bool> ---------
//------- to a Python dict of { std::complex<double> : bool, ...}    ------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, bool>(const std::map<std::complex<double>, bool> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::complex<double>, bool,
        &cpp_complex_to_py_complex, &cpp_bool_to_py_bool
    >(map);
}

//------ Converts a Python dict of {std::complex<double> : bool, ...} -----
//------------- to a std::std::map<std::complex<double>, bool> ------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, bool>(PyObject* op, std::map<std::complex<double>, bool> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::complex<double>, bool,
        &py_complex_check, &py_bool_check,
        &py_complex_to_cpp_complex, &py_bool_to_cpp_bool
    >(op, map);
}

//---------- Converts a std::std::map<std::complex<double>, long> ---------
//------- to a Python dict of { std::complex<double> : long, ...}    ------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, long>(const std::map<std::complex<double>, long> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::complex<double>, long,
        &cpp_complex_to_py_complex, &cpp_long_to_py_long
    >(map);
}

//------ Converts a Python dict of {std::complex<double> : long, ...} -----
//------------- to a std::std::map<std::complex<double>, long> ------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, long>(PyObject* op, std::map<std::complex<double>, long> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::complex<double>, long,
        &py_complex_check, &py_long_check,
        &py_complex_to_cpp_complex, &py_long_to_cpp_long
    >(op, map);
}

//--------- Converts a std::std::map<std::complex<double>, double> --------
//------ to a Python dict of { std::complex<double> : double, ...}    -----
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, double>(const std::map<std::complex<double>, double> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::complex<double>, double,
        &cpp_complex_to_py_complex, &cpp_double_to_py_float
    >(map);
}

//----- Converts a Python dict of {std::complex<double> : double, ...} ----
//------------ to a std::std::map<std::complex<double>, double> -----------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, double>(PyObject* op, std::map<std::complex<double>, double> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::complex<double>, double,
        &py_complex_check, &py_float_check,
        &py_complex_to_cpp_complex, &py_float_to_cpp_double
    >(op, map);
}

//-- Converts a std::std::map<std::complex<double>, std::complex<double>> -
// to a Python dict of { std::complex<double> : std::complex<double>, ...}    
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, std::complex<double>>(const std::map<std::complex<double>, std::complex<double>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::complex<double>, std::complex<double>,
        &cpp_complex_to_py_complex, &cpp_complex_to_py_complex
    >(map);
}

// Converts a Python dict of {std::complex<double> : std::complex<double>, ...} 
//----- to a std::std::map<std::complex<double>, std::complex<double>> ----
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, std::complex<double>>(PyObject* op, std::map<std::complex<double>, std::complex<double>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::complex<double>, std::complex<double>,
        &py_complex_check, &py_complex_check,
        &py_complex_to_cpp_complex, &py_complex_to_cpp_complex
    >(op, map);
}

//--- Converts a std::std::map<std::complex<double>, std::vector<char>> ---
// to a Python dict of { std::complex<double> : std::vector<char>, ...}    
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, std::vector<char>>(const std::map<std::complex<double>, std::vector<char>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::complex<double>, std::vector<char>,
        &cpp_complex_to_py_complex, &cpp_vector_char_to_py_bytes
    >(map);
}

// Converts a Python dict of {std::complex<double> : std::vector<char>, ...} 
//------ to a std::std::map<std::complex<double>, std::vector<char>> ------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, std::vector<char>>(PyObject* op, std::map<std::complex<double>, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::complex<double>, std::vector<char>,
        &py_complex_check, &py_bytes_check,
        &py_complex_to_cpp_complex, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//------ Converts a std::std::map<std::complex<double>, std::string> ------
//--- to a Python dict of { std::complex<double> : std::string, ...}    ---
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, std::string>(const std::map<std::complex<double>, std::string> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::complex<double>, std::string,
        &cpp_complex_to_py_complex, &cpp_string_to_py_unicode
    >(map);
}

//-- Converts a Python dict of {std::complex<double> : std::string, ...} --
//--------- to a std::std::map<std::complex<double>, std::string> ---------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, std::string>(PyObject* op, std::map<std::complex<double>, std::string> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::complex<double>, std::string,
        &py_complex_check, &py_unicode_check,
        &py_complex_to_cpp_complex, &py_unicode_to_cpp_string
    >(op, map);
}

//----------- Converts a std::std::map<std::vector<char>, bool> -----------
//-------- to a Python dict of { std::vector<char> : bool, ...}    --------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, bool>(const std::map<std::vector<char>, bool> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::vector<char>, bool,
        &cpp_vector_char_to_py_bytes, &cpp_bool_to_py_bool
    >(map);
}

//------- Converts a Python dict of {std::vector<char> : bool, ...} -------
//-------------- to a std::std::map<std::vector<char>, bool> --------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, bool>(PyObject* op, std::map<std::vector<char>, bool> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::vector<char>, bool,
        &py_bytes_check, &py_bool_check,
        &py_bytes_to_cpp_vector_char, &py_bool_to_cpp_bool
    >(op, map);
}

//----------- Converts a std::std::map<std::vector<char>, long> -----------
//-------- to a Python dict of { std::vector<char> : long, ...}    --------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, long>(const std::map<std::vector<char>, long> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::vector<char>, long,
        &cpp_vector_char_to_py_bytes, &cpp_long_to_py_long
    >(map);
}

//------- Converts a Python dict of {std::vector<char> : long, ...} -------
//-------------- to a std::std::map<std::vector<char>, long> --------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, long>(PyObject* op, std::map<std::vector<char>, long> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::vector<char>, long,
        &py_bytes_check, &py_long_check,
        &py_bytes_to_cpp_vector_char, &py_long_to_cpp_long
    >(op, map);
}

//---------- Converts a std::std::map<std::vector<char>, double> ----------
//------- to a Python dict of { std::vector<char> : double, ...}    -------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, double>(const std::map<std::vector<char>, double> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::vector<char>, double,
        &cpp_vector_char_to_py_bytes, &cpp_double_to_py_float
    >(map);
}

//------ Converts a Python dict of {std::vector<char> : double, ...} ------
//------------- to a std::std::map<std::vector<char>, double> -------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, double>(PyObject* op, std::map<std::vector<char>, double> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::vector<char>, double,
        &py_bytes_check, &py_float_check,
        &py_bytes_to_cpp_vector_char, &py_float_to_cpp_double
    >(op, map);
}

//--- Converts a std::std::map<std::vector<char>, std::complex<double>> ---
// to a Python dict of { std::vector<char> : std::complex<double>, ...}    
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, std::complex<double>>(const std::map<std::vector<char>, std::complex<double>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::vector<char>, std::complex<double>,
        &cpp_vector_char_to_py_bytes, &cpp_complex_to_py_complex
    >(map);
}

// Converts a Python dict of {std::vector<char> : std::complex<double>, ...} 
//------ to a std::std::map<std::vector<char>, std::complex<double>> ------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, std::complex<double>>(PyObject* op, std::map<std::vector<char>, std::complex<double>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::vector<char>, std::complex<double>,
        &py_bytes_check, &py_complex_check,
        &py_bytes_to_cpp_vector_char, &py_complex_to_cpp_complex
    >(op, map);
}

//----- Converts a std::std::map<std::vector<char>, std::vector<char>> ----
//-- to a Python dict of { std::vector<char> : std::vector<char>, ...}    -
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, std::vector<char>>(const std::map<std::vector<char>, std::vector<char>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::vector<char>, std::vector<char>,
        &cpp_vector_char_to_py_bytes, &cpp_vector_char_to_py_bytes
    >(map);
}

//- Converts a Python dict of {std::vector<char> : std::vector<char>, ...} 
//-------- to a std::std::map<std::vector<char>, std::vector<char>> -------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, std::vector<char>>(PyObject* op, std::map<std::vector<char>, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::vector<char>, std::vector<char>,
        &py_bytes_check, &py_bytes_check,
        &py_bytes_to_cpp_vector_char, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//-------- Converts a std::std::map<std::vector<char>, std::string> -------
//----- to a Python dict of { std::vector<char> : std::string, ...}    ----
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, std::string>(const std::map<std::vector<char>, std::string> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::vector<char>, std::string,
        &cpp_vector_char_to_py_bytes, &cpp_string_to_py_unicode
    >(map);
}

//---- Converts a Python dict of {std::vector<char> : std::string, ...} ---
//----------- to a std::std::map<std::vector<char>, std::string> ----------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, std::string>(PyObject* op, std::map<std::vector<char>, std::string> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::vector<char>, std::string,
        &py_bytes_check, &py_unicode_check,
        &py_bytes_to_cpp_vector_char, &py_unicode_to_cpp_string
    >(op, map);
}

//-------------- Converts a std::std::map<std::string, bool> --------------
//----------- to a Python dict of { std::string : bool, ...}    -----------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, bool>(const std::map<std::string, bool> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::string, bool,
        &cpp_string_to_py_unicode, &cpp_bool_to_py_bool
    >(map);
}

//---------- Converts a Python dict of {std::string : bool, ...} ----------
//----------------- to a std::std::map<std::string, bool> -----------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, bool>(PyObject* op, std::map<std::string, bool> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::string, bool,
        &py_unicode_check, &py_bool_check,
        &py_unicode_to_cpp_string, &py_bool_to_cpp_bool
    >(op, map);
}

//-------------- Converts a std::std::map<std::string, long> --------------
//----------- to a Python dict of { std::string : long, ...}    -----------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, long>(const std::map<std::string, long> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::string, long,
        &cpp_string_to_py_unicode, &cpp_long_to_py_long
    >(map);
}

//---------- Converts a Python dict of {std::string : long, ...} ----------
//----------------- to a std::std::map<std::string, long> -----------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, long>(PyObject* op, std::map<std::string, long> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::string, long,
        &py_unicode_check, &py_long_check,
        &py_unicode_to_cpp_string, &py_long_to_cpp_long
    >(op, map);
}

//------------- Converts a std::std::map<std::string, double> -------------
//---------- to a Python dict of { std::string : double, ...}    ----------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, double>(const std::map<std::string, double> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::string, double,
        &cpp_string_to_py_unicode, &cpp_double_to_py_float
    >(map);
}

//--------- Converts a Python dict of {std::string : double, ...} ---------
//---------------- to a std::std::map<std::string, double> ----------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, double>(PyObject* op, std::map<std::string, double> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::string, double,
        &py_unicode_check, &py_float_check,
        &py_unicode_to_cpp_string, &py_float_to_cpp_double
    >(op, map);
}

//------ Converts a std::std::map<std::string, std::complex<double>> ------
//--- to a Python dict of { std::string : std::complex<double>, ...}    ---
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, std::complex<double>>(const std::map<std::string, std::complex<double>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::string, std::complex<double>,
        &cpp_string_to_py_unicode, &cpp_complex_to_py_complex
    >(map);
}

//-- Converts a Python dict of {std::string : std::complex<double>, ...} --
//--------- to a std::std::map<std::string, std::complex<double>> ---------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, std::complex<double>>(PyObject* op, std::map<std::string, std::complex<double>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::string, std::complex<double>,
        &py_unicode_check, &py_complex_check,
        &py_unicode_to_cpp_string, &py_complex_to_cpp_complex
    >(op, map);
}

//-------- Converts a std::std::map<std::string, std::vector<char>> -------
//----- to a Python dict of { std::string : std::vector<char>, ...}    ----
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, std::vector<char>>(const std::map<std::string, std::vector<char>> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::string, std::vector<char>,
        &cpp_string_to_py_unicode, &cpp_vector_char_to_py_bytes
    >(map);
}

//---- Converts a Python dict of {std::string : std::vector<char>, ...} ---
//----------- to a std::std::map<std::string, std::vector<char>> ----------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, std::vector<char>>(PyObject* op, std::map<std::string, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::string, std::vector<char>,
        &py_unicode_check, &py_bytes_check,
        &py_unicode_to_cpp_string, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//----------- Converts a std::std::map<std::string, std::string> ----------
//-------- to a Python dict of { std::string : std::string, ...}    -------
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, std::string>(const std::map<std::string, std::string> &map) {
    return generic_cpp_std_map_like_to_py_dict<
        std::map,
        std::string, std::string,
        &cpp_string_to_py_unicode, &cpp_string_to_py_unicode
    >(map);
}

//------- Converts a Python dict of {std::string : std::string, ...} ------
//-------------- to a std::std::map<std::string, std::string> -------------
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, std::string>(PyObject* op, std::map<std::string, std::string> &map) {
    return generic_py_dict_to_cpp_std_map_like<
        std::map,
        std::string, std::string,
        &py_unicode_check, &py_unicode_check,
        &py_unicode_to_cpp_string, &py_unicode_to_cpp_string
    >(op, map);
}

//******************* END: std::std::map <-> Python dict ******************

// Definitions written: 216
//#########################################################################
//#### END: Auto-generated code - do not edit. Seriously, do NOT edit. ####
//#########################################################################

} // namespace Python_Cpp_Containers

//========================== END: Definition file =========================

