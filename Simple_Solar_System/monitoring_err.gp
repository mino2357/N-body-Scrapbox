set logscale y
# set yr [0.0001:]
intv=100
start=4
plot "e.log" every intv::start u 1:10 w l title "err"
pause 5
reread
