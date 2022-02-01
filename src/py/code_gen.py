"""
Writes out .h and .cpp files to support Python/C++ homogeneous containers.

This facilitates conversion between Python and C++ containers where the Python types are consistent.

For example a Python set of strings to and from a C++ unordered_set<std::string>

Note on nomenclature:

- 'cpp' is C++
- C++ namespaced types are '_' separated so 'std::vector' is 'cpp_std_vector'
- 'py' is Python
- Conversion functions are always ..._to_...

"""
import itertools
import logging
import os
import typing

from src.py import code_gen_documentation, code_gen_common

logger = logging.getLogger(__file__)

#: The namespace that all the C++ code lives within.
CPP_NAMESPACE = 'Python_Cpp_Containers'

#: This is the map of type conversion functions between Python and C/C++ that we are going to need.
#: These refer to hand written functions.
#: for k, v in itertools.product(CPP_TYPE_TO_FUNCS.keys(), repeat=2):
CPP_TYPE_TO_FUNCS = {
    'bool': code_gen_common.CppTypeFunctions('cpp_bool_to_py_bool', 'py_bool_check', 'py_bool_to_cpp_bool', 'bool'),
    'long': code_gen_common.CppTypeFunctions('cpp_long_to_py_long', 'py_long_check', 'py_long_to_cpp_long', 'int'),
    'double': code_gen_common.CppTypeFunctions('cpp_double_to_py_float', 'py_float_check', 'py_float_to_cpp_double',
                                               'float'),
    'std::complex<double>': code_gen_common.CppTypeFunctions('cpp_complex_to_py_complex', 'py_complex_check',
                                                             'py_complex_to_cpp_complex', 'complex'),
    'std::vector<char>': code_gen_common.CppTypeFunctions('cpp_vector_char_to_py_bytes', 'py_bytes_check',
                                                          'py_bytes_to_cpp_vector_char', 'bytes'),
    'std::string': code_gen_common.CppTypeFunctions('cpp_string_to_py_unicode', 'py_unicode_check',
                                                    'py_unicode_to_cpp_string', 'str'),
}

#: This is the map of C++ containers of those types and conversion functions that we are going to need.
#: These refer to hand written template functions.
UNARY_COLLECTIONS = (
    code_gen_common.UnaryFunctions('tuple', 'std::vector', 'cpp_std_list_like_to_py_tuple',
                                   'py_tuple_to_cpp_list_like'),
    code_gen_common.UnaryFunctions('tuple', 'std::list', 'cpp_std_list_like_to_py_tuple', 'py_tuple_to_cpp_list_like'),
    code_gen_common.UnaryFunctions('list', 'std::vector', 'cpp_std_list_like_to_py_list', 'py_list_to_cpp_list_like'),
    code_gen_common.UnaryFunctions('list', 'std::list', 'cpp_std_list_like_to_py_list', 'py_list_to_cpp_list_like'),
    code_gen_common.UnaryFunctions('set', 'std::unordered_set', 'cpp_std_unordered_set_to_py_set',
                                   'py_set_to_cpp_std_unordered_set'),
    code_gen_common.UnaryFunctions('frozenset', 'std::unordered_set', 'cpp_std_unordered_set_to_py_frozenset',
                                   'py_frozenset_to_cpp_std_unordered_set'),
)

#: Not really needed as the hand written file, python_convert.h does this.
REQUIRED_INCLUDES = []

# ==== String templates for C++ declarations and definitions. ====

# ---- C++ to Python
# Declarations to go in header file
# Base declaration to convert to Python, requires fn= and cpp_container=
# Example:
#     template<typename T>
#     PyObject *
#     cpp_std_list_like_to_py_tuple(const std::vector<T> &container);
CPP_UNARY_FUNCTION_TO_PY_BASE_DECL = """template<typename T>
PyObject *
{fn}(const {cpp_container}<T> &container);"""

# Declarations to go in header file
# Convert to Python, requires fn=, cpp_type= and cpp_container=
# Example:
#     // Declaration for std::vector -> tuple
#     template <>
#     PyObject *
#     cpp_std_list_like_to_py_tuple<long>(const std::vector<long> &container);
CPP_UNARY_FUNCTION_TO_PY_DECL = """template <>
PyObject *
{fn}<{cpp_type}>(const {cpp_container}<{cpp_type}> &container);"""

# Definitions to go in implementation file
# To Python, requires fn_decl=, cpp_type=, cpp_container=, fn_defn=, convert_to_py=
# Example:
#     // Definition for std::vector -> tuple
#     template <>
#     PyObject *
#     cpp_std_list_like_to_py_tuple<long>(const std::vector<long> &container) {
#         return generic_cpp_std_vector_to_py_tuple<long, &cpp_long_to_py_long>(container);
#     }
CPP_UNARY_FUNCTION_TO_PY_DEFN = """template <>
PyObject *
{fn_decl}<{cpp_type}>(const {cpp_container}<{cpp_type}> &container) {{
    return {fn_defn}<{cpp_type}, &{convert_to_py}>(container);
}}
"""

# ---- Python to C++
# Base declaration to convert from Python, requires fn= and cpp_container=
# Example:
#     // Python to C++ std::vector
#     // Base declaration
#     template<typename T>
#     int
#     py_list_to_cpp_list_like(PyObject *op, std::vector<T> &container);
PY_TO_CPP_UNARY_FUNCTION_BASE_DECL = """template<typename T>
int
{fn}(PyObject *op, {cpp_container}<T> &container);"""

# Declaration in header file
# Convert from Python, requires fn=, cpp_type= and cpp_container=
# Example:
#     // Instantiation declaration in .h file
#    template <>
#    int
#    py_list_to_cpp_list_like<long>(PyObject *op, std::vector<long> &container);
PY_TO_CPP_UNARY_FUNCTION_DECL = """template <>
int
{fn}<{cpp_type}>(PyObject *op, {cpp_container}<{cpp_type}> &container);"""

# Definition in implementation file
# From Python, requires fn_decl=, cpp_type=, cpp_container=, fn_defn=, py_check=, convert_to_py=
# Example:
#     template <>
#     int
#     py_list_to_cpp_list_like<long>(PyObject *op, std::vector<long> &container) {
#         return generic_py_list_to_cpp_std_vector<long, &py_long_check, &py_long_to_cpp_long>(op, container);
#     }
PY_TO_CPP_UNARY_FUNCTION_DEFN = """template <>
int
{fn_decl}<{cpp_type}>(PyObject *op, {cpp_container}<{cpp_type}> &container) {{
    return {fn_defn}<{cpp_type}, &{py_check}, &{convert_from_py}>(op, container);
}}
"""

# ===== std::unordered_map and std::map <-> dict ====
CPP_MAP_TYPES = ('std::unordered_map', 'std::map')

# ==== C++ to Python

# Declarations to go in header file
# Base declaration, C++ to Python, example:
#     template<template<typename ...> class Map, typename K, typename V>
#     PyObject *
#     cpp_std_map_like_to_py_dict(const std::unordered_map<K, V> &map);
CPP_MAP_TYPE_TO_PY_DICT_BASE_DECL = """template<template<typename ...> class Map, typename K, typename V>
PyObject *
cpp_std_map_like_to_py_dict(const Map<K, V> &map);"""

# Completed declaration, C++ to Python, example:
#     template<>
#     PyObject *
#     cpp_std_map_like_to_py_dict<std::unordered_map, long, long>(const std::unordered_map<long, long> &map);
CPP_MAP_TYPE_TO_PY_DICT_DECL = """template <>
PyObject *
cpp_std_map_like_to_py_dict<{cpp_map_type}, {cpp_type_K}, {cpp_type_V}>(const {cpp_map_type}<{cpp_type_K}, {cpp_type_V}> &map);"""

# Definitions to go in implementation file
# C++ to Python, example:
#     template<>
#     PyObject *
#     cpp_std_map_like_to_py_dict<std::unordered_map, long, long>(const std::unordered_map<long, long> &map) {
#         return generic_cpp_std_map_like_to_py_dict<
#                 std::unordered_map,
#                 long, long,
#                 &cpp_long_to_py_long, &cpp_long_to_py_long
#         >(map);
#     }
CPP_MAP_TYPE_TO_PY_DICT_DEFN = """template <>
PyObject *
cpp_std_map_like_to_py_dict<{cpp_map_type}, {type_K}, {type_V}>(const {cpp_map_type}<{type_K}, {type_V}> &map) {{
    return generic_cpp_std_map_like_to_py_dict<
        {cpp_map_type},
        {type_K}, {type_V},
        &{convert_K_to_py}, &{convert_V_to_py}
    >(map);
}}
"""

# ==== Python to C++

# Base declaration, Python to C++, example:
#     template<template<typename ...> class Map, typename K, typename V>
#     int
#     py_dict_to_cpp_std_map_like(PyObject *op, std::unordered_map<K, V> &map);
CPP_PY_DICT_TO_MAP_TYPE_BASE_DECL = """template<template<typename ...> class Map, typename K, typename V>
int 
py_dict_to_cpp_std_map_like(PyObject *op, Map<K, V> &map);"""

# Completed declaration, Python to C++, example:
# template<>
#     int
#     py_dict_to_cpp_std_map_like<std::unordered_map, long, long>(PyObject *op, std::unordered_map<long, long> &map);
CPP_PY_DICT_TO_MAP_TYPE_DECL = """template <>
int
py_dict_to_cpp_std_map_like<{cpp_map_type}, {cpp_type_K}, {cpp_type_V}>(PyObject* op, {cpp_map_type}<{cpp_type_K}, {cpp_type_V}> &map);"""

# Definitions to go in implementation file
# Python to C++, example:
#     template<>
#     int
#     py_dict_to_cpp_std_map_like<std::unordered_map, long, long>(PyObject *op, std::unordered_map<long, long> &map) {
#         return generic_py_dict_to_cpp_std_map_like<
#                 std::unordered_map,
#                 long, long,
#                 &py_long_check, &py_long_check,
#                 &py_long_to_cpp_long, &py_long_to_cpp_long
#         >(op, map);
#     }
CPP_PY_DICT_TO_MAP_TYPE_DEFN = """template <>
int
py_dict_to_cpp_std_map_like<{cpp_map_type}, {type_K}, {type_V}>(PyObject* op, {cpp_map_type}<{type_K}, {type_V}> &map) {{
    return generic_py_dict_to_cpp_std_map_like<
        {cpp_map_type},
        {type_K}, {type_V},
        &{py_check_K}, &{py_check_V},
        &{convert_K_from_py}, &{convert_V_from_py}
    >(op, map);
}}
"""


# ==== END: String templates for C++ declarations and definitions. ====

# Example:
#     // Definition for std::vector -> tuple
#     template <>
#     PyObject *
#     cpp_std_list_like_to_py_tuple<long>(const std::vector<long> &container) {
#         return generic_cpp_std_vector_to_py_tuple<long, &cpp_long_to_py_long>(container);
#     }
#
#     return generic_cpp_std_vector_to_py_tuple<bool, &cpp_bool_to_py_bool>(container);
# //    return generic_cpp_std_list_like_to_py_tuple<bool, &cpp_bool_to_py_bool>(container);
#
# name generic_cpp_std_vector_to_py_tuple
# was generic_cpp_std_list_like_to_py_tuple
# now generic_cpp_std_vector_to_py_tuple
#
# template <>
# PyObject *
# cpp_std_list_like_to_py_tuple<bool>(const std::vector<bool> &container) {
#     // FIXME:
#     return generic_cpp_std_vector_to_py_tuple<bool, &cpp_bool_to_py_bool>(container);
# //    return generic_cpp_std_list_like_to_py_tuple<bool, &cpp_bool_to_py_bool>(container);
# }

def defn_name_from_decl_name(name: str,  cpp_container: str) -> str:
    """Returns the definition name given the declaration name by the convention that it is preceded with 'generic_'.
    These 'generic_*' functions are handwritten templates in python_convert.h
    """
    container_name = cpp_container.replace('::', '_')
    return 'generic_{}'.format(name.replace('std_list_like', container_name))


class CodeCount(typing.NamedTuple):
    """PoD class that contains a list of C++ lines of code and a count of the number of declarations or definitions."""
    code: typing.List[str]
    count: int


def unary_declarations() -> CodeCount:
    """Returns the C++ code for the unary declarations (tuples, lists, sets and so on)."""
    code = []
    count = 0
    with code_gen_documentation.cpp_comment_section(code, 'Unary collections <-> Python collections', '*'):
        for unary_collection in UNARY_COLLECTIONS:
            with code_gen_documentation.cpp_comment_section(code,
                                                            '{} -> Python {}'.format(unary_collection.cpp_container,
                                                                                     unary_collection.python_container),
                                                            '-'):
                # //---------------------- std::vector -> Python tuple ----------------------
                code.append(code_gen_documentation.comment_str(' Base declaration'))
                # Doxygen comment
                code.extend(
                    code_gen_documentation.doxygen_cpp_to_python_unary_base_class(unary_collection.cpp_container,
                                                                                  unary_collection.python_container))
                code.append(CPP_UNARY_FUNCTION_TO_PY_BASE_DECL.format(fn=unary_collection.decl_to_py,
                                                                      cpp_container=unary_collection.cpp_container))
                code.append('')
                code.append(code_gen_documentation.comment_str(' Instantiations'))
                for cpp_type in CPP_TYPE_TO_FUNCS:
                    # Doxygen comment
                    code.extend(
                        code_gen_documentation.doxygen_cpp_to_python_unary_instantiation(
                            unary_collection.cpp_container, unary_collection.python_container, cpp_type,
                            CPP_TYPE_TO_FUNCS[cpp_type].py_type
                        )
                    )
                    code.append(CPP_UNARY_FUNCTION_TO_PY_DECL.format(
                        fn=unary_collection.decl_to_py,
                        cpp_container=unary_collection.cpp_container,
                        cpp_type=cpp_type,
                    ))
                    count += 1
                    code.append('')
            with code_gen_documentation.cpp_comment_section(code,
                                                            'Python {} -> {}'.format(unary_collection.python_container,
                                                                                     unary_collection.cpp_container),
                                                            '-'):
                code.append(code_gen_documentation.comment_str(' Base declaration'))
                # Doxygen comment
                code.extend(
                    code_gen_documentation.doxygen_python_to_cpp_unary_base_class(unary_collection.cpp_container,
                                                                                  unary_collection.python_container))
                code.append(PY_TO_CPP_UNARY_FUNCTION_BASE_DECL.format(
                    fn=unary_collection.decl_to_cpp,
                    cpp_container=unary_collection.cpp_container
                ))
                code.append('')
                code.append(code_gen_documentation.comment_str(' Instantiations'))
                for cpp_type in CPP_TYPE_TO_FUNCS:
                    # Doxygen comment
                    code.extend(
                        code_gen_documentation.doxygen_python_to_cpp_unary_instantiation(
                            unary_collection.cpp_container, unary_collection.python_container, cpp_type,
                            CPP_TYPE_TO_FUNCS[cpp_type].py_type
                        )
                    )
                    code.append(PY_TO_CPP_UNARY_FUNCTION_DECL.format(
                        fn=unary_collection.decl_to_cpp,
                        cpp_container=unary_collection.cpp_container,
                        cpp_type=cpp_type,
                    ))
                    count += 1
                    code.append('')
    return CodeCount(code, count)


def unary_definitions() -> CodeCount:
    """Returns the C++ code for the unary definitions (tuples, lists, sets and so on)."""
    code = []
    count = 0
    with code_gen_documentation.cpp_comment_section(code, 'Unary collections <-> Python collections', '*'):
        for unary_collection in UNARY_COLLECTIONS:
            with code_gen_documentation.cpp_comment_section(code,
                                                            '{} -> Python {}'.format(unary_collection.cpp_container,
                                                                                     unary_collection.python_container),
                                                            '-'):
                for cpp_type in CPP_TYPE_TO_FUNCS:
                    # Example:
                    #     // Definition for std::vector -> tuple
                    #     template <>
                    #     PyObject *
                    #     cpp_std_list_like_to_py_tuple<long>(const std::vector<long> &container) {
                    #         return generic_cpp_std_vector_to_py_tuple<long, &cpp_long_to_py_long>(container);
                    #     }

                    code.append(CPP_UNARY_FUNCTION_TO_PY_DEFN.format(
                        fn_decl=unary_collection.decl_to_py,
                        fn_defn=defn_name_from_decl_name(unary_collection.decl_to_py, unary_collection.cpp_container),
                        cpp_container=unary_collection.cpp_container,
                        cpp_type=cpp_type,
                        convert_to_py=CPP_TYPE_TO_FUNCS[cpp_type].cpp_type_to_py_type,
                    ))
                    count += 1
            with code_gen_documentation.cpp_comment_section(code,
                                                            'Python {} -> {}'.format(unary_collection.python_container,
                                                                                     unary_collection.cpp_container),
                                                            '-'):
                for cpp_type in CPP_TYPE_TO_FUNCS:
                    code.append(PY_TO_CPP_UNARY_FUNCTION_DEFN.format(
                        fn_decl=unary_collection.decl_to_cpp,
                        fn_defn=defn_name_from_decl_name(unary_collection.decl_to_cpp, unary_collection.cpp_container),
                        cpp_container=unary_collection.cpp_container,
                        cpp_type=cpp_type,
                        py_check=CPP_TYPE_TO_FUNCS[cpp_type].py_check,
                        convert_from_py=CPP_TYPE_TO_FUNCS[cpp_type].py_type_to_cpp_type,
                    ))
                    count += 1
    return CodeCount(code, count)


def dict_map_declarations() -> CodeCount:
    """Returns the C++ code for the Python dictionary declarations."""
    code = []
    count_decl = 0
    for cpp_map_type in CPP_MAP_TYPES:
        with code_gen_documentation.cpp_comment_section(code, f'std::{cpp_map_type} <-> Python dict', '*'):
            # Python dict
            with code_gen_documentation.cpp_comment_section(code, f'std::{cpp_map_type} -> Python dict', '-'):
                code.append(code_gen_documentation.comment_str(' Base declaration'))
                # Doxygen comment
                code.extend(code_gen_documentation.doxygen_cpp_to_python_dict_base_class())
                code.append(CPP_MAP_TYPE_TO_PY_DICT_BASE_DECL.format(cpp_map_type=cpp_map_type))
                code.append('')
                count_decl += 1
                code.append(code_gen_documentation.comment_str(' Instantiations'))
                for k, v in itertools.product(CPP_TYPE_TO_FUNCS.keys(), repeat=2):
                    # Doxygen comment
                    code.extend(
                        code_gen_documentation.doxygen_cpp_to_python_dict_instantiation(
                            k, v, CPP_TYPE_TO_FUNCS[k].py_type, CPP_TYPE_TO_FUNCS[v].py_type,
                        )
                    )
                    code.append(
                        CPP_MAP_TYPE_TO_PY_DICT_DECL.format(cpp_map_type=cpp_map_type, cpp_type_K=k, cpp_type_V=v))
                    code.append('')
                    count_decl += 1
            with code_gen_documentation.cpp_comment_section(code, 'Python dict -> std::unordered_map', '-'):
                code.append(code_gen_documentation.comment_str(' Base declaration'))
                # Doxygen comment
                code.extend(code_gen_documentation.doxygen_python_dict_to_cpp_base_class())
                code.append(CPP_PY_DICT_TO_MAP_TYPE_BASE_DECL.format(cpp_map_type=cpp_map_type))
                code.append('')
                count_decl += 1
                code.append(code_gen_documentation.comment_str(' Instantiations'))
                for k, v in itertools.product(CPP_TYPE_TO_FUNCS.keys(), repeat=2):
                    # Doxygen comment
                    code.extend(
                        code_gen_documentation.doxygen_python_dict_to_cpp_instantiation(
                            k, v, CPP_TYPE_TO_FUNCS[k].py_type, CPP_TYPE_TO_FUNCS[v].py_type,
                        )
                    )
                    code.append(
                        CPP_PY_DICT_TO_MAP_TYPE_DECL.format(cpp_map_type=cpp_map_type, cpp_type_K=k, cpp_type_V=v))
                    code.append('')
                    count_decl += 1
    return CodeCount(code, count_decl)


def dict_map_definitions() -> CodeCount:
    """Returns the C++ code for the Python dictionary definitions."""
    code = []
    count_defn = 0
    for cpp_map_type in CPP_MAP_TYPES:
        with code_gen_documentation.cpp_comment_section(code, f'std::{cpp_map_type} <-> Python dict', '*'):
            for k, v in itertools.product(CPP_TYPE_TO_FUNCS.keys(), repeat=2):
                code.append(code_gen_documentation.comment_str('{}'.format(
                    ' Converts a std::{cpp_map_type}<{type_K}, {type_V}> '.format(
                        cpp_map_type=cpp_map_type, type_K=k, type_V=v,
                    ).center(code_gen_documentation.WIDTH, '-')
                )))
                code.append(code_gen_documentation.comment_str('{}'.format(
                    ' to a Python dict of {{ {type_K} : {type_V}, ...}}    '.format(
                        type_K=k, type_V=v,
                    ).center(code_gen_documentation.WIDTH, '-')
                )))
                code.append(CPP_MAP_TYPE_TO_PY_DICT_DEFN.format(
                    cpp_map_type=cpp_map_type,
                    type_K=k, type_V=v,
                    convert_K_to_py=CPP_TYPE_TO_FUNCS[k].cpp_type_to_py_type,
                    convert_V_to_py=CPP_TYPE_TO_FUNCS[v].cpp_type_to_py_type,
                ))
                count_defn += 1
                code.append(code_gen_documentation.comment_str('{}'.format(
                    ' Converts a Python dict of {{{type_K} : {type_V}, ...}} '.format(
                        type_K=k, type_V=v,
                    ).center(code_gen_documentation.WIDTH, '-')
                )))
                code.append(code_gen_documentation.comment_str('{}'.format(
                    ' to a std::{cpp_map_type}<{type_K}, {type_V}> '.format(
                        cpp_map_type=cpp_map_type,
                        type_K=k, type_V=v,
                    ).center(code_gen_documentation.WIDTH, '-')
                )))
                code.append(CPP_PY_DICT_TO_MAP_TYPE_DEFN.format(
                    cpp_map_type=cpp_map_type,
                    type_K=k, type_V=v,
                    py_check_K=CPP_TYPE_TO_FUNCS[k].py_check,
                    py_check_V=CPP_TYPE_TO_FUNCS[v].py_check,
                    convert_K_from_py=CPP_TYPE_TO_FUNCS[k].py_type_to_cpp_type,
                    convert_V_from_py=CPP_TYPE_TO_FUNCS[v].py_type_to_cpp_type,
                ))
                count_defn += 1
    return CodeCount(code, count_defn)


def declarations() -> CodeCount:
    """Returns the C++ code for all declarations."""
    code_lines: typing.List[str] = []
    count_decl = 0
    with code_gen_documentation.cpp_comment_section(code_lines, 'Declaration file', '='):
        with code_gen_documentation.get_codegen_please_no_edit_warning_context(code_lines):
            code_lines.extend(code_gen_documentation.documentation(UNARY_COLLECTIONS, CPP_TYPE_TO_FUNCS))
            code_lines.append('#include <Python.h>')
            code_lines.append('')
            for include in REQUIRED_INCLUDES:
                code_lines.append('#include {}'.format(include))
            code_lines.append('')
            code_lines.append(f'namespace {CPP_NAMESPACE} {{\n')
            code_lines.append('')
            # Unary functions
            code_count = unary_declarations()
            count_decl += code_count.count
            code_lines.extend(code_count.code)
            code_count = dict_map_declarations()
            count_decl += code_count.count
            code_lines.extend(code_count.code)
            code_lines.append(code_gen_documentation.comment_str(' Declarations written: {}'.format(count_decl)))
        code_lines.append('')
        code_lines.append('} ' + code_gen_documentation.comment_str(f' namespace {CPP_NAMESPACE}'))
        code_lines.append('')
    return CodeCount(code_lines, count_decl)


def definitions() -> CodeCount:
    """Returns the C++ code for all definitions."""
    code_lines: typing.List[str] = []
    count_defn = 0
    with code_gen_documentation.cpp_comment_section(code_lines, 'Definition file', '='):
        with code_gen_documentation.get_codegen_please_no_edit_warning_context(code_lines):
            code_lines.extend(code_gen_documentation.documentation(UNARY_COLLECTIONS, CPP_TYPE_TO_FUNCS))
            code_lines.append('#include "python_convert.h"')
            code_lines.append('')
            code_lines.append(f'namespace {CPP_NAMESPACE} {{\n')
            code_count = unary_definitions()
            count_defn += code_count.count
            code_lines.extend(code_count.code)
            code_count = dict_map_definitions()
            count_defn += code_count.count
            code_lines.extend(code_count.code)
            code_lines.append(code_gen_documentation.comment_str(' Definitions written: {}'.format(count_defn)))
        code_lines.append('')
        code_lines.append('} ' + code_gen_documentation.comment_str(f' namespace {CPP_NAMESPACE}'))
        code_lines.append('')
    return CodeCount(code_lines, count_defn)


AUTO_FILE_NAME = 'auto_py_convert_internal'


def write_files() -> None:
    """Writes all C++ files."""
    dir_path = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir, 'cpy'))
    print('Target directory "{}"'.format(dir_path))
    file_path = os.path.join(dir_path, '{}.h'.format(AUTO_FILE_NAME))
    print('Writing declarations to "{}"'.format(file_path))
    with open(file_path, 'w') as f:
        code_lines_and_count = declarations()
        for line in code_lines_and_count.code:
            f.write('{}\n'.format(line))
        line_count = sum(len(fragment.split('\n')) for fragment in code_lines_and_count.code)
        print(f'Wrote {line_count} lines of code with {code_lines_and_count.count} declarations.')
    file_path = os.path.join(dir_path, '{}.cpp'.format(AUTO_FILE_NAME))
    print('Writing definitions to  "{}"'.format(file_path))
    with open(file_path, 'w') as f:
        code_lines_and_count = definitions()
        for line in code_lines_and_count.code:
            f.write('{}\n'.format(line))
        line_count = sum(len(fragment.split('\n')) for fragment in code_lines_and_count.code)
        print(f'Wrote {line_count} lines of code with {code_lines_and_count.count} definitions.')


def main():
    write_files()
    return 0


if __name__ == '__main__':
    exit(main())
