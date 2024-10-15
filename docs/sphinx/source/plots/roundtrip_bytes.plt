set logscale x
set grid
set title "Python bytes to a C++ std::vector<char> and Back." noenhanced
set xlabel "Bytes length"
#set xrange [1:1e7]

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
latency = 0.5e-6
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

max(x, y) = (x > y ? x : y)

# Time plots
set ylabel "Time (µs)"

set terminal png size 700,400           # choose the file format
set output "images/roundtrip_bytes_time.png"   # choose the output device

plot "dat/roundtrip_bytes.dat" using 1:(max(1e6 * ($4 - $6), 0.01)):(1e6 * $3):(1e6 * $7):(1e6 * ($4 + $6)) \
        t "bytes <-> C++ std::vector<char>" with candlesticks whiskerbars 0.5, \
    "dat/roundtrip_bytes.dat" using 1:(rate_10_000_000_000($1) * 1e6) t sprintf("Guide: %.2f µs + 10 GB/s", latency*1e6) with lines lw 2 dashtype 5

#plot "dat/roundtrip_bytes.dat" using 1:(1e6 * $3) \
        t "bytes <-> C++ std::vector<char>" with linespoints,\
    "dat/roundtrip_bytes.dat" using 1:(rate_10_000_000_000($1) * 1e6) t sprintf("Guide: %.2f µs + 10 GB/s", latency*1e6) with lines lw 2 dashtype 5, \
    "dat/roundtrip_bytes.dat" using 1:(rate_100_000_000_000($1) * 1e6) t sprintf("Guide: %.2f µs + 100 GB/s", latency*1e6) with lines lw 2 dashtype 5

# Rate plots
set ylabel "Time per Byte (µs)"
#set yrange [0.1:10]

set terminal png size 700,400           # choose the file format
set output "images/roundtrip_bytes_rate.png"   # choose the output device

plot "dat/roundtrip_bytes.dat" using 1:(max(1e6 * ($4 - $6) / $1, 0.00001)):(1e6 * $3 / $1):(1e6 * $7 / $1):(1e6 * ($4 + $6) / $1) \
        t "Bytes <-> C++ std::vector<char>" with candlesticks whiskerbars 0.5,\
        "dat/roundtrip_bytes.dat" using 1:(1e6 * $3 / $1) t "Min bytes <-> C++ std::vector<char>" with lines

#plot "dat/roundtrip_bytes.dat" using 1:(1e6 * $3 / $1) \
        t "Bytes <-> C++ std::vector<char>" with linespoints

reset
