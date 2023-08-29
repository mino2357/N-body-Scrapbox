intv=100000
start=4
set xlabel "yr"
set ylabel "eccentricity"
plot "log.log" every intv::start u 1:9 w l title "e"
pause 5
reread
