//============================ Definition file ============================
//#########################################################################
//####### Auto-generated code - do not edit. Seriously, do NOT edit. ######
//#########################################################################
// Conversion from homogeneous data structures in Python and C++
// 
// Unary conversions
// tuple:
// tuple <-> std::vector<double>
// 
// 
// Mapping conversions
// dict <-> std::unordered_map<double, double>
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

//-------------------- END: std::vector -> Python tuple -------------------

//---------------------- Python tuple -> std::vector ----------------------
template <> int
py_tuple_to_cpp_std_vector<double>(PyObject *op, std::vector<double> &container) {
    return generic_py_tuple_to_cpp_std_vector<double, &py_float_check, &py_float_as_double>(op, container);
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

//**************** END: std::unordered_map <-> Python dict ****************

// Definitions written: 4
//#########################################################################
//#### END: Auto-generated code - do not edit. Seriously, do NOT edit. ####
//#########################################################################

} // namespace Python_Cpp_Homogeneous_Containers

//========================== END: Definition file =========================

