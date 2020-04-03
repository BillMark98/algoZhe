#include <iostream>
using namespace std;
int MaxSequence(int n, int arr[]);

int main() {
    int len;
    cin >> len;
    int arr[len];
    for(int index = 0; index < len; index++) {
        cin >> arr[index];
    }
    int result = MaxSequence(len, arr);
    cout << result << endl;
}

int MaxSequence(int n, int arr[]) {
    int MaxSum = 0;
    int TempSum = 0;
    for (int index = 0; index < n; index++) {
        TempSum += arr[index];
        if (TempSum > MaxSum) {
            MaxSum = TempSum;
        }
        else if (TempSum < 0) {
            TempSum = 0;
        }
    }
    return MaxSum;
}