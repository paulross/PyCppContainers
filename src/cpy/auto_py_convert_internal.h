//============================ Declaration file ===========================
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
// frozenset:
// frozenset <-> std::unordered_set<bool>
// frozenset <-> std::unordered_set<long>
// frozenset <-> std::unordered_set<double>
// frozenset <-> std::unordered_set<std::string>
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
#include <Python.h>


namespace Python_Cpp_Containers {


//**************** Unary collections <-> Python collections ***************
//---------------------- std::vector -> Python tuple ----------------------
// Base declaration
template<typename T>
PyObject *
cpp_std_vector_to_py_tuple(const std::vector<T> &container);
// Instantiations
template <>
PyObject *
cpp_std_vector_to_py_tuple<bool>(const std::vector<bool> &container);
template <>
PyObject *
cpp_std_vector_to_py_tuple<long>(const std::vector<long> &container);
template <>
PyObject *
cpp_std_vector_to_py_tuple<double>(const std::vector<double> &container);
template <>
PyObject *
cpp_std_vector_to_py_tuple<std::string>(const std::vector<std::string> &container);
//-------------------- END: std::vector -> Python tuple -------------------

//---------------------- Python tuple -> std::vector ----------------------
// Base declaration
template<typename T>
int
py_tuple_to_cpp_std_vector(PyObject *tuple, std::vector<T> &container);
// Instantiations
template <>
int
py_tuple_to_cpp_std_vector<bool>(PyObject *tuple, std::vector<bool> &container);
template <>
int
py_tuple_to_cpp_std_vector<long>(PyObject *tuple, std::vector<long> &container);
template <>
int
py_tuple_to_cpp_std_vector<double>(PyObject *tuple, std::vector<double> &container);
template <>
int
py_tuple_to_cpp_std_vector<std::string>(PyObject *tuple, std::vector<std::string> &container);
//-------------------- END: Python tuple -> std::vector -------------------

//----------------------- std::vector -> Python list ----------------------
// Base declaration
template<typename T>
PyObject *
cpp_std_vector_to_py_list(const std::vector<T> &container);
// Instantiations
template <>
PyObject *
cpp_std_vector_to_py_list<bool>(const std::vector<bool> &container);
template <>
PyObject *
cpp_std_vector_to_py_list<long>(const std::vector<long> &container);
template <>
PyObject *
cpp_std_vector_to_py_list<double>(const std::vector<double> &container);
template <>
PyObject *
cpp_std_vector_to_py_list<std::string>(const std::vector<std::string> &container);
//-------------------- END: std::vector -> Python list --------------------

//----------------------- Python list -> std::vector ----------------------
// Base declaration
template<typename T>
int
py_list_to_cpp_std_vector(PyObject *tuple, std::vector<T> &container);
// Instantiations
template <>
int
py_list_to_cpp_std_vector<bool>(PyObject *tuple, std::vector<bool> &container);
template <>
int
py_list_to_cpp_std_vector<long>(PyObject *tuple, std::vector<long> &container);
template <>
int
py_list_to_cpp_std_vector<double>(PyObject *tuple, std::vector<double> &container);
template <>
int
py_list_to_cpp_std_vector<std::string>(PyObject *tuple, std::vector<std::string> &container);
//-------------------- END: Python list -> std::vector --------------------

//-------------------- std::unordered_set -> Python set -------------------
// Base declaration
template<typename T>
PyObject *
cpp_std_unordered_set_to_py_set(const std::unordered_set<T> &container);
// Instantiations
template <>
PyObject *
cpp_std_unordered_set_to_py_set<bool>(const std::unordered_set<bool> &container);
template <>
PyObject *
cpp_std_unordered_set_to_py_set<long>(const std::unordered_set<long> &container);
template <>
PyObject *
cpp_std_unordered_set_to_py_set<double>(const std::unordered_set<double> &container);
template <>
PyObject *
cpp_std_unordered_set_to_py_set<std::string>(const std::unordered_set<std::string> &container);
//----------------- END: std::unordered_set -> Python set -----------------

//-------------------- Python set -> std::unordered_set -------------------
// Base declaration
template<typename T>
int
py_set_to_cpp_std_unordered_set(PyObject *tuple, std::unordered_set<T> &container);
// Instantiations
template <>
int
py_set_to_cpp_std_unordered_set<bool>(PyObject *tuple, std::unordered_set<bool> &container);
template <>
int
py_set_to_cpp_std_unordered_set<long>(PyObject *tuple, std::unordered_set<long> &container);
template <>
int
py_set_to_cpp_std_unordered_set<double>(PyObject *tuple, std::unordered_set<double> &container);
template <>
int
py_set_to_cpp_std_unordered_set<std::string>(PyObject *tuple, std::unordered_set<std::string> &container);
//----------------- END: Python set -> std::unordered_set -----------------

//----------------- std::unordered_set -> Python frozenset ----------------
// Base declaration
template<typename T>
PyObject *
cpp_std_unordered_set_to_py_frozenset(const std::unordered_set<T> &container);
// Instantiations
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<bool>(const std::unordered_set<bool> &container);
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<long>(const std::unordered_set<long> &container);
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<double>(const std::unordered_set<double> &container);
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<std::string>(const std::unordered_set<std::string> &container);
//-------------- END: std::unordered_set -> Python frozenset --------------

//----------------- Python frozenset -> std::unordered_set ----------------
// Base declaration
template<typename T>
int
py_frozenset_to_cpp_std_unordered_set(PyObject *tuple, std::unordered_set<T> &container);
// Instantiations
template <>
int
py_frozenset_to_cpp_std_unordered_set<bool>(PyObject *tuple, std::unordered_set<bool> &container);
template <>
int
py_frozenset_to_cpp_std_unordered_set<long>(PyObject *tuple, std::unordered_set<long> &container);
template <>
int
py_frozenset_to_cpp_std_unordered_set<double>(PyObject *tuple, std::unordered_set<double> &container);
template <>
int
py_frozenset_to_cpp_std_unordered_set<std::string>(PyObject *tuple, std::unordered_set<std::string> &container);
//-------------- END: Python frozenset -> std::unordered_set --------------

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
cpp_std_unordered_map_to_py_dict<bool, bool>(const std::unordered_map<bool, bool> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, long>(const std::unordered_map<bool, long> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, double>(const std::unordered_map<bool, double> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, std::string>(const std::unordered_map<bool, std::string> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, bool>(const std::unordered_map<long, bool> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, long>(const std::unordered_map<long, long> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, double>(const std::unordered_map<long, double> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, std::string>(const std::unordered_map<long, std::string> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, bool>(const std::unordered_map<double, bool> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, long>(const std::unordered_map<double, long> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, double>(const std::unordered_map<double, double> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, std::string>(const std::unordered_map<double, std::string> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::string, bool>(const std::unordered_map<std::string, bool> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::string, long>(const std::unordered_map<std::string, long> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::string, double>(const std::unordered_map<std::string, double> &map);
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::string, std::string>(const std::unordered_map<std::string, std::string> &map);
//----------------- END: std::unordered_map -> Python dict ----------------

//------------------- Python dict -> std::unordered_map -------------------
// Base declaration
template<typename K, typename V>
int 
py_dict_to_cpp_std_unordered_map(PyObject *op, std::unordered_map<K, V> &map);
// Instantiations
template <>
int
py_dict_to_cpp_std_unordered_map<bool, bool>(PyObject* op, std::unordered_map<bool, bool> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<bool, long>(PyObject* op, std::unordered_map<bool, long> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<bool, double>(PyObject* op, std::unordered_map<bool, double> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<bool, std::string>(PyObject* op, std::unordered_map<bool, std::string> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<long, bool>(PyObject* op, std::unordered_map<long, bool> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<long, long>(PyObject* op, std::unordered_map<long, long> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<long, double>(PyObject* op, std::unordered_map<long, double> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<long, std::string>(PyObject* op, std::unordered_map<long, std::string> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<double, bool>(PyObject* op, std::unordered_map<double, bool> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<double, long>(PyObject* op, std::unordered_map<double, long> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<double, double>(PyObject* op, std::unordered_map<double, double> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<double, std::string>(PyObject* op, std::unordered_map<double, std::string> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<std::string, bool>(PyObject* op, std::unordered_map<std::string, bool> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<std::string, long>(PyObject* op, std::unordered_map<std::string, long> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<std::string, double>(PyObject* op, std::unordered_map<std::string, double> &map);
template <>
int
py_dict_to_cpp_std_unordered_map<std::string, std::string>(PyObject* op, std::unordered_map<std::string, std::string> &map);
//----------------- END: Python dict -> std::unordered_map ----------------

//**************** END: std::unordered_map <-> Python dict ****************

// Declarations written: 66
//#########################################################################
//#### END: Auto-generated code - do not edit. Seriously, do NOT edit. ####
//#########################################################################

} // namespace Python_Cpp_Containers

//========================= END: Declaration file =========================

