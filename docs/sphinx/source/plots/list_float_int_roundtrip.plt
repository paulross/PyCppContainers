set logscale x
set grid
set title "Time to convert a Python List to a C++ std::vector<T> then back to a Python list."
set xlabel "List length"

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
set output "images/list_float_int_roundtrip.svg"   # choose the output device

#plot "dat/test_new_list_float.dat" using 1:(1e6 * $4 / $1):(1e6 * ($2 - $3) / $1):(1e6 * ($2 + $3) / $1):(1e6 * $5 / $1) t "Floats" with candlesticks whiskerbars 0.5
#plot "dat/test_new_list_float.dat" using 1:(1e6 * $2 / $1):(1e6 * $4 / $1):(1e6 * $5 / $1) t "String length 128" with yerrorbars

plot "dat/test_new_list_float.dat" using 1:(1e6 * $3 / $1) t "Floats" with linespoints, \
    "dat/test_new_list_int.dat" using 1:(1e6 * $3 / $1) t "Ints" with linespoints


set terminal png size 1400,700           # choose the file format
set output "images/list_float_int_roundtrip.png"   # choose the output device

#plot "dat/test_new_list_float.dat" using 1:(1e6 * $4 / $1):(1e6 * ($2 - $3) / $1):(1e6 * ($2 + $3) / $1):(1e6 * $5 / $1) t "Floats" with candlesticks whiskerbars 0.5
#plot "dat/test_new_list_float.dat" using 1:(1e6 * $2 / $1):(1e6 * $4 / $1):(1e6 * $5 / $1) t "String length 128" with yerrorbars

plot "dat/test_new_list_float.dat" using 1:(1e6 * $3 / $1) t "Floats" with linespoints, \
    "dat/test_new_list_int.dat" using 1:(1e6 * $3 / $1) t "Ints" with linespoints

reset
