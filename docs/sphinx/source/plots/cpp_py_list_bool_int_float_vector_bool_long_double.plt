set grid

set logscale x
set xlabel "Size of List"

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

set key left
set boxwidth 0.2 relative

# First the raw time graphs:
# Python to C++
set title "Time to copy a Python list of bool, int, float to a C++ std::vector<T>."
set ylabel "Time (µs)"

set terminal svg size 1400,700           # choose the file format
set output "images/cpp_py_list_bool_int_float_vector_bool_long_double_time.svg"   # choose the output device

plot "dat/test_py_list_to_vector_multiple_bool.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python List[bool] -> C++" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_to_vector_multiple_long.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python List[int] -> C++" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_to_vector_multiple_double.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python List[int] -> C++" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

set terminal png size 1400,700           # choose the file format
set output "images/cpp_py_list_bool_int_float_vector_bool_long_double_time.png"   # choose the output device

plot "dat/test_py_list_to_vector_multiple_bool.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python List[bool] -> C++" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_to_vector_multiple_long.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python List[int] -> C++" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_to_vector_multiple_double.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python List[int] -> C++" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

# C++ to Python
set terminal svg size 1400,700           # choose the file format
set output "images/cpp_vector_bool_long_double_py_list_bool_int_float_time.svg"   # choose the output device

set title "Time to copy a C++ std::vector<T> to a Python list of bool, int, float."
set ylabel "Time (µs)"

plot "dat/test_vector_to_py_list_multiple_bool.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ List<bool> -> Python" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_to_py_list_multiple_long.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ List<long> -> Python" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_to_py_list_multiple_double.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ List<double> -> Python" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

set terminal png size 1400,700           # choose the file format
set output "images/cpp_vector_bool_long_double_py_list_bool_int_float_time.png"   # choose the output device

plot "dat/test_vector_to_py_list_multiple_bool.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ List<bool> -> Python" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_to_py_list_multiple_long.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ List<long> -> Python" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_to_py_list_multiple_double.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ List<double> -> Python" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

# Now the rate graphs.
TODO

# Python to C++
set title "Rate of copying a Python list of bool, int, float to a C++ std::vector<T>."
set ylabel "Time per Item (µs)"

set terminal svg size 1400,700           # choose the file format
set output "images/cpp_py_list_bool_int_float_vector_bool_long_doublerate.svg"   # choose the output device

plot "dat/test_py_list_bytes_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python List -> C++, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python List -> C++, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python List -> C++, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python List -> C++, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

set terminal png size 1400,700           # choose the file format
set output "images/cpp_py_list_bool_int_float_vector_bool_long_doublerate.png"   # choose the output device

plot "dat/test_py_list_bytes_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python List -> C++, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python List -> C++, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python List -> C++, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python List -> C++, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_bytes_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

# Python to C++
set terminal svg size 1400,700           # choose the file format
set output "images/cpp_vector_string_py_list_bytes_rate.svg"   # choose the output device

set title "Rate of copying a C++ std::vector<T> to a Python list of bool, int, float."
set ylabel "Time per Item (µs)"

plot "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
            t "C+ List -> Python, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_list_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C+ List -> Python, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_list_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C+ List -> Python, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_list_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C+ List -> Python, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

set terminal png size 1400,700           # choose the file format
set output "images/cpp_vector_string_py_list_bytes_rate.png"   # choose the output device

plot "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
            t "C+ List -> Python, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_list_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C+ List -> Python, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_list_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C+ List -> Python, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_list_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C+ List -> Python, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

reset
