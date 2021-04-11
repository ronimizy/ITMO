import math


def determinant(a):
    return a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2]) \
           - a[0][1] * (a[1][0] * a[2][2] - a[2][0] * a[1][2]) \
           + a[0][2] * (a[1][0] * a[2][1] - a[2][0] * a[1][1])


class Vector:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def add(self, vector):
        return Vector(self.x + vector.x, self.y + vector.y, self.z + vector.z)

    def subtract(self, vector):
        return self.add(vector.multiply(-1))

    def multiply(self, a):
        return Vector(self.x * a, self.y * a, self.z * a)

    def multiplyV(self, vector):
        return Vector(self.y * vector.z - vector.y * self.z,
                      -self.x * vector.z + vector.x * self.z,
                      self.x * vector.y - vector.x * self.y)

    def multiplyS(self, vector):
        return self.x * vector.x + self.y * vector.y + self.z * vector.z

    def cos(self, vector):
        return self.multiplyS(vector) / (self.length() * vector.length())

    def length(self):
        return math.sqrt(self.x ** 2 + self.y ** 2 + self.z ** 2)


class Line:
    def __init__(self, point, direction):
        self.point = point
        self.direction = direction


class Plain:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c

        if a.subtract(b).multiplyS(c.subtract(b)) == 0:
            self.d = a.add(c.subtract(b))
        else:
            self.d = c.add(b.subtract(a))

        self.normal = b.subtract(a).multiplyV(self.c.subtract(a))

        self.A = self.normal.x
        self.B = self.normal.y
        self.C = self.normal.z
        self.D = self.normal.x * a.x + self.normal.y * a.y + self.normal.z * a.z

    def belong(self, point):
        if self.A * point.x + self.B * point.y + self.C * point.z == self.D:
            if min(self.a.x, self.b.x, self.c.x, self.d.x) <= point.x <= max(self.a.x, self.b.x, self.c.x, self.d.x):
                if min(self.a.y, self.b.y, self.c.y, self.d.y) <= point.y <= max(self.a.y, self.b.y, self.c.y,
                                                                                 self.d.y):
                    if min(self.a.z, self.b.z, self.c.z, self.d.z) <= point.z <= max(self.a.z, self.b.z, self.c.z,
                                                                                     self.d.z):
                        return point
        return False

    def crossingPoint(self, line):
        divider = self.A * line.direction.x + self.B * line.direction.y + self.C * line.direction.z

        if divider == 0:
            return False, False
        parameter = -(self.A * line.point.x + self.B * line.point.y + self.C * line.point.z - self.D) / divider

        return line.direction.multiply(parameter).add(line.point), parameter >= 0


def inCube(cube, point):
    x = []
    y = []
    z = []

    for p in cube:
        x.append(p.x)
        y.append(p.y)
        z.append(p.z)

    if min(x) <= point.x <= max(x):
        if min(y) <= point.y <= max(y):
            if min(z) <= point.z <= max(z):
                return True

    return False


file = open("input.txt", "r")
out = open("output.txt", "w")

cubePoints = []

for i in range(4):
    data = list(map(float, file.readline().split()))
    cubePoints.append(Vector(data[0], data[1], data[2]))

cubePoints.append(cubePoints[0].add(cubePoints[2].subtract(cubePoints[1])))
cubePoints.append(cubePoints[0].add(cubePoints[3].subtract(cubePoints[2])))
cubePoints.append(cubePoints[5].add(cubePoints[2].subtract(cubePoints[1])))
cubePoints.append(cubePoints[1].add(cubePoints[3].subtract(cubePoints[2])))

cube = [Plain(cubePoints[0], cubePoints[1], cubePoints[2]),
        Plain(cubePoints[0], cubePoints[1], cubePoints[7]),
        Plain(cubePoints[0], cubePoints[4], cubePoints[5]),
        Plain(cubePoints[3], cubePoints[2], cubePoints[1]),
        Plain(cubePoints[3], cubePoints[2], cubePoints[4]),
        Plain(cubePoints[3], cubePoints[6], cubePoints[5])]

data = list(map(float, file.readline().split()))
direction = Vector(data[0], data[1], data[2])

data = list(map(float, file.readline().split()))
point = Vector(data[0], data[1], data[2])

power = int(file.readline().split()[0])
mirrorCount = int(file.readline().split()[0])

mirrors = []
for i in range(mirrorCount):
    points = []
    for j in range(3):
        data = list(map(float, file.readline().split()))
        points.append(Vector(data[0], data[1], data[2]))
    mirrors.append(Plain(points[0], points[1], points[2]))
file.close()

while power > 0:
    distance = False
    line = Line(point, direction)
    crossingPoint = False

    newDirection = False
    newPoint = False
    for mirror in mirrors:
        crossingPoint, codir = mirror.crossingPoint(line)
        if not mirror.belong(point) and crossingPoint and mirror.belong(crossingPoint) and codir:
            length = point.subtract(crossingPoint).length()
            if not distance or distance > length:
                distance = length
            else:
                continue
            projection, _ = mirror.crossingPoint(Line(point, mirror.normal))

            newDirection = Vector(point.x - 2 * projection.x + crossingPoint.x,
                                  point.y - 2 * projection.y + crossingPoint.y,
                                  point.z - 2 * projection.z + crossingPoint.z)
            newPoint = crossingPoint
    if distance:
        point = newPoint
        direction = newDirection
        power -= 1
        print("{0} {1} {2}".format(point.x, point.y, point.z))
        print("{0} {1} {2}\n".format(direction.x, direction.y, direction.z))
    else:
        out.write("1\n")
        out.write(str(power) + "\n")

        p = False
        d = False

        for side in cube:
            crossingPoint, codir = side.crossingPoint(line)
            if crossingPoint and codir:
                p = crossingPoint

        out.write("{0} {1} {2}\n".format(p.x, p.y, p.z))
        out.write("{0} {1} {2}\n".format(direction.x, direction.y, direction.z))
        out.close()
        exit(0)


out.write("0\n")
out.write("{0} {1} {2}\n".format(point.x, point.y, point.z))
