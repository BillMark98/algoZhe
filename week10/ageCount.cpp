#include <iostream>
// #include <vector>
using namespace std;

#define VALRANGE 51

void BucketSort(int N);

int main() 
{
    int N;
    cin >> N;
    BucketSort(N);
}

void BucketSort(int N)
{
    int A[VALRANGE];
    for (int i = 0; i < VALRANGE; i++) {
        A[i] = 0;
    }
    int age;
    // vector<int> vecAges;
    while (N--) {
        cin >> age;
        A[age]++;
        // if (A[age] == 1) {
        //     vecAges.push_back(age);
        // }
    }
    for (int i = 0; i < VALRANGE; i++) {
        if (A[i]) {
            cout << i << ":" << A[i] << endl;
        }
    }
}