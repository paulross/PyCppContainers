set logscale x
set grid
set title "Time to convert a Python Set to a C++ std::unordered_set then back to a Python Set."
set xlabel "List length"

set logscale y
# set yrange [8:35]
set ytics
# set ytics 8,35,3

# set logscale y2
# set y2label "Bytes"
# set y2range [1:1e9]
# set y2tics

set pointsize 1
set datafile separator whitespace

set key left
set boxwidth 0.2 relative

# Some rate lines
latency = 0.8e-6
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

# Time plots
set ylabel "Time (µs)"
set terminal svg size 700,400           # choose the file format
set output "images/roundtrip_set_ints_and_floats_time.svg"   # choose the output device

plot "dat/roundtrip_set_int.dat" using 1:(1e6 * ($4 - $6)):(1e6 * $3):(1e6 * $7):(1e6 * ($4 + $6)) \
        t "Set [int] <-> C++ <long>" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_set_float.dat" using 1:(1e6 * ($4 - $6)):(1e6 * $3):(1e6 * $7):(1e6 * ($4 + $6)) \
        t "Set [float] <-> C++ <double>" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_set_complex.dat" using 1:(1e6 * ($4 - $6)):(1e6 * $3):(1e6 * $7):(1e6 * ($4 + $6)) \
        t "Set [complex] <-> C++ <std::complex<double>>" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_set_int.dat" using 1:(rate_1_000_000($1) * 1e6) t sprintf("Guide: %.1f µs + 1m objects/s", latency*1e6) with lines lw 2 dashtype 5, \
    "dat/roundtrip_set_int.dat" using 1:(rate_10_000_000($1) * 1e6) t sprintf("Guide: %.1f µs + 10m objects/s", latency*1e6) with lines lw 2 dashtype 5

set terminal png size 700,400           # choose the file format
set output "images/roundtrip_set_ints_and_floats_time.png"   # choose the output device

plot "dat/roundtrip_set_int.dat" using 1:(1e6 * ($4 - $6)):(1e6 * $3):(1e6 * $7):(1e6 * ($4 + $6)) \
        t "Set [int] <-> C++ <long>" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_set_float.dat" using 1:(1e6 * ($4 - $6)):(1e6 * $3):(1e6 * $7):(1e6 * ($4 + $6)) \
        t "Set [float] <-> C++ <double>" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_set_complex.dat" using 1:(1e6 * ($4 - $6)):(1e6 * $3):(1e6 * $7):(1e6 * ($4 + $6)) \
        t "Set [complex] <-> C++ <std::complex<double>>" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_set_int.dat" using 1:(rate_1_000_000($1) * 1e6) t sprintf("Guide: %.1f µs + 1m objects/s", latency*1e6) with lines lw 2 dashtype 5, \
    "dat/roundtrip_set_int.dat" using 1:(rate_10_000_000($1) * 1e6) t sprintf("Guide: %.1f µs + 10m objects/s", latency*1e6) with lines lw 2 dashtype 5

# Rate plots
set ylabel "Time per Item (µs)"
set yrange [0.1:1]

set terminal svg size 700,400           # choose the file format
set output "images/roundtrip_set_ints_and_floats_rate.svg"   # choose the output device

plot "dat/roundtrip_set_int.dat" using 1:(1e6 * ($4 - $6) / $1):(1e6 * $3 / $1):(1e6 * $7 / $1):(1e6 * ($4 + $6) / $1) \
        t "Set [int] <-> C++ <long>" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_set_int.dat" using 1:(1e6 * $3 / $1) t "Minimum Set [int] <-> C++ <long>" with lines, \
    "dat/roundtrip_set_float.dat" using 1:(1e6 * ($4 - $6) / $1):(1e6 * $3 / $1):(1e6 * $7 / $1):(1e6 * ($4 + $6) / $1) \
        t "Set [float] <-> C++ <double>" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_set_float.dat" using 1:(1e6 * $3 / $1) t "Minimum Set [float] <-> C++ <double>" with lines, \
    "dat/roundtrip_set_complex.dat" using 1:(1e6 * ($4 - $6) / $1):(1e6 * $3 / $1):(1e6 * $7 / $1):(1e6 * ($4 + $6) / $1) \
        t "Set [complex] <-> C++ <std::complex<double>>" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_set_complex.dat" using 1:(1e6 * $3 / $1) t "Minimum Set [complex] <-> C++ <std::complex<double>>" with lines

set terminal png size 700,400           # choose the file format
set output "images/roundtrip_set_ints_and_floats_rate.png"   # choose the output device

plot "dat/roundtrip_set_int.dat" using 1:(1e6 * ($4 - $6) / $1):(1e6 * $3 / $1):(1e6 * $7 / $1):(1e6 * ($4 + $6) / $1) \
        t "Set [int] <-> C++ <long>" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_set_int.dat" using 1:(1e6 * $3 / $1) t "Minimum Set [int] <-> C++ <long>" with lines, \
    "dat/roundtrip_set_float.dat" using 1:(1e6 * ($4 - $6) / $1):(1e6 * $3 / $1):(1e6 * $7 / $1):(1e6 * ($4 + $6) / $1) \
        t "Set [float] <-> C++ <double>" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_set_float.dat" using 1:(1e6 * $3 / $1) t "Minimum Set [float] <-> C++ <double>" with lines, \
    "dat/roundtrip_set_complex.dat" using 1:(1e6 * ($4 - $6) / $1):(1e6 * $3 / $1):(1e6 * $7 / $1):(1e6 * ($4 + $6) / $1) \
        t "Set [complex] <-> C++ <std::complex<double>>" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_set_complex.dat" using 1:(1e6 * $3 / $1) t "Minimum Set [complex] <-> C++ <std::complex<double>>" with lines

reset
