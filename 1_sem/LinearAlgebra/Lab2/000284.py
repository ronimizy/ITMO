import math


class RadiusVector:
    def __init__(self, x=0, y=0, z=0):
        self.x = x
        self.y = y
        self.z = z


def subdivideVectors(a, b):
    return RadiusVector(a.x - b.x, a.y - b.y, a.z - b.z)


def addVectors(a, b):
    return RadiusVector(a.x + b.x, a.y + b.y, a.z + b.z)


def multiplyVectorOnNumber(n, v):
    return RadiusVector(n * v.x, n * v.y, n * v.z)


def vMultipyVecotrs(vD, vM):
    X = vD.y * vM.z - vM.y * vD.z
    Y = -(vD.x * vM.z - vM.x * vD.z)
    Z = vD.x * vM.y - vM.x * vD.y

    return RadiusVector(X, Y, Z)


def sMultiplyVectors(a, b):
    return a.x * b.x + a.y * b.y + a.z * b.z


def vectorLength(a):
    return (a.x ** 2 + a.y ** 2 + a.z ** 2) ** 0.5


def cosBetweenVectors(a, b):
    return (sMultiplyVectors(a, b) / (vectorLength(a) * vectorLength(b)))


def s(r, n, D):
    r = sMultiplyVectors(r, n)
    if r > D:
        return 1
    if r < D:
        return -1
    return 0


def acos(a):
    return math.acos(a) * 180 / math.pi


class PirateShip:
    def __init__(self, data):
        self.position = RadiusVector(data[0], data[1])
        self.direction = RadiusVector(data[2], data[3])
        self.mast = RadiusVector(data[4], data[5], 1)
        self.enemy = subdivideVectors(RadiusVector(data[6], data[7]), self.position)

        self.position = RadiusVector()

        self.gunLeft = RadiusVector(-self.direction.y, self.direction.x)
        self.gunRight = RadiusVector(self.direction.y, -self.direction.x)


file = open("input.txt", "r")
out = open("output.txt", "w")

ship = PirateShip(list(map(float, sum([i.split() for i in file.readlines()], []))))

cosL = cosBetweenVectors(ship.gunLeft, ship.enemy)
cosR = cosBetweenVectors(ship.gunRight, ship.enemy)
cosD = cosBetweenVectors(ship.direction, ship.enemy)

if cosL >= 0.5:
    out.write("1\n")
    if cosD < 0:
        out.write('-')
    out.write(str(acos(cosL)) + '\n')
elif cosR >= 0.5:
    out.write("-1\n")
    if cosD < 0:
        out.write('-')
    out.write(str(acos(cosR)) + '\n')
else:
    out.write('0\n')

mAng = acos(cosBetweenVectors(ship.mast, RadiusVector(0, 0, 1)))
mlAng = acos(cosBetweenVectors(ship.mast, ship.gunLeft))

if mlAng > 90:
    out.write('-')

out.write(str(mAng))


out.close()