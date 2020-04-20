#include <iostream>
#include <algorithm>

using namespace std;

const int SIZE = 7;

int main()
{
    int intArray[SIZE] = {5, 3, 32, -1, 7, 104, 53};

    //Now we call the sort function
    sort(intArray + 1, intArray + 5, [](int & a, int & b) {
        return a > b;
    });

    cout << "Sorted Array looks like this." << endl;
    for (size_t i = 0; i != SIZE; ++i)
        cout << intArray[i] << " ";
    cout << endl;
    return 0;
}