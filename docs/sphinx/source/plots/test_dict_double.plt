set logscale x
set grid
set title "Time to copy a C++ std::unordered map<double> to and from a Python dict."
set xlabel "Size"

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
set output "test_dict_double.svg"   # choose the output device

plot "test_dict_double.dat" using 1:(1e6 * $2 / $1) t "C++ to Python" with linespoints axes x1y1 pt 1 lw 1, \
    "test_dict_double.dat" using 1:(1e6 * $3 / $1) t "Python to C++" with linespoints axes x1y1 pt 2 lw 1

reset
