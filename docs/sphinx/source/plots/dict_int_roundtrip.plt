set logscale x
set grid
set title "Time to convert a Python dict [int, int] to a C++ std::unordered_map<long, long> then back to a Python dict."
set xlabel "Dict length"

set logscale y
set ylabel "Time per Item (µs)"
# set yrange [8:35]
set ytics
# set ytics 8,35,3

# set logscale y2
# set y2label "Bytes"
# set y2range [1:1e9]
# set y2tics

set pointsize 1
set datafile separator whitespace

set key right

set terminal svg size 1400,700           # choose the file format
set output "images/dict_int_roundtrip.svg"   # choose the output device

plot "dat/test_new_dict_int_int.dat" using 1:(1e6 * $3 / $1) t "[int, int]" with linespoints

set terminal png size 1400,700           # choose the file format
set output "images/dict_int_roundtrip.png"   # choose the output device

plot "dat/test_new_dict_int_int.dat" using 1:(1e6 * $3 / $1) t "[int, int]" with linespoints

reset
