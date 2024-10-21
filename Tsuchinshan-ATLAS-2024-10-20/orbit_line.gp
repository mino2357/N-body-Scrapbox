# set size square
intv=10
start=1
end=1000
set title "Orbits of C/2023 A3 (Tsuchinshan-ATLAS) from 2024-10-20, mass = 1.0e13"
set xlabel "x [au]"
set ylabel "y [au]"
set zlabel "z [au]"
set xr [-10:10]
set yr [-10:10]
set zr [-10:10]
splot "log.log"  every intv::start::end u 12:13:14 w l title "Mercury"
replot "log.log" every intv::start::end u 22:23:24 w l title "Venus"
replot "log.log" every intv::start::end u 32:33:34 w l title "Earth"
replot "log.log" every intv::start::end u 42:43:44 w l title "Mars"
replot "log.log" every intv::start::end u 52:53:54 w l title "Jupiter"
replot "log.log" every intv::start::end u 62:63:64 w l title "Saturn"
replot "log.log" every intv::start::end u 72:73:74 w l title "Uranus"
replot "log.log" every intv::start::end u 82:83:84 w l title "Neptune"
replot "log.log" every intv::start::end u 92:93:94 w l title "C/2023 A3 (Tsuchinshan-ATLAS)"
pause 60
reread