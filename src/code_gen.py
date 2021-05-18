"""
Writes out .hpp and .cpp files to support Python/C++ homogeneous containers.

This facilitates conversion between Python and C++ containers where the Python types are consistent.

For example a Python set of strings to and from a C++ unordered_set<std::string>

"""
import collections
import contextlib
import itertools
import logging
import os
import typing


logger = logging.getLogger(__file__)


class CppFunctions(typing.NamedTuple):
    to_py_type: str
    py_check: str
    from_py_type: str


CPP_TYPE_TO_FUNCS = {
    'double': CppFunctions('py_float_from_double', 'py_float_check', 'PyFloat_AsDouble'),
    # 'long': CppFunctions('py_long_from_long', 'py_long_check', 'PyLong_AsLong'),
    # 'std::string': CppFunctions('py_str_from_std_string', 'py_str_check', 'py_str_as_std_sting'),
    # 'bool': CppFunctions('py_bool_from_bool', 'py_bool_check', 'py_bool_as_bool'),
}

# TODO: Sort out nomenclature, here we use to_py, to_cpp. In other places we use to/from


class UnaryFunctions(typing.NamedTuple):
    cpp_container: str
    decl_to_py: str
    decl_to_cpp: str


UNARY_COLLECTIONS = {
    'tuple': UnaryFunctions('std::vector', 'std_vector_to_py_tuple', 'py_tuple_to_std_vector'),
    # 'set': UnaryFunctions('std::unordered_set', 'std_unordered_set_to_py_set', 'py_set_to_std_unordered_set'),
}

REQUIRED_INCLUDES = [
    '<vector>',
    '<unordered_map>',
]


def required_function_declarations() -> typing.List[str]:
    ret: typing.List[str] = []
    ret.append(comment_str('Functions to convert a type:'))
    for cpp_type in CPP_TYPE_TO_FUNCS:
        ret.append('// {cpp_type}'.format(cpp_type=cpp_type))
        ret.append(
            'PyObject *{fn}(const {cpp_type} &value);'.format(
                fn=CPP_TYPE_TO_FUNCS[cpp_type].to_py_type,
                cpp_type=cpp_type,
            )
        )
        ret.append(
            'int {fn}(PyObject *op);'.format(
                fn=CPP_TYPE_TO_FUNCS[cpp_type].py_check,
            )
        )
        ret.append(
            '{cpp_type} {fn}(PyObject *op);'.format(
                fn=CPP_TYPE_TO_FUNCS[cpp_type].from_py_type,
                cpp_type=cpp_type,
            )
        )
    # ret.append(comment_str('Functions to convert containers:'))
    # for c in UNARY_COLLECTIONS:
    #     pass
    return ret


# Declarations to go in header file
# Base declararation to convert to Python, requires fn= and cpp_container=
CPP_UNARY_FUNCTION_TO_PY_BASE_DECL = """// Base declaration
template<typename T>
PyObject *
{fn}(const {cpp_container}<T> &container);"""

# Convert to Python, requires fn=, cpp_type= and cpp_container=
CPP_UNARY_FUNCTION_TO_PY_DECL = """template <>
PyObject *
{fn}<{cpp_type}>(const {cpp_container}<{cpp_type}> &container);"""

# Base declararation to convert from Python, requires fn= and cpp_container=
CPP_UNARY_FUNCTION_FROM_PY_BASE_DECL = """// Base declaration
template<typename T>
int
{fn}(PyObject *tuple, {cpp_container}<T> &container);"""

# Convert from Python, requires fn=, cpp_type= and cpp_container=
CPP_UNARY_FUNCTION_FROM_PY_DECL = """template <>
int
{fn}<{cpp_type}>(PyObject *tuple, {cpp_container}<{cpp_type}> &container);"""


# Definitions to go in implementation file
# To Python, reqires fn_decl=, cpp_type=, cpp_container=, fn_defn=, convert_to_py=
CPP_UNARY_FUNCTION_TO_PY_DEFN = """template <>
PyObject *
{fn_decl}<{cpp_type}>(const {cpp_container}<{cpp_type}> &container) {{
    return {fn_defn}<{cpp_type}, &{convert_to_py}>(container);
}}
"""

# From Python, reqires fn_decl=, cpp_type=, cpp_container=, fn_defn=, py_check=, convert_to_py=
CPP_UNARY_FUNCTION_FROM_PY_DEFN = """template <> int
{fn_decl}<{cpp_type}>(PyObject *op, {cpp_container}<{cpp_type}> &container) {{
    return {fn_defn}<{cpp_type}, &{py_check}, &{convert_from_py}>(op, container);
}}
"""

#===== std::unordered_map <-> dict ====
# Declarations to go in header file
CPP_STD_UNORDERED_MAP_TO_PY_DICT_BASE_DECL = """// Base declaration
template<typename K, typename V>
PyObject *
std_unordered_map_to_py_dict(const std::unordered_map<K, V> &map);
// Instantiations"""

CPP_STD_UNORDERED_MAP_TO_PY_DICT_DECL = """template <>
PyObject *
std_unordered_map_to_py_dict<{cpp_type_K}, {cpp_type_V}>(const std::unordered_map<{cpp_type_K}, {cpp_type_V}> &map);"""

CPP_PY_DICT_TO_STD_UNORDERED_MAP_BASE_DECL = """// Base declaration
template<typename K, typename V>
int 
py_dict_to_std_unordered_map(PyObject *op, std::unordered_map<K, V> &map);
// Instantiations"""

CPP_PY_DICT_TO_STD_UNORDERED_MAP_DECL = """template <>
int
py_dict_to_std_unordered_map<{cpp_type_K}, {cpp_type_V}>(PyObject* op, std::unordered_map<{cpp_type_K}, {cpp_type_V}> &map);"""

# Definitions to go in implementation file
CPP_STD_UNORDERED_MAP_TO_PY_DICT_DEFN = """template <>
PyObject *
std_unordered_map_to_py_dict<{type_K}, {type_V}>(const std::unordered_map<{type_K}, {type_V}> &map) {{
    return _std_unordered_map_to_py_dict<
        {type_K}, {type_V},
        &{convert_K_to_py}, &{convert_V_to_py}
    >(map);
}}
"""

CPP_PY_DICT_TO_STD_UNORDERED_MAP_DEFN = """template <> int
py_dict_to_std_unordered_map<{type_K}, {type_V}>(PyObject* op, std::unordered_map<{type_K}, {type_V}> &map) {{
    return _py_dict_to_std_unordered_map<
        {type_K}, {type_V},
        &{py_check_K}, &{py_check_V},
        &{convert_K_from_py}, &{convert_V_from_py}
    >(op, map);
}}
"""
#===== END: std::unordered_map <-> dict ====

WIDTH = 75 - len('//')

def get_codegen_warning(is_end: bool) -> typing.List[str]:
    if is_end:
        prefix = 'END: '
    else:
        prefix = ''
    return [
        '//{}'.format('#' * WIDTH),
        '//{}'.format(
            ' {prefix}Auto-generated code - do not edit. Seriously, do NOT edit. '.format(prefix=prefix).center(WIDTH, '#')),
        '//{}'.format('#' * WIDTH),
    ]


@contextlib.contextmanager
def cpp_comment_section(str_list: typing.List[str], title:str, sep:str):
    """Context manager for writing begining and end comments."""
    str_list.append('//{}'.format(' {} '.format(title).center(WIDTH, sep)))
    yield
    str_list.append('//{}'.format(' END: {} '.format(title).center(WIDTH, sep)))
    str_list.append('')


def defn_name_from_decl_name(name: str) -> str:
    """Returns the definition name given the declaration name by convention."""
    return '_{}'.format(name)


def comment_str(s: str) -> str:
    assert '\n' not in s
    return '// {}'.format(s)


def comment_list_str(input: typing.List[str]) -> typing.List[str]:
    """Returns the strings as a C++ comments."""
    ret = []
    for s in input:
        if '\n' in s:
            ret.extend([comment_str(v) for v in s.split('\n')])
        else:
            ret.append(comment_str(s))
    return ret


def documentation() -> typing.List[str]:
    ret = [
        'Conversion from homogeneous data structures in Python and C++',
        '',
    ]
    ret.append('Unary conversions')
    for py_container in UNARY_COLLECTIONS:
        ret.append('{}:'.format(py_container))
        for typ in CPP_TYPE_TO_FUNCS:
            ret.append('{} <-> {}<{}>'.format(
                py_container,
                UNARY_COLLECTIONS[py_container].cpp_container,
                typ,
            ))
        ret.append('')
    ret.append('')
    ret.append('Mapping conversions')
    for type_k, type_v in itertools.product(CPP_TYPE_TO_FUNCS.keys(), repeat=2):
        ret.append('{} <-> std::unordered_map<{}, {}>'.format(
            'dict',
            type_k, type_v
        ))
    ret.append('')
    return comment_list_str(ret)


CodeCount = collections.namedtuple('CodeCount', 'code, count')


def unary_declarations() -> CodeCount:
    code = []
    count = 0
    with cpp_comment_section(code, 'Unary collections <-> Python collections', '*'):
        for k, v in UNARY_COLLECTIONS.items():
            with cpp_comment_section(code, '{} -> Python {}'.format(v.cpp_container, k), '-'):
                # //---------------------- std::vector -> Python tuple ----------------------
                code.append(CPP_UNARY_FUNCTION_TO_PY_BASE_DECL.format(fn=v.decl_to_py, cpp_container=v.cpp_container))
                code.append('// Instantiations')
                for cpp_type in CPP_TYPE_TO_FUNCS:
                    code.append(CPP_UNARY_FUNCTION_TO_PY_DECL.format(
                        fn=v.decl_to_py,
                        cpp_container=v.cpp_container,
                        cpp_type=cpp_type,
                    ))
                    count += 1
            with cpp_comment_section(code, 'Python {} -> {}'.format(k, v.cpp_container), '-'):
                code.append(CPP_UNARY_FUNCTION_FROM_PY_BASE_DECL.format(
                    fn=v.decl_to_cpp,
                    cpp_container=v.cpp_container
                ))
                code.append('// Instantiations')
                for cpp_type in CPP_TYPE_TO_FUNCS:
                    code.append(CPP_UNARY_FUNCTION_FROM_PY_DECL.format(
                        fn=v.decl_to_cpp,
                        cpp_container=v.cpp_container,
                        cpp_type=cpp_type,
                    ))
                    count += 1
    return CodeCount(code, count)


def unary_definitions() -> CodeCount:
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
                        convert_to_py=CPP_TYPE_TO_FUNCS[cpp_type].to_py_type,
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
                        convert_from_py=CPP_TYPE_TO_FUNCS[cpp_type].from_py_type,
                    ))
                    count += 1
    return CodeCount(code, count)


def dict_declarations() -> CodeCount:
    code = []
    count_decl = 0
    with cpp_comment_section(code, 'std::unordered_map <-> Python dict', '*'):
        # Python dict
        with cpp_comment_section(code, 'std::unordered_map -> Python dict', '-'):
            code.append(CPP_STD_UNORDERED_MAP_TO_PY_DICT_BASE_DECL)
            count_decl += 1
            for k, v in itertools.product(CPP_TYPE_TO_FUNCS.keys(), repeat=2):
                code.append(CPP_STD_UNORDERED_MAP_TO_PY_DICT_DECL.format(cpp_type_K=k, cpp_type_V=v))
                count_decl += 1
        with cpp_comment_section(code, 'Python dict -> std::unordered_map', '-'):
            code.append(CPP_PY_DICT_TO_STD_UNORDERED_MAP_BASE_DECL)
            count_decl += 1
            for k, v in itertools.product(CPP_TYPE_TO_FUNCS.keys(), repeat=2):
                code.append(CPP_PY_DICT_TO_STD_UNORDERED_MAP_DECL.format(cpp_type_K=k, cpp_type_V=v))
                count_decl += 1
    return CodeCount(code, count_decl)


def dict_definitions() -> CodeCount:
    code = []
    count_defn = 0
    with cpp_comment_section(code, 'std::unordered_map <-> Python dict', '*'):
        for k, v in itertools.product(CPP_TYPE_TO_FUNCS.keys(), repeat=2):
            code.append('//{}'.format(
                ' Converts a std::unordered_map<{type_K}, {type_V}> '.format(
                    type_K=k, type_V=v,
                ).center(WIDTH, '-')
            ))
            code.append('//{}'.format(
                ' to a Python dict of {{ {type_K} : {type_V}, ...}}    '.format(
                    type_K=k, type_V=v,
                ).center(WIDTH, '-')
            ))
            code.append(CPP_STD_UNORDERED_MAP_TO_PY_DICT_DEFN.format(
                type_K=k, type_V=v,
                convert_K_to_py=CPP_TYPE_TO_FUNCS[k].to_py_type,
                convert_V_to_py=CPP_TYPE_TO_FUNCS[v].to_py_type,
            ))
            count_defn += 1
            code.append('//{}'.format(
                ' Converts a Python dict of {{{type_K} : {type_V}, ...}} '.format(
                    type_K=k, type_V=v,
                ).center(WIDTH, '-')
            ))
            code.append('//{}'.format(
                ' to a std::unordered_map<{type_K}, {type_V}> '.format(
                    type_K=k, type_V=v,
                ).center(WIDTH, '-')
            ))
            code.append(CPP_PY_DICT_TO_STD_UNORDERED_MAP_DEFN.format(
                type_K=k, type_V=v,
                py_check_K=CPP_TYPE_TO_FUNCS[k].py_check,
                py_check_V=CPP_TYPE_TO_FUNCS[v].py_check,
                convert_K_from_py=CPP_TYPE_TO_FUNCS[k].from_py_type,
                convert_V_from_py=CPP_TYPE_TO_FUNCS[v].from_py_type,
            ))
            count_defn += 1
    return CodeCount(code, count_defn)


def declarations() -> typing.List[str]:
    ret = []
    with cpp_comment_section(ret, 'Declaration file', '='):
        ret.extend(get_codegen_warning(False))
        ret.extend(documentation())
        ret.append('#include <Python.h>')
        ret.append('')
        for include in REQUIRED_INCLUDES:
            ret.append('#include {}'.format(include))
        ret.append('')
        with cpp_comment_section(ret, 'Required conversion functions', '-'):
            ret.extend(required_function_declarations())
        count_decl = 0
        # Unary functions
        code_count = unary_declarations()
        count_decl += code_count.count
        ret.extend(code_count.code)
        code_count = dict_declarations()
        count_decl += code_count.count
        ret.extend(code_count.code)
        ret.append('// Declarations written: {}'.format(count_decl))
        ret.extend(get_codegen_warning(True))
    return ret


def definitions() -> typing.List[str]:
    ret = []
    with cpp_comment_section(ret, 'Definition file', '='):
        ret.extend(get_codegen_warning(False))
        ret.extend(documentation())
        # TODO: Hard coded name in two places ???
        ret.append('#include "python_convert.hpp"')
        ret.append('')
        count_defn = 0
        code_count = unary_definitions()
        count_defn += code_count.count
        ret.extend(code_count.code)
        code_count = dict_definitions()
        count_defn += code_count.count
        ret.extend(code_count.code)
        ret.append('// Definitions written: {}'.format(count_defn))
        ret.extend(get_codegen_warning(True))
    return ret


AUTO_FILE_NAME = 'auto_py_convert_internal'


def write_files() -> None:
    dir_path = os.path.dirname(os.path.abspath(__file__))
    file_path = os.path.join(dir_path, '{}.h'.format(AUTO_FILE_NAME))
    print('Writing to "{}"'.format(file_path))
    with open(file_path, 'w') as f:
        for line in declarations():
            f.write('{}\n'.format(line))
    file_path = os.path.join(dir_path, '{}.cpp'.format(AUTO_FILE_NAME))
    print('Writing to "{}"'.format(file_path))
    with open(file_path, 'w') as f:
        for line in definitions():
            f.write('{}\n'.format(line))



def main():
    # print('\n'.join(declarations()))
    # print()
    # print('\n'.join(definitions()))
    write_files()
    return 0


if __name__ == '__main__':
    exit(main())
