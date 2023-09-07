# set size square
intv=1
start=1
end=1000
set title "Orbits of planets in the solar system in ICRF coordinates from 2023-09-01"
set xlabel "x [au]"
set ylabel "y [au]"
set zlabel "z [au]"
set xr [-50:50]
set yr [-50:50]
set zr [-50:50]
splot "log.log"  every intv::start::end u 12:13:14 w p ps 0.2 title "Mercury"
replot "log.log" every intv::start::end u 22:23:24 w p ps 0.2 title "Venus"
replot "log.log" every intv::start::end u 32:33:34 w p ps 0.2 title "Earth"
replot "log.log" every intv::start::end u 42:43:44 w p ps 0.2 title "Mars"
replot "log.log" every intv::start::end u 52:53:54 w p ps 0.2 title "Jupiter"
replot "log.log" every intv::start::end u 62:63:64 w p ps 0.2 title "Saturn"
replot "log.log" every intv::start::end u 72:73:74 w p ps 0.2 title "Uranus"
replot "log.log" every intv::start::end u 82:83:84 w p ps 0.2 title "Neptune"
replot "log.log" every intv::start::end u 92:93:94 w p ps 0.2 title "*Pluto"
