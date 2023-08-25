# set yr [0:0.01]
p for [i=2:9] "e.log" every ::4 u 1:i w l
pause 1
reread
