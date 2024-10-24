# set terminal dumb # size 150, 50
intv=100000
start=1
#set xr [0.9999:1.0001]
set xlabel "time [Myr]"
set ylabel "eccentricity"
plot   "log.log" every intv::start u ($1/1000000):21 w l title "Mercury"
replot "log.log" every intv::start u ($1/1000000):31 w l title "Venus"
replot "log.log" every intv::start u ($1/1000000):41 w l title "Earth"
replot "log.log" every intv::start u ($1/1000000):51 w l title "Mars"
replot "log.log" every intv::start u ($1/1000000):61 w l title "Jupiter"
replot "log.log" every intv::start u ($1/1000000):71 w l title "Saturn"
replot "log.log" every intv::start u ($1/1000000):81 w l title "Uranus"
replot "log.log" every intv::start u ($1/1000000):91 w l title "Neptune"
replot "log.log" every intv::start u ($1/1000000):101 w l title "*Pluto"
