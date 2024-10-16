"""
This is a fairly exhaustive set of tests that take a long time to run.
The tests always pass as they are print the memory usage to stdout rather than functional tests.

Run this with:
$ caffeinate pytest -vs --pymemtrace tests/unit/test_with_pymemtrace.py
"""
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


def _test_new_str(char: str, scale: int, test_function: typing.Callable):
    proc = psutil.Process()
    rss = proc.memory_info().rss
    # 1Gb
    total_bytes = 2**20 * 2**10
    original = char * (total_bytes // scale)
    results = []
    for _r in range(10):
        time_start = time.perf_counter()
        test_function(original)
        time_exec = time.perf_counter() - time_start
        results.append(time_exec)
        # del original
    # print()
    # print('\n'.join(f'{v:8.3f}' for v in results))
    print(f'Time: Min: {min(results):8.3f} Mean: {sum(results) / len(results):8.3f} Max: {max(results):8.3f}')
    rss_new = proc.memory_info().rss
    print(f'_test_new_str(): Total bytes {total_bytes:16,d} RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


@pytest.mark.pymemtrace
def test_new_str():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    # with cPyMemTrace.Profile():
    with cPyMemTrace.Profile(4096 * 16):
        _test_new_str(' ', 1, cPyCppContainers.new_str)
    gc.collect()
    rss_new = proc.memory_info().rss
    print(f'test_new_str(): RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


@pytest.mark.pymemtrace
def test_new_str16():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    # with cPyMemTrace.Profile():
    with cPyMemTrace.Profile(4096 * 16):
        # The euro symbol as 16 bit unicode
        _test_new_str('\u8000', 2, cPyCppContainers.new_str16)
    gc.collect()
    rss_new = proc.memory_info().rss
    print(f'test_new_str(): RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


@pytest.mark.pymemtrace
def test_new_str32():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    # with cPyMemTrace.Profile():
    with cPyMemTrace.Profile(4096 * 16):
        # The euro symbol as 32 bit unicode
        _test_new_str('\U00018000', 4, cPyCppContainers.new_str32)
    gc.collect()
    rss_new = proc.memory_info().rss
    print(f'test_new_str(): RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


def _test_new_list_bool(test_function):
    proc = psutil.Process()
    rss = proc.memory_info().rss
    vector_length = 10 * 1024**2
    print(f'Total bytes: {vector_length * 8:16,d} vector length: {vector_length:16,d}')
    results = []
    for _r in range(10):
        original = [True for _i in range(vector_length)]
        time_start = time.perf_counter()
        test_function(original)
        time_exec = time.perf_counter() - time_start
        results.append(time_exec)
        # del original
    # print()
    # print('\n'.join(f'{v:8.3f}' for v in results))
    print(f'Time: Min: {min(results):8.3f} Mean: {sum(results) / len(results):8.3f} Max: {max(results):8.3f}')
    rss_new = proc.memory_info().rss
    print(f'Total bytes RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


@pytest.mark.pymemtrace
def test_new_list_bool_with_vector():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    with cPyMemTrace.Profile():
        _test_new_list_bool(cPyCppContainers.new_list_vector_bool)
    gc.collect()
    rss_new = proc.memory_info().rss
    print(f'RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


@pytest.mark.pymemtrace
def test_new_list_bool_with_list():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    with cPyMemTrace.Profile():
        _test_new_list_bool(cPyCppContainers.new_list_list_bool)
    gc.collect()
    rss_new = proc.memory_info().rss
    print(f'RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


def _test_new_list_double(test_function):
    proc = psutil.Process()
    rss = proc.memory_info().rss
    vector_length = 10 * 1024**2
    print(f'Total bytes: {vector_length * 8:16,d} vector length: {vector_length:16,d}')
    results = []
    for _r in range(10):
        original = [float(_i) for _i in range(vector_length)]
        time_start = time.perf_counter()
        test_function(original)
        time_exec = time.perf_counter() - time_start
        results.append(time_exec)
        # del original
    # print()
    # print('\n'.join(f'{v:8.3f}' for v in results))
    print(f'Time: Min: {min(results):8.3f} Mean: {sum(results) / len(results):8.3f} Max: {max(results):8.3f}')
    rss_new = proc.memory_info().rss
    print(f'Total bytes RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


@pytest.mark.pymemtrace
def test_new_list_double_with_vector():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    with cPyMemTrace.Profile():
        _test_new_list_double(cPyCppContainers.new_list_vector_float)
    gc.collect()
    rss_new = proc.memory_info().rss
    print(f'RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


@pytest.mark.pymemtrace
def test_new_list_double_with_list():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    with cPyMemTrace.Profile():
        _test_new_list_double(cPyCppContainers.new_list_list_float)
    gc.collect()
    rss_new = proc.memory_info().rss
    print(f'RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


def _test_new_list_vector_bytes():
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
        cPyCppContainers.new_list_vector_bytes(original)
        time_exec = time.perf_counter() - time_start
        results.append(time_exec)
        # del original
    # print()
    # print('\n'.join(f'{v:8.3f}' for v in results))
    print(f'Time: Min: {min(results):8.3f} Mean: {sum(results) / len(results):8.3f} Max: {max(results):8.3f}')
    rss_new = proc.memory_info().rss
    print(f'Total bytes {total_bytes:16,d} RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


@pytest.mark.pymemtrace
def test_new_list_vector_bytes():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    with cPyMemTrace.Profile():
        _test_new_list_vector_bytes()
    gc.collect()
    # for i in range(4):
    #     time.sleep(1.0)
    rss_new = proc.memory_info().rss
    print(f'RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


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
    # print()
    # print('\n'.join(f'{v:8.3f}' for v in results))
    print(f'Time: Min: {min(results):8.3f} Mean: {sum(results) / len(results):8.3f} Max: {max(results):8.3f}')
    rss_new = proc.memory_info().rss
    print(f'_test_new_set_bytes(): Total bytes {total_bytes:16,d} RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


@pytest.mark.pymemtrace
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


def _test_new_dict_unordered_map_bytes():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    # 1Gb
    total_bytes = 2**20 * 2**10
    byte_length = 1024
    # total_bytes = 2**20 * 2**4
    # byte_length = 1024
    dict_length = total_bytes // byte_length // 2
    print(f'_test_new_dict_unordered_map_bytes(): Total bytes: {total_bytes:16,d} byte length: {byte_length:16,d} dict length: {dict_length:16,d}')
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
        # print(f'Actual dict length: {len(original):16,d}')
        time_start = time.perf_counter()
        cPyCppContainers.new_dict_from_std_unordered_map_bytes_bytes(original)
        time_exec = time.perf_counter() - time_start
        results.append(time_exec)
        # del original
    # print()
    # print('\n'.join(f'{v:8.3f}' for v in results))
    print(f'Time: Min: {min(results):8.3f} Mean: {sum(results) / len(results):8.3f} Max: {max(results):8.3f}')
    rss_new = proc.memory_info().rss
    print(f'_test_new_dict_unordered_map_bytes(): Total bytes {total_bytes:16,d} RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


@pytest.mark.pymemtrace
def test_new_dict_unordered_map_bytes():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    with cPyMemTrace.Profile(4096 * 16):
        _test_new_dict_unordered_map_bytes()
    gc.collect()
    # for i in range(4):
    #     time.sleep(1.0)
    rss_new = proc.memory_info().rss
    print(f'test_new_dict_unordered_map_bytes(): RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


def _test_new_dict_map_str():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    # 1Gb
    total_bytes = 2**20 * 2**10
    byte_length = 1024
    # total_bytes = 2**20 * 2**4
    # byte_length = 1024
    dict_length = total_bytes // byte_length // 2
    print(f'_test_new_dict_map_str(): Total bytes: {total_bytes:16,d} byte length: {byte_length:16,d} dict length: {dict_length:16,d}')
    random_bytes = [random.randint(0, 127) for _i in range(byte_length)]
    # byte_entry = b' ' * byte_length
    results = []
    for _r in range(10):
        original = {}
        for i in range(dict_length):
            k = bytes(random_bytes).decode('ascii')
            original[k] = ' ' * byte_length
            # random.shuffle(random_bytes)
            # Shuffle is quite expensive. Try something simpler, chose a random value and increment it with roll over.
            index = random.randint(0, byte_length - 1)
            random_bytes[index] = (random_bytes[index] + 1) % 128
        # print(f'Actual dict length: {len(original):16,d}')
        time_start = time.perf_counter()
        cPyCppContainers.new_dict_from_std_map_str_str(original)
        time_exec = time.perf_counter() - time_start
        results.append(time_exec)
        # del original
    # print()
    # print('\n'.join(f'{v:8.3f}' for v in results))
    print(f'Time: Min: {min(results):8.3f} Mean: {sum(results) / len(results):8.3f} Max: {max(results):8.3f}')
    rss_new = proc.memory_info().rss
    print(f'_test_new_dict_map_str(): Total bytes {total_bytes:16,d} RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


@pytest.mark.pymemtrace
def test_new_dict_map_str():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    with cPyMemTrace.Profile(4096 * 16):
        _test_new_dict_map_str()
    gc.collect()
    rss_new = proc.memory_info().rss
    print(f'test_new_dict_map_str(): RSS was {rss:16,d} now {rss_new:16,d} diff: {rss_new - rss:+16,d}')


# Test for single item container leaks.
@pytest.mark.pymemtrace
def test_new_list_vector_vector_bytes_one_item():
    """Tests converting a list with a single 1024 byte item 10m times to look for memory leaks in list creation.

    Example pymemtrace log::

              Event        dEvent  Clock        What     File                                                                            #line Function                                  RSS         dRSS
        NEXT: 0            +0      0.807417     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_vector_bytes                       33898496     33898496
        NEXT: 1            +1      0.807427     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_vector_bytes                       33931264        32768
        PREV: 396898       +396897 1.469587     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_vector_bytes                       33931264            0
        NEXT: 396899       +396898 1.469631     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_bytes                       33964032        32768
        PREV: 562738       +165839 1.749167     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_bytes                       33964032            0
        NEXT: 562739       +165840 1.749218     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_bytes                       33996800        32768
        PREV: 563166       +427    1.749971     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_bytes                       33996800            0
        NEXT: 563167       +428    1.750000     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_bytes                       34029568        32768
        PREV: 563398       +231    1.750459     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_bytes                       34029568            0
        NEXT: 563399       +232    1.750484     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_bytes                       34062336        32768
        PREV: 912896       +349497 2.331721     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_bytes                       34062336            0
        NEXT: 912897       +349498 2.331773     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_bytes                       34095104        32768
        PREV: 912898       +1      2.331792     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_bytes                       34095104            0
        NEXT: 912899       +2      2.331825     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_bytes                       34160640        65536
        PREV: 913728       +829    2.333386     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_bytes                       34160640            0
        NEXT: 913729       +830    2.333407     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py#  59 new_list_vector_bytes                       34193408        32768

    So no apparent leaks.

    Mac Book Pro::

              Event        dEvent  Clock        What     File                                                                            #line Function                                  RSS         dRSS
        NEXT: 0            +0      1.313118     C_CALL   /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 185 new_list_vector_bytes                       29655040     29655040
        NEXT: 1            +1      1.313215     C_RETURN /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 185 new_list_vector_bytes                       29663232         8192
        PREV: 20000000     +19999999 54.401765    C_CALL   /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 186 collect                              29663232            0
        NEXT: 20000001     +20000000 54.412929    C_RETURN /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 186 collect                              29667328         4096
    """
    original = [b' ' * 1024]
    with cPyMemTrace.Profile():
        for _r in range(10_000_000):
            cPyCppContainers.new_list_vector_bytes(original)
        # Tends to force an event in pymemtrace.
        gc.collect()


@pytest.mark.pymemtrace
def test_new_set_bytes_one_item():
    """Tests converting a set with a single 1024 byte item 10m times to look for memory leaks in set creation.

    Example pymemtrace log::

              Event        dEvent  Clock        What     File                                                                            #line Function                                  RSS         dRSS
        NEXT: 0            +0      0.944762     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 157 new_set_bytes                        34013184     34013184
        NEXT: 1            +1      0.944807     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 157 new_set_bytes                        34062336        49152
        PREV: 268026       +268025 1.500365     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 157 new_set_bytes                        34062336            0
        NEXT: 268027       +268026 1.500405     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 157 new_set_bytes                        34095104        32768
        PREV: 5779708      +5511681 12.858060    C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 157 new_set_bytes                        34095104            0
        NEXT: 5779709      +5511682 12.858098    C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 157 new_set_bytes                        34127872        32768

    So no apparent leaks.

    Mac Book Pro::

                  Event        dEvent  Clock        What     File                                                                            #line Function                                  RSS         dRSS
        NEXT: 0            +0      1.298169     C_CALL   /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 206 new_set_bytes                        29270016     29270016
        NEXT: 1            +1      1.298269     C_RETURN /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 206 new_set_bytes                        29286400        16384
        PREV: 20000000     +19999999 59.288278    C_CALL   /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 207 collect                              29286400            0
        NEXT: 20000001     +20000000 59.296249    C_RETURN /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 207 collect                              29290496         4096
    """
    original = {b' ' * 1024}
    with cPyMemTrace.Profile():
        for _r in range(10_000_000):
            cPyCppContainers.new_set_bytes(original)
        # Tends to force an event in pymemtrace.
        gc.collect()


@pytest.mark.pymemtrace
def test_new_dict_unordered_map_bytes_one_item():
    """Tests converting a dict with a single 1024 byte item 1m times to look for memory leaks in dict creation.

    Example pymemtrace log::

              Event        dEvent  Clock        What     File                                                                            #line Function                                  RSS         dRSS
        NEXT: 0            +0      0.899987     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 208 new_dict_bytes_bytes                 34127872     34127872
        NEXT: 1            +1      0.900023     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 208 new_dict_bytes_bytes                 34160640        32768
        PREV: 34222        +34221  0.975236     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 208 new_dict_bytes_bytes                 34160640            0
        NEXT: 34223        +34222  0.975284     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 208 new_dict_bytes_bytes                 34226176        65536
        PREV: 34300        +77     0.975484     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 208 new_dict_bytes_bytes                 34226176            0
        NEXT: 34301        +78     0.975521     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 208 new_dict_bytes_bytes                 34291712        65536
        PREV: 64686        +30385  1.042318     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 208 new_dict_bytes_bytes                 34291712            0
        NEXT: 64687        +30386  1.042350     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 208 new_dict_bytes_bytes                 34324480        32768
        PREV: 65332        +645    1.044195     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 208 new_dict_bytes_bytes                 34324480            0
        NEXT: 65333        +646    1.044231     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 208 new_dict_bytes_bytes                 34357248        32768
        PREV: 69658        +4325   1.055505     C_CALL   /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 208 new_dict_bytes_bytes                 34357248            0
        NEXT: 69659        +4326   1.055551     C_RETURN /Users/paulross/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 208 new_dict_bytes_bytes                 34390016        32768

    So no apparent leaks.

    Mac book pro:
              Event        dEvent  Clock        What     File                                                                            #line Function                                  RSS         dRSS
        NEXT: 0            +0      1.252117     C_CALL   /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 227 new_dict_bytes_bytes                 29282304     29282304
        NEXT: 1            +1      1.252255     C_RETURN /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 227 new_dict_bytes_bytes                 29294592        12288
        PREV: 1504         +1503   1.257911     C_CALL   /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 227 new_dict_bytes_bytes                 29294592            0
        NEXT: 1505         +1504   1.257928     C_RETURN /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 227 new_dict_bytes_bytes                 29298688         4096
        PREV: 20210        +18705  1.322274     C_CALL   /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 227 new_dict_bytes_bytes                 29298688            0
        NEXT: 20211        +18706  1.322299     C_RETURN /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 227 new_dict_bytes_bytes                 29310976        12288
        PREV: 20000000     +19979789 65.900513    C_CALL   /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 228 collect                              29310976            0
        NEXT: 20000001     +19979790 65.909449    C_RETURN /Users/engun/CLionProjects/PythonCppHomogeneousContainers/tests/unit/test_with_pymemtrace.py# 228 collect                              29315072         4096
    """
    original = {b' ' * 1024: b' ' * 1024}
    with cPyMemTrace.Profile():
        for _r in range(10_000_000):
            cPyCppContainers.new_dict_from_std_unordered_map_bytes_bytes(original)
        # Tends to force an event in pymemtrace.
        gc.collect()
