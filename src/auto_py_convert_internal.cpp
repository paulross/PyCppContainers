//============================ Definition file ============================
//#########################################################################
//####### Auto-generated code - do not edit. Seriously, do NOT edit. ######
//#########################################################################
// Conversion from homogeneous data structures in Python and C++
// 
// Unary conversions
// tuple:
// tuple <-> std::vector<double>
// tuple <-> std::vector<long>
// 
// 
// Mapping conversions
// dict <-> std::unordered_map<double, double>
// dict <-> std::unordered_map<double, long>
// dict <-> std::unordered_map<long, double>
// dict <-> std::unordered_map<long, long>
// 
#include "python_convert.h"

namespace Python_Cpp_Homogeneous_Containers {

//**************** Unary collections <-> Python collections ***************
//---------------------- std::vector -> Python tuple ----------------------
template <>
PyObject *
cpp_std_vector_to_py_tuple<double>(const std::vector<double> &container) {
    return generic_cpp_std_vector_to_py_tuple<double, &py_float_from_double>(container);
}

template <>
PyObject *
cpp_std_vector_to_py_tuple<long>(const std::vector<long> &container) {
    return generic_cpp_std_vector_to_py_tuple<long, &py_long_from_long>(container);
}

//-------------------- END: std::vector -> Python tuple -------------------

//---------------------- Python tuple -> std::vector ----------------------
template <> int
py_tuple_to_cpp_std_vector<double>(PyObject *op, std::vector<double> &container) {
    return generic_py_tuple_to_cpp_std_vector<double, &py_float_check, &py_float_as_double>(op, container);
}

template <> int
py_tuple_to_cpp_std_vector<long>(PyObject *op, std::vector<long> &container) {
    return generic_py_tuple_to_cpp_std_vector<long, &py_long_check, &py_long_as_long>(op, container);
}

//-------------------- END: Python tuple -> std::vector -------------------

//************* END: Unary collections <-> Python collections *************

//******************* std::unordered_map <-> Python dict ******************
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
template <> int
py_dict_to_cpp_std_unordered_map<double, double>(PyObject* op, std::unordered_map<double, double> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        double, double,
        &py_float_check, &py_float_check,
        &py_float_as_double, &py_float_as_double
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
template <> int
py_dict_to_cpp_std_unordered_map<double, long>(PyObject* op, std::unordered_map<double, long> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        double, long,
        &py_float_check, &py_long_check,
        &py_float_as_double, &py_long_as_long
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
template <> int
py_dict_to_cpp_std_unordered_map<long, double>(PyObject* op, std::unordered_map<long, double> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        long, double,
        &py_long_check, &py_float_check,
        &py_long_as_long, &py_float_as_double
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
template <> int
py_dict_to_cpp_std_unordered_map<long, long>(PyObject* op, std::unordered_map<long, long> &map) {
    return generic_py_dict_to_cpp_std_unordered_map<
        long, long,
        &py_long_check, &py_long_check,
        &py_long_as_long, &py_long_as_long
    >(op, map);
}

//**************** END: std::unordered_map <-> Python dict ****************

// Definitions written: 12
//#########################################################################
//#### END: Auto-generated code - do not edit. Seriously, do NOT edit. ####
//#########################################################################

} // namespace Python_Cpp_Homogeneous_Containers

//========================== END: Definition file =========================

