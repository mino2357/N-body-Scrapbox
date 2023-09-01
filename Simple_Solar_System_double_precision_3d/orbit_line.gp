# set size square
set title "Orbits of planets in the solar system in ICRF coordinates from 2023-09-01"
set xlabel "x [au]"
set ylabel "y [au]"
set zlabel "z [au]"
set xr [-50:50]
set yr [-50:50]
set zr [-50:50]
splot "log.log"  u 12:13:14 w p ps 0.4 title "Mercury"
replot "log.log" u 22:23:24 w p ps 0.4 title "Venus"
replot "log.log" u 32:33:34 w p ps 0.4 title "Earth"
replot "log.log" u 42:43:44 w p ps 0.4 title "Mars"
replot "log.log" u 52:53:54 w p ps 0.4 title "Jupiter"
replot "log.log" u 62:63:64 w p ps 0.4 title "Saturn"
replot "log.log" u 72:73:74 w p ps 0.4 title "Uranus"
replot "log.log" u 82:83:84 w p ps 0.4 title "Neptune"
replot "log.log" u 92:93:94 w p ps 0.4 title "*Pluto"
