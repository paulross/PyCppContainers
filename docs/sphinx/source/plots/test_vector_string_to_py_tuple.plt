set logscale x
set grid
set title "Time to copy a C++ std::vector<std::string> to a Python tuple with different string lengths."
set xlabel "Vector Size"

set logscale y
set ylabel "Time (s)"
# set yrange [8:35]
# set ytics 8,35,3

# set logscale y2
# set y2label "Bytes"
# set y2range [1:1e9]
# set y2tics

set pointsize 1
set datafile separator whitespace
# Curve fit
#cost(x) = a + (b / (x/1024))
#fit cost(x) "perf_size_of.dat" using 1:2 via a,b

set terminal svg size 1000,700           # choose the file format
set output "test_vector_string_to_py_tuple.svg"   # choose the output device

plot "test_vector_string_to_py_tuple.dat" using 1:2 t "1" with linespoints axes x1y1 pt 1 lw 1, \
    "test_vector_string_to_py_tuple.dat" using 1:3 t "2" with linespoints axes x1y1 pt 2 lw 1, \
    "test_vector_string_to_py_tuple.dat" using 1:4 t "4" with linespoints axes x1y1 pt 3 lw 1, \
    "test_vector_string_to_py_tuple.dat" using 1:5 t "8" with linespoints axes x1y1 pt 4 lw 1, \
    "test_vector_string_to_py_tuple.dat" using 1:6 t "16" with linespoints axes x1y1 pt 5 lw 1, \
    "test_vector_string_to_py_tuple.dat" using 1:7 t "32" with linespoints axes x1y1 pt 6 lw 1, \
    "test_vector_string_to_py_tuple.dat" using 1:8 t "64" with linespoints axes x1y1 pt 7 lw 1, \
    "test_vector_string_to_py_tuple.dat" using 1:9 t "128" with linespoints axes x1y1 pt 8 lw 1, \
    "test_vector_string_to_py_tuple.dat" using 1:10 t "256" with linespoints axes x1y1 pt 9 lw 1, \
    "test_vector_string_to_py_tuple.dat" using 1:11 t "512" with linespoints axes x1y1 pt 10 lw 1
    
reset
