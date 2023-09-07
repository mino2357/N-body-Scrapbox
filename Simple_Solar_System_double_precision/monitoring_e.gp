set logscale y
# set yr [0.0001:]
intv=1
start=4
plot "e.log" every intv::start u 1:2 w l title "Mercury", "e.log" every intv::start u 1:3 w l title "Venus", "e.log" every intv::start u 1:4 w l title "Eeath", "e.log" every intv::start u 1:5 w l title "Mars", "e.log" every intv::start u 1:6 w l title "Jupiter", "e.log" every intv::start u 1:7 w l title "Saturn", "e.log" every intv::start u 1:8 w l title "Uranus", "e.log" every intv::start u 1:9 w l title "Neptune",
pause 5
reread
