import math


def determinant(a):
    return a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2]) - \
           a[0][1] * (a[1][0] * a[2][2] - a[2][0] * a[1][2]) + \
           a[0][2] * (a[1][0] * a[2][1] - a[2][0] * a[1][1])


class Vector:
    def __init__(self, x: float = 0, y: float = 0, z: float = 0):
        self.x = x
        self.y = y
        self.z = z

    def multiply(self, number: float):
        return Vector(self.x * number, self.y * number, self.z * number)

    def multiplyV(self, vector):
        return Vector(self.y * vector.z - vector.y * self.z, -self.x * vector.z + vector.x * self.z,
                      self.x * vector.y - vector.x * self.y)

    def multiplyS(self, vector):
        return self.x * vector.x + self.y * vector.y + self.z * vector.z

    def length(self):
        return math.sqrt(self.x ** 2 + self.y ** 2 + self.z ** 2)

    def cos(self, vector):
        return self.multiplyS(vector) / (self.length() * vector.length())

    def add(self, vector):
        return Vector(self.x + vector.x, self.y + vector.y, self.z + vector.z)

    def subtract(self, vector):
        return self.add(vector.multiply(-1))

    def coefficient(self, vector):
        return self.length() / vector.length()


class Line:
    def __init__(self, point: Vector, direction: Vector):
        self.point = point
        self.direction = direction

        self.m = direction.x
        self.n = direction.y
        self.p = direction.z


class Rectangle:
    def __init__(self, a=Vector(), b=Vector(), c=Vector()):
        self.a = a
        self.b = b
        self.c = c

        if b.subtract(a).multiplyS(c.subtract(b)) != 0:
            self.b, self.c = self.c, self.b

        self.d = a.add(c).subtract(b)

        self.normal = self.trailing().multiplyV(self.bottom())

        self.A = self.normal.x
        self.B = self.normal.y
        self.C = self.normal.z

        self.D = -a.x * self.A - a.y * self.B - a.z * self.C

    def bottom(self):
        return self.b.subtract(self.a)

    def trailing(self):
        return self.c.subtract(self.b)

    def belong(self, point: Vector):
        if not (min(self.a.x, self.b.x, self.c.x, self.d.x) <= point.x <= max(self.a.x, self.b.x, self.c.x,
                                                                              self.d.x)):
            return False

        if not (min(self.a.y, self.b.y, self.c.y, self.d.y) <= point.y <= max(self.a.y, self.b.y, self.c.y,
                                                                              self.d.y)):
            return False

        if not (min(self.a.z, self.b.z, self.c.z, self.d.z) <= point.z <= max(self.a.z, self.b.z, self.c.z,
                                                                              self.d.z)):
            return False

        return point

    def point(self, line: Line):
        divider = self.A * line.m + self.B * line.n + self.C * line.p

        if divider == 0:
            return False

        t = -(self.A * line.point.x + self.B * line.point.y + self.C * line.point.z + self.D) / divider

        return Vector(line.m * t + line.point.x,
                      line.n * t + line.point.y,
                      line.p * t + line.point.z)

    def crossing(self, line: Line):
        # if abs(line.direction.cos(self.leading())) == 1 or abs(line.direction.cos(self.bottom())) == 1:
        #     return False

        crossPoint = self.point(line)

        if not crossPoint:
            return False

        v = crossPoint.subtract(start)
        if v.x * line.direction.x > 0 and v.y * line.direction.y > 0 and v.z * line.direction.z > 0:
            return crossPoint
        else:
            return False


file = open("input.txt", "r")
out = open("output.txt", "w")

points: [Vector] = []

for i in range(0, 6):
    a = list(map(float, file.readline().split()))
    points.append(Vector(a[0], a[1], a[2]))

cube: [Rectangle] = [Rectangle(points[0], points[1], points[2]),
                     Rectangle(points[1], points[2], points[3]),
                     Rectangle(points[0], points[1], points[3].subtract(points[2].subtract(points[1]))),
                     Rectangle(points[2], points[3], points[0].add(points[2].subtract(points[1]))),
                     Rectangle(points[0], points[2].add(points[0].subtract(points[1])),
                               points[3].add(points[0].subtract(points[1]))),
                     Rectangle(points[3], points[0].add(points[3].subtract(points[2])),
                               points[1].add(points[3].subtract(points[2])))]

direction = points[4]
start = points[5]

power = int(file.readline().split()[0])
mirrorCount = int(file.readline().split()[0])

mirrors: [Rectangle] = []
for i in range(0, mirrorCount):
    points = []
    for j in range(0, 3):
        a = list(map(float, file.readline().split()))
        points.append(Vector(a[0], a[1], a[2]))
    mirrors.append(Rectangle(points[0], points[1], points[2]))

file.close()

while power > 0:
    isSet = False
    minLen = -1
    for mirror in mirrors:
        if mirror.belong(start):
            continue
        crossPoint = mirror.crossing(Line(start, direction))
        if crossPoint:
            if minLen == -1 or minLen > crossPoint.subtract(start).length():
                minLen = crossPoint.subtract(start).length()
            else:
                continue
            projection = mirror.point(Line(start, mirror.normal))
            direction = Vector(start.x - 2 * projection.x + crossPoint.x,
                               start.y - 2 * projection.y + crossPoint.y,
                               start.z - 2 * projection.z + crossPoint.z)
            start = crossPoint
            isSet = True
            break

    print(str(start.x) + " " + str(start.y) + " " + str(start.z) + "\n")
    print(str(direction.x) + " " + str(direction.y) + " " + str(direction.z) + "\n")
    if not isSet:
        out.write("1\n")
        out.write(str(power) + "\n")
        for square in cube:
            crossPoint = square.crossing(Line(start, direction))
            if crossPoint:
                out.write(str(crossPoint.x) + " " + str(crossPoint.y) + " " + str(crossPoint.z) + "\n")
                out.write(str(direction.x) + " " + str(direction.y) + " " + str(direction.z) + "\n")
                break
        exit(0)
    else:
        power -= 1

if power == 0:
    out.write("0\n")
    out.write(str(start.x) + " " + str(start.y) + " " + str(start.z) + "\n")
out.close()
