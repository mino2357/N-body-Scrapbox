plot "log.log" every 1::1 u 1:(sqrt(($12-$22)**2+($13-$23)**2+($14-$24)**2)+sqrt(($22-$32)**2+($23-$33)**2+($24-$34)**2)+sqrt(($32-$42)**2+($33-$43)**2+($34-$44)**2)+sqrt(($42-$52)**2+($43-$53)**2+($44-$54)**2)+sqrt(($52-$62)**2+($53-$63)**2+($54-$64)**2)+sqrt(($62-$72)**2+($63-$73)**2+($64-$74)**2)+sqrt(($72-$82)**2+($73-$83)**2+($74-$84)**2)+sqrt(($82-$92)**2+($83-$93)**2+($84-$94)**2)) w l
