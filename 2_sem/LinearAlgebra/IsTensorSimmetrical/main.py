class Tensor:
    def __addLayer(self, n: int, depth: int):
        if depth > 0:
            return [self.__addLayer(n, depth - 1) for _ in range(n)]
        else:
            return 0

    def __at(self, i: [int], matrix):
        if len(i) != 0:
            return self.__at(i[:-1], matrix[i[-1]])
        else:
            return matrix

    def __init__(self, n: int, p: int, r: int):
        self.size = n
        self.matrix = self.__addLayer(n, p + r)
        self.p = p
        self.r = r

    def __getitem__(self, item):
        return self.matrix[item]

    def isSymmetrical(self, by: [int]):
        indices = [0 for _ in range(self.p + self.r)]
        result = True

        for i in by:
            for j in range(self.size):
                indices[i] = j
                value = self.__at(indices, self.matrix)

                prev = i
                for k in by:
                    if k != i:
                        indices[prev], indices[k] = indices[k], indices[prev]
                        buffer = self.__at(indices, self.matrix)

                        if value != buffer:
                            print(value)
                            print(buffer)
                            print(indices)
                            result = False

                        prev = k

                indices[i], indices[prev] = indices[prev], indices[i]

        return result


a = Tensor(2, 4, 0)
a.matrix = [[[[1, -1],
              [-1, 1]],

             [[1, -0.5],
              [-0.5, 1]]],

            [[[1, 0],
              [0, 1]],

             [[1, 0],
              [0, 1]]]]

print(a.isSymmetrical([2, 3]))
print(a[1][0][0][1])
