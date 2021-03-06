#set logscale x
set grid
set title "Memory usage of creating a 0.5m dict of 1k strings and round-tripping it through a C++ std::map 10 times."
set xlabel "Time (s)"

#set logscale y
set ylabel "RSS (Mb)"
set yrange [0:5e3]
# set ytics 8,35,3

# set logscale y2
set y2label "dRSS (Mb)"
set y2range [-2.5e3:2.5e3]
set y2tics

set pointsize 1
set datafile separator whitespace
# Curve fit
#cost(x) = a + (b / (x/1024))
#fit cost(x) "perf_size_of.dat" using 1:2 via a,b

set key left

set terminal svg size 1400,700           # choose the file format
set output "images/pymemtrace_dict_str.svg"   # choose the output device

plot "dat/pymemtrace_dict_str.dat" using 4:($9 / (1024 * 1024)) t "RSS (Mb)" with linespoints axes x1y1 pt 1 lw 1, \
    "dat/pymemtrace_dict_str.dat" using 4:($10 / (1024 * 1024)) t "dRSS (Mb)" with points axes x1y2 pt 2 lw 1

#plot "dat/test_with_pymemtrace.dat" using 4:9 t "RSS" with linespoints axes x1y1 pt 1 lw 1

#reset

set terminal png size 1400,700           # choose the file format
set output "images/pymemtrace_dict_str.png"   # choose the output device

plot "dat/pymemtrace_dict_str.dat" using 4:($9 / (1024 * 1024)) t "RSS (Mb)" with linespoints axes x1y1 pt 1 lw 1, \
    "dat/pymemtrace_dict_str.dat" using 4:($10 / (1024 * 1024)) t "dRSS (Mb)" with points axes x1y2 pt 2 lw 1

reset
