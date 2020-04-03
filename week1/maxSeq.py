
def MaxSequence(n, arr) :
    MaxSum = 0
    TempSum = 0
    for num in arr :
        TempSum += num
        if (TempSum > MaxSum) :
           MaxSum = TempSum
        if TempSum < 0 :
            TempSum = 0
    print(MaxSum) 

n = int(input())
arr = list(map(int, input().split()))
MaxSequence(n, arr)
