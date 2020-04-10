#include <iostream>
#include <iomanip>
#include <map>
#include <string>
using namespace std;
struct Item {
    int address;
    // string address;
    int data;
    int nextAddress;
    // string nextAddress;
    int nextIndex;
    int prevIndex;

    Item():address(0),data(0),nextAddress(0),nextIndex(-1),prevIndex(-1){}
    Item(int addr, int dat, int nextAddr) : 
        address(addr), data(dat), nextAddress(nextAddr) {
            nextIndex = prevIndex = -1;
    }
    //  Item():address("0"),data(0),nextAddress("0"),nextIndex(-1),prevIndex(-1){}
    // Item(string addr, int dat, string nextAddr) : 
    //     address(addr), data(dat), nextAddress(nextAddr) {
    //         nextIndex = prevIndex = -1;
    // }
    void setValue(int addr, int dat, int nextAddr) {
        address = addr;
        data = dat;
        nextAddress = nextAddr;
    }
};

void reverseList();
int main() {
    reverseList();
    // std::cout << std::setfill('0') << std::setw(5) << 25 << " " << 24;
}

void reverseList()
{
    int initialAddress,N,K;
    cin >> initialAddress >> N >> K;
    Item nodeArr[N];
    int rootIndex;
    map<int,int> keyMap;
    for(int index = 0; index < N; index++) {
        int addr, data, nAddr;
        cin >> addr >> data >> nAddr;
        nodeArr[index].setValue(addr,data,nAddr);
        keyMap[addr] = index;
        if(addr == initialAddress) {
            rootIndex = index;
        }
    }

    // connecting "dots"
    // kIndex: the initial index at the k-length reversed list
    // kp1Index: the nextIndex to the kIndex in the original array
    int kIndex,count, index,kp1Index;
    for(count = 0, index = rootIndex, kIndex = rootIndex; count < N; count++) {
        int nIndex;
        if(count < N - 1) {
            int addr = nodeArr[index].nextAddress;
            nIndex = keyMap[addr];
            nodeArr[index].nextIndex = nIndex;
            // if index points not the to next to the last element
            nodeArr[nIndex].prevIndex = index;
        }
        else {
            nIndex = -1;
        }
        if(count < K) {
            kIndex = index;
            if(count == K-1) {
                kp1Index = nIndex;
            }
        }
        index = nIndex;
    }


    int tempIndex, kCount;
    for(tempIndex = kIndex, count = 0, kCount = 0; count < N; count++) {
        if(count < K - 1) {
            cout << setfill('0') <<setw(5) <<  nodeArr[tempIndex].address << " " << nodeArr[tempIndex].data << " "<< setfill('0') <<setw(5) << nodeArr[nodeArr[tempIndex].prevIndex].address << endl;
            tempIndex = nodeArr[tempIndex].prevIndex;
        }
        else if(count == K - 1) {
            if(count != N - 1) {
                cout << setfill('0') <<setw(5) <<  nodeArr[rootIndex].address << " " << nodeArr[rootIndex].data << " "<< setfill('0') <<setw(5) <<  nodeArr[kp1Index].address << endl;
            }
            else {
                cout << setfill('0') <<setw(5) <<  nodeArr[rootIndex].address << " " << nodeArr[rootIndex].data << " "<< -1 << endl;
            }
            tempIndex = kp1Index;
        }
        else {
            if(count != N - 1) {
                cout << setfill('0') <<setw(5) <<  nodeArr[tempIndex].address << " " << nodeArr[tempIndex].data << " " << setfill('0') <<setw(5) << nodeArr[tempIndex].nextAddress << endl;
            }
            else {
                cout << setfill('0') <<setw(5) << nodeArr[tempIndex].address << " " << nodeArr[tempIndex].data << " " << -1 << endl;
            }
            tempIndex = nodeArr[tempIndex].nextIndex;
        }
    }
    return;
}