set print "-"

set style line 1 lc rgb 'red' pt 7
set style line 2 lc rgb 'black' pt 7

set xrange [-1:6]
set yrange [-1:6]
set zrange [-15:15]

set xlabel "x-axis"
set ylabel "y-axis"
set zlabel "z-axis"

str1 = '../plot_data/particles_'
str2 = '.dat' 

i = 0
while(1){
i=i+1
splot  '../plot_data/anchors.dat' w p ls 1, \
'../plot_data/particles_'.i.'.dat'  w p ls 2
print i
pause 0.01
}
