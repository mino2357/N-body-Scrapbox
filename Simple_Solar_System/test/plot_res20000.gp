unset key
set xr[-1.0:1.0]
set yr[-1.0:1.0]
set size square
plot "log2.log" u 1:2 w l
replot "log2.log" u 3:4 w l
replot "log2.log" u 5:6 w l
replot "log2.log" u 7:8 w l
replot "log2.log" u 9:10 w l
replot "log2.log" u 11:12 w l
replot "log2.log" u 13:14 w l
replot "log2.log" u 15:16 w l
replot "log2.log" u 17:18 w l
replot "log2.log" u 19:20 w l
replot "log2.log" u 21:22 w l
replot "log2.log" u 23:24 w l
replot "log2.log" u 25:26 w l
replot "log2.log" u 27:28 w l
replot "log2.log" u 29:30 w l
replot "log2.log" u 31:32 w l
replot "log2.log" u 33:34 w l
replot "log2.log" u 35:36 w l
replot "log2.log" u 37:38 w l
replot "log2.log" u 39:40 w l
replot "log2.log" u 41:42 w l
replot "log2.log" u 43:44 w l
replot "log2.log" u 45:46 w l
replot "log2.log" u 47:48 w l
replot "log2.log" u 49:50 w l
replot "log2.log" u 51:52 w l
replot "log2.log" u 53:54 w l
replot "log2.log" u 55:56 w l
replot "log2.log" u 57:58 w l
replot "log2.log" u 59:60 w l
replot "log2.log" u 61:62 w l
replot "log2.log" u 63:64 w l
replot
set terminal pngcairo size 20000, 20000
set output "n_32_res20000.png"
replot
set output
