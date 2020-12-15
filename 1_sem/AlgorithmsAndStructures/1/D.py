def merge(leftList, rightList):
    leftLength = len(leftList)
    rightLength = len(rightList)
    
    left = 0
    right = 0
    
    array = []
    
    for _ in range(leftLength + rightLength):
        if left < leftLength and right < rightLength:
            if leftList[left] <= rightList[right]:
                array.append(leftList[left])
                left += 1
            else:
                array.append(rightList[right])
                right += 1
                
        elif left == leftLength:
            array.append(rightList[right])
            right += 1
        elif right == rightLength:
            array.append(leftList[left])
            left += 1
            
    return array
    
def mergeSort(array):
    length = len(array)
    
    if length <= 1:
        return array
    
    center = length // 2
    leftList = mergeSort(array[:center])
    rightList = mergeSort(array[center:])
    
    return merge(leftList, rightList)

file = open("smallsort.in", "r")
lines = file.readlines()

array = list(map(int, lines[1].split()))
line = " ".join(list(map(str, mergeSort(array))))

ans = open("smallsort.out", "w")
ans.write(line)
ans.close
