# set size square
set title "Orbits of planets in the solar system in ICRF coordinates from 2023-09-01"
set xlabel "x [au]"
set ylabel "y [au]"
set zlabel "z [au]"
set xr [-50:50]
set yr [-50:50]
# set zr [-50:50]
splot "log.log" u 2:3:4 w l title "Sun"
replot "log.log" u 5:6:7 w l title "Mercury"
replot "log.log" u 8:9:10 w l title "Venus"
replot "log.log" u 11:12:13 w l title "Earth"
replot "log.log" u 14:15:16 w l title "Mars"
replot "log.log" u 17:18:19 w l title "Jupiter"
replot "log.log" u 20:21:22 w l title "Saturn"
replot "log.log" u 23:24:25 w l title "Uranus"
replot "log.log" u 26:27:28 w l title "Neptune"
# replot "log.log" u 29:30:31 w l title "*Pluto"
