set size square
intv=100
size=0.2
p [-35:35][-35:35] "log.log" every intv::3 u 4:5 w p ps size title "Mercury", "log.log" every intv::3 u 6:7 w p ps size title "Venus", "log.log" every intv::3 u 8:9 w p ps size title "Earth", "log.log" every intv::3 u 10:11 w p ps size title "Mars", "log.log" every intv::3 u 12:13 w p ps size title "Jupiter", "log.log" every intv::3 u 14:15 w p ps size title "Saturn", "log.log" every intv::3 u 16:17 w p ps size title "Uranus", "log.log" every intv::3 u 18:19 w p ps size title "Neptune"
pause 5
reread
