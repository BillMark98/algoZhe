
#include<iostream>
// #include<ctime>
using namespace std;
 
void Swap(int & a, int & b);

void InsertionSort(int A[],int testArr[], bool & isSubarray, int N);

void PercDown(int A[], int m, int N);
void HeapSort(int A[], int testArr[], int N);

bool isEqualArr(int A[], int testArr[], int N);

void isInsertHeap(int A[], int testArr[], int N);

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
    isInsertHeap(A, testArr, N);
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




void PercDown(int A[], int m, int N)
{
    int parent,child;
    int value = A[m];
    for(parent = m; parent * 2 < N - 1; parent = child) {
        child = 2 * parent + 1;
        if(child < N - 1 && A[child + 1] > A[child]) {
            child++;
        }
        if(value < A[child]) {
            A[parent] = A[child];
        }
        else {
            break;
        }
    }
    A[parent] = value;
}

void HeapSort(int A[], int testArr[], int N)
{
    bool isSubarray = false, runOneMoreFlag = false;
    for(int i = N/2 - 1; i >= 0; i--) {
        if (isSubarray) {
            if (!runOneMoreFlag) {
                return;
            }
        }
        PercDown(A,i,N);

        if (isSubarray && runOneMoreFlag) {
            outPut(A, N);
            runOneMoreFlag = false;
        }

        if (!isSubarray && isEqualArr(A, testArr, N)) {
            isSubarray = true;
            cout << "Heap Sort\n";
            runOneMoreFlag = true;
        }
    }
    for(int i = N - 1; i > 0; i--) {
        if (isSubarray) {
            if (!runOneMoreFlag) {
                return;
            }
        }

        Swap(A[0],A[i]);
        PercDown(A,0,i);

        if (isSubarray && runOneMoreFlag) {
            outPut(A, N);
            runOneMoreFlag = false;
        }

        if (!isSubarray && isEqualArr(A, testArr, N)) {
            isSubarray = true;
            cout << "Heap Sort\n";
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

bool isEqualArr(int A[], int testArr[], int N)
{
    for (int i = 0; i < N; i++) {
        if (A[i] != testArr[i]) {
            return false;
        }
    }
    return true;
}

void isInsertHeap(int A[], int testArr[], int N)
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
        HeapSort(A, testArr, N);
    }
}

void outPut(int A[], int N)
{
    for (int i = 0; i < N - 1; i++) {
        cout << A[i] << " ";
    }
    cout << A[N-1] << endl;
}