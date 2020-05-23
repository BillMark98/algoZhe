#include <iostream>
#include <vector>

using namespace std;

int _HashTableSize;
struct Node
{
    int _value;
    int _index;
    int _aughtIndex;
    // vector<int> _dependencyVec;
    
    Node(int value, int index): _value(value), _index(index)
    {
        _aughtIndex = value % _HashTableSize;
        if (_aughtIndex != index) {
            int len = _aughtIndex - index > 0 ? _aughtIndex - index : _aughtIndex + _HashTableSize - index;
            // _dependencyVec.resize(len);
            for (int i = 0; i < len; i++) {
                // _dependencyVec[i] = index + i % _HashTableSize;
            }
        }
    }

    Node(): _value(0),_index(-1),_aughtIndex(-2)
    {

    }

    void setValueIndex(int value, int index,
        vector<vector<int>> & ChildNodeVec,
         vector<int> & InDegree, vector<Node> & arrayNode)
    {
        _value = value;
        _index = index;
        if (value < 0) {
            return;
        }
        _aughtIndex = value % _HashTableSize;
        if (_aughtIndex != index) {
            int len = _index - _aughtIndex > 0 ? _index - _aughtIndex : _index + _HashTableSize - _aughtIndex;
            // _dependencyVec.resize(len);

            for (int i = 0; i < len; i++) {
                // _dependencyVec[i] = index + i % _HashTableSize;
                int tempIndex = (_aughtIndex + i) % _HashTableSize;
                if (arrayNode[tempIndex]._value < 0) {
                    continue;
                }
                ChildNodeVec[(_aughtIndex + i) % _HashTableSize].push_back(_index);
                InDegree[_index]++;
            }
        }           
    }

    bool operator<(const Node & n1) 
    {
        return _value < n1._value;
    }

    bool operator<=(const Node & n1)
    {
        return _value <= n1._value;
    }

    // if the node is entered into the hash table without collision
    bool isHitFirstTime() const
    {
        return _aughtIndex == _index;
    }
};

struct MinHeap
{
    int _sizeHeap;
    vector<Node *> _arrayPtrNode;
    MinHeap()
    {
        _sizeHeap = 0;
        _arrayPtrNode.resize(_HashTableSize + 1);
    }

    void insert(Node * ptrNd)
    {
        int index;
        for (index = ++_sizeHeap; index >= 2 && (*ptrNd) < *(_arrayPtrNode[index/2]); index /= 2) {
            _arrayPtrNode[index] = _arrayPtrNode[index/2];
        }
        _arrayPtrNode[index] = ptrNd;
    }

    Node * deleteMin()
    {
        int parent,child;
        Node * ptrMin = _arrayPtrNode[1];
        Node * tempPtr = _arrayPtrNode[_sizeHeap--];
        for (parent = 1; parent * 2 <= _sizeHeap; parent = child) {
            child = parent * 2;
            if (child < _sizeHeap && (*_arrayPtrNode[child + 1]) < (*_arrayPtrNode[child])) {
                child++;
            }
            if (*tempPtr <= (*_arrayPtrNode[child])) {
                break;  
            }
            _arrayPtrNode[parent] = _arrayPtrNode[child];
        }
        _arrayPtrNode[parent] = tempPtr;
        return ptrMin;
    }

    bool isEmpty() const
    {
        return _sizeHeap == 0;
    }
};

struct HashTable
{
    vector<Node> _arrayNode;
    vector<vector<int>> _ChildNodeVec;

    vector<int> _InDegree;

    MinHeap myHeap;
    HashTable(int N)
    {
        _arrayNode.resize(_HashTableSize);
        _ChildNodeVec.resize(_HashTableSize);
        _InDegree.resize(_HashTableSize);

        int value;
        for (int i = 0; i < N; i++) {
            cin >> value;
            _arrayNode[i].setValueIndex(value,i, _ChildNodeVec,_InDegree, _arrayNode);
            if (_arrayNode[i].isHitFirstTime()) {
                myHeap.insert(&_arrayNode[i]);
            }
        }
    }

    void getOriginInput()
    {
        int count = 0;
        while (!myHeap.isEmpty()) {
            Node * nptr = myHeap.deleteMin();
            vector<int> & vecChildNode =_ChildNodeVec[nptr -> _index];
            int len = vecChildNode.size();
            for (int i = 0; i < len; i++) {
                int index = vecChildNode[i];
                // in case some -1 value will be processed
                if (index < 0) 
                    continue;
                _InDegree[index]--;
                if (_InDegree[index] == 0) {
                    myHeap.insert(&(_arrayNode[index]));
                }
            }
            if (count != 0) {
                cout << " ";
            }
            count++;
            cout << nptr -> _value;
        }
        cout << endl;
    }
};

int main()
{
    int N;
    cin >> N;
    _HashTableSize = N;
    HashTable ht(N);
    ht.getOriginInput();
}