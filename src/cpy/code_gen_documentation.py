"""
Provides Doxygen style comments for code_gen.py
"""
import contextlib
import itertools
import typing

from src.cpy.code_gen_common import CppTypeFunctions, UnaryFunctions


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
        f' * Base declaration for converting C++ {cpp_container} to a Python {python_container}.',
        ' *',
        ' * @tparam T C++ type.',
        f' * @param container C++ input as a {cpp_container}<T>.',
        f' * @return A Python {python_container} containing type T.',
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
        f' * Instantiation for converting C++ {cpp_container} to a Python {python_container} of {py_type}.',
        ' *',
        f' * @param container C++ input as a {cpp_container}<{cpp_type}>.',
        f' * @return A Python {python_container} containing {py_type} objects.',
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
        f' * Base declaration for converting a Python {python_container} to a C++ {cpp_container}.',
        ' *',
        ' * @tparam T C++ type.',
        f' * @param op The Python container to read from.',
        f' * @param container The C++ {cpp_container} to write to.',
        f' * @return  0 on success, non-zero on failure.',
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
        f' * Instantiation for converting a Python {python_container} of {py_type} to a C++ {cpp_container}<{cpp_type}>.',
        ' *',
        f' * @param op Python input as a {python_container} of {py_type}.',
        f' * @param container C++ output as a {cpp_container}<{cpp_type}>.',
        f' * @return  0 on success, non-zero on failure.',
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


def documentation(unary_collections: typing.Dict[str, UnaryFunctions],
                  cpp_type_to_funcs: typing.Dict[str, CppTypeFunctions]) -> typing.List[str]:
    """General documentation."""
    ret = [
        ' Conversion from homogeneous data structures in Python and C++',
        ' ',
        ' Unary conversions',
    ]
    for py_container in unary_collections:
        ret.append(' {}:'.format(py_container))
        for typ in cpp_type_to_funcs:
            ret.append(' {} <-> {}<{}>'.format(
                py_container,
                unary_collections[py_container].cpp_container,
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