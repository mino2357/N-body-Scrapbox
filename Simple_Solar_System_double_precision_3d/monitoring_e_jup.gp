# set logscale y
# set yr [0.0001:]
intv=100
start=4
plot "e.log" every intv::start u 1:2 w l title "Mercury", "e.log" every intv::start u 1:3 w l title "Venus", "e.log" every intv::start u 1:4 w l title "Eeath", "e.log" every intv::start u 1:5 w l title "Mars" # , "e.log" every intv::start u 1:6 w l title "Jupiter"
pause 5
reread
