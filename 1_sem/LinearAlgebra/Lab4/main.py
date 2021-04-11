import math


class RadiusVector:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z


class Plain:
    def __init__(self, normal, point):
        self.normal = normal
        self.point = point

        self.A = normal.x
        self.B = normal.y
        self.C = normal.z
        self.D = point.x * self.A + point.y * self.B + point.z * self.C

    def belong(self, a):
        return self.A * a.x + self.B * a.y + self.C * a.z - self.D == 0


def determinant(a):
    return a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2]) \
           - a[0][1] * (a[1][0] * a[2][2] - a[2][0] * a[1][2]) \
           + a[0][2] * (a[1][0] * a[2][1] - a[2][0] * a[1][1])


def parallel(a, b):
    return abs(a.A * b.A + a.B * b.B + a.C * b.C) / (
            math.sqrt(a.A ** 2 + a.B ** 2 + a.C ** 2) * math.sqrt(b.A ** 2 + b.B ** 2 + b.C ** 2)) == 1


def intercept(a, b, c):
    if parallel(a, b) or parallel(a, c) or parallel(b, c):
        return None

    det = determinant([
        [a.A, a.B, a.C],
        [b.A, b.B, b.C],
        [c.A, c.B, c.C]
    ])

    if det == 0:
        return None

    detX = determinant([[a.D, a.B, a.C],
                        [b.D, b.B, b.C],
                        [c.D, c.B, c.C]])

    detY = determinant([[a.A, a.D, a.C],
                        [b.A, b.D, b.C],
                        [c.A, c.D, c.C]])

    detZ = determinant([[a.A, a.B, a.D],
                        [b.A, b.B, b.D],
                        [c.A, c.B, c.D]])

    return RadiusVector(detX / det, detY / det, detZ / det)


file = open("input.txt", "r")
out = open("output.txt", "w")
count = int(file.readline().split()[0])

plains = []

for i in range(0, count):
    array = list(map(float, file.readline().split()))
    plains.append(
        Plain(
            RadiusVector(array[0], array[1], array[2]),
            RadiusVector(array[3], array[4], array[5])))

intercepts = []

for i in range(0, count - 2):
    for j in range(i + 1, count - 1):
        for k in range(j + 1, count):
            p = intercept(plains[i], plains[j], plains[k])
            if p is not None:
                intercepts.append(p)

iN = []
for p in intercepts:
    have = True
    for plain in plains:
        if plain.A * p.x + plain.B * p.y + plain.C * p.z - plain.D > 0:
            have = False
            break
    if have:
        alr = False
        for i in iN:
            if p.x == i.x and p.y == i.y and p.z == i.z:
                alr = True
                break
        if not alr:
            iN.append(p)
intercepts = iN
iN = []

pN = []
for plain in plains:
    points = []
    for p in intercepts:
        if plain.belong(p):
            points.append(p)
    if len(points) > 2:
        pN.append(plain)
plains = pN
pN = []

if len(intercepts) < 4:
    out.write("0")
    exit(0)

for plain in plains:
    have = True
    for point in intercepts:
        if not plain.belong(point):
            have = False
            break
    if have:
        out.write("0")
        exit(0)

out.write(str(len(intercepts) + len(plains) - 2) + "\n")

for i in range(0, len(intercepts) - 1):
    for j in range(i + 1, len(intercepts)):
        p = []
        for plain in plains:
            if plain.belong(intercepts[i]) and plain.belong(intercepts[j]):
                p.append(plain)
        if len(p) > 1:
            out.write(str(intercepts[i].x) + " " + str(intercepts[i].y) + " " + str(intercepts[i].z) + " ")
            out.write(str(intercepts[j].x) + " " + str(intercepts[j].y) + " " + str(intercepts[j].z) + "\n")
