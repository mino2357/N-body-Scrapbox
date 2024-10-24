# set terminal dumb size 100, 50
intv=100
start=3
end=1000000000
set xr [0:0.2]
set xlabel "Myr"
set ylabel "eccentricity"
#plot   "log.log" every intv::start u 1:21 w l title "Mercury"
#replot "log.log" every intv::start u 1:31 w l title "Venus"
#replot "log.log" every intv::start u 1:41 w l title "Earth"
#replot "log.log" every intv::start u 1:51 w l title "Mars"
plot "log.log" every intv::start::end u ($1/1000000):61 w p ps 0.01 title "Jupiter"
replot "log.log" every intv::start::end u ($1/1000000):71 w p ps 0.01 title "Saturn"
#replot "log.log" every intv::start u 1:81 w l title "Uranus"
#replot "log.log" every intv::start u 1:91 w l title "Neptune"
#replot "log.log" every intv::start u 1:101 w l title "*Pluto"
