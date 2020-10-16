def showGrid(grid):
    print("---------------")
    for i in range(h):
        print(grid[i])
    print("---------------")

file = open("turtle.in","r")
lines = file.readlines()

dims = lines[0].split()
h = int(dims[0])
w = int(dims[1])

grid = []

# Grid Fill
for i in range(1, h+1):
    line = list(map(int, lines[i].split()))
    grid.append(line)
    
score = 0
# Left Collumn Counting
for i in range(h-1, -1, -1):
    grid[i][0] += score
    score = grid[i][0]

score = 0
# Right Collumn Counting
for i in range(w):
    grid[h-1][i] += score
    score = grid[h-1][i]

# Body Counting
for i in range(h-2, -1, -1):
    for j in range(1,w):
        if grid[i][j-1] > grid[i+1][j]:
            grid[i][j] += grid[i][j-1]
        else:
            grid[i][j] += grid[i+1][j]
            
            
showGrid(grid)
ans = open("turtle.out", "w")
ans.write(str(grid[0][w-1]))