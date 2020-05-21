#include <memory>
#include <iostream>
#include <map>
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
    TreeNode(shared_ptr<TreeNode> & ptr) {
        if(ptr == nullptr)
            return;
    
        symbol = ptr -> symbol;
        weight = ptr -> weight;
        leaf = ptr -> leaf;
        cout << "\n*******\nin the copy func\n";
        if(ptr -> leftNode == nullptr) {
            cout << "ptr -> leftNode is nullptr" << endl;
        }

        leftNode.reset(new TreeNode(ptr -> leftNode));
        rightNode.reset(new TreeNode(ptr -> rightNode));
        if(leftNode != nullptr) {
            leftNode -> parentNode.reset(this);
            cout << "this -> leftNode is not nullptr\n";
        }
        if(rightNode != nullptr) {
            rightNode -> parentNode.reset(this);
        }
        // leftNode = nullptr;
        // rightNode = nullptr;
        // parentNode = nullptr;
        setCode = false;
        cout << "bye copy\n\n";
    }

    TreeNode(shared_ptr<TreeNode> & ptr, map<char, shared_ptr<TreeNode> > & codeMap) {
        if(ptr == nullptr)
            return;
    
        symbol = ptr -> symbol;
        weight = ptr -> weight;
        leaf = ptr -> leaf;
        if(ptr -> leftNode == nullptr) {
            cout << "ptr -> leftNode is nullptr" << endl;
        }
        leftNode.reset(new TreeNode(ptr -> leftNode));
        rightNode.reset(new TreeNode(ptr -> rightNode));
        if(leftNode != nullptr) {
            leftNode -> parentNode.reset(this);
            cout << "this -> leftNode is not nullptr\n";
        }
        if(rightNode != nullptr) {
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

// HuffmanTree Heap[MAXSIZE];
typedef map<char, HuffmanTree > mapCodeType;
typedef map<Heap*, HuffmanTree> mapHeapTrees;
typedef vector<Heap*> vecHeap;

typedef struct Heap {
    int sizeHeap;
    shared_ptr<HuffmanTree[]> elementArr;
    // HuffmanTree * elementArr;
    mapCodeType codeMap;
    Heap(int _N) {
        // elementArr = new HuffmanTree [_N + 1];
        elementArr.reset(new HuffmanTree[_N + 1]);
        sizeHeap = 0;
    }

    Heap(const Heap & hp) {
        sizeHeap = hp.sizeHeap;
        elementArr.reset(new HuffmanTree[sizeHeap + 1]);
        // elementArr = new HuffmanTree [sizeHeap + 1];
        for(int index = 1; index <= sizeHeap; index++) {
            elementArr[index].reset(new TreeNode(hp.elementArr[index]));
        }
    }
}Heap;

int main() 
{
    // unique_ptr<int> ptr(nullptr);
    // if(ptr == nullptr) {
    //     cout << "Yes" << endl;
    // }
    // HuffmanTree t1(new TreeNode('a',1));
    // HuffmanTree t2(t1);
    // if(t2 -> leftNode == nullptr) {
    //     cout << "left tree ok" << endl;
    // }
    // if(t2 -> rightNode == nullptr) {
    //     cout << "right tree ok" << endl;
    // }
    // cout << t2 -> symbol << endl;

    Heap h1(3);
    h1.elementArr[1].reset(new TreeNode('a',1));
    h1.elementArr[2].reset(new TreeNode('b',2));
    h1.elementArr[3].reset(new TreeNode('d',5));
    h1.elementArr[1] -> leftNode = h1.elementArr[2];
    h1.elementArr[1] -> rightNode = h1.elementArr[3];
    h1.sizeHeap = 3;
    Heap h2(h1);
    cout << h2.elementArr[1] -> symbol << endl;
    cout << h2.elementArr[1] -> leftNode -> symbol << endl;


    // Heap h3(4);
    // if(h3.elementArr[1] == nullptr) {
    //     cout << "nullptr yes\n";
    // }
    return 0;
}