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
set key font ",9"
set boxwidth 0.2 relative

# First the raw time graph:
set title "Copy a Python list of str to a C++ std::vector<std::string> by string lengths."
set ylabel "Time (µs)"

# Python to C++

set terminal svg size 700,400           # choose the file format
set output "images/cpp_py_list_str_vector_string_time.svg"   # choose the output device

plot "dat/test_py_list_str_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python List -> C++, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python List -> C++, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python List -> C++, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python List -> C++, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_list_str_to_vector_string_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_list_str_to_vector_string_multiple_std_string_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

set terminal png size 700,400           # choose the file format
set output "images/cpp_py_list_str_vector_string_time.png"   # choose the output device

plot "dat/test_py_list_str_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python List -> C++, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python List -> C++, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python List -> C++, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python List -> C++, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_list_str_to_vector_string_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_list_str_to_vector_string_multiple_std_string_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

# Python to C++

set terminal svg size 700,400           # choose the file format
set output "images/cpp_vector_string_py_list_str_time.svg"   # choose the output device

set title "Copy a C++ std::vector<std::string> to a Python list of str by string lengths."
set ylabel "Time (µs)"

plot "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

set terminal png size 700,400           # choose the file format
set output "images/cpp_vector_string_py_list_str_time.png"   # choose the output device

plot "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

# Now the rate graph.
set title "Copy a Python list of str to a C++ std::vector<std::string> by string lengths."
set ylabel "Time per Item (µs)"
#set yrange[0.001:1]

set terminal svg size 700,400           # choose the file format
set output "images/cpp_py_list_str_vector_string_rate.svg"   # choose the output device

plot "dat/test_py_list_str_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python List -> C++, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_list_str_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python List -> C++, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_list_str_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python List -> C++, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_list_str_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python List -> C++, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

set terminal png size 700,400           # choose the file format
set output "images/cpp_py_list_str_vector_string_rate.png"   # choose the output device

plot "dat/test_py_list_str_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python List -> C++, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_list_str_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python List -> C++, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_list_str_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python List -> C++, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_list_str_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python List -> C++, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_list_str_to_vector_string_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

set terminal svg size 700,400           # choose the file format
set output "images/cpp_vector_string_py_list_str_rate.svg"   # choose the output device

set title "Copy a C++ std::vector<std::string> to a Python list of str by string lengths."
set ylabel "Time per Item (µs)"
#set yrange[0.01:1]

plot "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
            t "C+ List -> Python, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_list_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "C+ List -> Python, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_list_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "C+ List -> Python, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_list_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "C+ List -> Python, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

set terminal png size 700,400           # choose the file format
set output "images/cpp_vector_string_py_list_str_rate.png"   # choose the output device

plot "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
            t "C+ List -> Python, string length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_list_multiple_std_string_16.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "C+ List -> Python, string length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_list_multiple_std_string_128.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "C+ List -> Python, string length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_string_to_py_list_multiple_std_string_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "C+ List -> Python, string length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_string_to_py_list_multiple_std_string_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

reset
