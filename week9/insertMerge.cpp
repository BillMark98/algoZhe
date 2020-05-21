
#include<iostream>
// #include<ctime>
using namespace std;
 
void Swap(int & a, int & b);

void InsertionSort(int A[],int testArr[], bool & isSubarray, int N);

// void MSort(int A[], int tmpArray[], int L, int RightEnd);

// bool Merge(int A[], int tmpArray[], int L, int R, int RightEnd);
void Merge_Pass(int A[], int tmpArray[], int testArr[], 
    int N, int length, bool & isSubarray,bool& runOneMoreFlag);
// void Merge1(int A[], int tmpArray[], int L, int R, 
//     int RightEnd, bool printArray, int N);
void Merge1(int A[], int tmpArray[], int L, int R, 
    int RightEnd, int N);

// void MergeSort(int A[], int N);
bool MergeSort_Iterative(int A[], int testArr[], int N);

bool isEqualArr(int A[], int testArr[], int N);

void isInsertMerge(int A[], int testArr[], int N);

void outPut(int A[], int N);
int main()
{
    int N;
    cin >> N;
    int A[N];
    int testArr[N];
    int value;
    for (int i = 0; i < N; i++) {
        cin >> value;
        A[i] = value;
    }

    for (int i = 0; i < N; i++) {
        cin >> value;
        testArr[i] = value;
    }

    // BubbleSort(A,N);
    // InsertionSort(A,N);
    // SelectionSort(A,N);
    // ShellSort(A,N);
    // MergeSort(A,N);
    // MergeSort_Iterative(A,N);

    // for (int i = 0; i < N - 1; i++) {
    //     cout << A[i] << " ";
    // }
    // cout << A[N - 1] << endl;
    isInsertMerge(A, testArr, N);
}

void Swap(int & a, int & b)
{  
    int temp = b;
    b = a;
    a = temp;
}



void InsertionSort(int A[], int testArr[], bool & isSubarray, int N)
{
    // bool isSubarray = false;
    // int runOneMore = N + 1;
    bool runOneMoreFlag = false;
    for(int p = 1; p <= N - 1; p++) {
        if (isSubarray) {
            if (!runOneMoreFlag) {
                return;
            }
        }
        int temp = A[p];
        int i;
        for(i = p; i > 0 && A[i-1] > temp; i--) {
            A[i] = A[i - 1];
        }
        A[i] = temp;
        if (isSubarray && runOneMoreFlag) {
            outPut(A, N);
            runOneMoreFlag = false;
        }
        if(!isSubarray && isEqualArr(A,testArr,N)) {
            cout << "Insertion Sort" << endl;
            isSubarray = true;
            runOneMoreFlag = true;
        }
    }
    // if testArr coincides with the sorted array
    if(isSubarray) {
        // does not need to sort further, since it is already sorted.
        // so just print it, or put it another way, for a sorted array
        // doing one more time is still itself. So print it.
        if (runOneMoreFlag)
            outPut(A,N);    
        // already print it, return
        else 
            return;
    }
}


// void MSort(int A[], int tmpArray[], int L, int RightEnd)
// {
//     int Center;
//     if (L < RightEnd) {
//         Center = (L + RightEnd) / 2;
//         MSort(A, tmpArray, L, Center);
//         MSort(A, tmpArray, Center + 1, RightEnd);
//         Merge(A, tmpArray, L, Center + 1, RightEnd);
//     }
// }

// void Merge(int A[], int tmpArray[], int L, int R, int RightEnd)
// {
//     int leftEnd = R - 1;
//     int i = L,j = R,Tmp = L, NumOfElems = RightEnd - L + 1;
//     while(i <= leftEnd && j <= RightEnd) {
//         if(A[i] <= A[j]) {
//             tmpArray[Tmp++] = A[i++];
//         }
//         else {
//             tmpArray[Tmp++] = A[j++];
//         }
//     }
//     while(i <= leftEnd)
//         tmpArray[Tmp++] = A[i++];
//     while(j <= RightEnd)
//         tmpArray[Tmp++] = A[j++];

//     for(int index = L; index < NumOfElems; index++) {
//         A[index] = tmpArray[index];
//     }
// }

void Merge_Pass(int A[], int tmpArray[], int testArr[], 
    int N, int length, bool & isSubarray,bool & runOneMoreFlag)
{
    int i;
    if(isSubarray) {
        if(!runOneMoreFlag) {
            return;
        }
        else {
            runOneMoreFlag = false;
        }
    }
        
    // bool runOneMoreFlag = false;

    for (i = 0; i <= N - 2 * length; i += 2*length) {
        // if(isSubarray) {
        //     if(!runOneMoreFlag) {
        //         return;
        //     }
        //     else {
        //         runOneMoreFlag = false;
        //     }
        // }
        // Merge1(A, tmpArray, i, i + length, i + 2 * length - 1, isSubarray, N);
        Merge1(A, tmpArray, i, i + length, i + 2 * length - 1, N);        
        if (!isSubarray && isEqualArr(tmpArray, testArr, N)) {
            isSubarray = true;
            cout << "Merge Sort\n";
            runOneMoreFlag = true;
        }
    }
    // // it is possible that the last loop above sets the isSubarray to true
    // if (isSubarray) {
    //     if(runOneMoreFlag) {
    //         runOneMoreFlag = false;
    //     }
    //     else {
    //         // it is possible that thhe last loop above already run onece more and prints the array
    //         // dont need to anything further, simply return
    //         return;
    //     }
    // }
    if (i + length < N) {
        
        // Merge1(A, tmpArray, i, i + length, N - 1, isSubarray,N);
        Merge1(A, tmpArray, i, i + length, N - 1, N);
    }
    else {
        
        for (int j = i; j < N; j++)
            tmpArray[j] = A[j];
        // if (isSubarray) {
        //     outPut(tmpArray, N);
        // }
    }
    if (!isSubarray && isEqualArr(tmpArray, testArr, N)) {
            isSubarray = true;
            cout << "Merge Sort\n";
            runOneMoreFlag = true;
    }
    if (isSubarray && !runOneMoreFlag) {
        outPut(tmpArray, N);
    }

}

// void Merge1(int A[], int tmpArray[], int L, int R, 
//     int RightEnd, bool printArray, int N)
// {
//     int leftEnd = R - 1;
//     int Tmp = L;
//     while(L <= leftEnd && R <= RightEnd) {
//         if(A[L] <= A[R]) {
//             tmpArray[Tmp++] = A[L++];
//         }
//         else {
//             tmpArray[Tmp++] = A[R++];
//         }
//     }
//     while(L <= leftEnd)
//         tmpArray[Tmp++] = A[L++];
//     while(R <= RightEnd)
//         tmpArray[Tmp++] = A[R++];
//     if (printArray) {
//         outPut(tmpArray, N);
//     }
// }

void Merge1(int A[], int tmpArray[], int L, int R, 
    int RightEnd, int N)
{
    int leftEnd = R - 1;
    int Tmp = L;
    while(L <= leftEnd && R <= RightEnd) {
        if(A[L] <= A[R]) {
            tmpArray[Tmp++] = A[L++];
        }
        else {
            tmpArray[Tmp++] = A[R++];
        }
    }
    while(L <= leftEnd)
        tmpArray[Tmp++] = A[L++];
    while(R <= RightEnd)
        tmpArray[Tmp++] = A[R++];
}

// void MergeSort(int A[], int N)
// {
//     int * tmpArray = new int[N];
//     if (tmpArray != nullptr) {
//         MSort(A, tmpArray, 0, N - 1);
//         delete [] tmpArray;
//     }
//     else {
//         cout << "Not Enough Space\n";
//         exit(1);
//     }
// }

bool MergeSort_Iterative(int A[], int testArr[], int N)
{
    int tmpArray[N];
    for (int i = 0; i < N; i++) {
        tmpArray[i] = A[i];
    }
    bool isSubArray = false;
    bool runOneMoreFlag = false;
    if (tmpArray != nullptr) {
        int length = 1;
        while (length < N) {
            Merge_Pass(A, tmpArray, testArr, N, length, isSubArray, runOneMoreFlag);
            length *= 2;
            Merge_Pass(tmpArray, A, testArr, N, length, isSubArray, runOneMoreFlag);
            length *= 2;
        }
        return isSubArray;
        // delete [] tmpArray;
    }
    else {
        cout << "Not Enough Space\n";
        exit(1);
    }
}

bool isEqualArr(int A[], int testArr[], int N)
{
    for (int i = 0; i < N; i++) {
        if (A[i] != testArr[i]) {
            return false;
        }
    }
    return true;
}

void isInsertMerge(int A[], int testArr[], int N)
{
    bool isSubarray = false;
    int A_copy[N];
    for (int i = 0; i < N; i++) {
        A_copy[i] = A[i];
    }
    InsertionSort(A_copy, testArr, isSubarray, N);
    if(isSubarray) {
        return; 
    }
    else {
        MergeSort_Iterative(A, testArr, N);
    }
}

void outPut(int A[], int N)
{
    for (int i = 0; i < N - 1; i++) {
        cout << A[i] << " ";
    }
    cout << A[N-1] << endl;
}