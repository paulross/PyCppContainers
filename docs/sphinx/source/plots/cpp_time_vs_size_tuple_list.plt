set grid
set title "Time to Convert Containers Between Python and C++ for Some Fundamental Types."

set logscale x
set xlabel "Container Length"

set logscale y
set ylabel "Time (µs)"
# set yrange [8:35]
# set ytics
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

set terminal svg size 1400,700           # choose the file format
set output "images/cpp_time_vs_size_tuple_list.svg"   # choose the output device

plot "dat/test_py_list_to_vector_multiple_bool.dat" using 3:($7 * 1e6) t "List Py[bool] -> C++ <bool>" with linespoints, \
    "dat/test_py_list_to_vector_multiple_long.dat" using 3:($7 * 1e6) t "List Py[int] -> C++ <long>" with linespoints, \
    "dat/test_py_list_to_vector_multiple_double.dat" using 3:($7 * 1e6) t "List Py[float] -> C++ <double>" with linespoints, \
    "dat/test_vector_to_py_list_multiple_bool.dat" using 3:($7 * 1e6) t "List C++ <bool> -> Py[bool]" with linespoints, \
    "dat/test_vector_to_py_list_multiple_long.dat" using 3:($7 * 1e6) t "List C++ <long> -> Py[int]" with linespoints, \
    "dat/test_vector_to_py_list_multiple_double.dat" using 3:($7 * 1e6) t "List C++ <float> -> Py[double]" with linespoints, \
    "dat/test_py_tuple_to_vector_multiple_bool.dat" using 3:($7 * 1e6) t "Tuple Py[bool] -> C++ <bool>" with linespoints, \
    "dat/test_py_tuple_to_vector_multiple_long.dat" using 3:($7 * 1e6) t "Tuple Py[int] -> C++ <long>" with linespoints, \
    "dat/test_py_tuple_to_vector_multiple_double.dat" using 3:($7 * 1e6) t "Tuple Py[float] -> C++ <double>" with linespoints, \
    "dat/test_vector_to_py_tuple_multiple_bool.dat" using 3:($7 * 1e6) t "Tuple C++ <bool> -> Py[bool]" with linespoints, \
    "dat/test_vector_to_py_tuple_multiple_long.dat" using 3:($7 * 1e6) t "Tuple C++ <long> -> Py[int]" with linespoints, \
    "dat/test_vector_to_py_tuple_multiple_double.dat" using 3:($7 * 1e6) t "Tuple C++ <float> -> Py[double]" with linespoints, \
    "dat/test_vector_to_py_list_multiple_double.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines lw 2 dashtype 5, \
    "dat/test_vector_to_py_list_multiple_double.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines lw 2 dashtype 5, \
    "dat/test_vector_to_py_list_multiple_double.dat" using 3:(rate_1_000_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1,000m objects/s", latency*1e6) with lines lw 2 dashtype 5

#set terminal png size 1400,700           # choose the file format
#set output "images/cpp_time_vs_size_tuple_list.png"   # choose the output device

reset
