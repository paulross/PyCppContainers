"""
Writes out .h and .cpp files to support Python/C++ homogeneous containers.

This facilitates conversion between Python and C++ containers where the Python types are consistent.

For example a Python set of strings to and from a C++ unordered_set<std::string>

TODO: Add Doxygen style documentation:

// Base declaration
/**
 * Base declaration for converting C++ vectors to Python tuples.
 *
 * @tparam T C++ type.
 * @param container C++ input as a std::vector<T>.
 * @return A Python tuple containing type T.
 */
template<typename T>
PyObject *
cpp_std_vector_to_py_tuple(const std::vector<T> &container);

// Instantiations

/**
 * Instantiation for converting C++ vectors of bool to Python tuples or bool.
 *
 * @param container C++ input as a std::vector<bool>.
 * @return A Python tuple containing booleans.
 */
template <>
PyObject *
cpp_std_vector_to_py_tuple<bool>(const std::vector<bool> &container);
"""
import contextlib
import itertools
import logging
import os
import typing

from src.cpy.code_gen_common import CppTypeFunctions, UnaryFunctions
from src.cpy.code_gen_documentation import comment_str, cpp_comment_section, documentation, WIDTH

logger = logging.getLogger(__file__)

CPP_NAMESPACE = 'Python_Cpp_Containers'

# Note on nomenclature:
# 'cpp' is C++
# C++ namespaced types are '_' separated so 'std::vector' is 'cpp_std_vector'
# 'py' is Python
# Conversion functions are always ..._to_...
CPP_TYPE_TO_FUNCS = {
    'bool': CppTypeFunctions('cpp_bool_to_py_bool', 'py_bool_check', 'py_bool_to_cpp_bool'),
    'long': CppTypeFunctions('cpp_long_to_py_long', 'py_long_check', 'py_long_to_cpp_long'),
    'double': CppTypeFunctions('cpp_double_to_py_float', 'py_float_check', 'py_float_to_cpp_double'),
    # 'std::complex<double>': CppTypeFunctions('py_complex_from_complex', 'py_complex_check', 'py_complex_as_complex'),
    'std::string': CppTypeFunctions('cpp_string_to_py_bytes', 'py_bytes_check', 'py_bytes_to_cpp_string'),
}

UNARY_COLLECTIONS = {
    'tuple': UnaryFunctions('std::vector', 'cpp_std_vector_to_py_tuple', 'py_tuple_to_cpp_std_vector'),
    'list': UnaryFunctions('std::vector', 'cpp_std_vector_to_py_list', 'py_list_to_cpp_std_vector'),
    'set': UnaryFunctions('std::unordered_set', 'cpp_std_unordered_set_to_py_set', 'py_set_to_cpp_std_unordered_set'),
    'frozenset': UnaryFunctions('std::unordered_set', 'cpp_std_unordered_set_to_py_frozenset',
                                'py_frozenset_to_cpp_std_unordered_set'),
}

# Not really needed as the hand written file, python_convert.h does this.
REQUIRED_INCLUDES = [
]


# Declarations to go in header file
# Base declaration to convert to Python, requires fn= and cpp_container=
CPP_UNARY_FUNCTION_TO_PY_BASE_DECL = """template<typename T>
PyObject *
{fn}(const {cpp_container}<T> &container);"""

# Convert to Python, requires fn=, cpp_type= and cpp_container=
CPP_UNARY_FUNCTION_TO_PY_DECL = """template <>
PyObject *
{fn}<{cpp_type}>(const {cpp_container}<{cpp_type}> &container);"""

# Base declararation to convert from Python, requires fn= and cpp_container=
CPP_UNARY_FUNCTION_FROM_PY_BASE_DECL = """template<typename T>
int
{fn}(PyObject *op, {cpp_container}<T> &container);"""

# Convert from Python, requires fn=, cpp_type= and cpp_container=
CPP_UNARY_FUNCTION_FROM_PY_DECL = """template <>
int
{fn}<{cpp_type}>(PyObject *op, {cpp_container}<{cpp_type}> &container);"""


# Definitions to go in implementation file
# To Python, reqires fn_decl=, cpp_type=, cpp_container=, fn_defn=, convert_to_py=
CPP_UNARY_FUNCTION_TO_PY_DEFN = """template <>
PyObject *
{fn_decl}<{cpp_type}>(const {cpp_container}<{cpp_type}> &container) {{
    return {fn_defn}<{cpp_type}, &{convert_to_py}>(container);
}}
"""

# From Python, requires fn_decl=, cpp_type=, cpp_container=, fn_defn=, py_check=, convert_to_py=
CPP_UNARY_FUNCTION_FROM_PY_DEFN = """template <>
int
{fn_decl}<{cpp_type}>(PyObject *op, {cpp_container}<{cpp_type}> &container) {{
    return {fn_defn}<{cpp_type}, &{py_check}, &{convert_from_py}>(op, container);
}}
"""

# ===== std::unordered_map <-> dict ====
# Declarations to go in header file
CPP_STD_UNORDERED_MAP_TO_PY_DICT_BASE_DECL = """template<typename K, typename V>
PyObject *
cpp_std_unordered_map_to_py_dict(const std::unordered_map<K, V> &map);"""

CPP_STD_UNORDERED_MAP_TO_PY_DICT_DECL = """template <>
PyObject *
cpp_std_unordered_map_to_py_dict<{cpp_type_K}, {cpp_type_V}>(const std::unordered_map<{cpp_type_K}, {cpp_type_V}> &map);"""

CPP_PY_DICT_TO_STD_UNORDERED_MAP_BASE_DECL = """template<typename K, typename V>
int 
py_dict_to_cpp_std_unordered_map(PyObject *op, std::unordered_map<K, V> &map);"""

CPP_PY_DICT_TO_STD_UNORDERED_MAP_DECL = """template <>
int
py_dict_to_cpp_std_unordered_map<{cpp_type_K}, {cpp_type_V}>(PyObject* op, std::unordered_map<{cpp_type_K}, {cpp_type_V}> &map);"""

# Definitions to go in implementation file
CPP_STD_UNORDERED_MAP_TO_PY_DICT_DEFN = """template <>
PyObject *
cpp_std_unordered_map_to_py_dict<{type_K}, {type_V}>(const std::unordered_map<{type_K}, {type_V}> &map) {{
    return generic_cpp_std_unordered_map_to_py_dict<
        {type_K}, {type_V},
        &{convert_K_to_py}, &{convert_V_to_py}
    >(map);
}}
"""

CPP_PY_DICT_TO_STD_UNORDERED_MAP_DEFN = """template <>
int
py_dict_to_cpp_std_unordered_map<{type_K}, {type_V}>(PyObject* op, std::unordered_map<{type_K}, {type_V}> &map) {{
    return generic_py_dict_to_cpp_std_unordered_map<
        {type_K}, {type_V},
        &{py_check_K}, &{py_check_V},
        &{convert_K_from_py}, &{convert_V_from_py}
    >(op, map);
}}
"""
#===== END: std::unordered_map <-> dict ====


def get_codegen_please_no_edit_warning(is_end: bool) -> typing.List[str]:
    """Writes the start or end of a warning comment."""
    if is_end:
        prefix = 'END: '
    else:
        prefix = ''
    return [
        comment_str('{}'.format('#' * WIDTH)),
        comment_str('{}'.format(
                ' {prefix}Auto-generated code - do not edit. Seriously, do NOT edit. '.format(
                    prefix=prefix).center(WIDTH, '#')
            )
        ),
        comment_str('{}'.format('#' * WIDTH)),
    ]


@contextlib.contextmanager
def get_codegen_please_no_edit_warning_context(str_list: typing.List[str]):
    """Context manager that writes the start or end of a warning comment."""
    str_list.extend(get_codegen_please_no_edit_warning(False))
    yield
    str_list.extend(get_codegen_please_no_edit_warning(True))


def defn_name_from_decl_name(name: str) -> str:
    """Returns the definition name given the declaration name by the convention that it is preceded with 'generic_'."""
    return 'generic_{}'.format(name)


class CodeCount(typing.NamedTuple):
    """PoD class that contains a list of C++ lines of code and a count of the number of declarations definitions."""
    code: typing.List[str]
    count: int


def unary_declarations() -> CodeCount:
    """Returns the C++ code for the unary declarations."""
    code = []
    count = 0
    with cpp_comment_section(code, 'Unary collections <-> Python collections', '*'):
        for k, v in UNARY_COLLECTIONS.items():
            with cpp_comment_section(code, '{} -> Python {}'.format(v.cpp_container, k), '-'):
                # //---------------------- std::vector -> Python tuple ----------------------
                code.append(comment_str(' Base declaration'))
                code.append(CPP_UNARY_FUNCTION_TO_PY_BASE_DECL.format(fn=v.decl_to_py, cpp_container=v.cpp_container))
                # code.append('')
                code.append(comment_str(' Instantiations'))
                for cpp_type in CPP_TYPE_TO_FUNCS:
                    code.append(CPP_UNARY_FUNCTION_TO_PY_DECL.format(
                        fn=v.decl_to_py,
                        cpp_container=v.cpp_container,
                        cpp_type=cpp_type,
                    ))
                    count += 1
                    # code.append('')
            with cpp_comment_section(code, 'Python {} -> {}'.format(k, v.cpp_container), '-'):
                code.append(comment_str(' Base declaration'))
                code.append(CPP_UNARY_FUNCTION_FROM_PY_BASE_DECL.format(
                    fn=v.decl_to_cpp,
                    cpp_container=v.cpp_container
                ))
                # code.append('')
                code.append(comment_str(' Instantiations'))
                for cpp_type in CPP_TYPE_TO_FUNCS:
                    code.append(CPP_UNARY_FUNCTION_FROM_PY_DECL.format(
                        fn=v.decl_to_cpp,
                        cpp_container=v.cpp_container,
                        cpp_type=cpp_type,
                    ))
                    count += 1
                    # code.append('')
    return CodeCount(code, count)


def unary_definitions() -> CodeCount:
    """Returns the C++ code for the unary definitions."""
    code = []
    count = 0
    with cpp_comment_section(code, 'Unary collections <-> Python collections', '*'):
        for k, v in UNARY_COLLECTIONS.items():
            with cpp_comment_section(code, '{} -> Python {}'.format(v.cpp_container, k), '-'):
                # //---------------------- std::vector -> Python tuple ----------------------
                for cpp_type in CPP_TYPE_TO_FUNCS:
                    code.append(CPP_UNARY_FUNCTION_TO_PY_DEFN.format(
                        fn_decl=v.decl_to_py,
                        fn_defn=defn_name_from_decl_name(v.decl_to_py),
                        cpp_container=v.cpp_container,
                        cpp_type=cpp_type,
                        convert_to_py=CPP_TYPE_TO_FUNCS[cpp_type].cpp_type_to_py_type,
                    ))
                    count += 1
            with cpp_comment_section(code, 'Python {} -> {}'.format(k, v.cpp_container), '-'):
                for cpp_type in CPP_TYPE_TO_FUNCS:
                    code.append(CPP_UNARY_FUNCTION_FROM_PY_DEFN.format(
                        fn_decl=v.decl_to_cpp,
                        fn_defn=defn_name_from_decl_name(v.decl_to_cpp),
                        cpp_container=v.cpp_container,
                        cpp_type=cpp_type,
                        py_check=CPP_TYPE_TO_FUNCS[cpp_type].py_check,
                        convert_from_py=CPP_TYPE_TO_FUNCS[cpp_type].py_type_to_cpp_type,
                    ))
                    count += 1
    return CodeCount(code, count)


def dict_declarations() -> CodeCount:
    """Returns the C++ code for the Python dictionary declarations."""
    code = []
    count_decl = 0
    with cpp_comment_section(code, 'std::unordered_map <-> Python dict', '*'):
        # Python dict
        with cpp_comment_section(code, 'std::unordered_map -> Python dict', '-'):
            code.append(comment_str(' Base declaration'))
            code.append(CPP_STD_UNORDERED_MAP_TO_PY_DICT_BASE_DECL)
            # code.append('')
            count_decl += 1
            code.append(comment_str(' Instantiations'))
            for k, v in itertools.product(CPP_TYPE_TO_FUNCS.keys(), repeat=2):
                code.append(CPP_STD_UNORDERED_MAP_TO_PY_DICT_DECL.format(cpp_type_K=k, cpp_type_V=v))
                # code.append('')
                count_decl += 1
        with cpp_comment_section(code, 'Python dict -> std::unordered_map', '-'):
            code.append(comment_str(' Base declaration'))
            code.append(CPP_PY_DICT_TO_STD_UNORDERED_MAP_BASE_DECL)
            # code.append('')
            count_decl += 1
            code.append(comment_str(' Instantiations'))
            for k, v in itertools.product(CPP_TYPE_TO_FUNCS.keys(), repeat=2):
                code.append(CPP_PY_DICT_TO_STD_UNORDERED_MAP_DECL.format(cpp_type_K=k, cpp_type_V=v))
                # code.append('')
                count_decl += 1
    return CodeCount(code, count_decl)


def dict_definitions() -> CodeCount:
    """Returns the C++ code for the Python dictionary definitions."""
    code = []
    count_defn = 0
    with cpp_comment_section(code, 'std::unordered_map <-> Python dict', '*'):
        for k, v in itertools.product(CPP_TYPE_TO_FUNCS.keys(), repeat=2):
            code.append(comment_str('{}'.format(
                ' Converts a std::unordered_map<{type_K}, {type_V}> '.format(
                    type_K=k, type_V=v,
                ).center(WIDTH, '-')
            )))
            code.append(comment_str('{}'.format(
                ' to a Python dict of {{ {type_K} : {type_V}, ...}}    '.format(
                    type_K=k, type_V=v,
                ).center(WIDTH, '-')
            )))
            code.append(CPP_STD_UNORDERED_MAP_TO_PY_DICT_DEFN.format(
                type_K=k, type_V=v,
                convert_K_to_py=CPP_TYPE_TO_FUNCS[k].cpp_type_to_py_type,
                convert_V_to_py=CPP_TYPE_TO_FUNCS[v].cpp_type_to_py_type,
            ))
            count_defn += 1
            code.append(comment_str('{}'.format(
                ' Converts a Python dict of {{{type_K} : {type_V}, ...}} '.format(
                    type_K=k, type_V=v,
                ).center(WIDTH, '-')
            )))
            code.append(comment_str('{}'.format(
                ' to a std::unordered_map<{type_K}, {type_V}> '.format(
                    type_K=k, type_V=v,
                ).center(WIDTH, '-')
            )))
            code.append(CPP_PY_DICT_TO_STD_UNORDERED_MAP_DEFN.format(
                type_K=k, type_V=v,
                py_check_K=CPP_TYPE_TO_FUNCS[k].py_check,
                py_check_V=CPP_TYPE_TO_FUNCS[v].py_check,
                convert_K_from_py=CPP_TYPE_TO_FUNCS[k].py_type_to_cpp_type,
                convert_V_from_py=CPP_TYPE_TO_FUNCS[v].py_type_to_cpp_type,
            ))
            count_defn += 1
    return CodeCount(code, count_defn)


def declarations() -> typing.List[str]:
    """Returns the C++ code for all declarations."""
    ret = []
    with cpp_comment_section(ret, 'Declaration file', '='):
        with get_codegen_please_no_edit_warning_context(ret):
            ret.extend(documentation(UNARY_COLLECTIONS, CPP_TYPE_TO_FUNCS))
            ret.append('#include <Python.h>')
            ret.append('')
            for include in REQUIRED_INCLUDES:
                ret.append('#include {}'.format(include))
            ret.append('')
            ret.append(f'namespace {CPP_NAMESPACE} {{\n')
            ret.append('')
            count_decl = 0
            # Unary functions
            code_count = unary_declarations()
            count_decl += code_count.count
            ret.extend(code_count.code)
            code_count = dict_declarations()
            count_decl += code_count.count
            ret.extend(code_count.code)
            ret.append(comment_str(' Declarations written: {}'.format(count_decl)))
        ret.append('')
        ret.append('} ' + comment_str(f' namespace {CPP_NAMESPACE}'))
        ret.append('')
    return ret


def definitions() -> typing.List[str]:
    """Returns the C++ code for all definitions."""
    ret = []
    with cpp_comment_section(ret, 'Definition file', '='):
        with get_codegen_please_no_edit_warning_context(ret):
            ret.extend(documentation(UNARY_COLLECTIONS, CPP_TYPE_TO_FUNCS))
            ret.append('#include "python_convert.h"')
            ret.append('')
            ret.append(f'namespace {CPP_NAMESPACE} {{\n')
            count_defn = 0
            code_count = unary_definitions()
            count_defn += code_count.count
            ret.extend(code_count.code)
            code_count = dict_definitions()
            count_defn += code_count.count
            ret.extend(code_count.code)
            ret.append(comment_str(' Definitions written: {}'.format(count_defn)))
        ret.append('')
        ret.append('} ' + comment_str(f' namespace {CPP_NAMESPACE}'))
        ret.append('')
    return ret


AUTO_FILE_NAME = 'auto_py_convert_internal'


def write_files() -> None:
    """Writes all C++ files."""
    dir_path = os.path.dirname(os.path.abspath(__file__))
    file_path = os.path.join(dir_path, '{}.h'.format(AUTO_FILE_NAME))
    print('Writing declarations to "{}"'.format(file_path))
    with open(file_path, 'w') as f:
        for line in declarations():
            f.write('{}\n'.format(line))
    file_path = os.path.join(dir_path, '{}.cpp'.format(AUTO_FILE_NAME))
    print('Writing definitions to  "{}"'.format(file_path))
    with open(file_path, 'w') as f:
        for line in definitions():
            f.write('{}\n'.format(line))


def main():
    write_files()
    return 0


if __name__ == '__main__':
    exit(main())
