set grid

set logscale x
set xlabel "Size of Tuple"

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

# First the raw time graph:
set title "Time to copy a Python tuple of str to a C++ std::vector<std::string> with different string lengths."
set ylabel "Time (µs)"

set terminal svg size 800,400           # choose the file format
set output "images/cpp_py_tuple_str_vector_string_time.svg"   # choose the output device

plot "dat/test_py_tuple_str_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Tuple -> C++, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Tuple -> C++, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Tuple -> C++, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Tuple -> C++, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

set terminal png size 800,400           # choose the file format
set output "images/cpp_py_tuple_str_vector_string_time.png"   # choose the output device

plot "dat/test_py_tuple_str_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Tuple -> C++, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Tuple -> C++, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Tuple -> C++, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Tuple -> C++, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

set terminal svg size 800,400           # choose the file format
set output "images/cpp_vector_string_py_tuple_str_time.svg"   # choose the output device

set title "Time to copy a C++ std::vector<std::string> to a Python tuple of str with different string lengths."
set ylabel "Time (µs)"

plot "dat/test_vector_string_to_py_tuple_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Tuple -> Python, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Tuple -> Python, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Tuple -> Python, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Tuple -> Python, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_string_to_py_tuple_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_string_to_py_tuple_multiple_std_string_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

set terminal png size 800,400           # choose the file format
set output "images/cpp_vector_string_py_tuple_str_time.png"   # choose the output device

plot "dat/test_vector_string_to_py_tuple_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Tuple -> Python, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Tuple -> Python, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Tuple -> Python, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "C++ Tuple -> Python, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_string_to_py_tuple_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_string_to_py_tuple_multiple_std_string_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

# Now the rate graph.
set title "Rate of copying a Python tuple of str to a C++ std::vector<std::string> with different string lengths."
set ylabel "Time per Item (µs)"

set terminal svg size 800,400           # choose the file format
set output "images/cpp_py_tuple_str_vector_string_rate.svg"   # choose the output device

plot "dat/test_py_tuple_str_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Tuple -> C++, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Tuple -> C++, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Tuple -> C++, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Tuple -> C++, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

set terminal png size 800,400           # choose the file format
set output "images/cpp_py_tuple_str_vector_string_rate.png"   # choose the output device

plot "dat/test_py_tuple_str_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Tuple -> C++, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Tuple -> C++, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Tuple -> C++, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "Python Tuple -> C++, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_str_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

set terminal svg size 800,400           # choose the file format
set output "images/cpp_vector_string_py_tuple_str_rate.svg"   # choose the output device

set title "Rate of copying a C++ std::vector<std::string> to a Python tuple of str with different string lengths."
set ylabel "Time per Item (µs)"

plot "dat/test_vector_string_to_py_tuple_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
            t "C+ Tuple -> Python, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_tuple_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C+ Tuple -> Python, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_tuple_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C+ Tuple -> Python, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_tuple_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C+ Tuple -> Python, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

set terminal png size 800,400           # choose the file format
set output "images/cpp_vector_string_py_tuple_str_rate.png"   # choose the output device

plot "dat/test_vector_string_to_py_tuple_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
            t "C+ Tuple -> Python, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_tuple_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C+ Tuple -> Python, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_tuple_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C+ Tuple -> Python, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_tuple_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
        t "C+ Tuple -> Python, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_tuple_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

reset
