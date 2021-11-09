import gc
import pprint
import random
import statistics
import time
import typing

import pytest
import psutil
from pymemtrace import cPyMemTrace

import cPyCppContainers


def _test_new_list_bytes():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    byte_length = 1024
    size = 2**20
    byte_entry = b' ' * byte_length
    results = []
    total_bytes = byte_length * size
    for _r in range(10):
        original = [byte_entry[:] for _i in range(size)]
        time_start = time.perf_counter()
        cPyCppContainers.new_list_bytes(original)
        time_exec = time.perf_counter() - time_start
        results.append(time_exec)
        # del original
    print()
    print('\n'.join(f'{v:8.3f}' for v in results))
    rss_new = proc.memory_info().rss
    print(f'Total bytes {total_bytes:16,d} RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


def test_new_list_bytes():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    with cPyMemTrace.Profile():
        _test_new_list_bytes()
    gc.collect()
    # for i in range(4):
    #     time.sleep(1.0)
    rss_new = proc.memory_info().rss
    print(f'RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')
    assert 0

