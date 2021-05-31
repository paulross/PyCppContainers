set logscale x
set grid
set title "Time to copy a C++ std::unordered map<string> to a Python dict."
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
set output "test_dict_string.svg"   # choose the output device

#plot "test_dict_string.dat" using 1:(1e6 * $2 / $1) t "String size 8" with linespoints axes x1y1 pt 1 lw 1, \
    "test_dict_string.dat" using 1:(1e6 * $3 / $1) t "String size 16" with linespoints axes x1y1 pt 2 lw 1, \
    "test_dict_string.dat" using 1:(1e6 * $4 / $1) t "String size 32" with linespoints axes x1y1 pt 2 lw 1, \
    "test_dict_string.dat" using 1:(1e6 * $5 / $1) t "String size 64" with linespoints axes x1y1 pt 2 lw 1, \
    "test_dict_string.dat" using 1:(1e6 * $6 / $1) t "String size 128" with linespoints axes x1y1 pt 2 lw 1, \
    "test_dict_string.dat" using 1:(1e6 * $7 / $1) t "String size 256" with linespoints axes x1y1 pt 2 lw 1, \
    "test_dict_string.dat" using 1:(1e6 * $8 / $1) t "String size 512" with linespoints axes x1y1 pt 2 lw 1, \
    "test_dict_string.dat" using 1:(1e6 * $9 / $1) t "String size 1024" with linespoints axes x1y1 pt 2 lw 1, \
    "test_dict_string.dat" using 1:(1e6 * $10 / $1) t "String size 2048" with linespoints axes x1y1 pt 2 lw 1, \
    "test_dict_string.dat" using 1:(1e6 * $11 / $1) t "String size 4096" with linespoints axes x1y1 pt 2 lw 1

plot "test_dict_string.dat" using 1:(1e6 * $2 / $1) t "String size 8" with linespoints axes x1y1 pt 1 lw 1, \
    "test_dict_string.dat" using 1:(1e6 * $5 / $1) t "String size 64" with linespoints axes x1y1 pt 2 lw 1, \
    "test_dict_string.dat" using 1:(1e6 * $8 / $1) t "String size 512" with linespoints axes x1y1 pt 2 lw 1, \
    "test_dict_string.dat" using 1:(1e6 * $11 / $1) t "String size 4096" with linespoints axes x1y1 pt 2 lw 1

reset
