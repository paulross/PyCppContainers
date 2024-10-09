set grid

set title "Conversion of a Single 8/16/32 bit String C++ to Python."

set logscale x
set xlabel "Size of String"

set logscale y
set ylabel "Time per String (µs)"

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
# 10,000,000,000 items per second
rate_10_000_000_000(x) = latency + x / 1e10

set boxwidth 0.2 relative

set key top left
set key font ",9"

set terminal png size 700,400           # choose the file format

# All 8/16/32 bit strings.
set output "images/fundamental_string_cpp_to_py_8_16_32.png"   # choose the output device

plot \
    "dat/fundamental_test_cpp_string_to_py_str_multiple.dat" \
        using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python str 8 bit -> C++" with candlesticks whiskerbars 0.5 linewidth 2,\
    "dat/fundamental_test_cpp_string_to_py_str_multiple.dat" using 3:(1e6 * $7 * $4 / $9) \
         t "Minimum Python str 8 bit -> C++" with lines linewidth 2, \
    "dat/fundamental_test_cpp_u16string_to_py_str16_multiple.dat" \
        using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python str 16 bit -> C++" with candlesticks whiskerbars 0.5 linewidth 2,\
    "dat/fundamental_test_cpp_u16string_to_py_str16_multiple.dat" using 3:(1e6 * $7 * $4 / $9) \
        t "Minimum Python str 16 bit -> C++" with lines, \
    "dat/fundamental_test_cpp_u32string_to_py_str32_multiple.dat" \
        using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python str 32 bit -> C++" with candlesticks whiskerbars 0.5 linewidth 2, \
    "dat/fundamental_test_cpp_u32string_to_py_str32_multiple.dat" using 3:(1e6 * $7 * $4 / $9) \
        t "Minimum Python str 32 bit -> C++" with lines linewidth 2, \
    "dat/fundamental_test_cpp_string_to_py_str_multiple.dat" using 3:(rate_100_000_000($3) * 1e6) \
        t sprintf("Guide: %.3f µs + 100 MB/s", latency*1e6) with lines smooth bezier dashtype 3 lw 2, \
    "dat/fundamental_test_cpp_string_to_py_str_multiple.dat" using 3:(rate_10_000_000_000($3) * 1e6) \
        t sprintf("Guide: %.3f µs + 10 GB/s", latency*1e6) with lines smooth bezier dashtype 3 lw 2

# 8 bit strings.
set title "Conversion of a Single 8 bit String C++ to Python."
latency = 0.08e-6

set output "images/fundamental_string_cpp_to_py_8.png"   # choose the output device

plot \
    "dat/fundamental_test_cpp_string_to_py_str_multiple.dat" \
        using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python str 8 bit -> C++" with candlesticks whiskerbars 0.5 linewidth 2,\
    "dat/fundamental_test_cpp_string_to_py_str_multiple.dat" using 3:(1e6 * $7 * $4 / $9) \
         t "Minimum Python str 8 bit -> C++" with lines linewidth 2, \
    "dat/fundamental_test_cpp_string_to_py_str_multiple.dat" using 3:(rate_1_000_000_000($3) * 1e6) \
        t sprintf("Guide: %.3f µs + 1 GB/s", latency*1e6) with lines smooth bezier dashtype 3 lw 2, \
    "dat/fundamental_test_cpp_string_to_py_str_multiple.dat" using 3:(rate_10_000_000_000($3) * 1e6) \
        t sprintf("Guide: %.3f µs + 10 GB/s", latency*1e6) with lines smooth bezier dashtype 3 lw 2

# 16 bit strings.
set title "Conversion of a Single 16 bit String C++ to Python."
latency = 0.04e-6

set output "images/fundamental_string_cpp_to_py_16.png"   # choose the output device

plot \
    "dat/fundamental_test_cpp_u16string_to_py_str16_multiple.dat" \
        using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python str 16 bit -> C++" with candlesticks whiskerbars 0.5 linewidth 2,\
    "dat/fundamental_test_cpp_u16string_to_py_str16_multiple.dat" using 3:(1e6 * $7 * $4 / $9) \
        t "Minimum Python str 16 bit -> C++" with lines, \
    "dat/fundamental_test_cpp_string_to_py_str_multiple.dat" using 3:(rate_100_000_000($3) * 1e6) \
        t sprintf("Guide: %.3f µs + 100 MB/s", latency*1e6) with lines smooth bezier dashtype 3 lw 2

# 32 bit strings.
set title "Conversion of a Single 32 bit String C++ to Python."
latency = 0.02e-6

set output "images/fundamental_string_cpp_to_py_32.png"   # choose the output device

plot \
    "dat/fundamental_test_cpp_u32string_to_py_str32_multiple.dat" \
        using 3:(1e6 * ($5 - $6) * $4 / $9):(1e6 * $7 * $4 / $9):(1e6 * $8 * $4 / $9):(1e6 * ($5 + $6) * $4 / $9) \
        t "Python str 32 bit -> C++" with candlesticks whiskerbars 0.5 linewidth 2,\
    "dat/fundamental_test_cpp_u32string_to_py_str32_multiple.dat" using 3:(1e6 * $7 * $4 / $9) \
        t "Minimum Python str 32 bit -> C++" with lines, \
    "dat/fundamental_test_cpp_string_to_py_str_multiple.dat" using 3:(rate_100_000_000($3) * 1e6) \
        t sprintf("Guide: %.3f µs + 100 MB/s", latency*1e6) with lines smooth bezier dashtype 3 lw 2

reset
