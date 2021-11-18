import pprint
import random
import statistics
import time
import typing

import pytest
import psutil

import cPyCppContainers

SIZE_DOUBLING = tuple(2 ** v for v in range(1, 20 + 1))
# SIZE_DOUBLING = tuple(2 ** v for v in range(1, 16 + 1))
SIZE_DOUBLING_BYTE_LENGTH = (8, 64, 512, 4096)
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
        return (
            f'{len(self):12d}'
            f' {self.min():16.9f}'
            f' {self.mean():16.9f}'
            f' {self.median():16.9f}'
            f' {self.stdev():16.9f}'
            f' {self.max():16.9f}'
            f' {self.max() / self.min():12.3f}'
        )

    def __len__(self):
        return len(self.times)


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
    assert 0


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
    assert 0


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
    assert 0


def random_bytes(byte_values: typing.List[int], length: int) -> bytes:
    random.shuffle(byte_values)
    # b = bytearray()
    # for i in range(length):
    #     b.append(random.randint(0, 255))
    return bytes(byte_values[:length])


LIST_OF_BYTE_VALUES = [v % 0xFF for v in range(max(SIZE_DOUBLING))]

# Pre-allocated lists of random bytes
BYTES_LISTS = {
    k: random_bytes(LIST_OF_BYTE_VALUES, max(SIZE_DOUBLING)) for k in SIZE_DOUBLING_BYTE_LENGTH
}


def _test_new_list_bytes():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    for byte_length in SIZE_DOUBLING_BYTE_LENGTH:
        results = []
        # 1Gb limit is 2**30
        max_size = 2 ** 24 // byte_length
        for size in SIZE_DOUBLING:
            if size > max_size:
                print(f'Breaking as max size {max_size} reached memory {max_size * byte_length:,d}.')
                break
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


def test_new_list_bytes():
    for i in range(1):
        _test_new_list_bytes()
    assert 0


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
    assert 0


def test_new_dict_float_float():
    results = []
    proc = psutil.Process()
    rss = proc.memory_info().rss
    for size in SIZE_DOUBLING:
        original = {float(i): float(i) for i in range(size)}
        timer = TimedResults()
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
    assert 0


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
            if size >= 1024 * 128:
                break
        # pprint.pprint(results)
        print()
        rss_new = proc.memory_info().rss
        print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
        print(f'test_new_dict_bytes_bytes() Byte length {byte_length}')
        print(f'{"Size":<8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
        for s, t in results:
            print(f'{s:<8d} {t} {1e9 * t.min() / s:12.1f}')
    assert 0
