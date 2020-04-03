def maxSequencePivot(n, arr) :
    MaxSum = 0
    TempSum = 0
    tempLeft = 0
    i = 0
    j = n - 1
    maxModified = False
    for index in range(n) :
        TempSum += arr[index]
        if (not maxModified and TempSum == 0) :
            maxModified = True
            i = tempLeft
            j = index
        if TempSum > MaxSum :
            maxModified = True
            MaxSum = TempSum
            i = tempLeft
            j = index
        elif TempSum < 0 :
            TempSum = 0
            tempLeft = index + 1
    
    print("%d %d %d" %(MaxSum, arr[i], arr[j]))

n = int(input())
arr = list(map(int, input().split()))
maxSequencePivot(n, arr)