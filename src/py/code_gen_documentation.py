"""
Provides Doxygen style comments for code_gen.py
"""
import contextlib
import itertools
import typing

from src.py import code_gen_common


def doxygen_cpp_to_python_unary_base_class(cpp_container: str, python_container: str) -> typing.List[str]:
    """Returns a Doxygen style comment. For example::

        /**
         * Base declaration for converting C++ vectors to a Python tuple.
         *
         * @tparam T C++ type.
         * @param container C++ input as a std::vector<T>.
         * @return A Python tuple containing type T.
         */

    This is for::

        template<typename T>
        PyObject *
        cpp_std_vector_to_py_tuple(const std::vector<T> &container);
    """
    return [
        '/**',
        f' * Base declaration for converting C++ \c {cpp_container} to a Python \c {python_container}.',
        ' *',
        ' * @tparam T C++ type.',
        f' * @param container C++ input as a \c {cpp_container}<T>.',
        f' * @return A Python \c {python_container} containing type corresponding to the C++ type \c T.',
        ' */',
    ]


def doxygen_cpp_to_python_unary_instantiation(cpp_container: str, python_container: str, cpp_type: str, py_type: str):
    """Returns a Doxygen style comment. For example::

        /**
         * Instantiation for converting C++ vectors of bool to a Python tuple of bool.
         *
         * @param container C++ input as a std::vector<bool>.
         * @return A Python tuple containing bool objects.
         */

    This is for::

        template <>
        PyObject *
        cpp_std_vector_to_py_tuple<bool>(const std::vector<bool> &container);
    """
    return [
        '/**',
        f' * Instantiation for converting C++ \c {cpp_container}<{cpp_type}> to a Python \c {python_container} of \c {py_type}.',
        ' *',
        f' * @param container C++ input as a \c {cpp_container}<{cpp_type}>.',
        f' * @return A Python \c {python_container} containing \c {py_type} objects.',
        ' */',
    ]


def doxygen_python_to_cpp_unary_base_class(cpp_container: str, python_container: str) -> typing.List[str]:
    """Returns a Doxygen style comment. For example::

        /**
         * Base declaration for converting a Python tuple to a C++ std::vector.
         *
         * @tparam T The C++ type.
         * @param op The Python container to read from.
         * @param container The C++ std::vector to write to.
         * @return 0 on success, non-zero on failure.
         */

    This is for::

        template<typename T>
        int
        py_tuple_to_cpp_std_vector(PyObject *op, std::vector<T> &container);
    """
    return [
        '/**',
        f' * Base declaration for converting a Python \c {python_container} to a C++ \c {cpp_container}.',
        ' *',
        ' * @tparam T C++ type.',
        f' * @param op The Python container to read from.',
        f' * @param container The C++ \c {cpp_container} to write to.',
        f' * @return 0 on success, non-zero on failure.',
        ' */',
    ]


def doxygen_python_to_cpp_unary_instantiation(cpp_container: str, python_container: str, cpp_type: str, py_type: str):
    """Returns a Doxygen style comment. For example::

        /**
         * Instantiation for converting a Python tuple of bool to a C++ std::vector<bool>.
         *
         * @param op The Python container to read from.
         * @param container The C++ container ot write to.
         * @return 0 on success, non-zero on failure.
         */

    This is for::

        template <>
        int
        py_tuple_to_cpp_std_vector<bool>(PyObject *op, std::vector<bool> &container);
    """
    return [
        '/**',
        f' * Instantiation for converting a Python \c {python_container} of \c {py_type} to a C++ \c {cpp_container}<{cpp_type}>.',
        ' *',
        f' * @param op Python input as a \c {python_container} of \c {py_type}.',
        f' * @param container C++ output as a \c {cpp_container}<{cpp_type}>.',
        f' * @return 0 on success, non-zero on failure.',
        ' */',
    ]


def doxygen_cpp_to_python_dict_base_class() -> typing.List[str]:
    """
        /**
         * * Base declaration for converting a C++ std::unordered_map<K, V> to a Python dictionary.
         *
         * @tparam K The C++ type for the key.
         * @tparam V The C++ type for the value.
         * @param map Input C++ std::unordered_map<K, V>.
         * @return Python dictionary corresponding to {K : V, ...}.
         */

    For::
        template<typename K, typename V>
        PyObject *
        cpp_std_unordered_map_to_py_dict(const std::unordered_map<K, V> &map);
    """
    return [
        '/**',
        ' * Base declaration for converting a C++ <tt>std::unordered_map<K, V></tt> to a Python dictionary.',
        ' *',
        ' * @tparam K The C++ type for the key.',
        ' * @tparam V The C++ type for the value.',
        ' * @param map Input C++ <tt>std::unordered_map<K, V></tt>.',
        ' * @return Python dictionary corresponding to <tt>{K : V, ...}</tt>.',
        ' */',
    ]


def doxygen_cpp_to_python_dict_instantiation(cpp_key_type: str, cpp_val_type: str, py_key_type: str, py_val_type: str):
    """
        /**
         * Converts a C++ std::unordered_map<long, bool> to a Python dictionary.
         *
         * @param map Input C++ std::unordered_map<long, bool>.
         * @return A Python dictionary of {int : bool, ...}.
         */

    For::

        template <>
        PyObject *
        cpp_std_unordered_map_to_py_dict<long, bool>(const std::unordered_map<long, bool> &map);

    """
    return [
        '/**',
        f' * Instantiation for converting a C++ <tt>std::unordered_map<{cpp_key_type}, {cpp_val_type}></tt> to a Python dictionary.',
        ' *',
        f' * @param map Input C++ <tt>std::unordered_map<{cpp_key_type}, {cpp_val_type}></tt>.',
        f' * @return A Python dictionary of <tt>{{{py_key_type} : {py_val_type}, ...}}</tt>.',
        ' */',
    ]


def doxygen_python_dict_to_cpp_base_class():
    """Example::
        /**
         * Base declaration for converting a Python dictionary to a C++ std::unordered_map<K, V>.
         *
         * @tparam K The type of the C++ key.
         * @tparam V The type of the C++ value.
         * @param op The Python dictionary as the input.
         * @param map C++ std::unordered_map<K, V> to write to.
         * @return 0 on success, non-zero on failure.
         */

    From::

        template<typename K, typename V>
        int
        py_dict_to_cpp_std_unordered_map(PyObject *op, std::unordered_map<K, V> &map);
    """
    return [
        '/**',
        ' * Base declaration for converting a Python dictionary to a C++ std::unordered_map<K, V>.',
        ' *',
        ' * @tparam K The C++ type for the key.',
        ' * @tparam V The C++ type for the value.',
        ' * @param op The Python dictionary as the input.',
        ' * @param map C++ <tt>std::unordered_map<K, V></tt> to write to.',
        ' * @return 0 on success, non-zero on failure.',
        ' */',
    ]


def doxygen_python_dict_to_cpp_instantiation(cpp_key_type: str, cpp_val_type: str, py_key_type: str, py_val_type: str):
    """Example::

        /**
         * Instantiation for converting a Python dictionary to a C++ std::unordered_map<long, bool>.
         *
         * @param op The Python dictionary as the input.
         * @param map C++ std::unordered_map<long, bool> to write to.
         * @return 0 on success, non-zero on failure.
         */

    From::

        template <>
        int
        py_dict_to_cpp_std_unordered_map<bool, bool>(PyObject* op, std::unordered_map<long, bool> &map);
    """
    return [
        '/**',
        f' * Instantiation for converting a Python dictionary <tt>{{{py_key_type} : {py_val_type}, ...}}</tt> to a C++ <tt>std::unordered_map<{cpp_key_type}, {cpp_val_type}></tt>.',
        ' *',
        f' * @param op A Python dictionary of <tt>{{{py_key_type} : {py_val_type}, ...}}</tt> as the input.',
        f' * @param map The C++ <tt>std::unordered_map<{cpp_key_type}, {cpp_val_type}></tt> to write to.',
        f' * @return 0 on success, non-zero on failure.',
        ' */',
    ]


def comment_str(s: str) -> str:
    """Turn a single line string into an inline comment."""
    if '\n' in s:
        raise ValueError(f'Inline comment can not have newlines in it.')
    return '//{}'.format(s)


def comment_list_str(inputs: typing.List[str]) -> typing.List[str]:
    """Returns the strings as a C++ comments."""
    ret = []
    for s in inputs:
        if '\n' in s:
            ret.extend([comment_str(v) for v in s.split('\n')])
        else:
            ret.append(comment_str(s))
    return ret


@contextlib.contextmanager
def cpp_comment_section(str_list: typing.List[str], title: str, sep: str):
    """Context manager for writing beginning and end comments."""
    str_list.append(comment_str('{}'.format(' {} '.format(title).center(WIDTH, sep))))
    yield
    str_list.append(comment_str('{}'.format(' END: {} '.format(title).center(WIDTH, sep))))
    str_list.append('')


def documentation(unary_collections: typing.Tuple[code_gen_common.UnaryFunctions, ...],
                  cpp_type_to_funcs: typing.Dict[str, code_gen_common.CppTypeFunctions]) -> typing.List[str]:
    """General documentation."""
    ret = [
        ' Conversion from homogeneous data structures in Python and C++',
        ' ',
        ' Unary conversions',
    ]
    for py_container in unary_collections:
        ret.append(' {}:'.format(py_container.python_container))
        for typ in cpp_type_to_funcs:
            ret.append(' {} <-> {}<{}>'.format(
                py_container,
                py_container.cpp_container,
                typ,
            ))
        ret.append(' ')
    ret.append(' ')
    ret.append(' Mapping conversions')
    for type_k, type_v in itertools.product(cpp_type_to_funcs.keys(), repeat=2):
        ret.append(' {} <-> std::unordered_map<{}, {}>'.format(
            'dict',
            type_k, type_v
        ))
    ret.append(' ')
    return comment_list_str(ret)


WIDTH = 75 - len('//')


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
        )),
        comment_str('{}'.format('#' * WIDTH)),
    ]


@contextlib.contextmanager
def get_codegen_please_no_edit_warning_context(str_list: typing.List[str]):
    """Context manager that writes the start or end of a warning comment."""
    str_list.extend(get_codegen_please_no_edit_warning(False))
    yield
    str_list.extend(get_codegen_please_no_edit_warning(True))
