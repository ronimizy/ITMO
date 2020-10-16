data = open("aplusb.in").readline().split()
out = open("aplusb.out", "w")
summa = int(data[0]) + int(data[1])
out.write(str(summa))