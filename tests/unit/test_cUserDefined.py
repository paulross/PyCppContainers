import pytest

import cUserDefined


def test_cuserdefined_dir():
    assert dir(cUserDefined) == ['Custom',
                                 'PYTHON_CPP_CONTAINERS_VERSION',
                                 '__doc__',
                                 '__file__',
                                 '__loader__',
                                 '__name__',
                                 '__package__',
                                 '__spec__',
                                 'reverse_dict_names',
                                 'reverse_list_names']


def test_cuserdefined_custom_noargs():
    c = cUserDefined.Custom()
    assert c.first == ''
    assert c.last == ''
    assert c.number == 0


def test_cuserdefined_custom_args():
    c = cUserDefined.Custom('first', 'last', 42)
    assert c.first == 'first'
    assert c.last == 'last'
    assert c.number == 42


def test_cuserdefined_custom_repr():
    c = cUserDefined.Custom('first', 'last', 42)
    assert repr(c).startswith('<cUserDefined.Custom object at')


def test_cuserdefined_custom_str():
    c = cUserDefined.Custom('first', 'last', 42)
    assert str(c).startswith('<cUserDefined.Custom object at')


def test_cuserdefined_custom_name():
    c = cUserDefined.Custom('first', 'last', 42)
    assert c.name() == 'first last'


def test_cuserdefined_custom_list_names():
    list_of_names = [
        cUserDefined.Custom('First', 'Last', 21), cUserDefined.Custom('François', 'Truffaut', 21468)
    ]
    assert [v.name() for v in list_of_names] == ['First Last', 'François Truffaut']


def test_cuserdefined_reverse_list_names():
    list_of_names = [
        cUserDefined.Custom('First', 'Last', 21), cUserDefined.Custom('François', 'Truffaut', 21468)
    ]
    result = cUserDefined.reverse_list_names(list_of_names)
    assert [v.name() for v in result] == ['Last First', 'Truffaut François']


def test_cuserdefined_reverse_dict_names():
    dict_of_names = {
        0 : cUserDefined.Custom('First', 'Last', 17953),
        1 : cUserDefined.Custom('François', 'Truffaut', 21468),
    }
    result = cUserDefined.reverse_dict_names(dict_of_names)
    assert {k: v.name() for k, v in result.items()} == {0: 'Last First', 1: 'Truffaut François'}
