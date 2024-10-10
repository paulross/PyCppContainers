set grid

set logscale x
set xlabel "Size of tuple"

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
set title "Copy a Python tuple of bytes C++ std::vector<std::vector<char>>by bytes lengths."
set ylabel "Time (µs)"

set terminal svg size 700,400           # choose the file format
set output "images/cpp_py_tuple_bytes_vector_vector_char_time.svg"   # choose the output device

plot "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_2.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python Tuple -> C++, vector<char> length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_16.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python Tuple -> C++, vector<char> length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_128.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python Tuple -> C++, vector<char> length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python Tuple -> C++, vector<char> length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

set terminal png size 700,400           # choose the file format
set output "images/cpp_py_tuple_bytes_vector_vector_char_time.png"   # choose the output device

plot "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_2.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python Tuple -> C++, vector<char> length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_16.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python Tuple -> C++, vector<char> length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_128.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python Tuple -> C++, vector<char> length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python Tuple -> C++, vector<char> length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

set terminal svg size 700,400           # choose the file format
set output "images/cpp_vector_vector_char_py_tuple_bytes_time.svg"   # choose the output device

set title "Copy a C++ std::vector<std::vector<char>> to a Python tuple of bytesby bytes lengths."
set ylabel "Time (µs)"

plot "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_2.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python tuple, bytes length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_16.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python tuple, bytes length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_128.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python tuple, bytes length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python tuple, bytes length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

set terminal png size 700,400           # choose the file format
set output "images/cpp_vector_vector_char_py_tuple_bytes_time.png"   # choose the output device

plot "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_2.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python tuple, bytes length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_16.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python tuple, bytes length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_128.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python tuple, bytes length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "C++ List -> Python tuple, bytes length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_2.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_2.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2 lw 2, \
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_2.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2 lw 2

# Now the rate graph.
set title "Copy a Python tuple of bytes to a C++ std::vector<std::vector<char>>by bytes lengths."
set ylabel "Time per Item (µs)"

set terminal svg size 700,400           # choose the file format
set output "images/cpp_py_tuple_bytes_vector_vector_char_rate.svg"   # choose the output device

plot "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_2.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python Tuple -> C++, vector<char> length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_16.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python Tuple -> C++, vector<char> length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_128.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python Tuple -> C++, vector<char> length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python Tuple -> C++, vector<char> length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

set terminal png size 700,400           # choose the file format
set output "images/cpp_py_tuple_bytes_vector_vector_char_rate.png"   # choose the output device

plot "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_2.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python Tuple -> C++, vector<char> length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_16.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python Tuple -> C++, vector<char> length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_128.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python Tuple -> C++, vector<char> length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "Python Tuple -> C++, vector<char> length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_py_tuple_bytes_to_vector_vector_char_multiple_std_vector_char_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines


set terminal svg size 700,400           # choose the file format
set output "images/cpp_vector_vector_char_py_tuple_bytes_rate.svg"   # choose the output device

set title "Copy a C++ std::vector<std::vector<char>> to a Python tuple of bytesby bytes lengths."
set ylabel "Time per Item (µs)"

plot "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_2.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
            t "C+ List -> Python, bytes length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_16.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "C+ List -> Python, bytes length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_128.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "C+ List -> Python, bytes length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "C+ List -> Python, bytes length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

set terminal png size 700,400           # choose the file format
set output "images/cpp_vector_vector_char_py_tuple_bytes_rate.png"   # choose the output device

plot "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_2.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
            t "C+ List -> Python, bytes length 2" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_2.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_16.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "C+ List -> Python, bytes length 16" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_16.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_128.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "C+ List -> Python, bytes length 128" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_128.dat" using 3:(1e6 * $7 / $3) t "" with lines, \
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_1024.dat" using 3:(1e6 * ($5 - $6) * $4 / ($9 * $3)):(1e6 * $7 * $4 / ($9 * $3)):(1e6 * $8 * $4 / ($9 * $3)):(1e6 * ($5 + $6) * $4 / ($9 * $3)) \
        t "C+ List -> Python, bytes length 1024" with candlesticks whiskerbars 0.5,\
    "dat/test_vector_vector_char_to_py_tuple_multiple_std_vector_char_1024.dat" using 3:(1e6 * $7 / $3) t "" with lines

reset
