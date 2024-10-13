#set logscale x
set grid
set title "Memory usage of creating containers with one item of 1k bytes and round-tripping it through C++ 10,000,000 times."
set xlabel "Time (s)"

#set logscale y
set ylabel "RSS (Mb)"
set yrange [25:30]
# set ytics 8,35,3

# set logscale y2
#set y2label "dRSS (Mb)"
# set y2range [1:1e9]
#set y2tics

set pointsize 1
set datafile separator whitespace
# Curve fit
#cost(x) = a + (b / (x/1024))
#fit cost(x) "perf_size_of.dat" using 1:2 via a,b

set key left
set key font ",9"

set terminal png size 700,400           # choose the file format
set output "images/pymemtrace_list_set_dict_bytes_one_item.png"   # choose the output device

plot "dat/pymemtrace_list_bytes_one_item.dat" using 4:($9 / (1024 * 1024)) t "List RSS (Mb)" with linespoints axes x1y1 lw 1, \
    "dat/pymemtrace_set_bytes_one_item.dat" using 4:($9 / (1024 * 1024)) t "Set RSS (Mb)" with linespoints axes x1y1 lw 1, \
    "dat/pymemtrace_dict_bytes_one_item.dat" using 4:($9 / (1024 * 1024)) t "Dict RSS (Mb)" with linespoints axes x1y1 lw 1

reset
