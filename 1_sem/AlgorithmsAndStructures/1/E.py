def merge(leftList, rightList):
    leftLength = len(leftList[0])
    rightLength = len(rightList[0])
    
    left = 0
    right = 0
    
    array = [[],[]]
    
    for _ in range(leftLength + rightLength):
        if left < leftLength and right < rightLength:
            if leftList[0][left] <= rightList[0][right]:
                array[0].append(leftList[0][left])
                array[1].append(leftList[1][left])
                left += 1
            else:
                array[0].append(rightList[0][right])
                array[1].append(rightList[1][right])
                right += 1
                
        elif left == leftLength:
            array[0].append(rightList[0][right])
            array[1].append(rightList[1][right])
            right += 1
        elif right == rightLength:
            array[0].append(leftList[0][left])
            array[1].append(leftList[1][left])
            left += 1
            
    return array
    
def mergeSortDouble(array):
    length = len(array[0])
    
    if length <= 1:
        return array
    
    center = length // 2
    l = [array[0][:center],array[1][:center]]
    leftList = mergeSortDouble(l)
    r = [array[0][center:], array[1][center:]]
    rightList = mergeSortDouble(r)
    
    return merge(leftList, rightList)

file = open("sortland.in", "r")
lines = file.readlines()

count = int(lines[0])
array = [list(map(float, lines[1].split())), [i+1 for i in range(count)]]
sortedArray = mergeSortDouble(array)
minimum = sortedArray[1][0]
maximum = sortedArray[1][count-1]
middle = sortedArray[1][count // 2]


ans = open("sortland.out", "w")
ans.write(str(minimum) + " " + str(middle) + " " + str(maximum))
ans.close

