#include <iostream>
using namespace std;

typedef struct Node {
    int data;
    int balance;
    int height;
    Node * leftNode;
    Node * rightNode;
    Node(int _data) : data(_data), balance(0), height(1),leftNode(nullptr), rightNode(nullptr) {}
}Node;

typedef Node * p_Node;

void insert(p_Node * root, int _data);
void rotateRight(p_Node * root);
void rotateLeft(p_Node * root);
bool isEmpty(const p_Node * root);
void balanceTree(p_Node * root);
void deleteTree(p_Node root);
void printTree(p_Node root);
void initializeTree(p_Node * root);
void readTree(p_Node * root, int _N);
int height(p_Node root);
void update(p_Node * root);
int main() 
{
    int _N;
    cin >> _N;
    p_Node myRoot;
    initializeTree(&myRoot);
    try {
        readTree(&myRoot, _N);
    }
    catch (const char * s) 
    {
        cout << s << endl;
        deleteTree(myRoot);
    }
    catch(...) {
        deleteTree(myRoot);
    }
    
    cout << (myRoot) -> data << endl;
    deleteTree(myRoot);
}

void insert(p_Node * root, int _data)
{
    if(isEmpty(root)) {
        *root = new Node(_data);
        return;
    }
    else if(_data > (*root) -> data) {
        insert(&((*root) -> rightNode), _data);
    }
    else {
        insert(&((*root) -> leftNode), _data);
    }
    update(root);
    balanceTree(root);
}

void rotateRight(p_Node * root)
{
    p_Node leftChild = (*root) -> leftNode;
    (*root) -> leftNode = leftChild -> rightNode;
    leftChild -> rightNode = *root;
    update(root);
    *root = leftChild;
    update(root);

}

void rotateLeft(p_Node * root)
{
    p_Node rightChild = (*root) -> rightNode;
    (*root) -> rightNode = rightChild -> leftNode;
    rightChild -> leftNode = *root;
    update(root);
    *root = rightChild;
    update(root);
}

bool isEmpty(const p_Node * root)
{
    return *root == nullptr;
}

void balanceTree(p_Node * root)
{
    if(abs((*root) -> balance) <= 1) {
        return;
    }
    if((*root) -> balance == 2) {
        if((*root) -> leftNode -> balance < 0 ) {
            rotateLeft(&((*root) -> leftNode));
        }
        rotateRight(root);
    }
    else if((*root) -> balance == -2) {
        if((*root) -> rightNode -> balance > 0) {
            rotateRight(&((*root) -> rightNode));
        }
        rotateLeft(root);
    }
    else {
        throw("balance abs larger than 2 error");
    }
}

void deleteTree(p_Node root)
{
    if(isEmpty(&root)) {
        return;
    }
    deleteTree(root -> leftNode);
    deleteTree(root -> rightNode);
    delete root;
}

void printTree(p_Node root)
{
    if(isEmpty(&root)) {
        return;
    }
    printTree(root -> leftNode);
    cout << root -> data << " ";
    printTree(root -> rightNode);
}

void initializeTree(p_Node * root)
{
    *root = nullptr;
}

void readTree(p_Node * root, int _N)
{
    while(_N--) {
        int _data;
        cin >> _data;
        insert(root, _data);
    }
}

int height(p_Node root)
{
    if(isEmpty(&root)) {
        return 0;
    }
    return root -> height;
}

void update(p_Node * root) 
{
    int leftHeight = height((*root) -> leftNode);
    int rightHeight = height((*root) -> rightNode);
    (*root) -> balance = leftHeight - rightHeight;
    (*root) -> height = max(leftHeight, rightHeight) + 1;
}