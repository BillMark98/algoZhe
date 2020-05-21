#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <memory>
#include <vector>
using namespace std;
#define MAXSIZE 64
#define VALUEMAX 630000
struct Heap;
typedef struct TreeNode {
    char symbol;
    int weight;
    bool leaf;
    // TreeNode * leftNode;
    // TreeNode * rightNode;
    // TreeNode * parentNode;
    shared_ptr<TreeNode> leftNode;
    shared_ptr<TreeNode> rightNode;
    shared_ptr<TreeNode> parentNode;
    int codeBranch;
    bool setCode;
    TreeNode(char _symb, int _weig) : symbol(_symb), weight(_weig), leaf(true), leftNode(nullptr),rightNode(nullptr),parentNode(nullptr),setCode(false) {}
    TreeNode() : symbol('?'), weight(0),leaf(false),leftNode(nullptr),rightNode(nullptr),parentNode(nullptr), setCode(false){}
    TreeNode(int _weig) : symbol('?'), weight(_weig),leaf(false),leftNode(nullptr),rightNode(nullptr),parentNode(nullptr),setCode(false){}
    TreeNode(shared_ptr<TreeNode> & ptr)  : leftNode(nullptr),
        rightNode(nullptr)
    {
        if(ptr == nullptr)
            return;
    
        symbol = ptr -> symbol;
        weight = ptr -> weight;
        leaf = ptr -> leaf;
        
        
        if(ptr -> leftNode != nullptr) {
            leftNode.reset(new TreeNode(ptr -> leftNode));
            leftNode -> parentNode.reset(this);
        }
        if(ptr -> rightNode != nullptr) {
            rightNode.reset(new TreeNode(ptr -> rightNode));
            rightNode -> parentNode.reset(this);
        }
        
        // leftNode = nullptr;
        // rightNode = nullptr;
        // parentNode = nullptr;
        setCode = false;
    }

    TreeNode(shared_ptr<TreeNode> & ptr, map<char, 
        shared_ptr<TreeNode> > & codeMap) : leftNode(nullptr),
        rightNode(nullptr)
    {
        if(ptr == nullptr)
            return;
    
        symbol = ptr -> symbol;
        weight = ptr -> weight;
        leaf = ptr -> leaf;
        if(ptr -> leftNode != nullptr) {
            leftNode.reset(new TreeNode(ptr -> leftNode));
            leftNode -> parentNode.reset(this);
        }
        if(ptr -> rightNode != nullptr) {
            rightNode.reset(new TreeNode(ptr -> rightNode));
            rightNode -> parentNode.reset(this);
        }
        // leftNode = nullptr;
        // rightNode = nullptr;
        // parentNode = nullptr;
        setCode = false;
        if(isLeaf()) {
            codeMap[symbol].reset(this);
        }
    }
    // void operator=(const TreeNode & tr) {
    //     if(ptr == nullptr)
    //         return;
    
    //     symbol = ptr -> symbol;
    //     weight = ptr -> weight;
    //     leaf = ptr -> leaf;
    //     leftNode.reset(new TreeNode(tr.leftNode));
    //     rightNode.reset(new TreeNode(tr.rightNode));
    //     leftNode -> parentNode.reset(this);
    //     rightNode -> parentNode.reset(this);
    //     // leftNode = nullptr;
    //     // rightNode = nullptr;
    //     // parentNode = nullptr;
    //     setCode = false;
    // }

    bool operator < (const TreeNode & t2) {
        return weight < t2.weight;
    }
    bool operator > (const TreeNode & t2) {
        return weight > t2.weight;
    }
    bool operator <= (const TreeNode & t2) {
        return weight <= t2.weight;
    }
    bool operator >= (const TreeNode & t2) {
        return weight >= t2.weight;
    }
    bool operator == (const TreeNode & t2) {
        return weight == t2.weight;
    }
    bool setValue(int _code) {
        if(setCode) {
            if(_code != codeBranch) {
                return false;
            }
            else {
                return true;
            }
        }
        codeBranch = _code;
        setCode = true;
        return true;
    }

    bool isLeaf() {
        return (leftNode == nullptr) && (rightNode == nullptr);
    }
}TreeNode;

typedef shared_ptr<TreeNode> HuffmanTree;
typedef shared_ptr<HuffmanTree> HuffmanTreePtr;
typedef shared_ptr<HuffmanTree[]> HuffmanTreeArrPtr;
typedef shared_ptr<Heap> HeapPtr;
// HuffmanTree Heap[MAXSIZE];
typedef map<char, HuffmanTree > mapCodeType;
typedef map<HeapPtr, HuffmanTree> mapHeapTrees;
typedef vector<HeapPtr> vecHeap;

typedef vector<HuffmanTree> vecHuffmanTree;
typedef pair<char,string> codingScheme;
typedef vector<codingScheme> codeTable;
int HeapSize;
typedef struct Heap {
    int sizeHeap;
    shared_ptr<HuffmanTree[]> elementArr;
    // HuffmanTree * elementArr;
    mapCodeType codeMap;
    Heap(int _N) {
        // elementArr = new HuffmanTree [_N + 1];
        HeapSize = _N;
        elementArr.reset(new HuffmanTree[_N + 1]);
        sizeHeap = 0;
    }

    Heap(const Heap & hp) {
        sizeHeap = hp.sizeHeap;
        elementArr.reset(new HuffmanTree[HeapSize + 1]);
        // elementArr = new HuffmanTree [sizeHeap + 1];
        for(int index = 1; index <= sizeHeap; index++) {
            elementArr[index].reset(new TreeNode(hp.elementArr[index],codeMap));
        }
    }
}Heap;



// int sizeHeap;

void createHeap(int _N, vecHeap & vHeap);

void readData(int _N,vecHeap & vHeap, mapHeapTrees & mHT);

void insert(HuffmanTree & T, int & _index, 
    vecHeap & vHeap, mapHeapTrees & mHT);

HuffmanTree deleteMin(int & _index, vecHeap & vHeap, mapHeapTrees & mHT);

void createHuffman(int _N, vecHeap & vHeap, 
    mapHeapTrees & mHT, vecHuffmanTree & vecH);

void deleteHuffman(HuffmanTree T);

bool isEmpty(HeapPtr);

bool isRoot(HuffmanTree & T);

void clearFlag(HuffmanTree & T);


bool codeValid(vecHuffmanTree & vecH, vecHeap & vHeap, int & _N);

bool setCode(HuffmanTree & T,string & code);

int main() 
{
    int _N;
    cin >> _N;

    vecHeap vHeap;
    mapHeapTrees mHT;
    vecHuffmanTree vecH;
    createHuffman(_N,vHeap,mHT,vecH);
    int _M;
    cin >> _M;
    bool flag[_M];
    int count = _M;
    while(_M--) {
        flag[_M] = codeValid(vecH, vHeap,_N);
    }
    for(int i = 0; i < count; i++) {
        if(flag[i]) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No\n";
        }
    }
    // deleteHuffman(T);
}


void createHeap(int _N, vecHeap & vHeap)
{
    HeapPtr hNew(new Heap(_N));
    vHeap.push_back(hNew);
}

void readData(int _N, vecHeap & vHeap, mapHeapTrees & mHT)
{
    char _symb;
    int _weig;
    while(_N--) {
        // think should extract the whitespace  
        cin >> _symb >> _weig;
        // each loop may enlarge the vHeap, but due to the insert
        // mechanism, the new created Heap already have the T HuffmanTree coppied,
        // so dont need to concern it in this loop, so instead of index < vHeap.size() at the
        // condition of the for-loop
        int _len = vHeap.size();
        for(int index = 0; index < _len; index++) {
            HuffmanTree T(new TreeNode(_symb, _weig));
            vHeap[index] -> codeMap[_symb] = T;
            insert(T,index,vHeap,mHT);
        }     
    }
}

void insert(HuffmanTree & T, int & _index, 
    vecHeap & vHeap, mapHeapTrees & mHT)
{
    int index;
    HeapPtr pHeap = vHeap[_index];
    HuffmanTreeArrPtr pHuff = pHeap -> elementArr;
    for(index = (pHeap -> sizeHeap) + 1;(index >= 2) && (*(pHuff[index/2]) >= *T); index /= 2) {
        if(((pHuff[index/2]) != nullptr) && (*pHuff[index/2]) == *T) {
            // int _len = pHeap -> sizeHeap;
            HeapPtr newHeap(new Heap(*pHeap));
            // newHeap ->elementArr[1] = pHeap -> elementArr[1];
            // int parent = 1, child = 2;
            // for(child = 2; child <= _len; child++) {
            //     newHeap -> elementArr[i] = pHeap -> elementArr[i];
            //     newHeap -> elementArr[parent] -> 
            // }
            
            // the new Heap's HuffmanTree array stops here
            newHeap -> elementArr[index].reset(new TreeNode(T, newHeap -> codeMap));
            newHeap -> sizeHeap++;
            vHeap.push_back(newHeap);
            // find the brother
            int tempFather = index / 2;
            int brother;
            if(index % 2 == 0) {
                brother = tempFather * 2 + 1;
            }
            else {
                brother = tempFather * 2;
            }
            // if brother and this equal, change the two
            // by induction, we see that we only need to change 
            // the two at this level and do not need to consider the lower level
            if(brother <= (pHeap -> sizeHeap) && *(pHuff[brother]) == *T) {
                HeapPtr new2Heap(new Heap(*pHeap));
                HuffmanTreeArrPtr new2Huff = new2Heap -> elementArr;
                new2Huff[index] = new2Huff[brother];

                // the same proble
                new2Huff[brother].reset(new TreeNode(T,new2Heap -> codeMap));
                vHeap.push_back(new2Heap);
            }
        }
        pHuff[index] = pHuff[index/2];
    }
    pHuff[index] = T;
    pHeap -> sizeHeap++;
}

HuffmanTree deleteMin(int & _index, vecHeap & vHeap, 
    mapHeapTrees & mHT) 
{
    if(_index > (int)vHeap.size()) {
        cout << "the index larger than the vHeap len";
        return nullptr;
    }
    if(isEmpty(vHeap[_index])) {
        cout << "the heap is empty cant delete\n";
        return nullptr;
    }

    int parent, child;
    HeapPtr hpt = vHeap[_index];
    HuffmanTreeArrPtr pHuff = hpt -> elementArr;
    HuffmanTree temp = pHuff[hpt -> sizeHeap--];
    HuffmanTree minTree = pHuff[1];
    int endIndex = hpt -> sizeHeap;
    for(parent = 1; parent * 2 <= endIndex; parent = child) {
        child = parent * 2;
        if(child != endIndex && (pHuff[child + 1] < pHuff[child])) {
            child++;
        }
        if(*temp < pHuff[child]) {
            break;
        }
        // since by insertion, we make sure we cover all the possible heaps
        // so by deletion, we could just use one case,
        // the child will change to his brother (if he exists) iff brother is strict smaller
        // and the loop stops beforehand iff *temp is strict smaller than the current son


        // else {
        //     if(*temp == pHuff[child]) {
                
        //     }
        //     Heap[parent] = Heap[child];
        // }
        pHuff[parent] = pHuff[child];
    }
    pHuff[parent] = temp;
    return minTree;
}

void createHuffman(int _N, vecHeap & vHeap, 
    mapHeapTrees & mHT, vecHuffmanTree & vecH)
{

    createHeap(_N,vHeap);
    readData(_N, vHeap, mHT);
    
    for(int index = 0; index < (int)vHeap.size(); index++) {
        HuffmanTree T;
        while(vHeap[index] -> sizeHeap != 1) {
            T.reset(new TreeNode());
            T -> leftNode = deleteMin(index, vHeap,mHT);
            T -> rightNode = deleteMin(index, vHeap,mHT);
            T -> leftNode -> parentNode = T;
            T -> rightNode -> parentNode = T;
            T -> weight = T -> leftNode -> weight + T -> rightNode -> weight;
            insert(T, index, vHeap, mHT);
        }
        T = deleteMin(index,vHeap,mHT);
        vecH.push_back(T);
    }
}

void deleteHuffman(HuffmanTree T)
{
    // if(T == nullptr) {
    //     return;
    // }
    // deleteHuffman(T -> leftNode);
    // deleteHuffman(T -> rightNode);
    // delete T;
    // return;
}

bool isEmpty(HeapPtr hp)
{
    return hp -> sizeHeap == 0;
}

bool isRoot(HuffmanTree & T)
{
    if(T == nullptr) {
        cout << "an empty tree!\n";
        return false;
    }
    return T -> parentNode == nullptr;
}

void clearFlag(HuffmanTree & T)
{
    if(T == nullptr) {
        return;
    }
    clearFlag(T -> leftNode);
    clearFlag(T -> rightNode);
    T -> setCode = false;
}

bool codeValid(vecHuffmanTree & vecH, vecHeap & vHeap, int & _N)
{
    char symb;
    string code;
    bool valid = true;
    int numAlpha = _N;
    codeTable cT;
    cT.resize(_N);
    while(_N--) {
        cin >> symb >> code;
        cT[_N].first = symb;
        cT[_N].second = code;
    }
    for(int index = 0; index < (int)vecH.size(); index++) {
        valid = true;
        for(int j = 0; j < numAlpha; j++) {
            if(valid) {
                symb = cT[j].first;
                code = cT[j].second;
                HuffmanTree leafTree = vHeap[index] -> codeMap[symb];
                reverse(code.begin(), code.end());
                valid = setCode(leafTree,code);
            }
            else {
                clearFlag(vecH[index]);
                break;
            }
        }
    }
    return valid;
}

bool setCode(HuffmanTree & T,string & code)
{
    int _len = code.length();
    int index = 0;
    HuffmanTree parentNode;
    while(!isRoot(T)) {
        parentNode = T -> parentNode;
        int val = code[index] - '0';
        if(!T -> setValue(val)) {
            return false;
        }
        parentNode -> rightNode -> setValue(1 - val);
        T = parentNode;
        index++;
        // code is invalid
        if(index > _len) {
            return false;
        }
    }
    if(index < _len) {
        return false;
    }
    else {
        return true;
    }
}