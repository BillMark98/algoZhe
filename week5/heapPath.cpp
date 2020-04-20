#include <iostream>
using namespace std;
#define MAXSIZE 1001
#define MIN -10001

int H[MAXSIZE],HeapSize;
void createHeap();
// insert an item to the heap
void insert(int i);
// print the path from i to the root
void printPath(int i);

int main() 
{
    int n,m;
    cin >> n >> m;
    createHeap();
    while(n--) {
        int temp;
        cin >> temp;
        insert(temp);
    }
    while(m--) {
        int elem;
        cin >> elem;
        printPath(elem);
    }
    return 0;
}

void createHeap()
{
    HeapSize = 0;
    H[0] = MIN;
}

void insert(int elem)
{
    int index;
    for(index = ++HeapSize;H[index/2] > elem; index /= 2) {
        H[index] = H[index/2];
    }
    H[index] = elem;
}
// print the path from i to the root
void printPath(int i)
{
    for(; i > 1; i /= 2) {
        cout << H[i] << ' ';
    }
    cout << H[i] << endl;
}