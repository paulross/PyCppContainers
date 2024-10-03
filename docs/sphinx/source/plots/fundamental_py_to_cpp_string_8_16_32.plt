set grid

set title "Conversion Time of a Single 8/16/32 bit String Python to C++."

set logscale x
set xlabel "Size of String in Characters"

set logscale y
set ylabel "Time per String (µs)"

set pointsize 1

set datafile separator whitespace

# Some rate lines
latency = 0.008e-6
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

set terminal png size 800,400           # choose the file format
set output "images/fundamental_py_to_cpp_string_8_16_32.png"   # choose the output device

plot "dat/fundamental_test_py_str_to_cpp_string_multiple.dat" \
        using 3:(1e6 * ($5 - $6) / $4):(1e6 * $7 / $4):(1e6 * $8 / $4):(1e6 * ($5 + $6) / $4) \
        t "Python str 8 bit -> C++" with candlesticks whiskerbars 0.5 linewidth 2,\
        "dat/fundamental_test_py_str_to_cpp_string_multiple.dat" using 3:($7 * 1e6 / $4) \
         t "Minimum Python str 8 bit -> C++" with lines linewidth 2, \
    "dat/fundamental_test_py_str16_to_cpp_u16string_multiple.dat" \
        using 3:(1e6 * ($5 - $6) / $4):(1e6 * $7 / $4):(1e6 * $8 / $4):(1e6 * ($5 + $6) / $4) \
        t "Python str 16 bit -> C++" with candlesticks whiskerbars 0.5 linewidth 2, \
        "dat/fundamental_test_py_str16_to_cpp_u16string_multiple.dat" using 3:($7 * 1e6 / $4) \
         t "Minimum Python str 16 bit -> C++" with lines linewidth 2, \
    "dat/fundamental_test_py_str32_to_cpp_u32string_multiple.dat" \
        using 3:(1e6 * ($5 - $6) / $4):(1e6 * $7 / $4):(1e6 * $8 / $4):(1e6 * ($5 + $6) / $4) \
        t "Python str 32 bit -> C++" with candlesticks whiskerbars 0.5 linewidth 2, \
        "dat/fundamental_test_py_str32_to_cpp_u32string_multiple.dat" using 3:($7 * 1e6 / $4) \
         t "Minimum Python str 32 bit -> C++" with lines linewidth 2, \
    "dat/fundamental_test_cpp_u32string_to_py_str32_multiple.dat" using 3:(rate_1_000_000_000($3) * 1e6) \
        t sprintf("Guide: %.3f µs + 1 GB/s", latency*1e6) with lines smooth bezier dashtype 3 lw 2, \
    "dat/fundamental_test_cpp_u32string_to_py_str32_multiple.dat" using 3:(rate_10_000_000_000($3) * 1e6) \
        t sprintf("Guide: %.3f µs + 10 GB/s", latency*1e6) with lines smooth bezier dashtype 3 lw 2, \
    "dat/fundamental_test_cpp_u32string_to_py_str32_multiple.dat" using 3:(rate_100_000_000_000($3) * 1e6) \
        t sprintf("Guide: %.3f µs + 100 GB/s", latency*1e6) with lines smooth bezier dashtype 3 lw 2

reset
