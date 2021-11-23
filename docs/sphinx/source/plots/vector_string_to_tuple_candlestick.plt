set logscale x
set grid
set title "Time to copy a C++ std::vector<std::string> to a Python tuple with different string lengths."
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

set terminal svg size 1400,700           # choose the file format
set output "vector_string_to_tuple_candlestick.svg"   # choose the output device

plot "vector_string_to_tuple_candlestick.dat" using 1:(1e6 * $4 / $1):(1e6 * ($2 - $3) / $1):(1e6 * ($2 + $3) / $1):(1e6 * $5 / $1) t "String length 128" with candlesticks whiskerbars 0.5
#plot "vector_string_to_tuple_candlestick.dat" using 1:(1e6 * $2 / $1):(1e6 * $4 / $1):(1e6 * $5 / $1) t "String length 128" with yerrorbars

set terminal png size 1400,700           # choose the file format
set output "vector_string_to_tuple_candlestick.svg.png"   # choose the output device

plot "vector_string_to_tuple_candlestick.dat" using 1:(1e6 * $4 / $1):(1e6 * ($2 - $3) / $1):(1e6 * ($2 + $3) / $1):(1e6 * $5 / $1) t "String length 128" with candlesticks whiskerbars 0.5
#plot "vector_string_to_tuple_candlestick.dat" using 1:(1e6 * $2 / $1):(1e6 * $4 / $1):(1e6 * $5 / $1) t "String length 128" with yerrorbars

reset
