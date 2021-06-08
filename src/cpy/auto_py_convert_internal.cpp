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
// tuple <-> std::vector<std::string>
// 
// list:
// list <-> std::vector<bool>
// list <-> std::vector<long>
// list <-> std::vector<double>
// list <-> std::vector<std::string>
// 
// set:
// set <-> std::unordered_set<bool>
// set <-> std::unordered_set<long>
// set <-> std::unordered_set<double>
// set <-> std::unordered_set<std::string>
// 
// 
// Mapping conversions
// dict <-> std::unordered_map<bool, bool>
// dict <-> std::unordered_map<bool, long>
// dict <-> std::unordered_map<bool, double>
// dict <-> std::unordered_map<bool, std::string>
// dict <-> std::unordered_map<long, bool>
// dict <-> std::unordered_map<long, long>
// dict <-> std::unordered_map<long, double>
// dict <-> std::unordered_map<long, std::string>
// dict <-> std::unordered_map<double, bool>
// dict <-> std::unordered_map<double, long>
// dict <-> std::unordered_map<double, double>
// dict <-> std::unordered_map<double, std::string>
// dict <-> std::unordered_map<std::string, bool>
// dict <-> std::unordered_map<std::string, long>
// dict <-> std::unordered_map<std::string, double>
// dict <-> std::unordered_map<std::string, std::string>
// 
#include "python_convert.h"

namespace Python_Cpp_Homogeneous_Containers {

//**************** Unary collections <-> Python collections ***************
//---------------------- std::vector -> Python tuple ----------------------
template <>
PyObject *
cpp_std_vector_to_py_tuple<bool>(const std::vector<bool> &container) {
    return generic_cpp_std_vector_to_py_tuple<bool, &py_bool_from_bool>(container);
}

template <>
PyObject *
cpp_std_vector_to_py_tuple<long>(const std::vector<long> &container) {
    return generic_cpp_std_vector_to_py_tuple<long, &py_long_from_long>(container);
}

template <>
PyObject *
cpp_std_vector_to_py_tuple<double>(const std::vector<double> &container) {
    return generic_cpp_std_vector_to_py_tuple<double, &py_float_from_double>(container);
}

template <>
PyObject *
cpp_std_vector_to_py_tuple<std::string>(const std::vector<std::string> &container) {
    return generic_cpp_std_vector_to_py_tuple<std::string, &py_bytes_from_string>(container);
}

//-------------------- END: std::vector -> Python tuple -------------------

//---------------------- Python tuple -> std::vector ----------------------
template <>
int
py_tuple_to_cpp_std_vector<bool>(PyObject *op, std::vector<bool> &container) {
    return generic_py_tuple_to_cpp_std_vector<bool, &py_bool_check, &py_bool_as_bool>(op, container);
}

template <>
int
py_tuple_to_cpp_std_vector<long>(PyObject *op, std::vector<long> &container) {
    return generic_py_tuple_to_cpp_std_vector<long, &py_long_check, &py_long_as_long>(op, container);
}

template <>
int
py_tuple_to_cpp_std_vector<double>(PyObject *op, std::vector<double> &container) {
    return generic_py_tuple_to_cpp_std_vector<double, &py_float_check, &py_float_as_double>(op, container);
}

template <>
int
py_tuple_to_cpp_std_vector<std::string>(PyObject *op, std::vector<std::string> &container) {
    return generic_py_tuple_to_cpp_std_vector<std::string, &py_bytes_check, &py_bytes_as_string>(op, container);
}

//-------------------- END: Python tuple -> std::vector -------------------

//----------------------- std::vector -> Python list ----------------------
template <>
PyObject *
cpp_std_vector_to_py_list<bool>(const std::vector<bool> &container) {
    return generic_cpp_std_vector_to_py_list<bool, &py_bool_from_bool>(container);
}

template <>
PyObject *
cpp_std_vector_to_py_list<long>(const std::vector<long> &container) {
    return generic_cpp_std_vector_to_py_list<long, &py_long_from_long>(container);
}

template <>
PyObject *
cpp_std_vector_to_py_list<double>(const std::vector<double> &container) {
    return generic_cpp_std_vector_to_py_list<double, &py_float_from_double>(container);
}

template <>
PyObject *
cpp_std_vector_to_py_list<std::string>(const std::vector<std::string> &container) {
    return generic_cpp_std_vector_to_py_list<std::string, &py_bytes_from_string>(container);
}

//-------------------- END: std::vector -> Python list --------------------

//----------------------- Python list -> std::vector ----------------------
template <>
int
py_list_to_cpp_std_vector<bool>(PyObject *op, std::vector<bool> &container) {
    return generic_py_list_to_cpp_std_vector<bool, &py_bool_check, &py_bool_as_bool>(op, container);
}

template <>
int
py_list_to_cpp_std_vector<long>(PyObject *op, std::vector<long> &container) {
    return generic_py_list_to_cpp_std_vector<long, &py_long_check, &py_long_as_long>(op, container);
}

template <>
int
py_list_to_cpp_std_vector<double>(PyObject *op, std::vector<double> &container) {
    return generic_py_list_to_cpp_std_vector<double, &py_float_check, &py_float_as_double>(op, container);
}

template <>
int
py_list_to_cpp_std_vector<std::string>(PyObject *op, std::vector<std::string> &container) {
    return generic_py_list_to_cpp_std_vector<std::string, &py_bytes_check, &py_bytes_as_string>(op, container);
}

//-------------------- END: Python list -> std::vector --------------------

//-------------------- std::unordered_set -> Python set -------------------
template <>
PyObject *
cpp_std_unordered_set_to_py_set<bool>(const std::unordered_set<bool> &container) {
    return generic_cpp_std_unordered_set_to_py_set<bool, &py_bool_from_bool>(container);
}

template <>
PyObject *
cpp_std_unordered_set_to_py_set<long>(const std::unordered_set<long> &container) {
    return generic_cpp_std_unordered_set_to_py_set<long, &py_long_from_long>(container);
}

template <>
PyObject *
cpp_std_unordered_set_to_py_set<double>(const std::unordered_set<double> &container) {
    return generic_cpp_std_unordered_set_to_py_set<double, &py_float_from_double>(container);
}

template <>
PyObject *
cpp_std_unordered_set_to_py_set<std::string>(const std::unordered_set<std::string> &container) {
    return generic_cpp_std_unordered_set_to_py_set<std::string, &py_bytes_from_string>(container);
}

//----------------- END: std::unordered_set -> Python set -----------------

//-------------------- Python set -> std::unordered_set -------------------
template <>
int
py_set_to_cpp_std_unordered_set<bool>(PyObject *op, std::unordered_set<bool> &container) {
    return generic_py_set_to_cpp_std_unordered_set<bool, &py_bool_check, &py_bool_as_bool>(op, container);
}

template <>
int
py_set_to_cpp_std_unordered_set<long>(PyObject *op, std::unordered_set<long> &container) {
    return generic_py_set_to_cpp_std_unordered_set<long, &py_long_check, &py_long_as_long>(op, container);
}

template <>
int
py_set_to_cpp_std_unordered_set<double>(PyObject *op, std::unordered_set<double> &container) {
    return generic_py_set_to_cpp_std_unordered_set<double, &py_float_check, &py_float_as_double>(op, container);
}

template <>
int
py_set_to_cpp_std_unordered_set<std::string>(PyObject *op, std::unordered_set<std::string> &container) {
    return generic_py_set_to_cpp_std_unordered_set<std::string, &py_bytes_check, &py_bytes_as_string>(op, container);
}

//----------------- END: Python set -> std::unordered_set -----------------

//************* END: Unary collections <-> Python collections *************

//******************* std::unordered_map <-> Python dict ******************
//--------------- Converts a std::unordered_map<bool, bool> ---------------
//--------------- to a Python dict of { bool : bool, ...}    --------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, bool>(const std::unordered_map<bool, bool> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        bool, bool,
        &py_bool_from_bool, &py_bool_from_bool
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
        &py_bool_as_bool, &py_bool_as_bool
    >(op, map);
}

//--------------- Converts a std::unordered_map<bool, long> ---------------
//--------------- to a Python dict of { bool : long, ...}    --------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, long>(const std::unordered_map<bool, long> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        bool, long,
        &py_bool_from_bool, &py_long_from_long
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
        &py_bool_as_bool, &py_long_as_long
    >(op, map);
}

//-------------- Converts a std::unordered_map<bool, double> --------------
//-------------- to a Python dict of { bool : double, ...}    -------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, double>(const std::unordered_map<bool, double> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        bool, double,
        &py_bool_from_bool, &py_float_from_double
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
        &py_bool_as_bool, &py_float_as_double
    >(op, map);
}

//------------ Converts a std::unordered_map<bool, std::string> -----------
//----------- to a Python dict of { bool : std::string, ...}    -----------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, std::string>(const std::unordered_map<bool, std::string> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        bool, std::string,
        &py_bool_from_bool, &py_bytes_from_string
    >(map);
}

//---------- Converts a Python dict of {bool : std::string, ...} ----------
//--------------- to a std::unordered_map<bool, std::string> --------------
template <>
int
py_dict_to_cpp_std_unordered_map<bool, std::string>(PyObject* op, std::unordered_map<bool, std::string> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        bool, std::string,
        &py_bool_check, &py_bytes_check,
        &py_bool_as_bool, &py_bytes_as_string
    >(op, map);
}

//--------------- Converts a std::unordered_map<long, bool> ---------------
//--------------- to a Python dict of { long : bool, ...}    --------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, bool>(const std::unordered_map<long, bool> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        long, bool,
        &py_long_from_long, &py_bool_from_bool
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
        &py_long_as_long, &py_bool_as_bool
    >(op, map);
}

//--------------- Converts a std::unordered_map<long, long> ---------------
//--------------- to a Python dict of { long : long, ...}    --------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, long>(const std::unordered_map<long, long> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        long, long,
        &py_long_from_long, &py_long_from_long
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
        &py_long_as_long, &py_long_as_long
    >(op, map);
}

//-------------- Converts a std::unordered_map<long, double> --------------
//-------------- to a Python dict of { long : double, ...}    -------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, double>(const std::unordered_map<long, double> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        long, double,
        &py_long_from_long, &py_float_from_double
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
        &py_long_as_long, &py_float_as_double
    >(op, map);
}

//------------ Converts a std::unordered_map<long, std::string> -----------
//----------- to a Python dict of { long : std::string, ...}    -----------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, std::string>(const std::unordered_map<long, std::string> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        long, std::string,
        &py_long_from_long, &py_bytes_from_string
    >(map);
}

//---------- Converts a Python dict of {long : std::string, ...} ----------
//--------------- to a std::unordered_map<long, std::string> --------------
template <>
int
py_dict_to_cpp_std_unordered_map<long, std::string>(PyObject* op, std::unordered_map<long, std::string> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        long, std::string,
        &py_long_check, &py_bytes_check,
        &py_long_as_long, &py_bytes_as_string
    >(op, map);
}

//-------------- Converts a std::unordered_map<double, bool> --------------
//-------------- to a Python dict of { double : bool, ...}    -------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, bool>(const std::unordered_map<double, bool> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        double, bool,
        &py_float_from_double, &py_bool_from_bool
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
        &py_float_as_double, &py_bool_as_bool
    >(op, map);
}

//-------------- Converts a std::unordered_map<double, long> --------------
//-------------- to a Python dict of { double : long, ...}    -------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, long>(const std::unordered_map<double, long> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        double, long,
        &py_float_from_double, &py_long_from_long
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
        &py_float_as_double, &py_long_as_long
    >(op, map);
}

//------------- Converts a std::unordered_map<double, double> -------------
//------------- to a Python dict of { double : double, ...}    ------------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, double>(const std::unordered_map<double, double> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        double, double,
        &py_float_from_double, &py_float_from_double
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
        &py_float_as_double, &py_float_as_double
    >(op, map);
}

//----------- Converts a std::unordered_map<double, std::string> ----------
//---------- to a Python dict of { double : std::string, ...}    ----------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, std::string>(const std::unordered_map<double, std::string> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        double, std::string,
        &py_float_from_double, &py_bytes_from_string
    >(map);
}

//--------- Converts a Python dict of {double : std::string, ...} ---------
//-------------- to a std::unordered_map<double, std::string> -------------
template <>
int
py_dict_to_cpp_std_unordered_map<double, std::string>(PyObject* op, std::unordered_map<double, std::string> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        double, std::string,
        &py_float_check, &py_bytes_check,
        &py_float_as_double, &py_bytes_as_string
    >(op, map);
}

//------------ Converts a std::unordered_map<std::string, bool> -----------
//----------- to a Python dict of { std::string : bool, ...}    -----------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::string, bool>(const std::unordered_map<std::string, bool> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        std::string, bool,
        &py_bytes_from_string, &py_bool_from_bool
    >(map);
}

//---------- Converts a Python dict of {std::string : bool, ...} ----------
//--------------- to a std::unordered_map<std::string, bool> --------------
template <>
int
py_dict_to_cpp_std_unordered_map<std::string, bool>(PyObject* op, std::unordered_map<std::string, bool> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        std::string, bool,
        &py_bytes_check, &py_bool_check,
        &py_bytes_as_string, &py_bool_as_bool
    >(op, map);
}

//------------ Converts a std::unordered_map<std::string, long> -----------
//----------- to a Python dict of { std::string : long, ...}    -----------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::string, long>(const std::unordered_map<std::string, long> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        std::string, long,
        &py_bytes_from_string, &py_long_from_long
    >(map);
}

//---------- Converts a Python dict of {std::string : long, ...} ----------
//--------------- to a std::unordered_map<std::string, long> --------------
template <>
int
py_dict_to_cpp_std_unordered_map<std::string, long>(PyObject* op, std::unordered_map<std::string, long> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        std::string, long,
        &py_bytes_check, &py_long_check,
        &py_bytes_as_string, &py_long_as_long
    >(op, map);
}

//----------- Converts a std::unordered_map<std::string, double> ----------
//---------- to a Python dict of { std::string : double, ...}    ----------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::string, double>(const std::unordered_map<std::string, double> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        std::string, double,
        &py_bytes_from_string, &py_float_from_double
    >(map);
}

//--------- Converts a Python dict of {std::string : double, ...} ---------
//-------------- to a std::unordered_map<std::string, double> -------------
template <>
int
py_dict_to_cpp_std_unordered_map<std::string, double>(PyObject* op, std::unordered_map<std::string, double> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        std::string, double,
        &py_bytes_check, &py_float_check,
        &py_bytes_as_string, &py_float_as_double
    >(op, map);
}

//-------- Converts a std::unordered_map<std::string, std::string> --------
//-------- to a Python dict of { std::string : std::string, ...}    -------
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::string, std::string>(const std::unordered_map<std::string, std::string> &map) {
    return generic_cpp_std_unordered_map_to_py_dict<
        std::string, std::string,
        &py_bytes_from_string, &py_bytes_from_string
    >(map);
}

//------- Converts a Python dict of {std::string : std::string, ...} ------
//----------- to a std::unordered_map<std::string, std::string> -----------
template <>
int
py_dict_to_cpp_std_unordered_map<std::string, std::string>(PyObject* op, std::unordered_map<std::string, std::string> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        std::string, std::string,
        &py_bytes_check, &py_bytes_check,
        &py_bytes_as_string, &py_bytes_as_string
    >(op, map);
}

//**************** END: std::unordered_map <-> Python dict ****************

// Definitions written: 56
//#########################################################################
//#### END: Auto-generated code - do not edit. Seriously, do NOT edit. ####
//#########################################################################

} // namespace Python_Cpp_Homogeneous_Containers

//========================== END: Definition file =========================

