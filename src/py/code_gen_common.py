import typing


class CppTypeFunctions(typing.NamedTuple):
    """
    PoD Class to contain the names of three C/C++ functions:
    - Conversion from C++ to Python object. Example 'cpp_bool_to_py_bool'.
    - Check it is a Python object of type. Example 'py_bool_check'.
    - Conversion from Python object to a C++ type. Example 'py_bool_to_cpp_bool'.
    """
    cpp_type_to_py_type: str
    py_check: str
    py_type_to_cpp_type: str
    py_type: str


class TypeConversionFunctions(typing.NamedTuple):
    """
    PoD Class to contain the names of three C/C++ functions:
    - Check it is a Python object of type. Example 'py_bool_check'.
    - Conversion from Python object to a C++ type. Example 'py_bool_to_cpp_bool'.
    - Conversion from C++ to Python object. Example 'cpp_bool_to_py_bool'.
    """
    py_type: str
    cpp_type: str
    py_check: str
    py_type_to_cpp_type: str
    cpp_type_to_py_type: str


class UnaryFunctions(typing.NamedTuple):
    """
    PoD Class to contain the names of three C/C++ functions:
    - Python container type. Example 'list'.
    - C++ container type. Example 'std::vector'.
    - Function declaration to convert to a Python type. Example 'cpp_std_list_like_to_py_tuple'.
    - Function declaration to convert to a C++ type. Example 'py_tuple_to_cpp_std_list_like'.
    """
    python_container: str
    cpp_container: str
    decl_to_py: str
    decl_to_cpp: str
