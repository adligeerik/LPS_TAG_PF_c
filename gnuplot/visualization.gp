set style line 1 lc rgb 'red' pt 7
set style line 2 lc rgb 'black' pt 7

set xrange [-1:6]
set yrange [-1:6]
set zrange [-3:3]

set xlabel "x-axis"
set ylabel "y-axis"
set zlabel "z-axis"

while(1){
splot  '../plot_data/anchors.dat' w p ls 1, \
'../plot_data/particles.dat' w p ls 2
pause 0.1

}
