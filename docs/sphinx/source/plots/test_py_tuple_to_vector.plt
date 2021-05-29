set logscale x
set grid
set title "Time to copy a Python tuple to a C++ std::vector."
set xlabel "Vector Size"

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

set terminal svg size 1000,700           # choose the file format
set output "test_py_tuple_to_vector.svg"   # choose the output device

plot "test_vector_to_py_tuple.dat" using 1:(1e6 * $5 / $1) t "Python tuple to C++ vector<bool>" with linespoints axes x1y1 pt 1 lw 1, \
    "test_vector_to_py_tuple.dat" using 1:(1e6 * $6 / $1) t "Python tuple to C++ vector<long>" with linespoints axes x1y1 pt 2 lw 1, \
    "test_vector_to_py_tuple.dat" using 1:(1e6 * $7 / $1) t "Python tuple to C++ vector<double>" with linespoints axes x1y1 pt 3 lw 1

reset
