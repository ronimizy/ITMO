data = open("aplusbb.in").readline().split()
out = open("aplusbb.out", "w")
summa = int(data[0]) + int(data[1])*int(data[1])
out.write(str(summa))