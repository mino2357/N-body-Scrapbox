intv=100000
start=4
set xlabel "yr"
set ylabel "Orbital Period [yr]"
plot "log.log" every intv::start u 1:10 w l title "OrbitalPeriodOfMercury"
pause 5
reread
