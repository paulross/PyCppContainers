"""
This is a fairly exhaustive set of tests that take a long time to run.

Run this with:
$ pytest -vs --runslow tests/unit/test_perf_cPyCppContainers.py
"""
import random
import statistics
import time
import typing

import pytest
import psutil

import cPyCppContainers

SIZE_DOUBLING = tuple(2 ** v for v in range(1, 20 + 1))
# SIZE_DOUBLING = tuple(2 ** v for v in range(1, 16 + 1))
# SIZE_DOUBLING_BYTE_LENGTH = (8, 64, 512, 4096)
SIZE_DOUBLING_BYTE_LENGTH = (2, 16, 128, 1024)
# SIZE_DOUBLING_BYTE_LENGTH = (8, 64)
REPEAT = 5


class TimedResults:
    def __init__(self):
        self.times: typing.List[float] = []

    def add(self, t: float):
        self.times.append(t)

    def min(self) -> float:
        self.times.sort()
        return self.times[0]

    def max(self) -> float:
        self.times.sort()
        return self.times[-1]

    def mean(self) -> float:
        return sum(self.times) / len(self.times)

    def median(self) -> float:
        self.times.sort()
        return statistics.median(self.times)

    def stdev(self) -> float:
        self.times.sort()
        return statistics.stdev(self.times)

    def min_max_range(self) -> float:
        return self.max() - self.min()

    def str_header(self) -> str:
        return f'{"Count":>12s} {"Min":>16s} {"Mean":>16s} {"Median":>16s} {"Std.Dev.":>16s} {"Max":>16s} {"Max/Min":>12s}'

    def __str__(self) -> str:
        ret = [
            f'{len(self):12d}',
            f'{self.min():16.9f}',
            f'{self.mean():16.9f}',
            f'{self.median():16.9f}',
            f'{self.stdev():16.9f}' if len(self) > 1 else f'{"N/A":>16}',
            f'{self.max():16.9f}',
            f'{self.max() / self.min():12.3f}',
        ]
        return ' '.join(ret)

    def __len__(self):
        return len(self.times)


def get_random_bytes(byte_values: typing.List[int], length: int) -> bytes:
    random.shuffle(byte_values)
    # b = bytearray()
    # for i in range(length):
    #     b.append(random.randint(0, 255))
    return bytes(byte_values[:length])


# Use 0x7F so we can convert these to strings with .decode('ascii')
LIST_OF_BYTE_VALUES = [v % 0x7F for v in range(max(SIZE_DOUBLING))]

# Pre-allocated lists of random bytes
BYTES_LISTS = {
    k: get_random_bytes(LIST_OF_BYTE_VALUES, max(SIZE_DOUBLING)) for k in SIZE_DOUBLING_BYTE_LENGTH
}


@pytest.mark.slow
def test_new_list_bool():
    results = []
    proc = psutil.Process()
    rss = proc.memory_info().rss
    for size in SIZE_DOUBLING:
        original = [True, False, ] * (size // 2)
        timer = TimedResults()
        for _r in range(REPEAT):
            time_start = time.perf_counter()
            cPyCppContainers.new_list_bool(original)
            time_exec = time.perf_counter() - time_start
            timer.add(time_exec)
        results.append((size, timer))
    # pprint.pprint(results)
    print()
    print('test_new_list_bool():')
    rss_new = proc.memory_info().rss
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
    print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_list_int():
    results = []
    proc = psutil.Process()
    rss = proc.memory_info().rss
    for size in SIZE_DOUBLING:
        original = list(range(size))
        timer = TimedResults()
        for _r in range(REPEAT):
            time_start = time.perf_counter()
            cPyCppContainers.new_list_int(original)
            time_exec = time.perf_counter() - time_start
            timer.add(time_exec)
        results.append((size, timer))
    # pprint.pprint(results)
    print()
    rss_new = proc.memory_info().rss
    print('test_new_list_int():')
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
    print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_list_float():
    results = []
    proc = psutil.Process()
    rss = proc.memory_info().rss
    for size in SIZE_DOUBLING:
        rss_here = proc.memory_info().rss
        original = [float(v) for v in range(size)]
        timer = TimedResults()
        for _r in range(REPEAT):
            time_start = time.perf_counter()
            cPyCppContainers.new_list_float(original)
            time_exec = time.perf_counter() - time_start
            timer.add(time_exec)
        results.append((size, timer))
        rss_now = proc.memory_info().rss
        # print(f'RSS HERE was {rss_here:,d} now {rss_now:,d} rate {(rss_now - rss_here) / (REPEAT * size)}')
    # pprint.pprint(results)
    print()
    rss_new = proc.memory_info().rss
    print('test_new_list_float()')
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
    print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_list_complex():
    results = []
    proc = psutil.Process()
    rss = proc.memory_info().rss
    for size in SIZE_DOUBLING:
        rss_here = proc.memory_info().rss
        original = [complex(v, v) for v in range(size)]
        timer = TimedResults()
        for _r in range(REPEAT):
            time_start = time.perf_counter()
            cPyCppContainers.new_list_complex(original)
            time_exec = time.perf_counter() - time_start
            timer.add(time_exec)
        results.append((size, timer))
        rss_now = proc.memory_info().rss
        # print(f'RSS HERE was {rss_here:,d} now {rss_now:,d} rate {(rss_now - rss_here) / (REPEAT * size)}')
    # pprint.pprint(results)
    print()
    rss_new = proc.memory_info().rss
    print('test_new_list_complex()')
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
    print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_list_bytes():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    for byte_length in SIZE_DOUBLING_BYTE_LENGTH:
        results = []
        # 1Gb limit is 2**30
        max_size = 2 ** 24 // byte_length
        for size in SIZE_DOUBLING:
            # original = [BYTES_LISTS[byte_length] for _i in range(size)]
            original_bytes = b' ' * byte_length
            original = [original_bytes for _i in range(size)]
            timer = TimedResults()
            for _r in range(REPEAT):
                time_start = time.perf_counter()
                cPyCppContainers.new_list_bytes(original)
                time_exec = time.perf_counter() - time_start
                timer.add(time_exec)
            results.append((size, timer))
        print()
        rss_new = proc.memory_info().rss
        print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
        print(f'test_new_list_bytes() Byte length {byte_length}')
        print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
        for s, t in results:
            print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')
    rss_new = proc.memory_info().rss
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')


@pytest.mark.slow
def test_new_list_str():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    for byte_length in SIZE_DOUBLING_BYTE_LENGTH:
        results = []
        # 1Gb limit is 2**30
        max_size = 2 ** 24 // byte_length
        for size in SIZE_DOUBLING:
            # original = [BYTES_LISTS[byte_length] for _i in range(size)]
            original_str = ' ' * byte_length
            original = [original_str for _i in range(size)]
            timer = TimedResults()
            for _r in range(REPEAT):
                time_start = time.perf_counter()
                cPyCppContainers.new_list_str(original)
                time_exec = time.perf_counter() - time_start
                timer.add(time_exec)
            results.append((size, timer))
        print()
        rss_new = proc.memory_info().rss
        print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
        print(f'test_new_list_str() String length {byte_length}')
        print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
        for s, t in results:
            print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')
    rss_new = proc.memory_info().rss
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')


@pytest.mark.slow
def test_new_set_int():
    results = []
    proc = psutil.Process()
    rss = proc.memory_info().rss
    for size in SIZE_DOUBLING:
        original = {i for i in range(size)}
        timer = TimedResults()
        for _r in range(REPEAT):
            time_start = time.perf_counter()
            cPyCppContainers.new_set_int(original)
            time_exec = time.perf_counter() - time_start
            timer.add(time_exec)
        results.append((size, timer))
    # pprint.pprint(results)
    print()
    rss_new = proc.memory_info().rss
    print('test_new_set_int()')
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
    print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_set_float():
    results = []
    proc = psutil.Process()
    rss = proc.memory_info().rss
    # for size in tuple(2 ** v for v in range(1, 16 + 1)):
    # for size in tuple(2 ** v for v in range(10, 11 + 1)):
    for size in SIZE_DOUBLING:
        original = {float(i) for i in range(size)}
        timer = TimedResults()
        for _r in range(REPEAT):
            time_start = time.perf_counter()
            cPyCppContainers.new_set_float(original)
            time_exec = time.perf_counter() - time_start
            timer.add(time_exec)
        results.append((size, timer))
    # pprint.pprint(results)
    print()
    rss_new = proc.memory_info().rss
    print('test_new_set_float()')
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
    print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_set_complex():
    results = []
    proc = psutil.Process()
    rss = proc.memory_info().rss
    # for size in tuple(2 ** v for v in range(1, 16 + 1)):
    # for size in tuple(2 ** v for v in range(10, 11 + 1)):
    for size in SIZE_DOUBLING:
        original = {complex(float(i), float(i)) for i in range(size)}
        timer = TimedResults()
        for _r in range(REPEAT):
            time_start = time.perf_counter()
            cPyCppContainers.new_set_complex(original)
            time_exec = time.perf_counter() - time_start
            timer.add(time_exec)
        results.append((size, timer))
    # pprint.pprint(results)
    print()
    rss_new = proc.memory_info().rss
    print('test_new_set_complex()')
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
    print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_set_bytes():
    random_bytes = [random.randint(0, 255) for _i in range(max(SIZE_DOUBLING_BYTE_LENGTH))]
    proc = psutil.Process()
    for byte_length in SIZE_DOUBLING_BYTE_LENGTH:
        results = []
        rss = proc.memory_info().rss
        for size in SIZE_DOUBLING:
            original = set()
            for i in range(size):
                random.shuffle(random_bytes)
                k = bytes(random_bytes[:byte_length])
                original.add(k)
            # print(f'TRACE dict len {len(original)}')
            timer = TimedResults()
            for _r in range(REPEAT):
                time_start = time.perf_counter()
                cPyCppContainers.new_set_bytes(original)
                time_exec = time.perf_counter() - time_start
                timer.add(time_exec)
            results.append((size, timer))
        # pprint.pprint(results)
        print()
        rss_new = proc.memory_info().rss
        print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
        print(f'test_new_set_bytes() Byte length {byte_length}')
        print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
        for s, t in results:
            print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_set_str():
    random_bytes = [random.randint(0, 127) for _i in range(max(SIZE_DOUBLING_BYTE_LENGTH))]
    proc = psutil.Process()
    for byte_length in SIZE_DOUBLING_BYTE_LENGTH:
        results = []
        rss = proc.memory_info().rss
        for size in SIZE_DOUBLING:
            original = set()
            for i in range(size):
                random.shuffle(random_bytes)
                k = bytes(random_bytes[:byte_length])
                original.add(k.decode('ascii'))
            # print(f'TRACE dict len {len(original)}')
            timer = TimedResults()
            for _r in range(REPEAT):
                time_start = time.perf_counter()
                cPyCppContainers.new_set_str(original)
                time_exec = time.perf_counter() - time_start
                timer.add(time_exec)
            results.append((size, timer))
        # pprint.pprint(results)
        print()
        rss_new = proc.memory_info().rss
        print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
        print(f'test_new_set_str() String length {byte_length}')
        print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
        for s, t in results:
            print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_dict_int_int():
    results = []
    proc = psutil.Process()
    rss = proc.memory_info().rss
    for size in SIZE_DOUBLING:
        original = {i: i for i in range(size)}
        timer = TimedResults()
        for _r in range(REPEAT):
            time_start = time.perf_counter()
            cPyCppContainers.new_dict_int_int(original)
            time_exec = time.perf_counter() - time_start
            timer.add(time_exec)
        results.append((size, timer))
    # pprint.pprint(results)
    print()
    rss_new = proc.memory_info().rss
    print('test_new_dict_int_int()')
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
    print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_dict_float_float():
    results = []
    proc = psutil.Process()
    rss = proc.memory_info().rss
    # for size in tuple(2 ** v for v in range(1, 16 + 1)):
    # for size in tuple(2 ** v for v in range(10, 11 + 1)):
    for size in SIZE_DOUBLING:
        original = {float(i): float(i) for i in range(size)}
        timer = TimedResults()
        # for _r in range(REPEAT):
        for _r in range(REPEAT):
            time_start = time.perf_counter()
            cPyCppContainers.new_dict_float_float(original)
            time_exec = time.perf_counter() - time_start
            timer.add(time_exec)
        results.append((size, timer))
    # pprint.pprint(results)
    print()
    rss_new = proc.memory_info().rss
    print('test_new_dict_float_float()')
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
    print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_dict_complex_complex():
    results = []
    proc = psutil.Process()
    rss = proc.memory_info().rss
    # for size in tuple(2 ** v for v in range(1, 16 + 1)):
    # for size in tuple(2 ** v for v in range(10, 11 + 1)):
    for size in SIZE_DOUBLING:
        original = {complex(float(i),  float(i)): complex(float(i),  float(i)) for i in range(size)}
        timer = TimedResults()
        # for _r in range(REPEAT):
        for _r in range(REPEAT):
            time_start = time.perf_counter()
            cPyCppContainers.new_dict_complex_complex(original)
            time_exec = time.perf_counter() - time_start
            timer.add(time_exec)
        results.append((size, timer))
    # pprint.pprint(results)
    print()
    rss_new = proc.memory_info().rss
    print('test_new_dict_complex_complex()')
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
    print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_dict_bytes_bytes():
    random_bytes = [random.randint(0, 255) for _i in range(max(SIZE_DOUBLING_BYTE_LENGTH))]
    proc = psutil.Process()
    for byte_length in SIZE_DOUBLING_BYTE_LENGTH:
        results = []
        rss = proc.memory_info().rss
        for size in SIZE_DOUBLING:
            original = {}
            for i in range(size):
                random.shuffle(random_bytes)
                k = bytes(random_bytes[:byte_length])
                original[k] = b' ' * byte_length
            # print(f'TRACE dict len {len(original)}')
            timer = TimedResults()
            for _r in range(REPEAT):
                time_start = time.perf_counter()
                cPyCppContainers.new_dict_bytes_bytes(original)
                time_exec = time.perf_counter() - time_start
                timer.add(time_exec)
            results.append((size, timer))
        # pprint.pprint(results)
        print()
        rss_new = proc.memory_info().rss
        print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
        print(f'test_new_dict_bytes_bytes() Byte length {byte_length}')
        print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
        for s, t in results:
            print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_dict_bytes_bytes():
    random_bytes = [random.randint(0, 255) for _i in range(max(SIZE_DOUBLING_BYTE_LENGTH))]
    proc = psutil.Process()
    for byte_length in SIZE_DOUBLING_BYTE_LENGTH:
        results = []
        rss = proc.memory_info().rss
        for size in SIZE_DOUBLING:
            original = {}
            for i in range(size):
                random.shuffle(random_bytes)
                k = bytes(random_bytes[:byte_length])
                original[k] = b' ' * byte_length
            # print(f'TRACE dict len {len(original)}')
            timer = TimedResults()
            for _r in range(REPEAT):
                time_start = time.perf_counter()
                cPyCppContainers.new_dict_bytes_bytes(original)
                time_exec = time.perf_counter() - time_start
                timer.add(time_exec)
            results.append((size, timer))
        # pprint.pprint(results)
        print()
        rss_new = proc.memory_info().rss
        print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
        print(f'test_new_dict_bytes_bytes() String length {byte_length}')
        print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
        for s, t in results:
            print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')


@pytest.mark.slow
def test_new_dict_str_str():
    random_bytes = [random.randint(0, 127) for _i in range(max(SIZE_DOUBLING_BYTE_LENGTH))]
    proc = psutil.Process()
    for byte_length in SIZE_DOUBLING_BYTE_LENGTH:
        results = []
        rss = proc.memory_info().rss
        for size in SIZE_DOUBLING:
            original = {}
            for i in range(size):
                random.shuffle(random_bytes)
                k = bytes(random_bytes[:byte_length])
                original[k.decode('ascii')] = ' ' * byte_length
            # print(f'TRACE dict len {len(original)}')
            timer = TimedResults()
            for _r in range(REPEAT):
                time_start = time.perf_counter()
                cPyCppContainers.new_dict_str_str(original)
                time_exec = time.perf_counter() - time_start
                timer.add(time_exec)
            results.append((size, timer))
        # pprint.pprint(results)
        print()
        rss_new = proc.memory_info().rss
        print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
        print(f'test_new_dict_str_str() String length {byte_length}')
        print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
        for s, t in results:
            print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')
