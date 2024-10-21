# set size square
intv=10000
start=1
end=10009000
set title "Orbits of C/2023 A3 (Tsuchinshan-ATLAS) from 2024-10-20, mass = 1.0e13"
set xlabel "x [au]"
set ylabel "y [au]"
set size square
set grid
set xr [-200:200]
set yr [-200:200]
# plot   "log.log" every intv::start::end u  2:3  w l title "Sun"
plot   "log.log" every intv::start::end u 12:13 w l title "Mercury"
replot "log.log" every intv::start::end u 22:23 w l title "Venus"
replot "log.log" every intv::start::end u 32:33 w l title "Earth"
replot "log.log" every intv::start::end u 42:43 w l title "Mars"
replot "log.log" every intv::start::end u 52:53 w l title "Jupiter"
replot "log.log" every intv::start::end u 62:63 w l title "Saturn"
replot "log.log" every intv::start::end u 72:73 w l title "Uranus"
replot "log.log" every intv::start::end u 82:83 w l title "Neptune"
replot "log.log" every intv::start::end u 92:93 w l title "C/2023 A3 (Tsuchinshan-ATLAS)"
pause 360
reread