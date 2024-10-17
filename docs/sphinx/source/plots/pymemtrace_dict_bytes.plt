#set logscale x
set grid
set title "A 0.5m dict of 1k bytes, round-tripping it through a C++ std::unordered_map 10 times." noenhanced
set xlabel "Time (s)"

#set logscale y
set ylabel "RSS (Mb)"
#set yrange [0:5e3]
# set ytics 8,35,3

# set logscale y2
set y2label "dRSS (Mb)"
set y2range [-2.5e3:2.5e3]
set y2tics

set pointsize 1
set datafile separator whitespace
# Curve fit
#cost(x) = a + (b / (x/1024))

set key left
set key font ",9"

#reset

set terminal png size 700,400           # choose the file format
set output "images/pymemtrace_dict_bytes.png"   # choose the output device

set yrange [0:5000]
set y2range [-2500:2500]

plot "dat/pymemtrace_dict_bytes.dat" using 4:($9 / (1024 * 1024)) t "RSS (Mb)" with linespoints axes x1y1 pt 1 lw 1, \
    "dat/pymemtrace_dict_bytes.dat" using 4:($10 / (1024 * 1024)) t "dRSS (Mb)" with points axes x1y2 pt 2 lw 1

reset
