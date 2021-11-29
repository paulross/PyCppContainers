set title "Time to copy a Python tuple of bytes to a C++ std::vector<std::string> with different string lengths."
set grid

set logscale x
set xlabel "Size off tuple and vector"

set logscale y
set ylabel "Time per Item (µs)"
# set yrange [8:35]
set yrange [0.001:10]
# set ytics 8,35,3

# set logscale y2
# set y2label "Bytes"
# set y2range [1:1e9]
# set y2tics

set pointsize 1
set datafile separator whitespace

set key left

set terminal svg size 1400,700           # choose the file format
set output "vector_string_to_py_tuple.svg"   # choose the output device

set boxwidth 0.2 relative

plot "vector_string_to_py_tuple_8.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 8" with candlesticks whiskerbars 0.5 linetype 1,\
    "vector_string_to_py_tuple_8.dat" using 3:(1e6 * $5 / $3) t "" with linespoints linetype 1, \
    "vector_string_to_py_tuple_64.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 64" with candlesticks whiskerbars 0.5 linetype 2,\
    "vector_string_to_py_tuple_64.dat" using 3:(1e6 * $5 / $3) t "" with linespoints linetype 2, \
    "vector_string_to_py_tuple_512.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 512" with candlesticks whiskerbars 0.5 linetype 4,\
    "vector_string_to_py_tuple_512.dat" using 3:(1e6 * $5 / $3) t "" with linespoints linetype 4, \
    "vector_string_to_py_tuple_4096.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 4096" with candlesticks whiskerbars 0.5 linetype 7,\
    "vector_string_to_py_tuple_4096.dat" using 3:(1e6 * $5 / $3) t "" with linespoints linetype 7
#plot "vector_string_to_py_tuple.dat" using 1:(1e6 * $2 / $1):(1e6 * $4 / $1):(1e6 * $5 / $1) t "String length 128" with yerrorbars

set terminal png size 1400,700           # choose the file format
set output "vector_string_to_py_tuple.svg.png"   # choose the output device

plot "vector_string_to_py_tuple_8.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 8" with candlesticks whiskerbars 0.5 linetype 1,\
    "vector_string_to_py_tuple_8.dat" using 3:(1e6 * $5 / $3) t "" with linespoints linetype 1, \
    "vector_string_to_py_tuple_64.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 64" with candlesticks whiskerbars 0.5 linetype 2,\
    "vector_string_to_py_tuple_64.dat" using 3:(1e6 * $5 / $3) t "" with linespoints linetype 2, \
    "vector_string_to_py_tuple_512.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 512" with candlesticks whiskerbars 0.5 linetype 4,\
    "vector_string_to_py_tuple_512.dat" using 3:(1e6 * $5 / $3) t "" with linespoints linetype 4, \
    "vector_string_to_py_tuple_4096.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 4096" with candlesticks whiskerbars 0.5 linetype 7,\
    "vector_string_to_py_tuple_4096.dat" using 3:(1e6 * $5 / $3) t "" with linespoints linetype 7
#plot "vector_string_to_py_tuple.dat" using 1:(1e6 * $2 / $1):(1e6 * $4 / $1):(1e6 * $5 / $1) t "String length 128" with yerrorbars

reset
