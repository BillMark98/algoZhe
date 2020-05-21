
#include<iostream>
// #include<ctime>
using namespace std;
 
void Swap(int & a, int & b);

void BuildHeap(int A[], int N);

void PercDown(int A[], int m, int N);
void HeapSort(int A[], int N);


int MinPosition(int A[], int left, int right);

void BubbleSort(int A[], int N);

void InsertionSort(int A[], int N);

void SelectionSort(int A[], int N);

void ShellSort(int A[], int N);

void MSort(int A[], int tmpArray[], int L, int RightEnd);

void Merge(int A[], int tmpArray[], int L, int R, int RightEnd);
void Merge_Pass(int A[], int tmpArray[], int N, int length);
void Merge1(int A[], int tmpArray[], int L, int R, int RightEnd);

void MergeSort(int A[], int N);
void MergeSort_Iterative(int A[], int N);

int main()
{
    int N;
    cin >> N;
    int A[N];
    int value;
    for (int i = 0; i < N; i++) {
        cin >> value;
        A[i] = value;
    }

    // BubbleSort(A,N);
    // InsertionSort(A,N);
    // SelectionSort(A,N);
    // ShellSort(A,N);
    // MergeSort(A,N);
    // MergeSort_Iterative(A,N);
    HeapSort(A,N);

    for (int i = 0; i < N - 1; i++) {
        cout << A[i] << " ";
    }
    cout << A[N - 1] << endl;
}

void Swap(int & a, int & b)
{  
    int temp = b;
    b = a;
    a = temp;
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

void HeapSort(int A[], int N)
{
    for(int i = N/2 - 1; i >= 0; i--) {
        PercDown(A,i,N);
    }
    for(int i = N - 1; i > 0; i--) {
        Swap(A[0],A[i]);
        PercDown(A,0,i);
    }
}

int MinPosition(int A[], int left, int right)
{
    int min = left;
    for(int i = left + 1; i <= right; i++) {
        if(A[i] < A[min]) {
            min = i;
        }
    }
    return min;
}

void BubbleSort(int A[], int N)
{
    bool flag;
    for(int p = N-1; p >= 0; p--) {
        flag = true;
        for(int i = 0; i < p; i++) {
            if(A[i] > A[i + 1]) {
                Swap(A[i],A[i+1]);
                flag = false;
            }
        }
        if(flag) {
            break;
        }
    }
}

void InsertionSort(int A[], int N)
{
    for(int p = 1; p <= N - 1;p++) {
        int temp = A[p];
        int i;
        for(i = p; i > 0 && A[i-1] > temp; i--) {
            A[i] = A[i - 1];
        }
        A[i] = temp;
    }
}

void SelectionSort(int A[], int N)
{
    for(int i = 0; i < N; i++) {
        int t = MinPosition(A,i,N - 1);
        Swap(A[i],A[t]);
    }
}

void ShellSort(int A[], int N)
{
    int Sedgewick[] = { 1 ,5 ,19 ,41 ,109 ,209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769, 146305 };
	int D;
	int temp;
	int i,j,P;
	for (j = 14; j >= 0; j--) {
		D = Sedgewick[j];
		for (P = D; P < N;P++) {
			temp = A[P];
			for (i = P; i >= D && A[i - D] > temp;i-=D) {
				A[i] = A[i-D];
			}
			A[i] = temp;
        }
    }
}

void MSort(int A[], int tmpArray[], int L, int RightEnd)
{
    int Center;
    if (L < RightEnd) {
        Center = (L + RightEnd) / 2;
        MSort(A, tmpArray, L, Center);
        MSort(A, tmpArray, Center + 1, RightEnd);
        Merge(A, tmpArray, L, Center + 1, RightEnd);
    }
}

void Merge(int A[], int tmpArray[], int L, int R, int RightEnd)
{
    int leftEnd = R - 1;
    int i = L,j = R,Tmp = L, NumOfElems = RightEnd - L + 1;
    while(i <= leftEnd && j <= RightEnd) {
        if(A[i] <= A[j]) {
            tmpArray[Tmp++] = A[i++];
        }
        else {
            tmpArray[Tmp++] = A[j++];
        }
    }
    while(i <= leftEnd)
        tmpArray[Tmp++] = A[i++];
    while(j <= RightEnd)
        tmpArray[Tmp++] = A[j++];

    for(int index = L; index < NumOfElems; index++) {
        A[index] = tmpArray[index];
    }
}

void Merge_Pass(int A[], int tmpArray[], int N, int length)
{
    int i;
    for (i = 0; i <= N - 2 * length; i += 2*length) {
        Merge1(A, tmpArray, i, i + length, i + 2 * length - 1);
    }
    if (i + length < N) {
        Merge1(A, tmpArray, i, i + length, N - 1);
    }
    else {
        for (int j = i; j < N; j++)
            tmpArray[j] = A[j];
    }
}

void Merge1(int A[], int tmpArray[], int L, int R, int RightEnd)
{
    int leftEnd = R - 1;
    int Tmp = L, NumOfElems = RightEnd - L + 1;
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

void MergeSort(int A[], int N)
{
    int * tmpArray = new int[N];
    if (tmpArray != nullptr) {
        MSort(A, tmpArray, 0, N - 1);
        delete [] tmpArray;
    }
    else {
        cout << "Not Enough Space\n";
        exit(1);
    }
}

void MergeSort_Iterative(int A[], int N)
{
    int * tmpArray = new int[N];
    if (tmpArray != nullptr) {
        int length = 1;
        while (length < N) {
            Merge_Pass(A, tmpArray, N, length);
            length *= 2;
            Merge_Pass(tmpArray, A, N, length);
            length *= 2;
        }
        delete [] tmpArray;
    }
    else {
        cout << "Not Enough Space\n";
        exit(1);
    }
}