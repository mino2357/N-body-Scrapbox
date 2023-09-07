set terminal dumb # size 100, 50
intv=100
start=4
set xlabel "yr"
set ylabel "eccentricity"
plot "log.log" every intv::start u 1:9 w l title "e"
pause 20
reread
