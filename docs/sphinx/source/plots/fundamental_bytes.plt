set grid

set logscale x
set xlabel "Length of Bytes"
#set xrange[1:1e5]

set logscale y
set ylabel "Time per String (µs)"

set pointsize 1

set datafile separator whitespace

# Some rate lines
latency = 0.025e-6
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
# 10,000,000,000 items per second
rate_10_000_000_000(x) = latency + x / 1e10
# 100,000,000,000 items per second
rate_100_000_000_000(x) = latency + x / 1e11
# 1,000,000,000,000 items per second
rate_1_000_000_000_000(x) = latency + x / 1e12

set boxwidth 0.2 relative

set key top left
set key font ",9"

# First C++ bytes to Python 
set title "Converting a C++ vector<char> to Python bytes."

set terminal png size 700,400           # choose the file format
set output "images/fundamental_cpp_vector_char_to_py_bytes.png"   # choose the output device

plot "dat/fundamental_cpp_vector_char_to_py_bytes.dat" \
     using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python str 8 bit -> C++" with candlesticks whiskerbars 0.5 linewidth 2,\
    "dat/fundamental_cpp_vector_char_to_py_bytes.dat" using 3:(1e6 * $7 * $4 / $9) \
        t "Minimum Python str 8 bit -> C++" with lines linewidth 2, \
    "dat/fundamental_cpp_vector_char_to_py_bytes.dat" using 3:(rate_10_000_000_000($3) * 1e6) \
        t sprintf("Guide: %.3f µs + 10 GB/s", latency*1e6) with lines smooth bezier dashtype 3 lw 2, \
    "dat/fundamental_cpp_vector_char_to_py_bytes.dat" using 3:(rate_100_000_000_000($3) * 1e6) \
        t sprintf("Guide: %.3f µs + 100 GB/s", latency*1e6) with lines smooth bezier dashtype 3 lw 2

# Python bytes to C++

latency = 0.1e-6

set title "Converting Python bytes to a C++ vector<char>."

set terminal png size 700,400           # choose the file format
set output "images/fundamental_py_bytes_to_cpp_vector_char_multiple.png"   # choose the output device

plot "dat/fundamental_py_bytes_to_cpp_vector_char_multiple.dat" \
     using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python str 8 bit -> C++" with candlesticks whiskerbars 0.5 linewidth 2,\
    "dat/fundamental_py_bytes_to_cpp_vector_char_multiple.dat" using 3:(1e6 * $7 * $4 / $9) \
        t "Minimum Python str 8 bit -> C++" with lines linewidth 2, \
    "dat/fundamental_py_bytes_to_cpp_vector_char_multiple.dat" using 3:(rate_10_000_000_000($3) * 1e6) \
        t sprintf("Guide: %.3f µs + 10 GB/s", latency*1e6) with lines smooth bezier dashtype 3 lw 2, \
    "dat/fundamental_py_bytes_to_cpp_vector_char_multiple.dat" using 3:(rate_100_000_000_000($3) * 1e6) \
        t sprintf("Guide: %.3f µs + 100 GB/s", latency*1e6) with lines smooth bezier dashtype 3 lw 2

reset
