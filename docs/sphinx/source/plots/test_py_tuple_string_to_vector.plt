set logscale x
set grid
set title "Time to copy a Python tuple with different string lengths to a C++ std::vector<std::string>."
set xlabel "Tuple Size"

set logscale y
set ylabel "Time per Item (µs)"
# set yrange [8:35]
# set ytics 8,35,3

# set logscale y2
# set y2label "Bytes"
# set y2range [1:1e9]
# set y2tics

set pointsize 1
set datafile separator whitespace
# Curve fit
#cost(x) = a + (b / (x/1024))
#fit cost(x) "perf_size_of.dat" using 1:2 via a,b

set key left

set terminal svg size 1400,700           # choose the file format
set output "test_py_tuple_string_to_vector.svg"   # choose the output device

plot "test_py_tuple_string_to_vector.dat" using 1:(1e6 * $2 / $1) t "String length 8" with linespoints axes x1y1 pt 1 lw 1, \
    "test_py_tuple_string_to_vector.dat" using 1:(1e6 * $5 / $1) t "String length 64" with linespoints axes x1y1 pt 5 lw 1, \
    "test_py_tuple_string_to_vector.dat" using 1:(1e6 * $8 / $1) t "String length 512" with linespoints axes x1y1 pt 7 lw 1, \
    "test_py_tuple_string_to_vector.dat" using 1:(1e6 * $11 / $1) t "String length 4096" with linespoints axes x1y1 pt 2 lw 1
    
set terminal png size 1400,700           # choose the file format
set output "test_py_tuple_string_to_vector.svg.png"   # choose the output device

plot "test_py_tuple_string_to_vector.dat" using 1:(1e6 * $2 / $1) t "String length 8" with linespoints axes x1y1 pt 1 lw 1, \
    "test_py_tuple_string_to_vector.dat" using 1:(1e6 * $5 / $1) t "String length 64" with linespoints axes x1y1 pt 5 lw 1, \
    "test_py_tuple_string_to_vector.dat" using 1:(1e6 * $8 / $1) t "String length 512" with linespoints axes x1y1 pt 7 lw 1, \
    "test_py_tuple_string_to_vector.dat" using 1:(1e6 * $11 / $1) t "String length 4096" with linespoints axes x1y1 pt 2 lw 1

reset
