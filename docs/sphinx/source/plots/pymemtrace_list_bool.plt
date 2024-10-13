#set logscale x
set grid
set title "Memory usage of creating a 10m list of booleans and round-tripping it through C++ std::vector or std::list 10 times."
set xlabel "Time (s)"

#set logscale y
set ylabel "RSS (Mb)"
# set yrange [8:35]
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
set output "images/pymemtrace_list_bool.png"   # choose the output device

plot "dat/pymemtrace_list_vector_bool.dat" using 4:($9 / (1024 * 1024)) t "RSS std::vector<double> (Mb)" with linespoints axes x1y1 pt 1 lw 1, \
    "dat/pymemtrace_list_list_bool.dat" using 4:($9 / (1024 * 1024)) t "RSS std::list<double> (Mb)" with linespoints axes x1y1 pt 2 lw 1

reset
