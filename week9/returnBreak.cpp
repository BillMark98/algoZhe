#include <iostream>
using namespace std;
void foo(int thresholdB, int returnB);
int main()
{
    int thresholdB =10,returnB = 14;
    cout << "first threshold\n";
    foo(thresholdB, returnB);

    returnB = 5;
    cout << "first return\n";
    foo(thresholdB,returnB);
}

void foo(int thresholdB, int returnB)
{
    int N = 20;
    for(int i = 0; i < N; i++) {
        if(i == returnB) {
            cout << endl;
            return;
        }
        if(i == thresholdB) {
            cout << endl;
            break;
        }
        cout << i << " ";
    }

    cout << "after break, still in the foo\n";
    return;
}