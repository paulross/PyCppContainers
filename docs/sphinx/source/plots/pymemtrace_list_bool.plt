#set logscale x
set grid
set xlabel "Time (s)"

#set logscale y
set ylabel "RSS (Mb)"
# set yrange [8:35]
# set ytics 8,35,3

# set logscale y2
set y2label "dRSS (Mb)"
# set y2range [1:1e9]
set y2tics

set pointsize 1
set datafile separator whitespace
# Curve fit
#cost(x) = a + (b / (x/1024))

set key left
set key font ",9"

set terminal png size 700,400           # choose the file format
set output "images/pymemtrace_list_list_bool.png"   # choose the output device
set title "Creating a 10m list of bool, round-tripping it through C++ std::list<bool> 10 times."
set yrange [0:600]
set y2range [-300:300]

plot "dat/pymemtrace_list_list_bool.dat" using 4:($9 / (1024 * 1024)) t "RSS std::list<bool> (Mb)" with linespoints axes x1y1 pt 1 lw 1, \
    "dat/pymemtrace_list_list_bool.dat" using 4:($10 / (1024 * 1024)) t "dRSS std::list<bool> (Mb)" with points axes x1y2 pt 2 lw 1

set output "images/pymemtrace_list_vector_bool.png"   # choose the output device
set yrange [0:250]
set y2range [-250:250]

set title "Creating a 10m list of bool, round-tripping it through C++ std::vector<bool> 10 times."
plot "dat/pymemtrace_list_vector_bool.dat" using 4:($9 / (1024 * 1024)) t "RSS std::vector<bool> (Mb)" with linespoints axes x1y1 pt 1 lw 1, \
    "dat/pymemtrace_list_vector_bool.dat" using 4:($10 / (1024 * 1024)) t "dRSS std::vector<bool> (Mb)" with points axes x1y2 pt 2 lw 1

reset
