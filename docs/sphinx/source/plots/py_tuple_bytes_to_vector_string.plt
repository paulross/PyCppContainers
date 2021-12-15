set title "Time to copy a Python tuple of bytes to a C++ std::vector<std::string> with different string lengths."
set grid

set logscale x
set xlabel "Size of Tuple and Vector"

set logscale y
set ylabel "Time per Item (µs)"
# set yrange [8:35]
# set yrange [0.001:10]
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
set boxwidth 0.2 relative

# First the raw time graph:
set ylabel "Time (µs)"

set terminal svg size 1400,700           # choose the file format
set output "images/py_tuple_bytes_to_vector_string_time.svg"   # choose the output device

plot "dat/py_tuple_bytes_to_vector_string_8.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
    t "String length 8" with candlesticks whiskerbars 0.5 linetype 1,\
    "dat/py_tuple_bytes_to_vector_string_64.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
    t "String length 64" with candlesticks whiskerbars 0.5 linetype 2,\
    "dat/py_tuple_bytes_to_vector_string_512.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
    t "String length 512" with candlesticks whiskerbars 0.5 linetype 4,\
    "dat/py_tuple_bytes_to_vector_string_4096.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
    t "String length 4096" with candlesticks whiskerbars 0.5 linetype 7,\
    "dat/py_tuple_bytes_to_vector_string_8.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2, \
    "dat/py_tuple_bytes_to_vector_string_8.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2, \
    "dat/py_tuple_bytes_to_vector_string_8.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2
#plot "dat/py_tuple_bytes_to_vector_string.dat" using 1:(1e6 * $2 / $1):(1e6 * $4 / $1):(1e6 * $5 / $1) t "String length 128" with yerrorbars

#plot "dat/py_tuple_bytes_to_vector_string.dat" using 1:(1e6 * $2 / $1):(1e6 * $4 / $1):(1e6 * $5 / $1) t "String length 128" with yerrorbars

set terminal png size 1400,700           # choose the file format
set output "images/py_tuple_bytes_to_vector_string_time.svg.png"   # choose the output device

plot "dat/py_tuple_bytes_to_vector_string_8.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
    t "String length 8" with candlesticks whiskerbars 0.5 linetype 1,\
    "dat/py_tuple_bytes_to_vector_string_64.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
    t "String length 64" with candlesticks whiskerbars 0.5 linetype 2,\
    "dat/py_tuple_bytes_to_vector_string_512.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
    t "String length 512" with candlesticks whiskerbars 0.5 linetype 4,\
    "dat/py_tuple_bytes_to_vector_string_4096.dat" using 3:(1e6 * ($5 - $6)):(1e6 * $7):(1e6 * $8):(1e6 * ($5 + $6)) \
    t "String length 4096" with candlesticks whiskerbars 0.5 linetype 7,\
    "dat/py_tuple_bytes_to_vector_string_8.dat" using 3:(rate_1_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 1m objects/s", latency*1e6) with lines dashtype 2, \
    "dat/py_tuple_bytes_to_vector_string_8.dat" using 3:(rate_10_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 10m objects/s", latency*1e6) with lines dashtype 2, \
    "dat/py_tuple_bytes_to_vector_string_8.dat" using 3:(rate_100_000_000($3) * 1e6) t sprintf("Guide: %.3f µs + 100m objects/s", latency*1e6) with lines dashtype 2
#plot "dat/py_tuple_bytes_to_vector_string.dat" using 1:(1e6 * $2 / $1):(1e6 * $4 / $1):(1e6 * $5 / $1) t "String length 128" with yerrorbars

# Now the rate graph.
set ylabel "Time per Item (µs)"
set yrange [0.001:10]

set terminal svg size 1400,700           # choose the file format
set output "images/py_tuple_bytes_to_vector_string_rate.svg"   # choose the output device

plot "dat/py_tuple_bytes_to_vector_string_8.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 8" with candlesticks whiskerbars 0.5 linetype 1,\
    "dat/py_tuple_bytes_to_vector_string_8.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 1, \
    "dat/py_tuple_bytes_to_vector_string_64.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 64" with candlesticks whiskerbars 0.5 linetype 2,\
    "dat/py_tuple_bytes_to_vector_string_64.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 2, \
    "dat/py_tuple_bytes_to_vector_string_512.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 512" with candlesticks whiskerbars 0.5 linetype 4,\
    "dat/py_tuple_bytes_to_vector_string_512.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 4, \
    "dat/py_tuple_bytes_to_vector_string_4096.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 4096" with candlesticks whiskerbars 0.5 linetype 7,\
    "dat/py_tuple_bytes_to_vector_string_4096.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 7
#plot "dat/py_tuple_bytes_to_vector_string.dat" using 1:(1e6 * $2 / $1):(1e6 * $4 / $1):(1e6 * $5 / $1) t "String length 128" with yerrorbars

set terminal png size 1400,700           # choose the file format
set output "images/py_tuple_bytes_to_vector_string_rate.svg.png"   # choose the output device

plot "dat/py_tuple_bytes_to_vector_string_8.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 8" with candlesticks whiskerbars 0.5 linetype 1,\
    "dat/py_tuple_bytes_to_vector_string_8.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 1, \
    "dat/py_tuple_bytes_to_vector_string_64.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 64" with candlesticks whiskerbars 0.5 linetype 2,\
    "dat/py_tuple_bytes_to_vector_string_64.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 2, \
    "dat/py_tuple_bytes_to_vector_string_512.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 512" with candlesticks whiskerbars 0.5 linetype 4,\
    "dat/py_tuple_bytes_to_vector_string_512.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 4, \
    "dat/py_tuple_bytes_to_vector_string_4096.dat" using 3:(1e6 * ($5 - $6) / $3):(1e6 * $7 / $3):(1e6 * $8 / $3):(1e6 * ($5 + $6) / $3) \
    t "String length 4096" with candlesticks whiskerbars 0.5 linetype 7,\
    "dat/py_tuple_bytes_to_vector_string_4096.dat" using 3:(1e6 * $7 / $3) t "" with lines linetype 7
#plot "dat/py_tuple_bytes_to_vector_string.dat" using 1:(1e6 * $2 / $1):(1e6 * $4 / $1):(1e6 * $5 / $1) t "String length 128" with yerrorbars

reset
