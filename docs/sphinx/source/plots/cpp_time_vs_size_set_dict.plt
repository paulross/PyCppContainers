set grid
set title "Time to Convert Sets and Dictionaries Between Python and C++ for Some Fundamental Types."

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

set terminal svg size 1400,700           # choose the file format
set output "images/cpp_vs_size_set_dict_time.svg"   # choose the output device

set key left
set ylabel "Time (µs)"

plot "dat/test_py_set_to_unordered_set_multiple_long.dat" using 3:($7 * 1e6) t "Set Py[int] -> C++ <long>" with points, \
    "dat/test_py_set_to_unordered_set_multiple_double.dat" using 3:($7 * 1e6) t "Set Py[float] -> C++ <double>" with points, \
    "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:($7 * 1e6) t "Set C++ <long> -> Py[int]" with points, \
    "dat/test_unordered_set_to_py_set_multiple_double.dat" using 3:($7 * 1e6) t "Set C++ <float> -> Py[double]" with points, \
    "dat/test_py_dict_to_cpp_std_unordered_map_multiple_long_long.dat" using 3:($7 * 1e6) t "Dict Py[int, int] -> C++ <long, long>" with points, \
    "dat/test_py_dict_to_cpp_std_unordered_map_multiple_double_double.dat" using 3:($7 * 1e6) t "Dict Py[float, float] -> C++ <double, double>" with points, \
    "dat/test_cpp_std_unordered_map_to_py_dict_multiple_long_long.dat" using 3:($7 * 1e6) t "Dict C++ <long, long> -> Py[int,  int]" with points, \
    "dat/test_cpp_std_unordered_map_to_py_dict_multiple_double_double.dat" using 3:($7 * 1e6) t "Dict C++ <float, float> -> Py[double, double]" with points, \
    "dat/test_vector_to_py_list_multiple_double.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines lw 2 dashtype 5, \
    "dat/test_vector_to_py_list_multiple_double.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines lw 2 dashtype 5

set output "images/cpp_vs_size_set_dict_rate.svg"   # choose the output device
set key top center
set ylabel "Time per item (µs)"

plot "dat/test_py_set_to_unordered_set_multiple_long.dat" using 3:($7 * 1e6 / $3) t "Set Py[int] -> C++ <long>" with linespoints, \
    "dat/test_py_set_to_unordered_set_multiple_double.dat" using 3:($7 * 1e6 / $3) t "Set Py[float] -> C++ <double>" with linespoints, \
    "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:($7 * 1e6 / $3) t "Set C++ <long> -> Py[int]" with linespoints, \
    "dat/test_unordered_set_to_py_set_multiple_double.dat" using 3:($7 * 1e6 / $3) t "Set C++ <float> -> Py[double]" with linespoints, \
    "dat/test_py_dict_to_cpp_std_unordered_map_multiple_long_long.dat" using 3:($7 * 1e6 / $3) t "Dict Py[int, int] -> C++ <long, long>" with linespoints, \
    "dat/test_py_dict_to_cpp_std_unordered_map_multiple_double_double.dat" using 3:($7 * 1e6 / $3) t "Dict Py[float, float] -> C++ <double, double>" with linespoints, \
    "dat/test_cpp_std_unordered_map_to_py_dict_multiple_long_long.dat" using 3:($7 * 1e6 / $3) t "Dict C++ <long, long> -> Py[int,  int]" with linespoints, \
    "dat/test_cpp_std_unordered_map_to_py_dict_multiple_double_double.dat" using 3:($7 * 1e6 / $3) t "Dict C++ <float, float> -> Py[double, double]" with linespoints

set terminal png size 1400,700           # choose the file format
set output "images/cpp_vs_size_set_dict_time.png"   # choose the output device

set key left
set ylabel "Time (µs)"

plot "dat/test_py_set_to_unordered_set_multiple_long.dat" using 3:($7 * 1e6) t "Set Py[int] -> C++ <long>" with points, \
    "dat/test_py_set_to_unordered_set_multiple_double.dat" using 3:($7 * 1e6) t "Set Py[float] -> C++ <double>" with points, \
    "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:($7 * 1e6) t "Set C++ <long> -> Py[int]" with points, \
    "dat/test_unordered_set_to_py_set_multiple_double.dat" using 3:($7 * 1e6) t "Set C++ <float> -> Py[double]" with points, \
    "dat/test_py_dict_to_cpp_std_unordered_map_multiple_long_long.dat" using 3:($7 * 1e6) t "Dict Py[int, int] -> C++ <long, long>" with points, \
    "dat/test_py_dict_to_cpp_std_unordered_map_multiple_double_double.dat" using 3:($7 * 1e6) t "Dict Py[float, float] -> C++ <double, double>" with points, \
    "dat/test_cpp_std_unordered_map_to_py_dict_multiple_long_long.dat" using 3:($7 * 1e6) t "Dict C++ <long, long> -> Py[int,  int]" with points, \
    "dat/test_cpp_std_unordered_map_to_py_dict_multiple_double_double.dat" using 3:($7 * 1e6) t "Dict C++ <float, float> -> Py[double, double]" with points, \
    "dat/test_vector_to_py_list_multiple_double.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines lw 2 dashtype 5, \
    "dat/test_vector_to_py_list_multiple_double.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines lw 2 dashtype 5

set output "images/cpp_vs_size_set_dict_rate.png"   # choose the output device
set key top center
set ylabel "Time per item (µs)"

plot "dat/test_py_set_to_unordered_set_multiple_long.dat" using 3:($7 * 1e6 / $3) t "Set Py[int] -> C++ <long>" with linespoints, \
    "dat/test_py_set_to_unordered_set_multiple_double.dat" using 3:($7 * 1e6 / $3) t "Set Py[float] -> C++ <double>" with linespoints, \
    "dat/test_unordered_set_to_py_set_multiple_long.dat" using 3:($7 * 1e6 / $3) t "Set C++ <long> -> Py[int]" with linespoints, \
    "dat/test_unordered_set_to_py_set_multiple_double.dat" using 3:($7 * 1e6 / $3) t "Set C++ <float> -> Py[double]" with linespoints, \
    "dat/test_py_dict_to_cpp_std_unordered_map_multiple_long_long.dat" using 3:($7 * 1e6 / $3) t "Dict Py[int, int] -> C++ <long, long>" with linespoints, \
    "dat/test_py_dict_to_cpp_std_unordered_map_multiple_double_double.dat" using 3:($7 * 1e6 / $3) t "Dict Py[float, float] -> C++ <double, double>" with linespoints, \
    "dat/test_cpp_std_unordered_map_to_py_dict_multiple_long_long.dat" using 3:($7 * 1e6 / $3) t "Dict C++ <long, long> -> Py[int,  int]" with linespoints, \
    "dat/test_cpp_std_unordered_map_to_py_dict_multiple_double_double.dat" using 3:($7 * 1e6 / $3) t "Dict C++ <float, float> -> Py[double, double]" with linespoints

reset
