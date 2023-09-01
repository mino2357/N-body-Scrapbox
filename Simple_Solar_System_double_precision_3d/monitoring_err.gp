set logscale y
# set yr [0.0001:]
intv=10000
start=4
set xlabel "steps/100"
set ylabel "relative error"
plot "e.log" every intv::start w l title "err"
pause 5
reread
