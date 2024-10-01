#ifndef PY_CPP_CONTAINERS_AUTO_PY_CONVERT_INTERNAL_H
#define PY_CPP_CONTAINERS_AUTO_PY_CONVERT_INTERNAL_H
//============================ Declaration file ===========================
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
// UnaryFunctions(python_container='tuple', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::vector<std::u16string>
// UnaryFunctions(python_container='tuple', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::vector<std::u32string>
// 
// tuple:
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<bool>
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<long>
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<double>
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<std::complex<double>>
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<std::vector<char>>
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<std::string>
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<std::u16string>
// UnaryFunctions(python_container='tuple', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_tuple', decl_to_cpp='py_tuple_to_cpp_std_list_like') <-> std::list<std::u32string>
// 
// list:
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<bool>
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<long>
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<double>
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<std::complex<double>>
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<std::vector<char>>
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<std::string>
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<std::u16string>
// UnaryFunctions(python_container='list', cpp_container='std::vector', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::vector<std::u32string>
// 
// list:
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<bool>
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<long>
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<double>
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<std::complex<double>>
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<std::vector<char>>
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<std::string>
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<std::u16string>
// UnaryFunctions(python_container='list', cpp_container='std::list', decl_to_py='cpp_std_list_like_to_py_list', decl_to_cpp='py_list_to_cpp_std_list_like') <-> std::list<std::u32string>
// 
// set:
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<bool>
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<long>
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<double>
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<std::complex<double>>
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<std::vector<char>>
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<std::string>
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<std::u16string>
// UnaryFunctions(python_container='set', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_set', decl_to_cpp='py_set_to_cpp_std_unordered_set') <-> std::unordered_set<std::u32string>
// 
// frozenset:
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<bool>
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<long>
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<double>
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<std::complex<double>>
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<std::vector<char>>
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<std::string>
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<std::u16string>
// UnaryFunctions(python_container='frozenset', cpp_container='std::unordered_set', decl_to_py='cpp_std_unordered_set_to_py_frozenset', decl_to_cpp='py_frozenset_to_cpp_std_unordered_set') <-> std::unordered_set<std::u32string>
// 
// 
// Mapping conversions
// dict <-> std::unordered_map<bool, bool>
// dict <-> std::unordered_map<bool, long>
// dict <-> std::unordered_map<bool, double>
// dict <-> std::unordered_map<bool, std::complex<double>>
// dict <-> std::unordered_map<bool, std::vector<char>>
// dict <-> std::unordered_map<bool, std::string>
// dict <-> std::unordered_map<bool, std::u16string>
// dict <-> std::unordered_map<bool, std::u32string>
// dict <-> std::unordered_map<long, bool>
// dict <-> std::unordered_map<long, long>
// dict <-> std::unordered_map<long, double>
// dict <-> std::unordered_map<long, std::complex<double>>
// dict <-> std::unordered_map<long, std::vector<char>>
// dict <-> std::unordered_map<long, std::string>
// dict <-> std::unordered_map<long, std::u16string>
// dict <-> std::unordered_map<long, std::u32string>
// dict <-> std::unordered_map<double, bool>
// dict <-> std::unordered_map<double, long>
// dict <-> std::unordered_map<double, double>
// dict <-> std::unordered_map<double, std::complex<double>>
// dict <-> std::unordered_map<double, std::vector<char>>
// dict <-> std::unordered_map<double, std::string>
// dict <-> std::unordered_map<double, std::u16string>
// dict <-> std::unordered_map<double, std::u32string>
// dict <-> std::unordered_map<std::complex<double>, bool>
// dict <-> std::unordered_map<std::complex<double>, long>
// dict <-> std::unordered_map<std::complex<double>, double>
// dict <-> std::unordered_map<std::complex<double>, std::complex<double>>
// dict <-> std::unordered_map<std::complex<double>, std::vector<char>>
// dict <-> std::unordered_map<std::complex<double>, std::string>
// dict <-> std::unordered_map<std::complex<double>, std::u16string>
// dict <-> std::unordered_map<std::complex<double>, std::u32string>
// dict <-> std::unordered_map<std::vector<char>, bool>
// dict <-> std::unordered_map<std::vector<char>, long>
// dict <-> std::unordered_map<std::vector<char>, double>
// dict <-> std::unordered_map<std::vector<char>, std::complex<double>>
// dict <-> std::unordered_map<std::vector<char>, std::vector<char>>
// dict <-> std::unordered_map<std::vector<char>, std::string>
// dict <-> std::unordered_map<std::vector<char>, std::u16string>
// dict <-> std::unordered_map<std::vector<char>, std::u32string>
// dict <-> std::unordered_map<std::string, bool>
// dict <-> std::unordered_map<std::string, long>
// dict <-> std::unordered_map<std::string, double>
// dict <-> std::unordered_map<std::string, std::complex<double>>
// dict <-> std::unordered_map<std::string, std::vector<char>>
// dict <-> std::unordered_map<std::string, std::string>
// dict <-> std::unordered_map<std::string, std::u16string>
// dict <-> std::unordered_map<std::string, std::u32string>
// dict <-> std::unordered_map<std::u16string, bool>
// dict <-> std::unordered_map<std::u16string, long>
// dict <-> std::unordered_map<std::u16string, double>
// dict <-> std::unordered_map<std::u16string, std::complex<double>>
// dict <-> std::unordered_map<std::u16string, std::vector<char>>
// dict <-> std::unordered_map<std::u16string, std::string>
// dict <-> std::unordered_map<std::u16string, std::u16string>
// dict <-> std::unordered_map<std::u16string, std::u32string>
// dict <-> std::unordered_map<std::u32string, bool>
// dict <-> std::unordered_map<std::u32string, long>
// dict <-> std::unordered_map<std::u32string, double>
// dict <-> std::unordered_map<std::u32string, std::complex<double>>
// dict <-> std::unordered_map<std::u32string, std::vector<char>>
// dict <-> std::unordered_map<std::u32string, std::string>
// dict <-> std::unordered_map<std::u32string, std::u16string>
// dict <-> std::unordered_map<std::u32string, std::u32string>
// 
#include <Python.h>


namespace Python_Cpp_Containers {


//**************** Unary collections <-> Python collections ***************
//---------------------- std::vector -> Python tuple ----------------------
// Base declaration
/**
 * Base declaration for converting C++ \c std::vector to a Python \c tuple.
 *
 * @tparam T C++ type.
 * @param container C++ input as a \c std::vector<T>.
 * @return A Python \c tuple containing type corresponding to the C++ type \c T.
 */
template<typename T>
PyObject *
cpp_std_list_like_to_py_tuple(const std::vector<T> &container);

// Instantiations
/**
 * Instantiation for converting C++ \c std::vector<bool> to a Python \c tuple of \c bool.
 *
 * @param container C++ input as a \c std::vector<bool>.
 * @return A Python \c tuple containing \c bool objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<bool>(const std::vector<bool> &container);

/**
 * Instantiation for converting C++ \c std::vector<long> to a Python \c tuple of \c int.
 *
 * @param container C++ input as a \c std::vector<long>.
 * @return A Python \c tuple containing \c int objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<long>(const std::vector<long> &container);

/**
 * Instantiation for converting C++ \c std::vector<double> to a Python \c tuple of \c float.
 *
 * @param container C++ input as a \c std::vector<double>.
 * @return A Python \c tuple containing \c float objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<double>(const std::vector<double> &container);

/**
 * Instantiation for converting C++ \c std::vector<std::complex<double>> to a Python \c tuple of \c complex.
 *
 * @param container C++ input as a \c std::vector<std::complex<double>>.
 * @return A Python \c tuple containing \c complex objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::complex<double>>(const std::vector<std::complex<double>> &container);

/**
 * Instantiation for converting C++ \c std::vector<std::vector<char>> to a Python \c tuple of \c bytes.
 *
 * @param container C++ input as a \c std::vector<std::vector<char>>.
 * @return A Python \c tuple containing \c bytes objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::vector<char>>(const std::vector<std::vector<char>> &container);

/**
 * Instantiation for converting C++ \c std::vector<std::string> to a Python \c tuple of \c str.
 *
 * @param container C++ input as a \c std::vector<std::string>.
 * @return A Python \c tuple containing \c str objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::string>(const std::vector<std::string> &container);

/**
 * Instantiation for converting C++ \c std::vector<std::u16string> to a Python \c tuple of \c str.
 *
 * @param container C++ input as a \c std::vector<std::u16string>.
 * @return A Python \c tuple containing \c str objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::u16string>(const std::vector<std::u16string> &container);

/**
 * Instantiation for converting C++ \c std::vector<std::u32string> to a Python \c tuple of \c str.
 *
 * @param container C++ input as a \c std::vector<std::u32string>.
 * @return A Python \c tuple containing \c str objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::u32string>(const std::vector<std::u32string> &container);

//-------------------- END: std::vector -> Python tuple -------------------

//---------------------- Python tuple -> std::vector ----------------------
// Base declaration
/**
 * Base declaration for converting a Python \c tuple to a C++ \c std::vector.
 *
 * @tparam T C++ type.
 * @param op The Python container to read from.
 * @param container The C++ \c std::vector to write to.
 * @return 0 on success, non-zero on failure.
 */
template<typename T>
int
py_tuple_to_cpp_std_list_like(PyObject *op, std::vector<T> &container);

// Instantiations
/**
 * Instantiation for converting a Python \c tuple of \c bool to a C++ \c std::vector<bool>.
 *
 * @param op Python input as a \c tuple of \c bool.
 * @param container C++ output as a \c std::vector<bool>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<bool>(PyObject *op, std::vector<bool> &container);

/**
 * Instantiation for converting a Python \c tuple of \c int to a C++ \c std::vector<long>.
 *
 * @param op Python input as a \c tuple of \c int.
 * @param container C++ output as a \c std::vector<long>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<long>(PyObject *op, std::vector<long> &container);

/**
 * Instantiation for converting a Python \c tuple of \c float to a C++ \c std::vector<double>.
 *
 * @param op Python input as a \c tuple of \c float.
 * @param container C++ output as a \c std::vector<double>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<double>(PyObject *op, std::vector<double> &container);

/**
 * Instantiation for converting a Python \c tuple of \c complex to a C++ \c std::vector<std::complex<double>>.
 *
 * @param op Python input as a \c tuple of \c complex.
 * @param container C++ output as a \c std::vector<std::complex<double>>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<std::complex<double>>(PyObject *op, std::vector<std::complex<double>> &container);

/**
 * Instantiation for converting a Python \c tuple of \c bytes to a C++ \c std::vector<std::vector<char>>.
 *
 * @param op Python input as a \c tuple of \c bytes.
 * @param container C++ output as a \c std::vector<std::vector<char>>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<std::vector<char>>(PyObject *op, std::vector<std::vector<char>> &container);

/**
 * Instantiation for converting a Python \c tuple of \c str to a C++ \c std::vector<std::string>.
 *
 * @param op Python input as a \c tuple of \c str.
 * @param container C++ output as a \c std::vector<std::string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<std::string>(PyObject *op, std::vector<std::string> &container);

/**
 * Instantiation for converting a Python \c tuple of \c str to a C++ \c std::vector<std::u16string>.
 *
 * @param op Python input as a \c tuple of \c str.
 * @param container C++ output as a \c std::vector<std::u16string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<std::u16string>(PyObject *op, std::vector<std::u16string> &container);

/**
 * Instantiation for converting a Python \c tuple of \c str to a C++ \c std::vector<std::u32string>.
 *
 * @param op Python input as a \c tuple of \c str.
 * @param container C++ output as a \c std::vector<std::u32string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<std::u32string>(PyObject *op, std::vector<std::u32string> &container);

//-------------------- END: Python tuple -> std::vector -------------------

//----------------------- std::list -> Python tuple -----------------------
// Base declaration
/**
 * Base declaration for converting C++ \c std::list to a Python \c tuple.
 *
 * @tparam T C++ type.
 * @param container C++ input as a \c std::list<T>.
 * @return A Python \c tuple containing type corresponding to the C++ type \c T.
 */
template<typename T>
PyObject *
cpp_std_list_like_to_py_tuple(const std::list<T> &container);

// Instantiations
/**
 * Instantiation for converting C++ \c std::list<bool> to a Python \c tuple of \c bool.
 *
 * @param container C++ input as a \c std::list<bool>.
 * @return A Python \c tuple containing \c bool objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<bool>(const std::list<bool> &container);

/**
 * Instantiation for converting C++ \c std::list<long> to a Python \c tuple of \c int.
 *
 * @param container C++ input as a \c std::list<long>.
 * @return A Python \c tuple containing \c int objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<long>(const std::list<long> &container);

/**
 * Instantiation for converting C++ \c std::list<double> to a Python \c tuple of \c float.
 *
 * @param container C++ input as a \c std::list<double>.
 * @return A Python \c tuple containing \c float objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<double>(const std::list<double> &container);

/**
 * Instantiation for converting C++ \c std::list<std::complex<double>> to a Python \c tuple of \c complex.
 *
 * @param container C++ input as a \c std::list<std::complex<double>>.
 * @return A Python \c tuple containing \c complex objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::complex<double>>(const std::list<std::complex<double>> &container);

/**
 * Instantiation for converting C++ \c std::list<std::vector<char>> to a Python \c tuple of \c bytes.
 *
 * @param container C++ input as a \c std::list<std::vector<char>>.
 * @return A Python \c tuple containing \c bytes objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::vector<char>>(const std::list<std::vector<char>> &container);

/**
 * Instantiation for converting C++ \c std::list<std::string> to a Python \c tuple of \c str.
 *
 * @param container C++ input as a \c std::list<std::string>.
 * @return A Python \c tuple containing \c str objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::string>(const std::list<std::string> &container);

/**
 * Instantiation for converting C++ \c std::list<std::u16string> to a Python \c tuple of \c str.
 *
 * @param container C++ input as a \c std::list<std::u16string>.
 * @return A Python \c tuple containing \c str objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::u16string>(const std::list<std::u16string> &container);

/**
 * Instantiation for converting C++ \c std::list<std::u32string> to a Python \c tuple of \c str.
 *
 * @param container C++ input as a \c std::list<std::u32string>.
 * @return A Python \c tuple containing \c str objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_tuple<std::u32string>(const std::list<std::u32string> &container);

//--------------------- END: std::list -> Python tuple --------------------

//----------------------- Python tuple -> std::list -----------------------
// Base declaration
/**
 * Base declaration for converting a Python \c tuple to a C++ \c std::list.
 *
 * @tparam T C++ type.
 * @param op The Python container to read from.
 * @param container The C++ \c std::list to write to.
 * @return 0 on success, non-zero on failure.
 */
template<typename T>
int
py_tuple_to_cpp_std_list_like(PyObject *op, std::list<T> &container);

// Instantiations
/**
 * Instantiation for converting a Python \c tuple of \c bool to a C++ \c std::list<bool>.
 *
 * @param op Python input as a \c tuple of \c bool.
 * @param container C++ output as a \c std::list<bool>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<bool>(PyObject *op, std::list<bool> &container);

/**
 * Instantiation for converting a Python \c tuple of \c int to a C++ \c std::list<long>.
 *
 * @param op Python input as a \c tuple of \c int.
 * @param container C++ output as a \c std::list<long>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<long>(PyObject *op, std::list<long> &container);

/**
 * Instantiation for converting a Python \c tuple of \c float to a C++ \c std::list<double>.
 *
 * @param op Python input as a \c tuple of \c float.
 * @param container C++ output as a \c std::list<double>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<double>(PyObject *op, std::list<double> &container);

/**
 * Instantiation for converting a Python \c tuple of \c complex to a C++ \c std::list<std::complex<double>>.
 *
 * @param op Python input as a \c tuple of \c complex.
 * @param container C++ output as a \c std::list<std::complex<double>>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<std::complex<double>>(PyObject *op, std::list<std::complex<double>> &container);

/**
 * Instantiation for converting a Python \c tuple of \c bytes to a C++ \c std::list<std::vector<char>>.
 *
 * @param op Python input as a \c tuple of \c bytes.
 * @param container C++ output as a \c std::list<std::vector<char>>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<std::vector<char>>(PyObject *op, std::list<std::vector<char>> &container);

/**
 * Instantiation for converting a Python \c tuple of \c str to a C++ \c std::list<std::string>.
 *
 * @param op Python input as a \c tuple of \c str.
 * @param container C++ output as a \c std::list<std::string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<std::string>(PyObject *op, std::list<std::string> &container);

/**
 * Instantiation for converting a Python \c tuple of \c str to a C++ \c std::list<std::u16string>.
 *
 * @param op Python input as a \c tuple of \c str.
 * @param container C++ output as a \c std::list<std::u16string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<std::u16string>(PyObject *op, std::list<std::u16string> &container);

/**
 * Instantiation for converting a Python \c tuple of \c str to a C++ \c std::list<std::u32string>.
 *
 * @param op Python input as a \c tuple of \c str.
 * @param container C++ output as a \c std::list<std::u32string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_tuple_to_cpp_std_list_like<std::u32string>(PyObject *op, std::list<std::u32string> &container);

//--------------------- END: Python tuple -> std::list --------------------

//----------------------- std::vector -> Python list ----------------------
// Base declaration
/**
 * Base declaration for converting C++ \c std::vector to a Python \c list.
 *
 * @tparam T C++ type.
 * @param container C++ input as a \c std::vector<T>.
 * @return A Python \c list containing type corresponding to the C++ type \c T.
 */
template<typename T>
PyObject *
cpp_std_list_like_to_py_list(const std::vector<T> &container);

// Instantiations
/**
 * Instantiation for converting C++ \c std::vector<bool> to a Python \c list of \c bool.
 *
 * @param container C++ input as a \c std::vector<bool>.
 * @return A Python \c list containing \c bool objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<bool>(const std::vector<bool> &container);

/**
 * Instantiation for converting C++ \c std::vector<long> to a Python \c list of \c int.
 *
 * @param container C++ input as a \c std::vector<long>.
 * @return A Python \c list containing \c int objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<long>(const std::vector<long> &container);

/**
 * Instantiation for converting C++ \c std::vector<double> to a Python \c list of \c float.
 *
 * @param container C++ input as a \c std::vector<double>.
 * @return A Python \c list containing \c float objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<double>(const std::vector<double> &container);

/**
 * Instantiation for converting C++ \c std::vector<std::complex<double>> to a Python \c list of \c complex.
 *
 * @param container C++ input as a \c std::vector<std::complex<double>>.
 * @return A Python \c list containing \c complex objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<std::complex<double>>(const std::vector<std::complex<double>> &container);

/**
 * Instantiation for converting C++ \c std::vector<std::vector<char>> to a Python \c list of \c bytes.
 *
 * @param container C++ input as a \c std::vector<std::vector<char>>.
 * @return A Python \c list containing \c bytes objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<std::vector<char>>(const std::vector<std::vector<char>> &container);

/**
 * Instantiation for converting C++ \c std::vector<std::string> to a Python \c list of \c str.
 *
 * @param container C++ input as a \c std::vector<std::string>.
 * @return A Python \c list containing \c str objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<std::string>(const std::vector<std::string> &container);

/**
 * Instantiation for converting C++ \c std::vector<std::u16string> to a Python \c list of \c str.
 *
 * @param container C++ input as a \c std::vector<std::u16string>.
 * @return A Python \c list containing \c str objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<std::u16string>(const std::vector<std::u16string> &container);

/**
 * Instantiation for converting C++ \c std::vector<std::u32string> to a Python \c list of \c str.
 *
 * @param container C++ input as a \c std::vector<std::u32string>.
 * @return A Python \c list containing \c str objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<std::u32string>(const std::vector<std::u32string> &container);

//-------------------- END: std::vector -> Python list --------------------

//----------------------- Python list -> std::vector ----------------------
// Base declaration
/**
 * Base declaration for converting a Python \c list to a C++ \c std::vector.
 *
 * @tparam T C++ type.
 * @param op The Python container to read from.
 * @param container The C++ \c std::vector to write to.
 * @return 0 on success, non-zero on failure.
 */
template<typename T>
int
py_list_to_cpp_std_list_like(PyObject *op, std::vector<T> &container);

// Instantiations
/**
 * Instantiation for converting a Python \c list of \c bool to a C++ \c std::vector<bool>.
 *
 * @param op Python input as a \c list of \c bool.
 * @param container C++ output as a \c std::vector<bool>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<bool>(PyObject *op, std::vector<bool> &container);

/**
 * Instantiation for converting a Python \c list of \c int to a C++ \c std::vector<long>.
 *
 * @param op Python input as a \c list of \c int.
 * @param container C++ output as a \c std::vector<long>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<long>(PyObject *op, std::vector<long> &container);

/**
 * Instantiation for converting a Python \c list of \c float to a C++ \c std::vector<double>.
 *
 * @param op Python input as a \c list of \c float.
 * @param container C++ output as a \c std::vector<double>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<double>(PyObject *op, std::vector<double> &container);

/**
 * Instantiation for converting a Python \c list of \c complex to a C++ \c std::vector<std::complex<double>>.
 *
 * @param op Python input as a \c list of \c complex.
 * @param container C++ output as a \c std::vector<std::complex<double>>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<std::complex<double>>(PyObject *op, std::vector<std::complex<double>> &container);

/**
 * Instantiation for converting a Python \c list of \c bytes to a C++ \c std::vector<std::vector<char>>.
 *
 * @param op Python input as a \c list of \c bytes.
 * @param container C++ output as a \c std::vector<std::vector<char>>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<std::vector<char>>(PyObject *op, std::vector<std::vector<char>> &container);

/**
 * Instantiation for converting a Python \c list of \c str to a C++ \c std::vector<std::string>.
 *
 * @param op Python input as a \c list of \c str.
 * @param container C++ output as a \c std::vector<std::string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<std::string>(PyObject *op, std::vector<std::string> &container);

/**
 * Instantiation for converting a Python \c list of \c str to a C++ \c std::vector<std::u16string>.
 *
 * @param op Python input as a \c list of \c str.
 * @param container C++ output as a \c std::vector<std::u16string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<std::u16string>(PyObject *op, std::vector<std::u16string> &container);

/**
 * Instantiation for converting a Python \c list of \c str to a C++ \c std::vector<std::u32string>.
 *
 * @param op Python input as a \c list of \c str.
 * @param container C++ output as a \c std::vector<std::u32string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<std::u32string>(PyObject *op, std::vector<std::u32string> &container);

//-------------------- END: Python list -> std::vector --------------------

//------------------------ std::list -> Python list -----------------------
// Base declaration
/**
 * Base declaration for converting C++ \c std::list to a Python \c list.
 *
 * @tparam T C++ type.
 * @param container C++ input as a \c std::list<T>.
 * @return A Python \c list containing type corresponding to the C++ type \c T.
 */
template<typename T>
PyObject *
cpp_std_list_like_to_py_list(const std::list<T> &container);

// Instantiations
/**
 * Instantiation for converting C++ \c std::list<bool> to a Python \c list of \c bool.
 *
 * @param container C++ input as a \c std::list<bool>.
 * @return A Python \c list containing \c bool objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<bool>(const std::list<bool> &container);

/**
 * Instantiation for converting C++ \c std::list<long> to a Python \c list of \c int.
 *
 * @param container C++ input as a \c std::list<long>.
 * @return A Python \c list containing \c int objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<long>(const std::list<long> &container);

/**
 * Instantiation for converting C++ \c std::list<double> to a Python \c list of \c float.
 *
 * @param container C++ input as a \c std::list<double>.
 * @return A Python \c list containing \c float objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<double>(const std::list<double> &container);

/**
 * Instantiation for converting C++ \c std::list<std::complex<double>> to a Python \c list of \c complex.
 *
 * @param container C++ input as a \c std::list<std::complex<double>>.
 * @return A Python \c list containing \c complex objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<std::complex<double>>(const std::list<std::complex<double>> &container);

/**
 * Instantiation for converting C++ \c std::list<std::vector<char>> to a Python \c list of \c bytes.
 *
 * @param container C++ input as a \c std::list<std::vector<char>>.
 * @return A Python \c list containing \c bytes objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<std::vector<char>>(const std::list<std::vector<char>> &container);

/**
 * Instantiation for converting C++ \c std::list<std::string> to a Python \c list of \c str.
 *
 * @param container C++ input as a \c std::list<std::string>.
 * @return A Python \c list containing \c str objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<std::string>(const std::list<std::string> &container);

/**
 * Instantiation for converting C++ \c std::list<std::u16string> to a Python \c list of \c str.
 *
 * @param container C++ input as a \c std::list<std::u16string>.
 * @return A Python \c list containing \c str objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<std::u16string>(const std::list<std::u16string> &container);

/**
 * Instantiation for converting C++ \c std::list<std::u32string> to a Python \c list of \c str.
 *
 * @param container C++ input as a \c std::list<std::u32string>.
 * @return A Python \c list containing \c str objects.
 */
template <>
PyObject *
cpp_std_list_like_to_py_list<std::u32string>(const std::list<std::u32string> &container);

//--------------------- END: std::list -> Python list ---------------------

//------------------------ Python list -> std::list -----------------------
// Base declaration
/**
 * Base declaration for converting a Python \c list to a C++ \c std::list.
 *
 * @tparam T C++ type.
 * @param op The Python container to read from.
 * @param container The C++ \c std::list to write to.
 * @return 0 on success, non-zero on failure.
 */
template<typename T>
int
py_list_to_cpp_std_list_like(PyObject *op, std::list<T> &container);

// Instantiations
/**
 * Instantiation for converting a Python \c list of \c bool to a C++ \c std::list<bool>.
 *
 * @param op Python input as a \c list of \c bool.
 * @param container C++ output as a \c std::list<bool>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<bool>(PyObject *op, std::list<bool> &container);

/**
 * Instantiation for converting a Python \c list of \c int to a C++ \c std::list<long>.
 *
 * @param op Python input as a \c list of \c int.
 * @param container C++ output as a \c std::list<long>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<long>(PyObject *op, std::list<long> &container);

/**
 * Instantiation for converting a Python \c list of \c float to a C++ \c std::list<double>.
 *
 * @param op Python input as a \c list of \c float.
 * @param container C++ output as a \c std::list<double>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<double>(PyObject *op, std::list<double> &container);

/**
 * Instantiation for converting a Python \c list of \c complex to a C++ \c std::list<std::complex<double>>.
 *
 * @param op Python input as a \c list of \c complex.
 * @param container C++ output as a \c std::list<std::complex<double>>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<std::complex<double>>(PyObject *op, std::list<std::complex<double>> &container);

/**
 * Instantiation for converting a Python \c list of \c bytes to a C++ \c std::list<std::vector<char>>.
 *
 * @param op Python input as a \c list of \c bytes.
 * @param container C++ output as a \c std::list<std::vector<char>>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<std::vector<char>>(PyObject *op, std::list<std::vector<char>> &container);

/**
 * Instantiation for converting a Python \c list of \c str to a C++ \c std::list<std::string>.
 *
 * @param op Python input as a \c list of \c str.
 * @param container C++ output as a \c std::list<std::string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<std::string>(PyObject *op, std::list<std::string> &container);

/**
 * Instantiation for converting a Python \c list of \c str to a C++ \c std::list<std::u16string>.
 *
 * @param op Python input as a \c list of \c str.
 * @param container C++ output as a \c std::list<std::u16string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<std::u16string>(PyObject *op, std::list<std::u16string> &container);

/**
 * Instantiation for converting a Python \c list of \c str to a C++ \c std::list<std::u32string>.
 *
 * @param op Python input as a \c list of \c str.
 * @param container C++ output as a \c std::list<std::u32string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_list_to_cpp_std_list_like<std::u32string>(PyObject *op, std::list<std::u32string> &container);

//--------------------- END: Python list -> std::list ---------------------

//-------------------- std::unordered_set -> Python set -------------------
// Base declaration
/**
 * Base declaration for converting C++ \c std::unordered_set to a Python \c set.
 *
 * @tparam T C++ type.
 * @param container C++ input as a \c std::unordered_set<T>.
 * @return A Python \c set containing type corresponding to the C++ type \c T.
 */
template<typename T>
PyObject *
cpp_std_unordered_set_to_py_set(const std::unordered_set<T> &container);

// Instantiations
/**
 * Instantiation for converting C++ \c std::unordered_set<bool> to a Python \c set of \c bool.
 *
 * @param container C++ input as a \c std::unordered_set<bool>.
 * @return A Python \c set containing \c bool objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_set<bool>(const std::unordered_set<bool> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<long> to a Python \c set of \c int.
 *
 * @param container C++ input as a \c std::unordered_set<long>.
 * @return A Python \c set containing \c int objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_set<long>(const std::unordered_set<long> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<double> to a Python \c set of \c float.
 *
 * @param container C++ input as a \c std::unordered_set<double>.
 * @return A Python \c set containing \c float objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_set<double>(const std::unordered_set<double> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<std::complex<double>> to a Python \c set of \c complex.
 *
 * @param container C++ input as a \c std::unordered_set<std::complex<double>>.
 * @return A Python \c set containing \c complex objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_set<std::complex<double>>(const std::unordered_set<std::complex<double>> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<std::vector<char>> to a Python \c set of \c bytes.
 *
 * @param container C++ input as a \c std::unordered_set<std::vector<char>>.
 * @return A Python \c set containing \c bytes objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_set<std::vector<char>>(const std::unordered_set<std::vector<char>> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<std::string> to a Python \c set of \c str.
 *
 * @param container C++ input as a \c std::unordered_set<std::string>.
 * @return A Python \c set containing \c str objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_set<std::string>(const std::unordered_set<std::string> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<std::u16string> to a Python \c set of \c str.
 *
 * @param container C++ input as a \c std::unordered_set<std::u16string>.
 * @return A Python \c set containing \c str objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_set<std::u16string>(const std::unordered_set<std::u16string> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<std::u32string> to a Python \c set of \c str.
 *
 * @param container C++ input as a \c std::unordered_set<std::u32string>.
 * @return A Python \c set containing \c str objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_set<std::u32string>(const std::unordered_set<std::u32string> &container);

//----------------- END: std::unordered_set -> Python set -----------------

//-------------------- Python set -> std::unordered_set -------------------
// Base declaration
/**
 * Base declaration for converting a Python \c set to a C++ \c std::unordered_set.
 *
 * @tparam T C++ type.
 * @param op The Python container to read from.
 * @param container The C++ \c std::unordered_set to write to.
 * @return 0 on success, non-zero on failure.
 */
template<typename T>
int
py_set_to_cpp_std_unordered_set(PyObject *op, std::unordered_set<T> &container);

// Instantiations
/**
 * Instantiation for converting a Python \c set of \c bool to a C++ \c std::unordered_set<bool>.
 *
 * @param op Python input as a \c set of \c bool.
 * @param container C++ output as a \c std::unordered_set<bool>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_set_to_cpp_std_unordered_set<bool>(PyObject *op, std::unordered_set<bool> &container);

/**
 * Instantiation for converting a Python \c set of \c int to a C++ \c std::unordered_set<long>.
 *
 * @param op Python input as a \c set of \c int.
 * @param container C++ output as a \c std::unordered_set<long>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_set_to_cpp_std_unordered_set<long>(PyObject *op, std::unordered_set<long> &container);

/**
 * Instantiation for converting a Python \c set of \c float to a C++ \c std::unordered_set<double>.
 *
 * @param op Python input as a \c set of \c float.
 * @param container C++ output as a \c std::unordered_set<double>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_set_to_cpp_std_unordered_set<double>(PyObject *op, std::unordered_set<double> &container);

/**
 * Instantiation for converting a Python \c set of \c complex to a C++ \c std::unordered_set<std::complex<double>>.
 *
 * @param op Python input as a \c set of \c complex.
 * @param container C++ output as a \c std::unordered_set<std::complex<double>>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_set_to_cpp_std_unordered_set<std::complex<double>>(PyObject *op, std::unordered_set<std::complex<double>> &container);

/**
 * Instantiation for converting a Python \c set of \c bytes to a C++ \c std::unordered_set<std::vector<char>>.
 *
 * @param op Python input as a \c set of \c bytes.
 * @param container C++ output as a \c std::unordered_set<std::vector<char>>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_set_to_cpp_std_unordered_set<std::vector<char>>(PyObject *op, std::unordered_set<std::vector<char>> &container);

/**
 * Instantiation for converting a Python \c set of \c str to a C++ \c std::unordered_set<std::string>.
 *
 * @param op Python input as a \c set of \c str.
 * @param container C++ output as a \c std::unordered_set<std::string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_set_to_cpp_std_unordered_set<std::string>(PyObject *op, std::unordered_set<std::string> &container);

/**
 * Instantiation for converting a Python \c set of \c str to a C++ \c std::unordered_set<std::u16string>.
 *
 * @param op Python input as a \c set of \c str.
 * @param container C++ output as a \c std::unordered_set<std::u16string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_set_to_cpp_std_unordered_set<std::u16string>(PyObject *op, std::unordered_set<std::u16string> &container);

/**
 * Instantiation for converting a Python \c set of \c str to a C++ \c std::unordered_set<std::u32string>.
 *
 * @param op Python input as a \c set of \c str.
 * @param container C++ output as a \c std::unordered_set<std::u32string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_set_to_cpp_std_unordered_set<std::u32string>(PyObject *op, std::unordered_set<std::u32string> &container);

//----------------- END: Python set -> std::unordered_set -----------------

//----------------- std::unordered_set -> Python frozenset ----------------
// Base declaration
/**
 * Base declaration for converting C++ \c std::unordered_set to a Python \c frozenset.
 *
 * @tparam T C++ type.
 * @param container C++ input as a \c std::unordered_set<T>.
 * @return A Python \c frozenset containing type corresponding to the C++ type \c T.
 */
template<typename T>
PyObject *
cpp_std_unordered_set_to_py_frozenset(const std::unordered_set<T> &container);

// Instantiations
/**
 * Instantiation for converting C++ \c std::unordered_set<bool> to a Python \c frozenset of \c bool.
 *
 * @param container C++ input as a \c std::unordered_set<bool>.
 * @return A Python \c frozenset containing \c bool objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<bool>(const std::unordered_set<bool> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<long> to a Python \c frozenset of \c int.
 *
 * @param container C++ input as a \c std::unordered_set<long>.
 * @return A Python \c frozenset containing \c int objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<long>(const std::unordered_set<long> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<double> to a Python \c frozenset of \c float.
 *
 * @param container C++ input as a \c std::unordered_set<double>.
 * @return A Python \c frozenset containing \c float objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<double>(const std::unordered_set<double> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<std::complex<double>> to a Python \c frozenset of \c complex.
 *
 * @param container C++ input as a \c std::unordered_set<std::complex<double>>.
 * @return A Python \c frozenset containing \c complex objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<std::complex<double>>(const std::unordered_set<std::complex<double>> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<std::vector<char>> to a Python \c frozenset of \c bytes.
 *
 * @param container C++ input as a \c std::unordered_set<std::vector<char>>.
 * @return A Python \c frozenset containing \c bytes objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<std::vector<char>>(const std::unordered_set<std::vector<char>> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<std::string> to a Python \c frozenset of \c str.
 *
 * @param container C++ input as a \c std::unordered_set<std::string>.
 * @return A Python \c frozenset containing \c str objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<std::string>(const std::unordered_set<std::string> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<std::u16string> to a Python \c frozenset of \c str.
 *
 * @param container C++ input as a \c std::unordered_set<std::u16string>.
 * @return A Python \c frozenset containing \c str objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<std::u16string>(const std::unordered_set<std::u16string> &container);

/**
 * Instantiation for converting C++ \c std::unordered_set<std::u32string> to a Python \c frozenset of \c str.
 *
 * @param container C++ input as a \c std::unordered_set<std::u32string>.
 * @return A Python \c frozenset containing \c str objects.
 */
template <>
PyObject *
cpp_std_unordered_set_to_py_frozenset<std::u32string>(const std::unordered_set<std::u32string> &container);

//-------------- END: std::unordered_set -> Python frozenset --------------

//----------------- Python frozenset -> std::unordered_set ----------------
// Base declaration
/**
 * Base declaration for converting a Python \c frozenset to a C++ \c std::unordered_set.
 *
 * @tparam T C++ type.
 * @param op The Python container to read from.
 * @param container The C++ \c std::unordered_set to write to.
 * @return 0 on success, non-zero on failure.
 */
template<typename T>
int
py_frozenset_to_cpp_std_unordered_set(PyObject *op, std::unordered_set<T> &container);

// Instantiations
/**
 * Instantiation for converting a Python \c frozenset of \c bool to a C++ \c std::unordered_set<bool>.
 *
 * @param op Python input as a \c frozenset of \c bool.
 * @param container C++ output as a \c std::unordered_set<bool>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_frozenset_to_cpp_std_unordered_set<bool>(PyObject *op, std::unordered_set<bool> &container);

/**
 * Instantiation for converting a Python \c frozenset of \c int to a C++ \c std::unordered_set<long>.
 *
 * @param op Python input as a \c frozenset of \c int.
 * @param container C++ output as a \c std::unordered_set<long>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_frozenset_to_cpp_std_unordered_set<long>(PyObject *op, std::unordered_set<long> &container);

/**
 * Instantiation for converting a Python \c frozenset of \c float to a C++ \c std::unordered_set<double>.
 *
 * @param op Python input as a \c frozenset of \c float.
 * @param container C++ output as a \c std::unordered_set<double>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_frozenset_to_cpp_std_unordered_set<double>(PyObject *op, std::unordered_set<double> &container);

/**
 * Instantiation for converting a Python \c frozenset of \c complex to a C++ \c std::unordered_set<std::complex<double>>.
 *
 * @param op Python input as a \c frozenset of \c complex.
 * @param container C++ output as a \c std::unordered_set<std::complex<double>>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_frozenset_to_cpp_std_unordered_set<std::complex<double>>(PyObject *op, std::unordered_set<std::complex<double>> &container);

/**
 * Instantiation for converting a Python \c frozenset of \c bytes to a C++ \c std::unordered_set<std::vector<char>>.
 *
 * @param op Python input as a \c frozenset of \c bytes.
 * @param container C++ output as a \c std::unordered_set<std::vector<char>>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_frozenset_to_cpp_std_unordered_set<std::vector<char>>(PyObject *op, std::unordered_set<std::vector<char>> &container);

/**
 * Instantiation for converting a Python \c frozenset of \c str to a C++ \c std::unordered_set<std::string>.
 *
 * @param op Python input as a \c frozenset of \c str.
 * @param container C++ output as a \c std::unordered_set<std::string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_frozenset_to_cpp_std_unordered_set<std::string>(PyObject *op, std::unordered_set<std::string> &container);

/**
 * Instantiation for converting a Python \c frozenset of \c str to a C++ \c std::unordered_set<std::u16string>.
 *
 * @param op Python input as a \c frozenset of \c str.
 * @param container C++ output as a \c std::unordered_set<std::u16string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_frozenset_to_cpp_std_unordered_set<std::u16string>(PyObject *op, std::unordered_set<std::u16string> &container);

/**
 * Instantiation for converting a Python \c frozenset of \c str to a C++ \c std::unordered_set<std::u32string>.
 *
 * @param op Python input as a \c frozenset of \c str.
 * @param container C++ output as a \c std::unordered_set<std::u32string>.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_frozenset_to_cpp_std_unordered_set<std::u32string>(PyObject *op, std::unordered_set<std::u32string> &container);

//-------------- END: Python frozenset -> std::unordered_set --------------

//************* END: Unary collections <-> Python collections *************

//**************** std::std::unordered_map <-> Python dict ****************
//----------------- std::std::unordered_map -> Python dict ----------------
// Base declaration
/**
 * Base declaration for converting a C++ <tt>std::unordered_map<K, V></tt> to a Python dictionary.
 *
 * @tparam K The C++ type for the key.
 * @tparam V The C++ type for the value.
 * @param map Input C++ <tt>std::unordered_map<K, V></tt>.
 * @return Python dictionary corresponding to <tt>{K : V, ...}</tt>.
 */
template<template<typename ...> class Map, typename K, typename V>
PyObject *
cpp_std_map_like_to_py_dict(const Map<K, V> &map);

// Instantiations
/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, bool></tt>.
 * @return A Python dictionary of <tt>{bool : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, bool>(const std::unordered_map<bool, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, long></tt>.
 * @return A Python dictionary of <tt>{bool : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, long>(const std::unordered_map<bool, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, double></tt>.
 * @return A Python dictionary of <tt>{bool : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, double>(const std::unordered_map<bool, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{bool : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, std::complex<double>>(const std::unordered_map<bool, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{bool : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, std::vector<char>>(const std::unordered_map<bool, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, std::string></tt>.
 * @return A Python dictionary of <tt>{bool : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, std::string>(const std::unordered_map<bool, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, std::u16string></tt>.
 * @return A Python dictionary of <tt>{bool : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, std::u16string>(const std::unordered_map<bool, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, std::u32string></tt>.
 * @return A Python dictionary of <tt>{bool : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, bool, std::u32string>(const std::unordered_map<bool, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, bool></tt>.
 * @return A Python dictionary of <tt>{int : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, bool>(const std::unordered_map<long, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, long></tt>.
 * @return A Python dictionary of <tt>{int : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, long>(const std::unordered_map<long, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, double></tt>.
 * @return A Python dictionary of <tt>{int : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, double>(const std::unordered_map<long, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{int : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, std::complex<double>>(const std::unordered_map<long, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{int : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, std::vector<char>>(const std::unordered_map<long, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, std::string></tt>.
 * @return A Python dictionary of <tt>{int : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, std::string>(const std::unordered_map<long, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, std::u16string></tt>.
 * @return A Python dictionary of <tt>{int : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, std::u16string>(const std::unordered_map<long, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, std::u32string></tt>.
 * @return A Python dictionary of <tt>{int : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, long, std::u32string>(const std::unordered_map<long, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, bool></tt>.
 * @return A Python dictionary of <tt>{float : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, bool>(const std::unordered_map<double, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, long></tt>.
 * @return A Python dictionary of <tt>{float : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, long>(const std::unordered_map<double, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, double></tt>.
 * @return A Python dictionary of <tt>{float : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, double>(const std::unordered_map<double, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{float : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, std::complex<double>>(const std::unordered_map<double, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{float : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, std::vector<char>>(const std::unordered_map<double, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, std::string></tt>.
 * @return A Python dictionary of <tt>{float : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, std::string>(const std::unordered_map<double, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, std::u16string></tt>.
 * @return A Python dictionary of <tt>{float : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, std::u16string>(const std::unordered_map<double, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, std::u32string></tt>.
 * @return A Python dictionary of <tt>{float : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, double, std::u32string>(const std::unordered_map<double, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, bool></tt>.
 * @return A Python dictionary of <tt>{complex : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, bool>(const std::unordered_map<std::complex<double>, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, long></tt>.
 * @return A Python dictionary of <tt>{complex : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, long>(const std::unordered_map<std::complex<double>, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, double></tt>.
 * @return A Python dictionary of <tt>{complex : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, double>(const std::unordered_map<std::complex<double>, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{complex : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, std::complex<double>>(const std::unordered_map<std::complex<double>, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{complex : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, std::vector<char>>(const std::unordered_map<std::complex<double>, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, std::string></tt>.
 * @return A Python dictionary of <tt>{complex : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, std::string>(const std::unordered_map<std::complex<double>, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, std::u16string></tt>.
 * @return A Python dictionary of <tt>{complex : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, std::u16string>(const std::unordered_map<std::complex<double>, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, std::u32string></tt>.
 * @return A Python dictionary of <tt>{complex : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::complex<double>, std::u32string>(const std::unordered_map<std::complex<double>, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, bool></tt>.
 * @return A Python dictionary of <tt>{bytes : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, bool>(const std::unordered_map<std::vector<char>, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, long></tt>.
 * @return A Python dictionary of <tt>{bytes : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, long>(const std::unordered_map<std::vector<char>, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, double></tt>.
 * @return A Python dictionary of <tt>{bytes : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, double>(const std::unordered_map<std::vector<char>, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{bytes : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, std::complex<double>>(const std::unordered_map<std::vector<char>, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{bytes : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, std::vector<char>>(const std::unordered_map<std::vector<char>, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, std::string></tt>.
 * @return A Python dictionary of <tt>{bytes : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, std::string>(const std::unordered_map<std::vector<char>, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, std::u16string></tt>.
 * @return A Python dictionary of <tt>{bytes : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, std::u16string>(const std::unordered_map<std::vector<char>, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, std::u32string></tt>.
 * @return A Python dictionary of <tt>{bytes : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::vector<char>, std::u32string>(const std::unordered_map<std::vector<char>, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, bool></tt>.
 * @return A Python dictionary of <tt>{str : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, bool>(const std::unordered_map<std::string, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, long></tt>.
 * @return A Python dictionary of <tt>{str : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, long>(const std::unordered_map<std::string, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, double></tt>.
 * @return A Python dictionary of <tt>{str : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, double>(const std::unordered_map<std::string, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{str : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, std::complex<double>>(const std::unordered_map<std::string, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{str : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, std::vector<char>>(const std::unordered_map<std::string, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, std::string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, std::string>(const std::unordered_map<std::string, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, std::u16string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, std::u16string>(const std::unordered_map<std::string, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, std::u32string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::string, std::u32string>(const std::unordered_map<std::string, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, bool></tt>.
 * @return A Python dictionary of <tt>{str : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u16string, bool>(const std::unordered_map<std::u16string, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, long></tt>.
 * @return A Python dictionary of <tt>{str : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u16string, long>(const std::unordered_map<std::u16string, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, double></tt>.
 * @return A Python dictionary of <tt>{str : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u16string, double>(const std::unordered_map<std::u16string, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{str : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u16string, std::complex<double>>(const std::unordered_map<std::u16string, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{str : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u16string, std::vector<char>>(const std::unordered_map<std::u16string, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, std::string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u16string, std::string>(const std::unordered_map<std::u16string, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, std::u16string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u16string, std::u16string>(const std::unordered_map<std::u16string, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, std::u32string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u16string, std::u32string>(const std::unordered_map<std::u16string, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, bool></tt>.
 * @return A Python dictionary of <tt>{str : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u32string, bool>(const std::unordered_map<std::u32string, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, long></tt>.
 * @return A Python dictionary of <tt>{str : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u32string, long>(const std::unordered_map<std::u32string, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, double></tt>.
 * @return A Python dictionary of <tt>{str : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u32string, double>(const std::unordered_map<std::u32string, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{str : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u32string, std::complex<double>>(const std::unordered_map<std::u32string, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{str : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u32string, std::vector<char>>(const std::unordered_map<std::u32string, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, std::string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u32string, std::string>(const std::unordered_map<std::u32string, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, std::u16string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u32string, std::u16string>(const std::unordered_map<std::u32string, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, std::u32string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::unordered_map, std::u32string, std::u32string>(const std::unordered_map<std::u32string, std::u32string> &map);

//-------------- END: std::std::unordered_map -> Python dict --------------

//------------------- Python dict -> std::unordered_map -------------------
// Base declaration
/**
 * Base declaration for converting a Python dictionary to a C++ std::unordered_map<K, V>.
 *
 * @tparam K The C++ type for the key.
 * @tparam V The C++ type for the value.
 * @param op The Python dictionary as the input.
 * @param map C++ <tt>std::unordered_map<K, V></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template<template<typename ...> class Map, typename K, typename V>
int 
py_dict_to_cpp_std_map_like(PyObject *op, Map<K, V> &map);

// Instantiations
/**
 * Instantiation for converting a Python dictionary <tt>{bool : bool, ...}</tt> to a C++ <tt>std::unordered_map<bool, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, bool>(PyObject* op, std::unordered_map<bool, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : int, ...}</tt> to a C++ <tt>std::unordered_map<bool, long></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, long>(PyObject* op, std::unordered_map<bool, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : float, ...}</tt> to a C++ <tt>std::unordered_map<bool, double></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, double>(PyObject* op, std::unordered_map<bool, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : complex, ...}</tt> to a C++ <tt>std::unordered_map<bool, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, std::complex<double>>(PyObject* op, std::unordered_map<bool, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : bytes, ...}</tt> to a C++ <tt>std::unordered_map<bool, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, std::vector<char>>(PyObject* op, std::unordered_map<bool, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : str, ...}</tt> to a C++ <tt>std::unordered_map<bool, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, std::string>(PyObject* op, std::unordered_map<bool, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : str, ...}</tt> to a C++ <tt>std::unordered_map<bool, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, std::u16string>(PyObject* op, std::unordered_map<bool, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : str, ...}</tt> to a C++ <tt>std::unordered_map<bool, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, bool, std::u32string>(PyObject* op, std::unordered_map<bool, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : bool, ...}</tt> to a C++ <tt>std::unordered_map<long, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{int : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, bool>(PyObject* op, std::unordered_map<long, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : int, ...}</tt> to a C++ <tt>std::unordered_map<long, long></tt>.
 *
 * @param op A Python dictionary of <tt>{int : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, long>(PyObject* op, std::unordered_map<long, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : float, ...}</tt> to a C++ <tt>std::unordered_map<long, double></tt>.
 *
 * @param op A Python dictionary of <tt>{int : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, double>(PyObject* op, std::unordered_map<long, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : complex, ...}</tt> to a C++ <tt>std::unordered_map<long, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{int : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, std::complex<double>>(PyObject* op, std::unordered_map<long, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : bytes, ...}</tt> to a C++ <tt>std::unordered_map<long, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{int : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, std::vector<char>>(PyObject* op, std::unordered_map<long, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : str, ...}</tt> to a C++ <tt>std::unordered_map<long, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{int : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, std::string>(PyObject* op, std::unordered_map<long, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : str, ...}</tt> to a C++ <tt>std::unordered_map<long, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{int : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, std::u16string>(PyObject* op, std::unordered_map<long, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : str, ...}</tt> to a C++ <tt>std::unordered_map<long, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{int : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, long, std::u32string>(PyObject* op, std::unordered_map<long, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : bool, ...}</tt> to a C++ <tt>std::unordered_map<double, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{float : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, bool>(PyObject* op, std::unordered_map<double, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : int, ...}</tt> to a C++ <tt>std::unordered_map<double, long></tt>.
 *
 * @param op A Python dictionary of <tt>{float : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, long>(PyObject* op, std::unordered_map<double, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : float, ...}</tt> to a C++ <tt>std::unordered_map<double, double></tt>.
 *
 * @param op A Python dictionary of <tt>{float : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, double>(PyObject* op, std::unordered_map<double, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : complex, ...}</tt> to a C++ <tt>std::unordered_map<double, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{float : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, std::complex<double>>(PyObject* op, std::unordered_map<double, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : bytes, ...}</tt> to a C++ <tt>std::unordered_map<double, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{float : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, std::vector<char>>(PyObject* op, std::unordered_map<double, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : str, ...}</tt> to a C++ <tt>std::unordered_map<double, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{float : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, std::string>(PyObject* op, std::unordered_map<double, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : str, ...}</tt> to a C++ <tt>std::unordered_map<double, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{float : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, std::u16string>(PyObject* op, std::unordered_map<double, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : str, ...}</tt> to a C++ <tt>std::unordered_map<double, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{float : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, double, std::u32string>(PyObject* op, std::unordered_map<double, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : bool, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, bool>(PyObject* op, std::unordered_map<std::complex<double>, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : int, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, long></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, long>(PyObject* op, std::unordered_map<std::complex<double>, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : float, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, double></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, double>(PyObject* op, std::unordered_map<std::complex<double>, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : complex, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, std::complex<double>>(PyObject* op, std::unordered_map<std::complex<double>, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : bytes, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, std::vector<char>>(PyObject* op, std::unordered_map<std::complex<double>, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : str, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, std::string>(PyObject* op, std::unordered_map<std::complex<double>, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : str, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, std::u16string>(PyObject* op, std::unordered_map<std::complex<double>, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : str, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::complex<double>, std::u32string>(PyObject* op, std::unordered_map<std::complex<double>, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : bool, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, bool>(PyObject* op, std::unordered_map<std::vector<char>, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : int, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, long></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, long>(PyObject* op, std::unordered_map<std::vector<char>, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : float, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, double></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, double>(PyObject* op, std::unordered_map<std::vector<char>, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : complex, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, std::complex<double>>(PyObject* op, std::unordered_map<std::vector<char>, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : bytes, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, std::vector<char>>(PyObject* op, std::unordered_map<std::vector<char>, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : str, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, std::string>(PyObject* op, std::unordered_map<std::vector<char>, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : str, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, std::u16string>(PyObject* op, std::unordered_map<std::vector<char>, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : str, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::vector<char>, std::u32string>(PyObject* op, std::unordered_map<std::vector<char>, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : bool, ...}</tt> to a C++ <tt>std::unordered_map<std::string, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{str : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, bool>(PyObject* op, std::unordered_map<std::string, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : int, ...}</tt> to a C++ <tt>std::unordered_map<std::string, long></tt>.
 *
 * @param op A Python dictionary of <tt>{str : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, long>(PyObject* op, std::unordered_map<std::string, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : float, ...}</tt> to a C++ <tt>std::unordered_map<std::string, double></tt>.
 *
 * @param op A Python dictionary of <tt>{str : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, double>(PyObject* op, std::unordered_map<std::string, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : complex, ...}</tt> to a C++ <tt>std::unordered_map<std::string, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{str : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, std::complex<double>>(PyObject* op, std::unordered_map<std::string, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : bytes, ...}</tt> to a C++ <tt>std::unordered_map<std::string, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{str : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, std::vector<char>>(PyObject* op, std::unordered_map<std::string, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::string, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, std::string>(PyObject* op, std::unordered_map<std::string, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::string, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, std::u16string>(PyObject* op, std::unordered_map<std::string, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::string, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::string, std::u32string>(PyObject* op, std::unordered_map<std::string, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : bool, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{str : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u16string, bool>(PyObject* op, std::unordered_map<std::u16string, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : int, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, long></tt>.
 *
 * @param op A Python dictionary of <tt>{str : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u16string, long>(PyObject* op, std::unordered_map<std::u16string, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : float, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, double></tt>.
 *
 * @param op A Python dictionary of <tt>{str : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u16string, double>(PyObject* op, std::unordered_map<std::u16string, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : complex, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{str : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u16string, std::complex<double>>(PyObject* op, std::unordered_map<std::u16string, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : bytes, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{str : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u16string, std::vector<char>>(PyObject* op, std::unordered_map<std::u16string, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u16string, std::string>(PyObject* op, std::unordered_map<std::u16string, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u16string, std::u16string>(PyObject* op, std::unordered_map<std::u16string, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u16string, std::u32string>(PyObject* op, std::unordered_map<std::u16string, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : bool, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{str : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u32string, bool>(PyObject* op, std::unordered_map<std::u32string, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : int, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, long></tt>.
 *
 * @param op A Python dictionary of <tt>{str : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u32string, long>(PyObject* op, std::unordered_map<std::u32string, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : float, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, double></tt>.
 *
 * @param op A Python dictionary of <tt>{str : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u32string, double>(PyObject* op, std::unordered_map<std::u32string, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : complex, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{str : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u32string, std::complex<double>>(PyObject* op, std::unordered_map<std::u32string, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : bytes, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{str : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u32string, std::vector<char>>(PyObject* op, std::unordered_map<std::u32string, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u32string, std::string>(PyObject* op, std::unordered_map<std::u32string, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u32string, std::u16string>(PyObject* op, std::unordered_map<std::u32string, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::unordered_map, std::u32string, std::u32string>(PyObject* op, std::unordered_map<std::u32string, std::u32string> &map);

//----------------- END: Python dict -> std::unordered_map ----------------

//************** END: std::std::unordered_map <-> Python dict *************

//********************* std::std::map <-> Python dict *********************
//---------------------- std::std::map -> Python dict ---------------------
// Base declaration
/**
 * Base declaration for converting a C++ <tt>std::unordered_map<K, V></tt> to a Python dictionary.
 *
 * @tparam K The C++ type for the key.
 * @tparam V The C++ type for the value.
 * @param map Input C++ <tt>std::unordered_map<K, V></tt>.
 * @return Python dictionary corresponding to <tt>{K : V, ...}</tt>.
 */
template<template<typename ...> class Map, typename K, typename V>
PyObject *
cpp_std_map_like_to_py_dict(const Map<K, V> &map);

// Instantiations
/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, bool></tt>.
 * @return A Python dictionary of <tt>{bool : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, bool>(const std::map<bool, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, long></tt>.
 * @return A Python dictionary of <tt>{bool : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, long>(const std::map<bool, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, double></tt>.
 * @return A Python dictionary of <tt>{bool : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, double>(const std::map<bool, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{bool : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, std::complex<double>>(const std::map<bool, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{bool : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, std::vector<char>>(const std::map<bool, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, std::string></tt>.
 * @return A Python dictionary of <tt>{bool : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, std::string>(const std::map<bool, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, std::u16string></tt>.
 * @return A Python dictionary of <tt>{bool : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, std::u16string>(const std::map<bool, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<bool, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<bool, std::u32string></tt>.
 * @return A Python dictionary of <tt>{bool : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, bool, std::u32string>(const std::map<bool, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, bool></tt>.
 * @return A Python dictionary of <tt>{int : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, bool>(const std::map<long, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, long></tt>.
 * @return A Python dictionary of <tt>{int : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, long>(const std::map<long, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, double></tt>.
 * @return A Python dictionary of <tt>{int : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, double>(const std::map<long, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{int : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, std::complex<double>>(const std::map<long, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{int : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, std::vector<char>>(const std::map<long, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, std::string></tt>.
 * @return A Python dictionary of <tt>{int : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, std::string>(const std::map<long, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, std::u16string></tt>.
 * @return A Python dictionary of <tt>{int : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, std::u16string>(const std::map<long, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<long, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<long, std::u32string></tt>.
 * @return A Python dictionary of <tt>{int : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, long, std::u32string>(const std::map<long, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, bool></tt>.
 * @return A Python dictionary of <tt>{float : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, bool>(const std::map<double, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, long></tt>.
 * @return A Python dictionary of <tt>{float : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, long>(const std::map<double, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, double></tt>.
 * @return A Python dictionary of <tt>{float : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, double>(const std::map<double, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{float : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, std::complex<double>>(const std::map<double, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{float : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, std::vector<char>>(const std::map<double, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, std::string></tt>.
 * @return A Python dictionary of <tt>{float : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, std::string>(const std::map<double, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, std::u16string></tt>.
 * @return A Python dictionary of <tt>{float : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, std::u16string>(const std::map<double, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<double, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<double, std::u32string></tt>.
 * @return A Python dictionary of <tt>{float : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, double, std::u32string>(const std::map<double, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, bool></tt>.
 * @return A Python dictionary of <tt>{complex : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, bool>(const std::map<std::complex<double>, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, long></tt>.
 * @return A Python dictionary of <tt>{complex : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, long>(const std::map<std::complex<double>, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, double></tt>.
 * @return A Python dictionary of <tt>{complex : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, double>(const std::map<std::complex<double>, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{complex : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, std::complex<double>>(const std::map<std::complex<double>, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{complex : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, std::vector<char>>(const std::map<std::complex<double>, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, std::string></tt>.
 * @return A Python dictionary of <tt>{complex : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, std::string>(const std::map<std::complex<double>, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, std::u16string></tt>.
 * @return A Python dictionary of <tt>{complex : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, std::u16string>(const std::map<std::complex<double>, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::complex<double>, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::complex<double>, std::u32string></tt>.
 * @return A Python dictionary of <tt>{complex : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::complex<double>, std::u32string>(const std::map<std::complex<double>, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, bool></tt>.
 * @return A Python dictionary of <tt>{bytes : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, bool>(const std::map<std::vector<char>, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, long></tt>.
 * @return A Python dictionary of <tt>{bytes : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, long>(const std::map<std::vector<char>, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, double></tt>.
 * @return A Python dictionary of <tt>{bytes : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, double>(const std::map<std::vector<char>, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{bytes : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, std::complex<double>>(const std::map<std::vector<char>, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{bytes : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, std::vector<char>>(const std::map<std::vector<char>, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, std::string></tt>.
 * @return A Python dictionary of <tt>{bytes : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, std::string>(const std::map<std::vector<char>, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, std::u16string></tt>.
 * @return A Python dictionary of <tt>{bytes : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, std::u16string>(const std::map<std::vector<char>, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::vector<char>, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::vector<char>, std::u32string></tt>.
 * @return A Python dictionary of <tt>{bytes : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::vector<char>, std::u32string>(const std::map<std::vector<char>, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, bool></tt>.
 * @return A Python dictionary of <tt>{str : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, bool>(const std::map<std::string, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, long></tt>.
 * @return A Python dictionary of <tt>{str : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, long>(const std::map<std::string, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, double></tt>.
 * @return A Python dictionary of <tt>{str : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, double>(const std::map<std::string, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{str : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, std::complex<double>>(const std::map<std::string, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{str : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, std::vector<char>>(const std::map<std::string, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, std::string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, std::string>(const std::map<std::string, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, std::u16string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, std::u16string>(const std::map<std::string, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::string, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::string, std::u32string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::string, std::u32string>(const std::map<std::string, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, bool></tt>.
 * @return A Python dictionary of <tt>{str : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u16string, bool>(const std::map<std::u16string, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, long></tt>.
 * @return A Python dictionary of <tt>{str : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u16string, long>(const std::map<std::u16string, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, double></tt>.
 * @return A Python dictionary of <tt>{str : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u16string, double>(const std::map<std::u16string, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{str : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u16string, std::complex<double>>(const std::map<std::u16string, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{str : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u16string, std::vector<char>>(const std::map<std::u16string, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, std::string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u16string, std::string>(const std::map<std::u16string, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, std::u16string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u16string, std::u16string>(const std::map<std::u16string, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u16string, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u16string, std::u32string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u16string, std::u32string>(const std::map<std::u16string, std::u32string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, bool></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, bool></tt>.
 * @return A Python dictionary of <tt>{str : bool, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u32string, bool>(const std::map<std::u32string, bool> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, long></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, long></tt>.
 * @return A Python dictionary of <tt>{str : int, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u32string, long>(const std::map<std::u32string, long> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, double></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, double></tt>.
 * @return A Python dictionary of <tt>{str : float, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u32string, double>(const std::map<std::u32string, double> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, std::complex<double>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, std::complex<double>></tt>.
 * @return A Python dictionary of <tt>{str : complex, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u32string, std::complex<double>>(const std::map<std::u32string, std::complex<double>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, std::vector<char>></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, std::vector<char>></tt>.
 * @return A Python dictionary of <tt>{str : bytes, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u32string, std::vector<char>>(const std::map<std::u32string, std::vector<char>> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, std::string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, std::string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u32string, std::string>(const std::map<std::u32string, std::string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, std::u16string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, std::u16string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u32string, std::u16string>(const std::map<std::u32string, std::u16string> &map);

/**
 * Instantiation for converting a C++ <tt>std::unordered_map<std::u32string, std::u32string></tt> to a Python dictionary.
 *
 * @param map Input C++ <tt>std::unordered_map<std::u32string, std::u32string></tt>.
 * @return A Python dictionary of <tt>{str : str, ...}</tt>.
 */
template <>
PyObject *
cpp_std_map_like_to_py_dict<std::map, std::u32string, std::u32string>(const std::map<std::u32string, std::u32string> &map);

//------------------- END: std::std::map -> Python dict -------------------

//------------------- Python dict -> std::unordered_map -------------------
// Base declaration
/**
 * Base declaration for converting a Python dictionary to a C++ std::unordered_map<K, V>.
 *
 * @tparam K The C++ type for the key.
 * @tparam V The C++ type for the value.
 * @param op The Python dictionary as the input.
 * @param map C++ <tt>std::unordered_map<K, V></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template<template<typename ...> class Map, typename K, typename V>
int 
py_dict_to_cpp_std_map_like(PyObject *op, Map<K, V> &map);

// Instantiations
/**
 * Instantiation for converting a Python dictionary <tt>{bool : bool, ...}</tt> to a C++ <tt>std::unordered_map<bool, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, bool>(PyObject* op, std::map<bool, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : int, ...}</tt> to a C++ <tt>std::unordered_map<bool, long></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, long>(PyObject* op, std::map<bool, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : float, ...}</tt> to a C++ <tt>std::unordered_map<bool, double></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, double>(PyObject* op, std::map<bool, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : complex, ...}</tt> to a C++ <tt>std::unordered_map<bool, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, std::complex<double>>(PyObject* op, std::map<bool, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : bytes, ...}</tt> to a C++ <tt>std::unordered_map<bool, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, std::vector<char>>(PyObject* op, std::map<bool, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : str, ...}</tt> to a C++ <tt>std::unordered_map<bool, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, std::string>(PyObject* op, std::map<bool, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : str, ...}</tt> to a C++ <tt>std::unordered_map<bool, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, std::u16string>(PyObject* op, std::map<bool, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bool : str, ...}</tt> to a C++ <tt>std::unordered_map<bool, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{bool : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<bool, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, bool, std::u32string>(PyObject* op, std::map<bool, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : bool, ...}</tt> to a C++ <tt>std::unordered_map<long, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{int : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, bool>(PyObject* op, std::map<long, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : int, ...}</tt> to a C++ <tt>std::unordered_map<long, long></tt>.
 *
 * @param op A Python dictionary of <tt>{int : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, long>(PyObject* op, std::map<long, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : float, ...}</tt> to a C++ <tt>std::unordered_map<long, double></tt>.
 *
 * @param op A Python dictionary of <tt>{int : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, double>(PyObject* op, std::map<long, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : complex, ...}</tt> to a C++ <tt>std::unordered_map<long, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{int : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, std::complex<double>>(PyObject* op, std::map<long, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : bytes, ...}</tt> to a C++ <tt>std::unordered_map<long, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{int : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, std::vector<char>>(PyObject* op, std::map<long, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : str, ...}</tt> to a C++ <tt>std::unordered_map<long, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{int : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, std::string>(PyObject* op, std::map<long, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : str, ...}</tt> to a C++ <tt>std::unordered_map<long, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{int : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, std::u16string>(PyObject* op, std::map<long, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{int : str, ...}</tt> to a C++ <tt>std::unordered_map<long, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{int : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<long, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, long, std::u32string>(PyObject* op, std::map<long, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : bool, ...}</tt> to a C++ <tt>std::unordered_map<double, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{float : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, bool>(PyObject* op, std::map<double, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : int, ...}</tt> to a C++ <tt>std::unordered_map<double, long></tt>.
 *
 * @param op A Python dictionary of <tt>{float : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, long>(PyObject* op, std::map<double, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : float, ...}</tt> to a C++ <tt>std::unordered_map<double, double></tt>.
 *
 * @param op A Python dictionary of <tt>{float : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, double>(PyObject* op, std::map<double, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : complex, ...}</tt> to a C++ <tt>std::unordered_map<double, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{float : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, std::complex<double>>(PyObject* op, std::map<double, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : bytes, ...}</tt> to a C++ <tt>std::unordered_map<double, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{float : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, std::vector<char>>(PyObject* op, std::map<double, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : str, ...}</tt> to a C++ <tt>std::unordered_map<double, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{float : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, std::string>(PyObject* op, std::map<double, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : str, ...}</tt> to a C++ <tt>std::unordered_map<double, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{float : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, std::u16string>(PyObject* op, std::map<double, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{float : str, ...}</tt> to a C++ <tt>std::unordered_map<double, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{float : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<double, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, double, std::u32string>(PyObject* op, std::map<double, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : bool, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, bool>(PyObject* op, std::map<std::complex<double>, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : int, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, long></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, long>(PyObject* op, std::map<std::complex<double>, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : float, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, double></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, double>(PyObject* op, std::map<std::complex<double>, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : complex, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, std::complex<double>>(PyObject* op, std::map<std::complex<double>, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : bytes, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, std::vector<char>>(PyObject* op, std::map<std::complex<double>, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : str, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, std::string>(PyObject* op, std::map<std::complex<double>, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : str, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, std::u16string>(PyObject* op, std::map<std::complex<double>, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{complex : str, ...}</tt> to a C++ <tt>std::unordered_map<std::complex<double>, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{complex : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::complex<double>, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::complex<double>, std::u32string>(PyObject* op, std::map<std::complex<double>, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : bool, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, bool>(PyObject* op, std::map<std::vector<char>, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : int, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, long></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, long>(PyObject* op, std::map<std::vector<char>, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : float, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, double></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, double>(PyObject* op, std::map<std::vector<char>, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : complex, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, std::complex<double>>(PyObject* op, std::map<std::vector<char>, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : bytes, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, std::vector<char>>(PyObject* op, std::map<std::vector<char>, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : str, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, std::string>(PyObject* op, std::map<std::vector<char>, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : str, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, std::u16string>(PyObject* op, std::map<std::vector<char>, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{bytes : str, ...}</tt> to a C++ <tt>std::unordered_map<std::vector<char>, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{bytes : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::vector<char>, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::vector<char>, std::u32string>(PyObject* op, std::map<std::vector<char>, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : bool, ...}</tt> to a C++ <tt>std::unordered_map<std::string, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{str : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, bool>(PyObject* op, std::map<std::string, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : int, ...}</tt> to a C++ <tt>std::unordered_map<std::string, long></tt>.
 *
 * @param op A Python dictionary of <tt>{str : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, long>(PyObject* op, std::map<std::string, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : float, ...}</tt> to a C++ <tt>std::unordered_map<std::string, double></tt>.
 *
 * @param op A Python dictionary of <tt>{str : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, double>(PyObject* op, std::map<std::string, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : complex, ...}</tt> to a C++ <tt>std::unordered_map<std::string, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{str : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, std::complex<double>>(PyObject* op, std::map<std::string, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : bytes, ...}</tt> to a C++ <tt>std::unordered_map<std::string, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{str : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, std::vector<char>>(PyObject* op, std::map<std::string, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::string, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, std::string>(PyObject* op, std::map<std::string, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::string, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, std::u16string>(PyObject* op, std::map<std::string, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::string, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::string, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::string, std::u32string>(PyObject* op, std::map<std::string, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : bool, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{str : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u16string, bool>(PyObject* op, std::map<std::u16string, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : int, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, long></tt>.
 *
 * @param op A Python dictionary of <tt>{str : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u16string, long>(PyObject* op, std::map<std::u16string, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : float, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, double></tt>.
 *
 * @param op A Python dictionary of <tt>{str : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u16string, double>(PyObject* op, std::map<std::u16string, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : complex, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{str : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u16string, std::complex<double>>(PyObject* op, std::map<std::u16string, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : bytes, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{str : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u16string, std::vector<char>>(PyObject* op, std::map<std::u16string, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u16string, std::string>(PyObject* op, std::map<std::u16string, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u16string, std::u16string>(PyObject* op, std::map<std::u16string, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::u16string, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u16string, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u16string, std::u32string>(PyObject* op, std::map<std::u16string, std::u32string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : bool, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, bool></tt>.
 *
 * @param op A Python dictionary of <tt>{str : bool, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, bool></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u32string, bool>(PyObject* op, std::map<std::u32string, bool> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : int, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, long></tt>.
 *
 * @param op A Python dictionary of <tt>{str : int, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, long></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u32string, long>(PyObject* op, std::map<std::u32string, long> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : float, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, double></tt>.
 *
 * @param op A Python dictionary of <tt>{str : float, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, double></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u32string, double>(PyObject* op, std::map<std::u32string, double> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : complex, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, std::complex<double>></tt>.
 *
 * @param op A Python dictionary of <tt>{str : complex, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, std::complex<double>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u32string, std::complex<double>>(PyObject* op, std::map<std::u32string, std::complex<double>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : bytes, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, std::vector<char>></tt>.
 *
 * @param op A Python dictionary of <tt>{str : bytes, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, std::vector<char>></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u32string, std::vector<char>>(PyObject* op, std::map<std::u32string, std::vector<char>> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, std::string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, std::string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u32string, std::string>(PyObject* op, std::map<std::u32string, std::string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, std::u16string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, std::u16string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u32string, std::u16string>(PyObject* op, std::map<std::u32string, std::u16string> &map);

/**
 * Instantiation for converting a Python dictionary <tt>{str : str, ...}</tt> to a C++ <tt>std::unordered_map<std::u32string, std::u32string></tt>.
 *
 * @param op A Python dictionary of <tt>{str : str, ...}</tt> as the input.
 * @param map The C++ <tt>std::unordered_map<std::u32string, std::u32string></tt> to write to.
 * @return 0 on success, non-zero on failure.
 */
template <>
int
py_dict_to_cpp_std_map_like<std::map, std::u32string, std::u32string>(PyObject* op, std::map<std::u32string, std::u32string> &map);

//----------------- END: Python dict -> std::unordered_map ----------------

//******************* END: std::std::map <-> Python dict ******************

// Declarations written: 356
//#########################################################################
//#### END: Auto-generated code - do not edit. Seriously, do NOT edit. ####
//#########################################################################

} // namespace Python_Cpp_Containers

//========================= END: Declaration file =========================


#endif // PY_CPP_CONTAINERS_AUTO_PY_CONVERT_INTERNAL_H
