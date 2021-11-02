import pprint

import pytest

import cPyCppContainers
import time


SIZE_DOUBLING = tuple(2**v for v in  range(1, 20+1))

@pytest.mark.parametrize(
    'size',
    SIZE_DOUBLING[:4],
)
def test_new_list_int_old(size):
    original = list(range(size))
    time_start = time.perf_counter()
    _result = cPyCppContainers.new_list_int(original)
    time_exec = time.perf_counter() - time_start
    print(f'Size: {size:8d} Time: {time_exec:.6f} (s)')
    assert 0


def test_new_list_int():
    results = []
    for size in SIZE_DOUBLING:
        original = list(range(size))
        time_start = time.perf_counter()
        _result = cPyCppContainers.new_list_int(original)
        time_exec = time.perf_counter() - time_start
        results.append((size, time_exec))
    # pprint.pprint(results)
    print()
    for s, t in results:
        print(f'{s:8d} {t:12.6f} {1e6 * t / s:12.3f}')
    assert 0
