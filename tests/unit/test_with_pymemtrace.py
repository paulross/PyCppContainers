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
    # 1Gb
    total_bytes = 2**20 * 2**10
    byte_length = 1024 #// (4 * 4 * 4 * 4)
    vector_length = total_bytes // byte_length
    print(f'Total bytes: {total_bytes:16,d} byte length: {byte_length:16,d} vector length: {vector_length:16,d}')
    byte_entry = b' ' * byte_length
    results = []
    for _r in range(10):
        original = [byte_entry[:] for _i in range(vector_length)]
        time_start = time.perf_counter()
        cPyCppContainers.new_list_bytes(original)
        time_exec = time.perf_counter() - time_start
        results.append(time_exec)
        # del original
    print()
    print('\n'.join(f'{v:8.3f}' for v in results))
    print(f'Mean: {sum(results) / len(results):8.3f}')
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


def _test_new_set_bytes():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    # 1Gb
    total_bytes = 2**20 * 2**10
    byte_length = 1024
    # total_bytes = 2**20 * 2**4
    # byte_length = 1024
    set_length = total_bytes // byte_length
    print(f'_test_new_set_bytes(): Total bytes: {total_bytes:16,d} byte length: {byte_length:16,d} set length: {set_length:16,d}')
    random_bytes = [random.randint(0, 255) for _i in range(byte_length)]
    byte_entry = b' ' * byte_length
    results = []
    for _r in range(10):
        original = set()
        for i in range(set_length):
            k = bytes(random_bytes)
            original.add(k)
            # random.shuffle(random_bytes)
            # Shuffle is quite expensive. Try something simpler, chose a random value and increment it with roll over.
            index = random.randint(0, byte_length - 1)
            random_bytes[index] = (random_bytes[index] + 1) % 256
        # print(f'Actual set length: {len(original):16,d}')
        time_start = time.perf_counter()
        cPyCppContainers.new_set_bytes(original)
        time_exec = time.perf_counter() - time_start
        results.append(time_exec)
        # del original
    print()
    print('\n'.join(f'{v:8.3f}' for v in results))
    print(f'Mean: {sum(results) / len(results):8.3f}')
    rss_new = proc.memory_info().rss
    print(f'_test_new_set_bytes(): Total bytes {total_bytes:16,d} RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


def test_new_set_bytes():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    # with cPyMemTrace.Profile():
    with cPyMemTrace.Profile(4096 * 16):
        _test_new_set_bytes()
    gc.collect()
    # for i in range(4):
    #     time.sleep(1.0)
    rss_new = proc.memory_info().rss
    print(f'test_new_set_bytes(): RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')
    assert 0


def _test_new_dict_bytes():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    # 1Gb
    total_bytes = 2**20 * 2**10
    byte_length = 1024
    # total_bytes = 2**20 * 2**4
    # byte_length = 1024
    dict_length = total_bytes // byte_length // 2
    print(f'_test_new_dict_bytes(): Total bytes: {total_bytes:16,d} byte length: {byte_length:16,d} dict length: {dict_length:16,d}')
    random_bytes = [random.randint(0, 255) for _i in range(byte_length)]
    byte_entry = b' ' * byte_length
    results = []
    for _r in range(10):
        original = {}
        for i in range(dict_length):
            k = bytes(random_bytes)
            original[k] = b' ' * byte_length
            # random.shuffle(random_bytes)
            # Shuffle is quite expensive. Try something simpler, chose a random value and increment it with roll over.
            index = random.randint(0, byte_length - 1)
            random_bytes[index] = (random_bytes[index] + 1) % 256
        print(f'Actual dict length: {len(original):16,d}')
        time_start = time.perf_counter()
        cPyCppContainers.new_dict_bytes_bytes(original)
        time_exec = time.perf_counter() - time_start
        results.append(time_exec)
        # del original
    print()
    print('\n'.join(f'{v:8.3f}' for v in results))
    print(f'Mean: {sum(results) / len(results):8.3f}')
    rss_new = proc.memory_info().rss
    print(f'_test_new_dict_bytes(): Total bytes {total_bytes:16,d} RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


def test_new_dict_bytes():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    with cPyMemTrace.Profile(4096 * 16):
        _test_new_dict_bytes()
    gc.collect()
    # for i in range(4):
    #     time.sleep(1.0)
    rss_new = proc.memory_info().rss
    print(f'test_new_dict_bytes(): RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')
    assert 0
