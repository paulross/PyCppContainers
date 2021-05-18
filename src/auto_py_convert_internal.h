//============================ Declaration file ===========================
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
#include <Python.h>

#include <vector>
#include <unordered_map>

namespace Python_Cpp_Homogeneous_Containers {


//--------------------- Required conversion functions ---------------------
// Functions to convert a type:
// double
PyObject *py_float_from_double(const double &value);
int py_float_check(PyObject *op);
double py_float_as_double(PyObject *op);
//------------------- END: Required conversion functions ------------------

//**************** Unary collections <-> Python collections ***************
//---------------------- std::vector -> Python tuple ----------------------
// Base declaration
template<typename T>
PyObject *
cpp_std_vector_to_py_tuple(const std::vector<T> &container);
// Instantiations
template <>
PyObject *
cpp_std_vector_to_py_tuple<double>(const std::vector<double> &container);
//-------------------- END: std::vector -> Python tuple -------------------

//---------------------- Python tuple -> std::vector ----------------------
// Base declaration
template<typename T>
int
py_tuple_to_cpp_std_vector(PyObject *tuple, std::vector<T> &container);
// Instantiations
template <>
int
py_tuple_to_cpp_std_vector<double>(PyObject *tuple, std::vector<double> &container);
//-------------------- END: Python tuple -> std::vector -------------------

//************* END: Unary collections <-> Python collections *************

//******************* std::unordered_map <-> Python dict ******************
//------------------- std::unordered_map -> Python dict -------------------
// Base declaration
template<typename K, typename V>
PyObject *
cpp_std_unordered_map_to_py_dict(const std::unordered_map<K, V> &map);
// Instantiations
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, double>(const std::unordered_map<double, double> &map);
//----------------- END: std::unordered_map -> Python dict ----------------

//------------------- Python dict -> std::unordered_map -------------------
// Base declaration
template<typename K, typename V>
int 
py_dict_to_cpp_std_unordered_map(PyObject *op, std::unordered_map<K, V> &map);
// Instantiations
template <>
int
py_dict_to_cpp_std_unordered_map<double, double>(PyObject* op, std::unordered_map<double, double> &map);
//----------------- END: Python dict -> std::unordered_map ----------------

//**************** END: std::unordered_map <-> Python dict ****************

// Declarations written: 6
//#########################################################################
//#### END: Auto-generated code - do not edit. Seriously, do NOT edit. ####
//#########################################################################

} // namespace Python_Cpp_Homogeneous_Containers

//========================= END: Declaration file =========================

