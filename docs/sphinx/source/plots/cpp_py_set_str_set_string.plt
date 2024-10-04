set title "Time to copy a Python set of str to a C++ set by string lengths."
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

set key left
set boxwidth 0.2 relative

# First the raw time graph:
set ylabel "Time (µs)"

set terminal svg size 700,400           # choose the file format
set output "images/cpp_py_set_str_unordered_set_string_time.svg"   # choose the output device

plot "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Set, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Set, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Set, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2

set terminal png size 700,400           # choose the file format
set output "images/cpp_py_set_str_unordered_set_string_time.png"   # choose the output device

plot "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Set, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Set, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Python Set, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2

# Now the rate graph.
set ylabel "Time per Item (µs)"

set terminal svg size 700,400           # choose the file format
set output "images/cpp_py_set_str_unordered_set_string_rate.svg"   # choose the output device

plot "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 16" with candlesticks whiskerbars 0.5 linetype 2,\
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 2, \
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 128" with candlesticks whiskerbars 0.5 linetype 4,\
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 4, \
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 1024" with candlesticks whiskerbars 0.5 linetype 7,\
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 7

set terminal png size 700,400           # choose the file format
set output "images/cpp_py_set_str_unordered_set_string_rate.png"   # choose the output device

plot "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 16" with candlesticks whiskerbars 0.5 linetype 2,\
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 2, \
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 128" with candlesticks whiskerbars 0.5 linetype 4,\
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 4, \
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 1024" with candlesticks whiskerbars 0.5 linetype 7,\
    "dat/test_py_set_str_to_unordered_set_string_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 7

# ======================
# C++ to Python
# ======================
set title "Time to copy a C++ std::unordered_set of std::string to a Python set of strbylengths."

set key left

# First the raw time graph:
set ylabel "Time (µs)"

set terminal svg size 700,400           # choose the file format
set output "images/cpp_unordered_set_string_to_py_set_multiple_std_string_time.svg"   # choose the output device

plot "dat/test_unordered_set_string_to_py_set_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Set, bytes length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Set, bytes length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Set, bytes length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2

set terminal png size 700,400           # choose the file format
set output "images/cpp_unordered_set_string_to_py_set_multiple_std_string_time.png"   # choose the output device

plot "dat/test_unordered_set_string_to_py_set_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Set, bytes length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Set, bytes length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
        t "Set, bytes length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2

# Now the rate graph.
set ylabel "Time per Item (µs)"

set terminal svg size 700,400           # choose the file format
set output "images/cpp_unordered_set_string_to_py_set_multiple_std_string_rate.svg"   # choose the output device

plot "dat/test_unordered_set_string_to_py_set_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 16" with candlesticks whiskerbars 0.5 linetype 2,\
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 2, \
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 128" with candlesticks whiskerbars 0.5 linetype 4,\
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 4, \
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 1024" with candlesticks whiskerbars 0.5 linetype 7,\
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 7

set terminal png size 700,400           # choose the file format
set output "images/cpp_unordered_set_string_to_py_set_multiple_std_string_rate.png"   # choose the output device

plot "dat/test_unordered_set_string_to_py_set_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 16" with candlesticks whiskerbars 0.5 linetype 2,\
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 2, \
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 128" with candlesticks whiskerbars 0.5 linetype 4,\
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 4, \
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 1024" with candlesticks whiskerbars 0.5 linetype 7,\
    "dat/test_unordered_set_string_to_py_set_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 7

reset
