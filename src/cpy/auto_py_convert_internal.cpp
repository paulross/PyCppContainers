//============================ Definition file ============================
//#########################################################################
//####### Auto-generated code - do not edit. Seriously, do NOT edit. ######
//#########################################################################
// Conversion from homogeneous data structures in Python and C++
// 
// Unary conversions
// tuple:
// tuple <-> std::vector<bool>
// tuple <-> std::vector<long>
// tuple <-> std::vector<double>
// tuple <-> std::vector<std::vector<char>>
// 
// list:
// list <-> std::vector<bool>
// list <-> std::vector<long>
// list <-> std::vector<double>
// list <-> std::vector<std::vector<char>>
// 
// set:
// set <-> std::unordered_set<bool>
// set <-> std::unordered_set<long>
// set <-> std::unordered_set<double>
// set <-> std::unordered_set<std::vector<char>>
// 
// frozenset:
// frozenset <-> std::unordered_set<bool>
// frozenset <-> std::unordered_set<long>
// frozenset <-> std::unordered_set<double>
// frozenset <-> std::unordered_set<std::vector<char>>
// 
// 
// Mapping conversions
// dict <-> std::unordered_map<bool, bool>
// dict <-> std::unordered_map<bool, long>
// dict <-> std::unordered_map<bool, double>
// dict <-> std::unordered_map<bool, std::vector<char>>
// dict <-> std::unordered_map<long, bool>
// dict <-> std::unordered_map<long, long>
// dict <-> std::unordered_map<long, double>
// dict <-> std::unordered_map<long, std::vector<char>>
// dict <-> std::unordered_map<double, bool>
// dict <-> std::unordered_map<double, long>
// dict <-> std::unordered_map<double, double>
// dict <-> std::unordered_map<double, std::vector<char>>
// dict <-> std::unordered_map<std::vector<char>, bool>
// dict <-> std::unordered_map<std::vector<char>, long>
// dict <-> std::unordered_map<std::vector<char>, double>
// dict <-> std::unordered_map<std::vector<char>, std::vector<char>>
// 
#include "python_convert.h"

namespace Python_Cpp_Containers {

//**************** Unary collections <-> Python collections ***************
//---------------------- std::vector -> Python tuple ----------------------
template <>
PyObject *
cpp_std_vector_to_py_tuple<bool>(const std::vector<bool> &container) {
    return generic_cpp_std_vector_to_py_tuple<bool, &cpp_bool_to_py_bool>(container);
}

template <>
PyObject *
cpp_std_vector_to_py_tuple<long>(const std::vector<long> &container) {
    return generic_cpp_std_vector_to_py_tuple<long, &cpp_long_to_py_long>(container);
}

template <>
PyObject *
cpp_std_vector_to_py_tuple<double>(const std::vector<double> &container) {
    return generic_cpp_std_vector_to_py_tuple<double, &cpp_double_to_py_float>(container);
}

template <>
PyObject *
cpp_std_vector_to_py_tuple<std::vector<char>>(const std::vector<std::vector<char>> &container) {
    return generic_cpp_std_vector_to_py_tuple<std::vector<char>, &cpp_vector_char_to_py_bytes>(container);
}

//-------------------- END: std::vector -> Python tuple -------------------

//---------------------- Python tuple -> std::vector ----------------------
template <>
int
py_tuple_to_cpp_std_vector<bool>(PyObject *op, std::vector<bool> &container) {
    return generic_py_tuple_to_cpp_std_vector<bool, &py_bool_check, &py_bool_to_cpp_bool>(op, container);
}

template <>
int
py_tuple_to_cpp_std_vector<long>(PyObject *op, std::vector<long> &container) {
    return generic_py_tuple_to_cpp_std_vector<long, &py_long_check, &py_long_to_cpp_long>(op, container);
}

template <>
int
py_tuple_to_cpp_std_vector<double>(PyObject *op, std::vector<double> &container) {
    return generic_py_tuple_to_cpp_std_vector<double, &py_float_check, &py_float_to_cpp_double>(op, container);
}

template <>
int
py_tuple_to_cpp_std_vector<std::vector<char>>(PyObject *op, std::vector<std::vector<char>> &container) {
    return generic_py_tuple_to_cpp_std_vector<std::vector<char>, &py_bytes_check, &py_bytes_to_cpp_vector_char>(op, container);
}

//-------------------- END: Python tuple -> std::vector -------------------

//----------------------- std::vector -> Python list ----------------------
template <>
PyObject *
cpp_std_vector_to_py_list<bool>(const std::vector<bool> &container) {
    return generic_cpp_std_vector_to_py_list<bool, &cpp_bool_to_py_bool>(container);
}

template <>
PyObject *
cpp_std_vector_to_py_list<long>(const std::vector<long> &container) {
    return generic_cpp_std_vector_to_py_list<long, &cpp_long_to_py_long>(container);
}

template <>
PyObject *
cpp_std_vector_to_py_list<double>(const std::vector<double> &container) {
    return generic_cpp_std_vector_to_py_list<double, &cpp_double_to_py_float>(container);
}

template <>
PyObject *
cpp_std_vector_to_py_list<std::vector<char>>(const std::vector<std::vector<char>> &container) {
    return generic_cpp_std_vector_to_py_list<std::vector<char>, &cpp_vector_char_to_py_bytes>(container);
}

//-------------------- END: std::vector -> Python list --------------------

//----------------------- Python list -> std::vector ----------------------
template <>
int
py_list_to_cpp_std_vector<bool>(PyObject *op, std::vector<bool> &container) {
    return generic_py_list_to_cpp_std_vector<bool, &py_bool_check, &py_bool_to_cpp_bool>(op, container);
}

template <>
int
py_list_to_cpp_std_vector<long>(PyObject *op, std::vector<long> &container) {
    return generic_py_list_to_cpp_std_vector<long, &py_long_check, &py_long_to_cpp_long>(op, container);
}

template <>
int
py_list_to_cpp_std_vector<double>(PyObject *op, std::vector<double> &container) {
    return generic_py_list_to_cpp_std_vector<double, &py_float_check, &py_float_to_cpp_double>(op, container);
}

template <>
int
py_list_to_cpp_std_vector<std::vector<char>>(PyObject *op, std::vector<std::vector<char>> &container) {
    return generic_py_list_to_cpp_std_vector<std::vector<char>, &py_bytes_check, &py_bytes_to_cpp_vector_char>(op, container);
}

//-------------------- END: Python list -> std::vector --------------------

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
cpp_std_unordered_set_to_py_set<std::vector<char>>(const std::unordered_set<std::vector<char>> &container) {
    return generic_cpp_std_unordered_set_to_py_set<std::vector<char>, &cpp_vector_char_to_py_bytes>(container);
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
py_set_to_cpp_std_unordered_set<std::vector<char>>(PyObject *op, std::unordered_set<std::vector<char>> &container) {
    return generic_py_set_to_cpp_std_unordered_set<std::vector<char>, &py_bytes_check, &py_bytes_to_cpp_vector_char>(op, container);
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
cpp_std_unordered_set_to_py_frozenset<std::vector<char>>(const std::unordered_set<std::vector<char>> &container) {
    return generic_cpp_std_unordered_set_to_py_frozenset<std::vector<char>, &cpp_vector_char_to_py_bytes>(container);
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
py_frozenset_to_cpp_std_unordered_set<std::vector<char>>(PyObject *op, std::unordered_set<std::vector<char>> &container) {
    return generic_py_frozenset_to_cpp_std_unordered_set<std::vector<char>, &py_bytes_check, &py_bytes_to_cpp_vector_char>(op, container);
}

//-------------- END: Python frozenset -> std::unordered_set --------------

//************* END: Unary collections <-> Python collections *************

//******************* std::unordered_map <-> Python dict ******************
//--------------- Converts a std::unordered_map<bool, bool> ---------------
//--------------- to a Python dict of { bool : bool, ...}    --------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, bool>(const std::unordered_map<bool, bool> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        bool, bool,
        &cpp_bool_to_py_bool, &cpp_bool_to_py_bool
    >(map);
}

//-------------- Converts a Python dict of {bool : bool, ...} -------------
//------------------ to a std::unordered_map<bool, bool> ------------------
template <>
int
py_dict_to_cpp_std_unordered_map<bool, bool>(PyObject* op, std::unordered_map<bool, bool> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        bool, bool,
        &py_bool_check, &py_bool_check,
        &py_bool_to_cpp_bool, &py_bool_to_cpp_bool
    >(op, map);
}

//--------------- Converts a std::unordered_map<bool, long> ---------------
//--------------- to a Python dict of { bool : long, ...}    --------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, long>(const std::unordered_map<bool, long> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        bool, long,
        &cpp_bool_to_py_bool, &cpp_long_to_py_long
    >(map);
}

//-------------- Converts a Python dict of {bool : long, ...} -------------
//------------------ to a std::unordered_map<bool, long> ------------------
template <>
int
py_dict_to_cpp_std_unordered_map<bool, long>(PyObject* op, std::unordered_map<bool, long> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        bool, long,
        &py_bool_check, &py_long_check,
        &py_bool_to_cpp_bool, &py_long_to_cpp_long
    >(op, map);
}

//-------------- Converts a std::unordered_map<bool, double> --------------
//-------------- to a Python dict of { bool : double, ...}    -------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, double>(const std::unordered_map<bool, double> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        bool, double,
        &cpp_bool_to_py_bool, &cpp_double_to_py_float
    >(map);
}

//------------- Converts a Python dict of {bool : double, ...} ------------
//----------------- to a std::unordered_map<bool, double> -----------------
template <>
int
py_dict_to_cpp_std_unordered_map<bool, double>(PyObject* op, std::unordered_map<bool, double> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        bool, double,
        &py_bool_check, &py_float_check,
        &py_bool_to_cpp_bool, &py_float_to_cpp_double
    >(op, map);
}

//--------- Converts a std::unordered_map<bool, std::vector<char>> --------
//-------- to a Python dict of { bool : std::vector<char>, ...}    --------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, std::vector<char>>(const std::unordered_map<bool, std::vector<char>> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        bool, std::vector<char>,
        &cpp_bool_to_py_bool, &cpp_vector_char_to_py_bytes
    >(map);
}

//------- Converts a Python dict of {bool : std::vector<char>, ...} -------
//------------ to a std::unordered_map<bool, std::vector<char>> -----------
template <>
int
py_dict_to_cpp_std_unordered_map<bool, std::vector<char>>(PyObject* op, std::unordered_map<bool, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        bool, std::vector<char>,
        &py_bool_check, &py_bytes_check,
        &py_bool_to_cpp_bool, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//--------------- Converts a std::unordered_map<long, bool> ---------------
//--------------- to a Python dict of { long : bool, ...}    --------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, bool>(const std::unordered_map<long, bool> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        long, bool,
        &cpp_long_to_py_long, &cpp_bool_to_py_bool
    >(map);
}

//-------------- Converts a Python dict of {long : bool, ...} -------------
//------------------ to a std::unordered_map<long, bool> ------------------
template <>
int
py_dict_to_cpp_std_unordered_map<long, bool>(PyObject* op, std::unordered_map<long, bool> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        long, bool,
        &py_long_check, &py_bool_check,
        &py_long_to_cpp_long, &py_bool_to_cpp_bool
    >(op, map);
}

//--------------- Converts a std::unordered_map<long, long> ---------------
//--------------- to a Python dict of { long : long, ...}    --------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, long>(const std::unordered_map<long, long> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        long, long,
        &cpp_long_to_py_long, &cpp_long_to_py_long
    >(map);
}

//-------------- Converts a Python dict of {long : long, ...} -------------
//------------------ to a std::unordered_map<long, long> ------------------
template <>
int
py_dict_to_cpp_std_unordered_map<long, long>(PyObject* op, std::unordered_map<long, long> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        long, long,
        &py_long_check, &py_long_check,
        &py_long_to_cpp_long, &py_long_to_cpp_long
    >(op, map);
}

//-------------- Converts a std::unordered_map<long, double> --------------
//-------------- to a Python dict of { long : double, ...}    -------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, double>(const std::unordered_map<long, double> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        long, double,
        &cpp_long_to_py_long, &cpp_double_to_py_float
    >(map);
}

//------------- Converts a Python dict of {long : double, ...} ------------
//----------------- to a std::unordered_map<long, double> -----------------
template <>
int
py_dict_to_cpp_std_unordered_map<long, double>(PyObject* op, std::unordered_map<long, double> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        long, double,
        &py_long_check, &py_float_check,
        &py_long_to_cpp_long, &py_float_to_cpp_double
    >(op, map);
}

//--------- Converts a std::unordered_map<long, std::vector<char>> --------
//-------- to a Python dict of { long : std::vector<char>, ...}    --------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, std::vector<char>>(const std::unordered_map<long, std::vector<char>> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        long, std::vector<char>,
        &cpp_long_to_py_long, &cpp_vector_char_to_py_bytes
    >(map);
}

//------- Converts a Python dict of {long : std::vector<char>, ...} -------
//------------ to a std::unordered_map<long, std::vector<char>> -----------
template <>
int
py_dict_to_cpp_std_unordered_map<long, std::vector<char>>(PyObject* op, std::unordered_map<long, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        long, std::vector<char>,
        &py_long_check, &py_bytes_check,
        &py_long_to_cpp_long, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//-------------- Converts a std::unordered_map<double, bool> --------------
//-------------- to a Python dict of { double : bool, ...}    -------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, bool>(const std::unordered_map<double, bool> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        double, bool,
        &cpp_double_to_py_float, &cpp_bool_to_py_bool
    >(map);
}

//------------- Converts a Python dict of {double : bool, ...} ------------
//----------------- to a std::unordered_map<double, bool> -----------------
template <>
int
py_dict_to_cpp_std_unordered_map<double, bool>(PyObject* op, std::unordered_map<double, bool> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        double, bool,
        &py_float_check, &py_bool_check,
        &py_float_to_cpp_double, &py_bool_to_cpp_bool
    >(op, map);
}

//-------------- Converts a std::unordered_map<double, long> --------------
//-------------- to a Python dict of { double : long, ...}    -------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, long>(const std::unordered_map<double, long> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        double, long,
        &cpp_double_to_py_float, &cpp_long_to_py_long
    >(map);
}

//------------- Converts a Python dict of {double : long, ...} ------------
//----------------- to a std::unordered_map<double, long> -----------------
template <>
int
py_dict_to_cpp_std_unordered_map<double, long>(PyObject* op, std::unordered_map<double, long> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        double, long,
        &py_float_check, &py_long_check,
        &py_float_to_cpp_double, &py_long_to_cpp_long
    >(op, map);
}

//------------- Converts a std::unordered_map<double, double> -------------
//------------- to a Python dict of { double : double, ...}    ------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, double>(const std::unordered_map<double, double> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        double, double,
        &cpp_double_to_py_float, &cpp_double_to_py_float
    >(map);
}

//------------ Converts a Python dict of {double : double, ...} -----------
//---------------- to a std::unordered_map<double, double> ----------------
template <>
int
py_dict_to_cpp_std_unordered_map<double, double>(PyObject* op, std::unordered_map<double, double> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        double, double,
        &py_float_check, &py_float_check,
        &py_float_to_cpp_double, &py_float_to_cpp_double
    >(op, map);
}

//-------- Converts a std::unordered_map<double, std::vector<char>> -------
//------- to a Python dict of { double : std::vector<char>, ...}    -------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, std::vector<char>>(const std::unordered_map<double, std::vector<char>> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        double, std::vector<char>,
        &cpp_double_to_py_float, &cpp_vector_char_to_py_bytes
    >(map);
}

//------ Converts a Python dict of {double : std::vector<char>, ...} ------
//----------- to a std::unordered_map<double, std::vector<char>> ----------
template <>
int
py_dict_to_cpp_std_unordered_map<double, std::vector<char>>(PyObject* op, std::unordered_map<double, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        double, std::vector<char>,
        &py_float_check, &py_bytes_check,
        &py_float_to_cpp_double, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//--------- Converts a std::unordered_map<std::vector<char>, bool> --------
//-------- to a Python dict of { std::vector<char> : bool, ...}    --------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::vector<char>, bool>(const std::unordered_map<std::vector<char>, bool> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        std::vector<char>, bool,
        &cpp_vector_char_to_py_bytes, &cpp_bool_to_py_bool
    >(map);
}

//------- Converts a Python dict of {std::vector<char> : bool, ...} -------
//------------ to a std::unordered_map<std::vector<char>, bool> -----------
template <>
int
py_dict_to_cpp_std_unordered_map<std::vector<char>, bool>(PyObject* op, std::unordered_map<std::vector<char>, bool> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        std::vector<char>, bool,
        &py_bytes_check, &py_bool_check,
        &py_bytes_to_cpp_vector_char, &py_bool_to_cpp_bool
    >(op, map);
}

//--------- Converts a std::unordered_map<std::vector<char>, long> --------
//-------- to a Python dict of { std::vector<char> : long, ...}    --------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::vector<char>, long>(const std::unordered_map<std::vector<char>, long> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        std::vector<char>, long,
        &cpp_vector_char_to_py_bytes, &cpp_long_to_py_long
    >(map);
}

//------- Converts a Python dict of {std::vector<char> : long, ...} -------
//------------ to a std::unordered_map<std::vector<char>, long> -----------
template <>
int
py_dict_to_cpp_std_unordered_map<std::vector<char>, long>(PyObject* op, std::unordered_map<std::vector<char>, long> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        std::vector<char>, long,
        &py_bytes_check, &py_long_check,
        &py_bytes_to_cpp_vector_char, &py_long_to_cpp_long
    >(op, map);
}

//-------- Converts a std::unordered_map<std::vector<char>, double> -------
//------- to a Python dict of { std::vector<char> : double, ...}    -------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::vector<char>, double>(const std::unordered_map<std::vector<char>, double> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        std::vector<char>, double,
        &cpp_vector_char_to_py_bytes, &cpp_double_to_py_float
    >(map);
}

//------ Converts a Python dict of {std::vector<char> : double, ...} ------
//----------- to a std::unordered_map<std::vector<char>, double> ----------
template <>
int
py_dict_to_cpp_std_unordered_map<std::vector<char>, double>(PyObject* op, std::unordered_map<std::vector<char>, double> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        std::vector<char>, double,
        &py_bytes_check, &py_float_check,
        &py_bytes_to_cpp_vector_char, &py_float_to_cpp_double
    >(op, map);
}

//-- Converts a std::unordered_map<std::vector<char>, std::vector<char>> --
//-- to a Python dict of { std::vector<char> : std::vector<char>, ...}    -
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::vector<char>, std::vector<char>>(const std::unordered_map<std::vector<char>, std::vector<char>> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        std::vector<char>, std::vector<char>,
        &cpp_vector_char_to_py_bytes, &cpp_vector_char_to_py_bytes
    >(map);
}

//- Converts a Python dict of {std::vector<char> : std::vector<char>, ...} 
//----- to a std::unordered_map<std::vector<char>, std::vector<char>> -----
template <>
int
py_dict_to_cpp_std_unordered_map<std::vector<char>, std::vector<char>>(PyObject* op, std::unordered_map<std::vector<char>, std::vector<char>> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        std::vector<char>, std::vector<char>,
        &py_bytes_check, &py_bytes_check,
        &py_bytes_to_cpp_vector_char, &py_bytes_to_cpp_vector_char
    >(op, map);
}

//**************** END: std::unordered_map <-> Python dict ****************

// Definitions written: 64
//#########################################################################
//#### END: Auto-generated code - do not edit. Seriously, do NOT edit. ####
//#########################################################################

} // namespace Python_Cpp_Containers

//========================== END: Definition file =========================

