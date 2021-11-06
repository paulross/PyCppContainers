import pprint
import random
import statistics
import time
import typing

import pytest
import psutil

import cPyCppContainers

SIZE_DOUBLING = tuple(2 ** v for v in range(1, 20 + 1))
SIZE_DOUBLING = tuple(2 ** v for v in range(1, 16 + 1))
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
        return f'{"Count":>12s} {"Min":>12s} {"Mean":>12s} {"Median":>12s} {"Std.Dev.":>12s} {"Max":>12s} {"Max/Min":>12s}'

    def __str__(self) -> str:
        return (
            f'{len(self):12d}'
            f' {self.min():12.6f}'
            f' {self.mean():12.6f}'
            f' {self.median():12.6f}'
            f' {self.stdev():12.6f}'
            f' {self.max():12.6f}'
            f' {self.max() / self.min():12.1f}'
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
    rss_new = proc.memory_info().rss
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
    print(f'{"Size":>8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:8d} {t} {1e9 * t.min() / s:12.1f}')
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
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
    print(f'{"Size":>8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:8d} {t} {1e9 * t.min() / s:12.1f}')
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
        print(f'RSS HERE was {rss_here:,d} now {rss_now:,d} rate {(rss_now - rss_here) / (REPEAT * size)}')
    # pprint.pprint(results)
    print()
    rss_new = proc.memory_info().rss
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')
    print(f'{"Size":>8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:8d} {t} {1e9 * t.min() / s:12.1f}')
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
        for size in SIZE_DOUBLING:
            original = [BYTES_LISTS[byte_length][:] for _i in range(size)]
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
        print(f'Byte length {byte_length}')
        print(f'{"Size":>8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
        for s, t in results:
            print(f'{s:8d} {t} {1e9 * t.min() / s:12.1f}')
    rss_new = proc.memory_info().rss
    print(f'RSS was {rss:,d} now {rss_new:,d} diff: {rss_new - rss:,d}')


def test_new_list_bytes():
    for i in range(5):
        _test_new_list_bytes()
    assert 0
