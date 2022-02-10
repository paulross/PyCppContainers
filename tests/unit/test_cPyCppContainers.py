import pytest

import cPyCppContainers


@pytest.mark.parametrize(
    'given',
    (
        'abc',
        # Examples from http://www.i18nguy.com/unicode-example.html
        # 'Михаил Горбачёв',  # Mikhail Gorbachev
        'François Truffaut',
        'Mika Häkkinen',
        'Céline Dion',
        'Johann Strauß',
    ),
)
def test_new_str(given):
    result = cPyCppContainers.new_str(given)
    assert result == given


@pytest.mark.xfail
@pytest.mark.parametrize(
    'given',
    (
        'Михаил Горбачёв',  # Mikhail Gorbachev
    ),
)
def test_new_str_fail(given):
    result = cPyCppContainers.new_str(given)
    assert result == given


@pytest.mark.parametrize(
    'given, expected',
    (
            (
                    [], [],
            ),
            (
                    [1.0, 2.0], [2.0, 4.0],
            ),
    ),
)
def test_list_x2(given, expected):
    result = cPyCppContainers.list_x2(given)
    assert result == expected


@pytest.mark.parametrize(
    'given',
    (
            [1.0, 2.0],
    ),
)
def test_list_x2_is_new(given):
    result = cPyCppContainers.list_x2(given)
    assert id(result) != id(given)


@pytest.mark.parametrize(
    'given, expected',
    (
            (
                    (1.0, 2.0), 'Can not convert Python container of type tuple',
            ),
            (
                    [1.0, 2], 'Python value of type int can not be converted',
            ),
            (
                    [1.0, '2'], 'Python value of type str can not be converted',
            ),
    ),
)
def test_list_x2_raises(given, expected):
    with pytest.raises(ValueError) as err:
        cPyCppContainers.list_x2(given)
    assert err.value.args[0] == expected


@pytest.mark.parametrize(
    'given, expected',
    (
            (
                    tuple(), tuple(),
            ),
            (
                    (b'1.0', b'2.0'), (b'2.0', b'1.0'),
            ),
    ),
)
def test_tuple_reverse(given, expected):
    result = cPyCppContainers.tuple_reverse(given)
    assert result == expected


@pytest.mark.parametrize(
    'given',
    (
            (b'1.0', b'2.0'),
    ),
)
def test_tuple_reverse_is_new(given):
    result = cPyCppContainers.tuple_reverse(given)
    assert id(result) != id(given)


@pytest.mark.parametrize(
    'given, expected',
    (
            (
                    (1.0, 2.0), 'Python value of type float can not be converted',
            ),
            (
                    [1.0, 2], 'Can not convert Python container of type list',
            ),
    ),
)
def test_tuple_reverse_raises(given, expected):
    with pytest.raises(ValueError) as err:
        cPyCppContainers.tuple_reverse(given)
    assert err.value.args[0] == expected


@pytest.mark.parametrize(
    'given, expected',
    (
            (
                    {}, {},
            ),
            (
                    {
                        b'1.0': 1,
                        b'2.0': 2,
                    },
                    {
                        b'1.0': 2,
                        b'2.0': 3,
                    },
            ),
    ),
)
def test_dict_inc(given, expected):
    result = cPyCppContainers.dict_inc(given)
    assert result == expected


@pytest.mark.parametrize(
    'given',
    (
            {},
            {
                b'1.0': 1,
                b'2.0': 2,
            },
    ),
)
def test_dict_inc_is_new(given):
    result = cPyCppContainers.dict_inc(given)
    assert id(result) != id(given)


@pytest.mark.parametrize(
    'given, expected',
    (
            (
                    (1.0, 2.0), 'Python object must be a dict not a tuple',
            ),
            (
                    {1.0: 1}, 'Python dict key is wrong type of: float',
            ),
            (
                    {b'1': 1.0}, 'Python dict value is wrong type of: float',
            ),
    ),
)
def test_dict_inc_raises(given, expected):
    with pytest.raises(ValueError) as err:
        cPyCppContainers.dict_inc(given)
    assert err.value.args[0] == expected


@pytest.mark.parametrize(
    'given',
    (
            [],
            [1.0, 2.0],
    ),
)
def test_new_list_vector_float(given):
    result = cPyCppContainers.new_list_vector_float(given)
    assert result == given
    assert id(result) != id(given)
    # floats are not interned
    all_ids_different = [id(a) != id(b) for a, b in zip(given, result)]
    assert all(all_ids_different)


@pytest.mark.parametrize(
    'given',
    (
            [],
            [1.0 + 4.0j, 2.0 + 8.0j],
    ),
)
def test_new_list_vector_complex(given):
    result = cPyCppContainers.new_list_vector_complex(given)
    assert result == given
    assert id(result) != id(given)
    # complex numbers are not interned
    all_ids_different = [id(a) != id(b) for a, b in zip(given, result)]
    assert all(all_ids_different)


# Because of the nature of the code in cPyCppContainers.cpp this test covers all new_list_vector_* functions.
@pytest.mark.parametrize(
    'given, expected',
    (
            (
                    (1.0, 2.0), 'Can not convert Python container of type tuple',
            ),
            (
                    [1.0, 2], 'Python value of type int can not be converted',
            ),
            (
                    [1.0, '2'], 'Python value of type str can not be converted',
            ),
    ),
)
def test_new_list_vector_float_raises(given, expected):
    with pytest.raises(ValueError) as err:
        cPyCppContainers.new_list_vector_float(given)
    assert err.value.args[0] == expected


@pytest.mark.parametrize(
    'given',
    (
            [],
            [True, False, True],
    ),
)
def test_new_list_vector_bool(given):
    result = cPyCppContainers.new_list_vector_bool(given)
    assert result == given
    assert id(result) != id(given)
    # NOTE: Can not check individual IDs are different because of interning.


@pytest.mark.parametrize(
    'given',
    (
            [],
            [1, 3, 5, 7, 46823],
    ),
)
def test_new_list_vector_int(given):
    result = cPyCppContainers.new_list_vector_int(given)
    assert result == given
    assert id(result) != id(given)
    # NOTE: Can not check individual IDs are different because of interning.


@pytest.mark.parametrize(
    'given',
    (
            [],
            [b'abc', b'xyz'],
    ),
)
def test_new_list_vector_bytes(given):
    result = cPyCppContainers.new_list_vector_bytes(given)
    assert result == given
    assert id(result) != id(given)
    # bytes are not interned
    all_ids_different = [id(a) != id(b) for a, b in zip(given, result)]
    assert all(all_ids_different)


@pytest.mark.parametrize(
    'given',
    (
            [],
            ['abc', 'xyz'],
    ),
)
def test_new_list_vector_str(given):
    result = cPyCppContainers.new_list_vector_str(given)
    assert result == given
    assert id(result) != id(given)
    # these strings should not be interned
    all_ids_different = [id(a) != id(b) for a, b in zip(given, result)]
    assert all(all_ids_different)


@pytest.mark.parametrize(
    'given',
    (
            [],
            [1.0, 2.0],
    ),
)
def test_new_list_list_float(given):
    result = cPyCppContainers.new_list_list_float(given)
    assert result == given
    assert id(result) != id(given)
    # floats are not interned
    all_ids_different = [id(a) != id(b) for a, b in zip(given, result)]
    assert all(all_ids_different)


@pytest.mark.parametrize(
    'given',
    (
            [],
            [1.0 + 4.0j, 2.0 + 8.0j],
    ),
)
def test_new_list_list_complex(given):
    result = cPyCppContainers.new_list_list_complex(given)
    assert result == given
    assert id(result) != id(given)
    # complex numbers are not interned
    all_ids_different = [id(a) != id(b) for a, b in zip(given, result)]
    assert all(all_ids_different)


# Because of the nature of the code in cPyCppContainers.cpp this test covers all new_list_list_* functions.
@pytest.mark.parametrize(
    'given, expected',
    (
            (
                    (1.0, 2.0), 'Can not convert Python container of type tuple',
            ),
            (
                    [1.0, 2], 'Python value of type int can not be converted',
            ),
            (
                    [1.0, '2'], 'Python value of type str can not be converted',
            ),
    ),
)
def test_new_list_list_float_raises(given, expected):
    with pytest.raises(ValueError) as err:
        cPyCppContainers.new_list_list_float(given)
    assert err.value.args[0] == expected


@pytest.mark.parametrize(
    'given',
    (
            [],
            [True, False, True],
    ),
)
def test_new_list_list_bool(given):
    result = cPyCppContainers.new_list_list_bool(given)
    assert result == given
    assert id(result) != id(given)
    # NOTE: Can not check individual IDs are different because of interning.


@pytest.mark.parametrize(
    'given',
    (
            [],
            [1, 3, 5, 7, 46823],
    ),
)
def test_new_list_list_int(given):
    result = cPyCppContainers.new_list_list_int(given)
    assert result == given
    assert id(result) != id(given)
    # NOTE: Can not check individual IDs are different because of interning.


@pytest.mark.parametrize(
    'given',
    (
            [],
            [b'abc', b'xyz'],
    ),
)
def test_new_list_list_bytes(given):
    result = cPyCppContainers.new_list_list_bytes(given)
    assert result == given
    assert id(result) != id(given)
    # bytes are not interned
    all_ids_different = [id(a) != id(b) for a, b in zip(given, result)]
    assert all(all_ids_different)


@pytest.mark.parametrize(
    'given',
    (
            [],
            ['abc', 'xyz'],
    ),
)
def test_new_list_list_str(given):
    result = cPyCppContainers.new_list_list_str(given)
    assert result == given
    assert id(result) != id(given)
    # these strings should not be interned
    all_ids_different = [id(a) != id(b) for a, b in zip(given, result)]
    assert all(all_ids_different)


@pytest.mark.parametrize(
    'given',
    (
            {},
            {1: 45, 2: 123, },
    ),
)
def test_new_dict_from_std_unordered_map_int_int(given):
    result = cPyCppContainers.new_dict_from_std_unordered_map_int_int(given)
    assert result == given
    assert id(result) != id(given)


@pytest.mark.parametrize(
    'given',
    (
            {},
            {1.0: 45.0, 2.0: 123.9, },
    ),
)
def new_dict_from_std_unordered_map_float_float(given):
    result = cPyCppContainers.new_dict_from_std_unordered_map_float_float(given)
    assert result == given
    assert id(result) != id(given)


@pytest.mark.parametrize(
    'given',
    (
            {},
            {b'abc': b'123', b'xyz': b'8790', },
    ),
)
def test_new_dict_from_std_unordered_map_bytes_bytes(given):
    result = cPyCppContainers.new_dict_from_std_unordered_map_bytes_bytes(given)
    assert result == given
    assert id(result) != id(given)


@pytest.mark.parametrize(
    'given',
    (
            {},
            {'abc': '123', 'xyz': '8790', },
    ),
)
def test_new_dict_from_std_unordered_map_str_str(given):
    result = cPyCppContainers.new_dict_from_std_unordered_map_str_str(given)
    assert result == given
    assert id(result) != id(given)


# Because of the nature of the code in cPyCppContainers.cpp this test covers all new_dict_* functions.
@pytest.mark.parametrize(
    'given, expected',
    (
            (
                    (1.0, 2.0), 'Python object must be a dict not a tuple',
            ),
            (
                    {1.0: 2}, 'Python dict value is wrong type of: int',
            ),
            (
                    {1: 2.0}, 'Python dict key is wrong type of: int',
            ),
    ),
)
def test_new_dict_from_std_unordered_map_float_float_raises(given, expected):
    with pytest.raises(ValueError) as err:
        cPyCppContainers.new_dict_from_std_unordered_map_float_float(given)
    assert err.value.args[0] == expected
    
    
@pytest.mark.parametrize(
    'given',
    (
            {},
            {1: 45, 2: 123, },
    ),
)
def test_new_dict_from_std_map_int_int(given):
    result = cPyCppContainers.new_dict_from_std_map_int_int(given)
    assert result == given
    assert id(result) != id(given)


@pytest.mark.parametrize(
    'given',
    (
            {},
            {1.0: 45.0, 2.0: 123.9, },
    ),
)
def new_dict_from_std_map_float_float(given):
    result = cPyCppContainers.new_dict_from_std_map_float_float(given)
    assert result == given
    assert id(result) != id(given)


@pytest.mark.parametrize(
    'given',
    (
            {},
            {b'abc': b'123', b'xyz': b'8790', },
    ),
)
def test_new_dict_from_std_map_bytes_bytes(given):
    result = cPyCppContainers.new_dict_from_std_map_bytes_bytes(given)
    assert result == given
    assert id(result) != id(given)


@pytest.mark.parametrize(
    'given',
    (
            {},
            {'abc': '123', 'xyz': '8790', },
    ),
)
def test_new_dict_from_std_map_str_str(given):
    result = cPyCppContainers.new_dict_from_std_map_str_str(given)
    assert result == given
    assert id(result) != id(given)


# Because of the nature of the code in cPyCppContainers.cpp this test covers all new_dict_* functions.
@pytest.mark.parametrize(
    'given, expected',
    (
            (
                    (1.0, 2.0), 'Python object must be a dict not a tuple',
            ),
            (
                    {1.0: 2}, 'Python dict value is wrong type of: int',
            ),
            (
                    {1: 2.0}, 'Python dict key is wrong type of: int',
            ),
    ),
)
def test_new_dict_from_std_map_float_float_raises(given, expected):
    with pytest.raises(ValueError) as err:
        cPyCppContainers.new_dict_from_std_map_float_float(given)
    assert err.value.args[0] == expected
