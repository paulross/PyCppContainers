import pprint
import statistics
import time
import typing

import pytest
import psutil

import cPyCppContainers


SIZE_DOUBLING = tuple(2**v for v in range(1, 20+1))
# SIZE_DOUBLING_BYTE_LENGTH = tuple(2**v for v in  range(1, 10+1))
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
        return f'{"Min":>12s} {"Mean":>12s} {"Median":>12s} {"Std.Dev.":>12s} {"Max":>12s} {"Max/Min":>12s}'

    def __str__(self) -> str:
        return (
            f'{self.min():12.6f}'
            f' {self.mean():12.6f}'
            f' {self.median():12.6f}'
            f' {self.stdev():12.6f}'
            f' {self.max():12.6f}'
            f' {self.max() / self.min():12.1f}'
        )


def test_new_list_bool():
    results = []
    proc = psutil.Process()
    rss = proc.memory_info().rss
    for size in SIZE_DOUBLING:
        original = [True, False,] * (size // 2)
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
    print(f'RSS was {rss:,d} now {rss_new:,d}')
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
    print(f'RSS was {rss:,d} now {rss_new:,d}')
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
    print(f'RSS was {rss:,d} now {proc.memory_info().rss:,d}')
    print(f'{"Size":>8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
    for s, t in results:
        print(f'{s:8d} {t} {1e9 * t.min() / s:12.1f}')
    assert 0


def _test_new_list_bytes():
    proc = psutil.Process()
    rss = proc.memory_info().rss
    for byte_length in SIZE_DOUBLING_BYTE_LENGTH:
        results = []
        for size in SIZE_DOUBLING:
            original = [b' ' * byte_length for v in range(size)]
            timer = TimedResults()
            for _r in range(REPEAT):
                time_start = time.perf_counter()
                cPyCppContainers.new_list_bytes(original)
                time_exec = time.perf_counter() - time_start
                timer.add(time_exec)
            results.append((size, timer))
        print()
        rss_new = proc.memory_info().rss
        print(f'RSS was {rss:,d} now {rss_new:,d}')
        print(f'Byte length {byte_length}')
        print(f'{"Size":>8s} {results[0][1].str_header():s} {"Min/Size e9":>12s}')
        for s, t in results:
            print(f'{s:8d} {t} {1e9 * t.min() / s:12.1f}')
    print(f'RSS was {rss:,d} now {proc.memory_info().rss:,d}')
    assert 0


def test_memory():
    for i in range(4):
        _test_new_list_bytes()