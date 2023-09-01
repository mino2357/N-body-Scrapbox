# set terminal dumb size 100, 50
intv=1
start=1
set xlabel "yr"
set ylabel "eccentricity"
plot   "log.log" u 1:21 w l title "Mercury"
replot "log.log" u 1:31 w l title "Venus"
replot "log.log" u 1:41 w l title "Earth"
replot "log.log" u 1:51 w l title "Mars"
replot "log.log" u 1:61 w l title "Jupiter"
replot "log.log" u 1:71 w l title "Saturn"
replot "log.log" u 1:81 w l title "Uranus"
replot "log.log" u 1:91 w l title "Neptune"
replot "log.log" u 1:101 w l title "*Pluto"
