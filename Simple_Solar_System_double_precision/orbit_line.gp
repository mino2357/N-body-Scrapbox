set terminal pngcairo size 1080,1080
set output 'orbit_line.png'
plot [-35:35][-35:35] "log.log" u 2:3 w l, "log.log" u 4:5 w l, "log.log" u 6:7 w l, "log.log" u 8:9 w l, "log.log" u 10:11 w l, "log.log" u 12:13 w l, "log.log" u 14:15 w l, "log.log" u 16:17 w l, "log.log" u 18:19 w l, "log.log" u 20:21 w l
unset output
