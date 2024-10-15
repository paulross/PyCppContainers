set logscale x
set grid
set title "Python str to a C++ String and Back." noenhanced
set xlabel "String length"

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
set key font ",9"
set boxwidth 0.2 relative

# Some rate lines
latency = 0.2e-6
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

# Time plots
set ylabel "Time (µs)"

set terminal png size 700,400           # choose the file format
set output "images/roundtrip_str_8_16_32_time.png"   # choose the output device

plot "dat/roundtrip_str.dat" using 1:(1e6 * ($4 - $6)):(1e6 * $3):(1e6 * $7):(1e6 * ($4 + $6)) \
        t "8bit str <-> C++ std::string" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_str16.dat" using 1:(1e6 * ($4 - $6)):(1e6 * $3):(1e6 * $7):(1e6 * ($4 + $6)) \
        t "16bit str <-> C++ std::u16string" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_str32.dat" using 1:(1e6 * ($4 - $6)):(1e6 * $3):(1e6 * $7):(1e6 * ($4 + $6)) \
        t "16bit str <-> C++ std::u16string" with candlesticks whiskerbars 0.5,\
    "dat/roundtrip_set_str_String_length_16.dat" using 1:(rate_10_000_000_000($1) * 1e6) t sprintf("Guide: %.2f µs + 10 GB/s", latency*1e6) with lines lw 2 dashtype 5

# Rate plots
set ylabel "Time per Word (µs)"
#set yrange [0.1:10]

set terminal png size 700,400           # choose the file format
set output "images/roundtrip_str_8_16_32_rate.png"   # choose the output device

plot "dat/roundtrip_str.dat" using 1:(1e6 * ($4 - $6) / $1):(1e6 * $3 / $1):(1e6 * $7 / $1):(1e6 * ($4 + $6) / $1) \
        t "8 bit str <-> C++ std::string" with candlesticks whiskerbars 0.5,\
        "dat/roundtrip_str.dat" using 1:(1e6 * $3 / $1) t "Min 8 bit str <-> C++ std::string" with lines, \
    "dat/roundtrip_str16.dat" using 1:(1e6 * ($4 - $6) / $1):(1e6 * $3 / $1):(1e6 * $7 / $1):(1e6 * ($4 + $6) / $1) \
        t "16 bit str <-> C++ std::u16string" with candlesticks whiskerbars 0.5,\
        "dat/roundtrip_str16.dat" using 1:(1e6 * $3 / $1) t "Min 16 bit str <-> C++ std::u16string" with lines, \
    "dat/roundtrip_str32.dat" using 1:(1e6 * ($4 - $6) / $1):(1e6 * $3 / $1):(1e6 * $7 / $1):(1e6 * ($4 + $6) / $1) \
        t "32 bit str <-> C++ std::u32string" with candlesticks whiskerbars 0.5,\
        "dat/roundtrip_str32.dat" using 1:(1e6 * $3 / $1) t "Min 32 bit str <-> C++ std::u32string" with lines

reset
