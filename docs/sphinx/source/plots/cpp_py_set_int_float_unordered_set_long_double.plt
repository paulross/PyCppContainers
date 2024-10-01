set grid

set logscale x
set xlabel "Size of Set"

set logscale y
set ylabel "Time per Item (µs)"
# set yrange [8:35]
# set yrange [0.001:10]
# set ytics 8,35,3

# set logscale y2
# set y2label "Bytes"
# set y2range [1:1e9]
# set y2tics

set pointsize 1
set datafile separator whitespace

# Some rate lines
latency = 0.04e-6
# 10,000 items per second
rate_10_000(x) = latency + x / 1e4
# 100,000 items per second
rate_100_000(x) = latency + x / 1e5
# 1,000,000 items per second
rate_1_000_000(x) = latency + x / 1e6
# 10,00,000 items per second
rate_10_000_000(x) = latency + x / 1e7
# 100,000,000 items per second
rate_100_000_000(x) = latency + x / 1e8
# 1,000,000,000 items per second
rate_1_000_000_000(x) = latency + x / 1e9

set boxwidth 0.2 relative

# First the raw time graphs:
# Python to C++
set title "Time to copy a Python set of int, float, complex to a C++ std::unordered_set<T>."
set key left
set ylabel "Time (µs)"

set terminal svg size 800,600           # choose the file format
set output "images/cpp_py_set_int_float_unordered_set_long_double_time.svg"   # choose the output device

plot "dat/test_py_set_to_unordered_set_multiple_long.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Set[int] -> C++" with candlesticks whiskerbars 0.5,\
    "dat/test_py_set_to_unordered_set_multiple_double.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Set[double] -> C++" with candlesticks whiskerbars 0.5,\
    "dat/test_py_set_to_unordered_set_multiple_std_complex_double.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Set[complex] -> C++" with candlesticks whiskerbars 0.5,\
    "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 0.5, \
    "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 0.5, \
    "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(rate_1_000_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1000m objects/s", latency*1e6) with lines dashtype 2 lw 0.5

set terminal png size 800,600           # choose the file format
set output "images/cpp_py_set_int_float_unordered_set_long_double_time.png"   # choose the output device

plot "dat/test_py_set_to_unordered_set_multiple_long.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Set[int] -> C++" with candlesticks whiskerbars 0.5,\
    "dat/test_py_set_to_unordered_set_multiple_double.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Set[double] -> C++" with candlesticks whiskerbars 0.5,\
    "dat/test_py_set_to_unordered_set_multiple_std_complex_double.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Set[complex] -> C++" with candlesticks whiskerbars 0.5,\
    "dat/test_py_set_to_unordered_set_multiple_long.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 0.5, \
    "dat/test_py_set_to_unordered_set_multiple_long.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 0.5, \
    "dat/test_py_set_to_unordered_set_multiple_long.dat" using 3:(rate_1_000_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1000m objects/s", latency*1e6) with lines dashtype 2 lw 0.5

# C++ to Python
set terminal svg size 800,600           # choose the file format
set output "images/cpp_unordered_set_long_double_py_set_int_float_time.svg"   # choose the output device

set title "Time to copy a C++ std::unordered_set<T> to a Python set of int, float, complex."
set ylabel "Time (µs)"

plot "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Set<long> -> Python" with candlesticks whiskerbars 0.5,\
    "dat/test_unordered_set_to_py_set_multiple_std_complex_double.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Set<double> -> Python" with candlesticks whiskerbars 0.5,\
    "dat/test_unordered_set_to_py_set_multiple_std_complex_double.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Set<std::complex<double>> -> Python" with candlesticks whiskerbars 0.5,\
    "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(rate_1_000_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1000m objects/s", latency*1e6) with lines dashtype 2 lw 2

set terminal png size 800,600           # choose the file format
set output "images/cpp_unordered_set_long_double_py_set_int_float_time.png"   # choose the output device

plot "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Set<long> -> Python" with candlesticks whiskerbars 0.5,\
    "dat/test_unordered_set_to_py_set_multiple_std_complex_double.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Set<double> -> Python" with candlesticks whiskerbars 0.5,\
    "dat/test_unordered_set_to_py_set_multiple_std_complex_double.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Set<std::complex<double>> -> Python" with candlesticks whiskerbars 0.5,\
    "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(rate_1_000_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1000m objects/s", latency*1e6) with lines dashtype 2 lw 2

# Now the rate graphs.
# Python to C++
set title "Rate of copying a Python set of int, float, complex to a C++ std::unordered_set<T>."
set key right
set ylabel "Time per Item (µs)"
set yrange [0.01:1]


set terminal svg size 800,600           # choose the file format
set output "images/cpp_py_set_int_float_unordered_set_long_double_rate.svg"   # choose the output device

plot "dat/test_py_set_to_unordered_set_multiple_long.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Set[int] -> C++" with candlesticks whiskerbars 0.5,\
        "dat/test_py_set_to_unordered_set_multiple_long.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_set_to_unordered_set_multiple_double.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Set[double] -> C++" with candlesticks whiskerbars 0.5,\
        "dat/test_py_set_to_unordered_set_multiple_double.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_set_to_unordered_set_multiple_std_complex_double.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Set[complex] -> C++" with candlesticks whiskerbars 0.5,\
        "dat/test_py_set_to_unordered_set_multiple_std_complex_double.dat" using 3:(1e6 * $7 / $3) t "" with lines

set terminal png size 800,600           # choose the file format
set output "images/cpp_py_set_int_float_unordered_set_long_double_rate.png"   # choose the output device

plot "dat/test_py_set_to_unordered_set_multiple_long.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Set[int] -> C++" with candlesticks whiskerbars 0.5,\
        "dat/test_py_set_to_unordered_set_multiple_long.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_set_to_unordered_set_multiple_double.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Set[double] -> C++" with candlesticks whiskerbars 0.5,\
        "dat/test_py_set_to_unordered_set_multiple_double.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_set_to_unordered_set_multiple_std_complex_double.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Set[complex] -> C++" with candlesticks whiskerbars 0.5,\
        "dat/test_py_set_to_unordered_set_multiple_std_complex_double.dat" using 3:(1e6 * $7 / $3) t "" with lines

# C++ to Python
set terminal svg size 800,600           # choose the file format
set output "images/cpp_unordered_set_long_double_py_set_int_float_rate.svg"   # choose the output device

set title "Rate of copying a C++ std::unordered_set<T> to a Python set of int, float, complex."
set ylabel "Time per Item (µs)"
set yrange [0.001:0.1]

plot "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C++ Set<long> -> Python" with candlesticks whiskerbars 0.5,\
        "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_unordered_set_to_py_set_multiple_double.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C++ Set<double> -> Python" with candlesticks whiskerbars 0.5,\
        "dat/test_unordered_set_to_py_set_multiple_double.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_unordered_set_to_py_set_multiple_std_complex_double.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C++ Set<std::complex<double>> -> Python" with candlesticks whiskerbars 0.5,\
        "dat/test_unordered_set_to_py_set_multiple_std_complex_double.dat" using 3:(1e6 * $7 / $3) t "" with lines

set terminal png size 800,600           # choose the file format
set output "images/cpp_unordered_set_long_double_py_set_int_float_rate.png"   # choose the output device

plot "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C++ Set<long> -> Python" with candlesticks whiskerbars 0.5,\
        "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_unordered_set_to_py_set_multiple_double.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C++ Set<double> -> Python" with candlesticks whiskerbars 0.5,\
        "dat/test_unordered_set_to_py_set_multiple_double.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_unordered_set_to_py_set_multiple_std_complex_double.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C++ Set<std::complex<double>> -> Python" with candlesticks whiskerbars 0.5,\
        "dat/test_unordered_set_to_py_set_multiple_std_complex_double.dat" using 3:(1e6 * $7 / $3) t "" with lines

reset
