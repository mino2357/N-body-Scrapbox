set term dumb size 100, 50
set size square
set xlabel "au"
set ylabel "au"
intv=100
start=1
size=0.1
p [0.38:0.39][-0.1:0.1] "log.log" every intv::start u 3:4 w p ps size title "Mercury"
# p [0.3868:0.3871][-0.02:0.02] "log.log" every intv::start u 3:4 w p ps size title "Mercury"
# p [0.25:0.40][-0.1:0.1] "log.log" every intv::start u 3:4 w l title "Mercury"
pause 60
reread
