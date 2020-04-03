#include <iostream>
using namespace std;
void MaxSequencePivot(int n, int arr[]);

int main() {
    int len;
    cin >> len;
    int arr[len];
    for(int index = 0; index < len; index++) {
        cin >> arr[index];
    }
    MaxSequencePivot(len, arr); 
    return 0;
}

void MaxSequencePivot(int n, int arr[]) {
    int MaxSum = 0;
    int TempSum = 0;
    int i = 0, j = n - 1;
    int tempLeft = 0;
    // , tempRight = 0;
    bool maxModified = false;
    for (int index = 0; index < n; index++) {
        TempSum += arr[index];
        // have to consider the case that all entries non positive
        // e.g -1 -1 0 0 -3 have to give 0 0 0 as output
        // so have to use a flag to test whether the MaxSum is modified or not
        // if not and TempSum == 0 it means that the sum 0 can be reached (not that all entries are negative thus maxSum 
        // is defined to be 0)
        // and if TempSum > MaxSum that means a positive value is reached and set the flag to be true
        // in case that if tempSum == 0 and the corresponding indices will be set to point the sequence where sum = 0 instead of a positive number
        if(!maxModified && TempSum == 0) {
            maxModified = true;
            i = tempLeft;
            j = index;
        }
        if (TempSum > MaxSum) {
            maxModified = true;
            MaxSum = TempSum;
            i = tempLeft;
            j = index;
        }
        else if (TempSum < 0) {
            TempSum = 0;
            tempLeft = index + 1;
            // tempRight = index + 1;
        }
    }
    cout << MaxSum << " " << arr[i] << " " << arr[j] << endl;
}