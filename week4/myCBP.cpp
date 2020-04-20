#include <iostream>
#include <array>
#include <algorithm>

using namespace std;
typedef struct Item {
    int data;
    bool set;
    Item() : data(-1), set(false) {}
}Item;

// struct {
//     bool operator()(Item & a, Item & b) {
//         return a.data < b.data;
//     }
// } customLess;

#define MAXSIZE 2001
Item dataVec[MAXSIZE];
void readData(int _N);
void setCBP(int _N);
// given integer x, calculate k s.t 2^k <= x < 2^(k + 1)
int get2Pot(int x);
// given k , calculate 2^k
int getPow2(int k);
// given _pivot, _index, set the elements in arr, s.t the subtree at pivot is all set.
void setTree(int _pivot, int & _index, Item * arr, int _N);

int main() {
    // int a = 8;
    // int b = get2Pot(a);
    // int c = getPow2(3);
    // cout << b << endl;
    // cout << c << endl;
    int _N;
    cin >> _N;
    readData(_N);
    setCBP(_N);
}
void readData(int _N)
{
    for(int index = 1; index <= _N; index++) {
        int temp;
        cin >> temp;
        dataVec[index].data = temp;
    }
    sort(dataVec+1, dataVec + _N + 1, [](Item & a, Item & b) {
        return a.data < b.data;
    } );

}

void setCBP(int _N)
{
    Item cbp[_N + 1];
    int _K = get2Pot(_N);
    int innerCount = getPow2(_K) - 1;
    // int _M = _N - innerCount;
    int pivotIndex = innerCount + 1;
    int index = 1;
    for(; pivotIndex > 0; pivotIndex /= 2) {
        setTree(pivotIndex, index, cbp, _N);
    }
    for(int i = 1; i <= _N; i++) {
        cout << cbp[i].data;
        if(i < _N) {
            cout << " ";
        }
    }
}

int get2Pot(int x)
{
    int i = 0;
    while(x /= 2) {
        i++;
    }
    return i;
}

int getPow2(int k)
{
    int i = 1;
    while(k--) {
        i = i << 1;
    }
    return i;
}

void setTree(int _pivot, int & _index, Item * arr, int _N)
{
    if(_pivot > _N) {
        return;
    }
    if(arr[_pivot].set) {
        return;
    }
    setTree(_pivot * 2, _index, arr,_N);
    arr[_pivot].data = dataVec[_index].data;
    arr[_pivot].set = true;
    _index++;

    setTree(_pivot * 2 + 1, _index, arr, _N);
}