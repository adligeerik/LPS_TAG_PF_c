set style line 1 lc rgb 'red' pt 7
set style line 2 lc rgb 'black' pt 3

set xrange [-1:6]
set yrange [-1:6]
set zrange [-1:6]

set xlabel "x-axis"
set ylabel "y-axis"
set zlabel "z-axis"

while(1){
splot '../plot_data/anchors.dat' w p ls 1
pause 1

}
