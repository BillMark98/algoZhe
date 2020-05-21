#include <iostream>
using namespace std;


void countCycle(int Arr[], int N);


int main()
{
    int N;
    cin >> N;
    int Arr[N];
    for (int i = 0; i < N; i++) {
        cin >> Arr[i];
    }
    countCycle(Arr, N);
}

void countCycle(int Arr[], int N)
{
    int index, nextIndex, cycleLen = 0, cycleNum = 0;
    index = 0;
    if (Arr[0] == 0) {
        cycleNum++;
    }
    while (index < N) {
        if (index == Arr[index]) {
            index++;
            continue;
        }
        int origTemp = index;
        nextIndex = Arr[index];
        Arr[index] = index;
        // cycleLen++;
        while (Arr[nextIndex] != nextIndex) {
            Arr[index] = index;
            cycleLen++;
            index = nextIndex;
            nextIndex = Arr[nextIndex];
        }
        cycleNum++;
        Arr[index] = index;
        index = origTemp + 1;
    }
    int swapNum;
    if (cycleNum > 0) {
        swapNum = cycleLen + 2 * (cycleNum - 1);
    }
    else {
        swapNum = 0;
    }
    cout << swapNum << endl;
}