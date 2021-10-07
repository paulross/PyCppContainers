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
/**
 * Base declaration for converting C++ std::vector to a Python tuple.
 *
 * @tparam T C++ type.
 * @param container C++ input as a std::vector<T>.
 * @return A Python tuple containing type corresponding to the C++ type T.
 */
template<typename T>
PyObject *
cpp_std_vector_to_py_tuple(const std::vector<T> &container);

// Instantiations
/**
 * Instantiation for converting C++ std::vector<bool> to a Python tuple of bool.
 *
 * @param container C++ input as a std::vector<bool>.
 * @return A Python tuple containing bool objects.
 */
template <>
PyObject *
cpp_std_vector_to_py_tuple<bool>(const std::vector<bool> &container);

/**
 * Instantiation for converting C++ std::vector<long> to a Python tuple of int.
 *
 * @param container C++ input as a std::vector<long>.
 * @return A Python tuple containing int objects.
 */
template <>
PyObject *
cpp_std_vector_to_py_tuple<long>(const std::vector<long> &container);

/**
 * Instantiation for converting C++ std::vector<double> to a Python tuple of float.
 *
 * @param container C++ input as a std::vector<double>.
 * @return A Python tuple containing float objects.
 */
template <>
PyObject *
cpp_std_vector_to_py_tuple<double>(const std::vector<double> &container);

/**
 * Instantiation for converting C++ std::vector<std::string> to a Python tuple of str.
 *
 * @param container C++ input as a std::vector<std::string>.
 * @return A Python tuple containing str objects.
 */
template <>
PyObject *
cpp_std_vector_to_py_tuple<std::string>(const std::vector<std::string> &container);

//-------------------- END: std::vector -> Python tuple -------------------

//---------------------- Python tuple -> std::vector ----------------------
// Base declaration
/**
 * Base declaration for converting a Python tuple to a C++ std::vector.
 *
 * @tparam T C++ type.
 * @param op The Python container to read from.
 * @param container The C++ std::vector to write to.
 * @return 0 on success, non-zero on failure.
 */
template<typename T>
int
py_tuple_to_cpp_std_vector(PyObject *op, std::vector<T> &container);

// Instantiations
/**
 * Instantiation for converting a Python tuple of bool to a C++ std::vector<bool>.
 *
 * @param op Python input as a tuple of bool.
 * @param container C++ output as a std::vector<bool>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_vector<bool>(PyObject *op, std::vector<bool> &container);

/**
 * Instantiation for converting a Python tuple of int to a C++ std::vector<long>.
 *
 * @param op Python input as a tuple of int.
 * @param container C++ output as a std::vector<long>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_vector<long>(PyObject *op, std::vector<long> &container);

/**
 * Instantiation for converting a Python tuple of float to a C++ std::vector<double>.
 *
 * @param op Python input as a tuple of float.
 * @param container C++ output as a std::vector<double>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_vector<double>(PyObject *op, std::vector<double> &container);

/**
 * Instantiation for converting a Python tuple of str to a C++ std::vector<std::string>.
 *
 * @param op Python input as a tuple of str.
 * @param container C++ output as a std::vector<std::string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_vector<std::string>(PyObject *op, std::vector<std::string> &container);

//-------------------- END: Python tuple -> std::vector -------------------

//----------------------- std::vector -> Python list ----------------------
// Base declaration
/**
 * Base declaration for converting C++ std::vector to a Python list.
 *
 * @tparam T C++ type.
 * @param container C++ input as a std::vector<T>.
 * @return A Python list containing type corresponding to the C++ type T.
 */
template<typename T>
PyObject *
cpp_std_vector_to_py_list(const std::vector<T> &container);

// Instantiations
/**
 * Instantiation for converting C++ std::vector<bool> to a Python list of bool.
 *
 * @param container C++ input as a std::vector<bool>.
 * @return A Python list containing bool objects.
 */
template <>
PyObject *
cpp_std_vector_to_py_list<bool>(const std::vector<bool> &container);

/**
 * Instantiation for converting C++ std::vector<long> to a Python list of int.
 *
 * @param container C++ input as a std::vector<long>.
 * @return A Python list containing int objects.
 */
template <>
PyObject *
cpp_std_vector_to_py_list<long>(const std::vector<long> &container);

/**
 * Instantiation for converting C++ std::vector<double> to a Python list of float.
 *
 * @param container C++ input as a std::vector<double>.
 * @return A Python list containing float objects.
 */
template <>
PyObject *
cpp_std_vector_to_py_list<double>(const std::vector<double> &container);

/**
 * Instantiation for converting C++ std::vector<std::string> to a Python list of str.
 *
 * @param container C++ input as a std::vector<std::string>.
 * @return A Python list containing str objects.
 */
template <>
PyObject *
cpp_std_vector_to_py_list<std::string>(const std::vector<std::string> &container);

//-------------------- END: std::vector -> Python list --------------------

//----------------------- Python list -> std::vector ----------------------
// Base declaration
/**
 * Base declaration for converting a Python list to a C++ std::vector.
 *
 * @tparam T C++ type.
 * @param op The Python container to read from.
 * @param container The C++ std::vector to write to.
 * @return 0 on success, non-zero on failure.
 */
template<typename T>
int
py_list_to_cpp_std_vector(PyObject *op, std::vector<T> &container);

// Instantiations
/**
 * Instantiation for converting a Python list of bool to a C++ std::vector<bool>.
 *
 * @param op Python input as a list of bool.
 * @param container C++ output as a std::vector<bool>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_vector<bool>(PyObject *op, std::vector<bool> &container);

/**
 * Instantiation for converting a Python list of int to a C++ std::vector<long>.
 *
 * @param op Python input as a list of int.
 * @param container C++ output as a std::vector<long>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_vector<long>(PyObject *op, std::vector<long> &container);

/**
 * Instantiation for converting a Python list of float to a C++ std::vector<double>.
 *
 * @param op Python input as a list of float.
 * @param container C++ output as a std::vector<double>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_vector<double>(PyObject *op, std::vector<double> &container);

/**
 * Instantiation for converting a Python list of str to a C++ std::vector<std::string>.
 *
 * @param op Python input as a list of str.
 * @param container C++ output as a std::vector<std::string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_vector<std::string>(PyObject *op, std::vector<std::string> &container);

//-------------------- END: Python list -> std::vector --------------------

//-------------------- std::unordered_set -> Python set -------------------
// Base declaration
/**
 * Base declaration for converting C++ std::unordered_set to a Python set.
 *
 * @tparam T C++ type.
 * @param container C++ input as a std::unordered_set<T>.
 * @return A Python set containing type corresponding to the C++ type T.
 */
template<typename T>
PyObject *
cpp_std_unordered_set_to_py_set(const std::unordered_set<T> &container);

// Instantiations
/**
 * Instantiation for converting C++ std::unordered_set<bool> to a Python set of bool.
 *
 * @param container C++ input as a std::unordered_set<bool>.
 * @return A Python set containing bool objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_set<bool>(const std::unordered_set<bool> &container);

/**
 * Instantiation for converting C++ std::unordered_set<long> to a Python set of int.
 *
 * @param container C++ input as a std::unordered_set<long>.
 * @return A Python set containing int objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_set<long>(const std::unordered_set<long> &container);

/**
 * Instantiation for converting C++ std::unordered_set<double> to a Python set of float.
 *
 * @param container C++ input as a std::unordered_set<double>.
 * @return A Python set containing float objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_set<double>(const std::unordered_set<double> &container);

/**
 * Instantiation for converting C++ std::unordered_set<std::string> to a Python set of str.
 *
 * @param container C++ input as a std::unordered_set<std::string>.
 * @return A Python set containing str objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_set<std::string>(const std::unordered_set<std::string> &container);

//----------------- END: std::unordered_set -> Python set -----------------

//-------------------- Python set -> std::unordered_set -------------------
// Base declaration
/**
 * Base declaration for converting a Python set to a C++ std::unordered_set.
 *
 * @tparam T C++ type.
 * @param op The Python container to read from.
 * @param container The C++ std::unordered_set to write to.
 * @return 0 on success, non-zero on failure.
 */
template<typename T>
int
py_set_to_cpp_std_unordered_set(PyObject *op, std::unordered_set<T> &container);

// Instantiations
/**
 * Instantiation for converting a Python set of bool to a C++ std::unordered_set<bool>.
 *
 * @param op Python input as a set of bool.
 * @param container C++ output as a std::unordered_set<bool>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_set_to_cpp_std_unordered_set<bool>(PyObject *op, std::unordered_set<bool> &container);

/**
 * Instantiation for converting a Python set of int to a C++ std::unordered_set<long>.
 *
 * @param op Python input as a set of int.
 * @param container C++ output as a std::unordered_set<long>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_set_to_cpp_std_unordered_set<long>(PyObject *op, std::unordered_set<long> &container);

/**
 * Instantiation for converting a Python set of float to a C++ std::unordered_set<double>.
 *
 * @param op Python input as a set of float.
 * @param container C++ output as a std::unordered_set<double>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_set_to_cpp_std_unordered_set<double>(PyObject *op, std::unordered_set<double> &container);

/**
 * Instantiation for converting a Python set of str to a C++ std::unordered_set<std::string>.
 *
 * @param op Python input as a set of str.
 * @param container C++ output as a std::unordered_set<std::string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_set_to_cpp_std_unordered_set<std::string>(PyObject *op, std::unordered_set<std::string> &container);

//----------------- END: Python set -> std::unordered_set -----------------

//----------------- std::unordered_set -> Python frozenset ----------------
// Base declaration
/**
 * Base declaration for converting C++ std::unordered_set to a Python frozenset.
 *
 * @tparam T C++ type.
 * @param container C++ input as a std::unordered_set<T>.
 * @return A Python frozenset containing type corresponding to the C++ type T.
 */
template<typename T>
PyObject *
cpp_std_unordered_set_to_py_frozenset(const std::unordered_set<T> &container);

// Instantiations
/**
 * Instantiation for converting C++ std::unordered_set<bool> to a Python frozenset of bool.
 *
 * @param container C++ input as a std::unordered_set<bool>.
 * @return A Python frozenset containing bool objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<bool>(const std::unordered_set<bool> &container);

/**
 * Instantiation for converting C++ std::unordered_set<long> to a Python frozenset of int.
 *
 * @param container C++ input as a std::unordered_set<long>.
 * @return A Python frozenset containing int objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<long>(const std::unordered_set<long> &container);

/**
 * Instantiation for converting C++ std::unordered_set<double> to a Python frozenset of float.
 *
 * @param container C++ input as a std::unordered_set<double>.
 * @return A Python frozenset containing float objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<double>(const std::unordered_set<double> &container);

/**
 * Instantiation for converting C++ std::unordered_set<std::string> to a Python frozenset of str.
 *
 * @param container C++ input as a std::unordered_set<std::string>.
 * @return A Python frozenset containing str objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<std::string>(const std::unordered_set<std::string> &container);

//-------------- END: std::unordered_set -> Python frozenset --------------

//----------------- Python frozenset -> std::unordered_set ----------------
// Base declaration
/**
 * Base declaration for converting a Python frozenset to a C++ std::unordered_set.
 *
 * @tparam T C++ type.
 * @param op The Python container to read from.
 * @param container The C++ std::unordered_set to write to.
 * @return 0 on success, non-zero on failure.
 */
template<typename T>
int
py_frozenset_to_cpp_std_unordered_set(PyObject *op, std::unordered_set<T> &container);

// Instantiations
/**
 * Instantiation for converting a Python frozenset of bool to a C++ std::unordered_set<bool>.
 *
 * @param op Python input as a frozenset of bool.
 * @param container C++ output as a std::unordered_set<bool>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_frozenset_to_cpp_std_unordered_set<bool>(PyObject *op, std::unordered_set<bool> &container);

/**
 * Instantiation for converting a Python frozenset of int to a C++ std::unordered_set<long>.
 *
 * @param op Python input as a frozenset of int.
 * @param container C++ output as a std::unordered_set<long>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_frozenset_to_cpp_std_unordered_set<long>(PyObject *op, std::unordered_set<long> &container);

/**
 * Instantiation for converting a Python frozenset of float to a C++ std::unordered_set<double>.
 *
 * @param op Python input as a frozenset of float.
 * @param container C++ output as a std::unordered_set<double>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_frozenset_to_cpp_std_unordered_set<double>(PyObject *op, std::unordered_set<double> &container);

/**
 * Instantiation for converting a Python frozenset of str to a C++ std::unordered_set<std::string>.
 *
 * @param op Python input as a frozenset of str.
 * @param container C++ output as a std::unordered_set<std::string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_frozenset_to_cpp_std_unordered_set<std::string>(PyObject *op, std::unordered_set<std::string> &container);

//-------------- END: Python frozenset -> std::unordered_set --------------

//************* END: Unary collections <-> Python collections *************

//******************* std::unordered_map <-> Python dict ******************
//------------------- std::unordered_map -> Python dict -------------------
// Base declaration
/**
 * Base declaration for converting a C++ std::unordered_map<K, V> to a Python dictionary.
 *
 * @tparam K The C++ type for the key.
 * @tparam V The C++ type for the value.
 * @param map Input C++ std::unordered_map<K, V>.
 * @return Python dictionary corresponding to {K : V, ...}.
 */
template<typename K, typename V>
PyObject *
cpp_std_unordered_map_to_py_dict(const std::unordered_map<K, V> &map);

// Instantiations
/**
 * Instantiation for converting a C++ std::unordered_map<bool, bool> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<bool, bool>.
 * @return A Python dictionary of {bool : bool, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, bool>(const std::unordered_map<bool, bool> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<bool, long> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<bool, long>.
 * @return A Python dictionary of {bool : int, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, long>(const std::unordered_map<bool, long> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<bool, double> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<bool, double>.
 * @return A Python dictionary of {bool : float, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, double>(const std::unordered_map<bool, double> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<bool, std::string> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<bool, std::string>.
 * @return A Python dictionary of {bool : str, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<bool, std::string>(const std::unordered_map<bool, std::string> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<long, bool> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<long, bool>.
 * @return A Python dictionary of {int : bool, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, bool>(const std::unordered_map<long, bool> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<long, long> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<long, long>.
 * @return A Python dictionary of {int : int, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, long>(const std::unordered_map<long, long> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<long, double> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<long, double>.
 * @return A Python dictionary of {int : float, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, double>(const std::unordered_map<long, double> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<long, std::string> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<long, std::string>.
 * @return A Python dictionary of {int : str, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<long, std::string>(const std::unordered_map<long, std::string> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<double, bool> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<double, bool>.
 * @return A Python dictionary of {float : bool, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, bool>(const std::unordered_map<double, bool> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<double, long> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<double, long>.
 * @return A Python dictionary of {float : int, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, long>(const std::unordered_map<double, long> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<double, double> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<double, double>.
 * @return A Python dictionary of {float : float, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, double>(const std::unordered_map<double, double> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<double, std::string> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<double, std::string>.
 * @return A Python dictionary of {float : str, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<double, std::string>(const std::unordered_map<double, std::string> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<std::string, bool> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<std::string, bool>.
 * @return A Python dictionary of {str : bool, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::string, bool>(const std::unordered_map<std::string, bool> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<std::string, long> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<std::string, long>.
 * @return A Python dictionary of {str : int, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::string, long>(const std::unordered_map<std::string, long> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<std::string, double> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<std::string, double>.
 * @return A Python dictionary of {str : float, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::string, double>(const std::unordered_map<std::string, double> &map);

/**
 * Instantiation for converting a C++ std::unordered_map<std::string, std::string> to a Python dictionary.
 *
 * @param map Input C++ std::unordered_map<std::string, std::string>.
 * @return A Python dictionary of {str : str, ...}.
 */
template <>
PyObject *
cpp_std_unordered_map_to_py_dict<std::string, std::string>(const std::unordered_map<std::string, std::string> &map);

//----------------- END: std::unordered_map -> Python dict ----------------

//------------------- Python dict -> std::unordered_map -------------------
// Base declaration
/**
 * Base declaration for converting a Python dictionary to a C++ std::unordered_map<K, V>.
 *
 * @tparam K The C++ type for the key.
 * @tparam V The C++ type for the value.
 * @param op The Python dictionary as the input.
 * @param map C++ std::unordered_map<K, V> to write to.
 * @return 0 on success, non-zero on failure.
 */
template<typename K, typename V>
int 
py_dict_to_cpp_std_unordered_map(PyObject *op, std::unordered_map<K, V> &map);

// Instantiations
/**
 * Instantiation for converting a Python dictionary {bool : bool, ...} to a C++ std::unordered_map<bool, bool>.
 *
 * @param op A Python dictionary of {bool : bool, ...} as the input.
 * @param map The C++ std::unordered_map<bool, bool> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<bool, bool>(PyObject* op, std::unordered_map<bool, bool> &map);

/**
 * Instantiation for converting a Python dictionary {bool : int, ...} to a C++ std::unordered_map<bool, long>.
 *
 * @param op A Python dictionary of {bool : int, ...} as the input.
 * @param map The C++ std::unordered_map<bool, long> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<bool, long>(PyObject* op, std::unordered_map<bool, long> &map);

/**
 * Instantiation for converting a Python dictionary {bool : float, ...} to a C++ std::unordered_map<bool, double>.
 *
 * @param op A Python dictionary of {bool : float, ...} as the input.
 * @param map The C++ std::unordered_map<bool, double> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<bool, double>(PyObject* op, std::unordered_map<bool, double> &map);

/**
 * Instantiation for converting a Python dictionary {bool : str, ...} to a C++ std::unordered_map<bool, std::string>.
 *
 * @param op A Python dictionary of {bool : str, ...} as the input.
 * @param map The C++ std::unordered_map<bool, std::string> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<bool, std::string>(PyObject* op, std::unordered_map<bool, std::string> &map);

/**
 * Instantiation for converting a Python dictionary {int : bool, ...} to a C++ std::unordered_map<long, bool>.
 *
 * @param op A Python dictionary of {int : bool, ...} as the input.
 * @param map The C++ std::unordered_map<long, bool> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<long, bool>(PyObject* op, std::unordered_map<long, bool> &map);

/**
 * Instantiation for converting a Python dictionary {int : int, ...} to a C++ std::unordered_map<long, long>.
 *
 * @param op A Python dictionary of {int : int, ...} as the input.
 * @param map The C++ std::unordered_map<long, long> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<long, long>(PyObject* op, std::unordered_map<long, long> &map);

/**
 * Instantiation for converting a Python dictionary {int : float, ...} to a C++ std::unordered_map<long, double>.
 *
 * @param op A Python dictionary of {int : float, ...} as the input.
 * @param map The C++ std::unordered_map<long, double> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<long, double>(PyObject* op, std::unordered_map<long, double> &map);

/**
 * Instantiation for converting a Python dictionary {int : str, ...} to a C++ std::unordered_map<long, std::string>.
 *
 * @param op A Python dictionary of {int : str, ...} as the input.
 * @param map The C++ std::unordered_map<long, std::string> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<long, std::string>(PyObject* op, std::unordered_map<long, std::string> &map);

/**
 * Instantiation for converting a Python dictionary {float : bool, ...} to a C++ std::unordered_map<double, bool>.
 *
 * @param op A Python dictionary of {float : bool, ...} as the input.
 * @param map The C++ std::unordered_map<double, bool> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<double, bool>(PyObject* op, std::unordered_map<double, bool> &map);

/**
 * Instantiation for converting a Python dictionary {float : int, ...} to a C++ std::unordered_map<double, long>.
 *
 * @param op A Python dictionary of {float : int, ...} as the input.
 * @param map The C++ std::unordered_map<double, long> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<double, long>(PyObject* op, std::unordered_map<double, long> &map);

/**
 * Instantiation for converting a Python dictionary {float : float, ...} to a C++ std::unordered_map<double, double>.
 *
 * @param op A Python dictionary of {float : float, ...} as the input.
 * @param map The C++ std::unordered_map<double, double> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<double, double>(PyObject* op, std::unordered_map<double, double> &map);

/**
 * Instantiation for converting a Python dictionary {float : str, ...} to a C++ std::unordered_map<double, std::string>.
 *
 * @param op A Python dictionary of {float : str, ...} as the input.
 * @param map The C++ std::unordered_map<double, std::string> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<double, std::string>(PyObject* op, std::unordered_map<double, std::string> &map);

/**
 * Instantiation for converting a Python dictionary {str : bool, ...} to a C++ std::unordered_map<std::string, bool>.
 *
 * @param op A Python dictionary of {str : bool, ...} as the input.
 * @param map The C++ std::unordered_map<std::string, bool> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<std::string, bool>(PyObject* op, std::unordered_map<std::string, bool> &map);

/**
 * Instantiation for converting a Python dictionary {str : int, ...} to a C++ std::unordered_map<std::string, long>.
 *
 * @param op A Python dictionary of {str : int, ...} as the input.
 * @param map The C++ std::unordered_map<std::string, long> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<std::string, long>(PyObject* op, std::unordered_map<std::string, long> &map);

/**
 * Instantiation for converting a Python dictionary {str : float, ...} to a C++ std::unordered_map<std::string, double>.
 *
 * @param op A Python dictionary of {str : float, ...} as the input.
 * @param map The C++ std::unordered_map<std::string, double> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_unordered_map<std::string, double>(PyObject* op, std::unordered_map<std::string, double> &map);

/**
 * Instantiation for converting a Python dictionary {str : str, ...} to a C++ std::unordered_map<std::string, std::string>.
 *
 * @param op A Python dictionary of {str : str, ...} as the input.
 * @param map The C++ std::unordered_map<std::string, std::string> to write to.
 * @return 0 on success, non-zero on failure.
 */
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

