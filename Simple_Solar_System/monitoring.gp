set size square
intv=10
start=4
size=0.2
p [0.0:1.0][0.0:1.0] "log.log" every intv::start u 4:5 w p ps size title "Mercury", "log.log" every intv::start u 6:7 w p ps size title "Venus", "log.log" every intv::start u 8:9 w p ps size title "Earth", "log.log" every intv::start u 10:11 w p ps size title "Mars", "log.log" every intv::start u 12:13 w p ps size title "Jupiter", "log.log" every intv::start u 14:15 w p ps size title "Saturn", "log.log" every intv::start u 16:17 w p ps size title "Uranus", "log.log" every intv::start u 18:19 w p ps size title "Neptune"
pause 5
reread
