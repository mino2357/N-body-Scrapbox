set size square
p [0:35][0:35] for [j=1:*] "log.log" every ::3 u 2*j:2*j+1 w l notitle
pause 1
reread
