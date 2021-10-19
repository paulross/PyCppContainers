
import pytest

import cPyCppContainers


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
