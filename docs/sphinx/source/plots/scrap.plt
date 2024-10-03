set grid

set logscale x
set xlabel "Size of String in Characters"

set logscale y
set ylabel "Time per Item (µs)"

set pointsize 1
set datafile separator whitespace

set boxwidth 0.2 relative

set terminal png size 800,400           # choose the file format
set output "images/scrap.png"   # choose the output device

#plot "dat/scrap.dat" using 3:7 with linespoints
plot "dat/fundamental_test_cpp_string_to_py_str_multiple.dat" using 3:7 with linespoints

reset
