#include <iostream>

using namespace std;
// #define DEBUG
struct TreeNode {
    int element;
    struct TreeNode * left;
    struct TreeNode * right;
    bool flag;

    TreeNode(int elem) {
        element = elem;
        left = nullptr;
        right = nullptr;
        flag = false;
    }
};

typedef TreeNode * Tree;

Tree createTree(int n);
void insert(int elem,Tree & T);
void deleteAll(Tree & T);
void judgeSameTree(int n, int times);
bool atRightPlace(int n, Tree & T);
void resetFlags(Tree & T);
void printTree(Tree & T);

int main() {
    int n,t;
    cin >> n;
    while (n) {
        cin >> t;
        judgeSameTree(n,t);
        cin >> n;
    }
}

Tree createTree(int n) 
{
    Tree T = nullptr;
    while(n--){
        int elem;
        cin >> elem;
        insert(elem, T);
    }
    return T;
}

void insert(int elem, Tree & T) 
{
    if(T == nullptr) {
        T = new TreeNode(elem);
        // T -> element = elem;
        // T -> flag = 0;
        // T -> left = nullptr;
        // T -> right = nullptr;
        return;
    }
    Tree next,prev = T;
    bool leftTree = false;
    if(elem < prev -> element) {
        next = prev -> left;
        leftTree = true;
    }
    else {
        next = prev -> right;
    }
    
    while(next) {
        leftTree = false;
        if(elem < next -> element) {
            prev = next;
            next = next -> left;
            leftTree = true;
        }
        else {
            prev = next;
            next = next -> right;
        }
    }
    if(leftTree) {
        prev -> left = new TreeNode(elem);
    }
    else {
        prev -> right = new TreeNode(elem);
    }
}

void deleteAll(Tree &T) {
    if(T == nullptr) return;
    deleteAll(T -> left);
    deleteAll(T -> right);
    delete T;
}

void judgeSameTree(int n, int times)
{
    Tree T = createTree(n);
#ifdef DEBUG
    cout << "*************************\n";
    cout << "print the tree !" << endl;
    printTree(T);
    cout << "*************************\n";
#endif
    while(times--) {
        bool flag = true;
        int elem;
        for(int i = 0; i < n; i++) {
            cin >> elem;
            if(flag) {
                flag = atRightPlace(elem,T);
            }
        }
        if(flag) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
        resetFlags(T);
    }
    deleteAll(T);
}

bool atRightPlace(int elem, Tree & T) 
{
    if(T == nullptr) {
        return false;
    }
    if(T -> element == elem) {
        T -> flag = true;
        return true;
    }
    else if(T -> flag == false) {
        return false;
    }
    else if (elem < T -> element){
        return atRightPlace(elem, T -> left);
    }
    else {
        return atRightPlace(elem, T -> right);
    }
}

void resetFlags(Tree & T)
{
    if(T == nullptr) {
        return;
    }
    T -> flag = false;
    resetFlags(T -> left);
    resetFlags(T -> right);
}

void printTree(Tree & T)
{
    if(T == nullptr) {
        return;
    }
    printTree(T -> left);
    cout << T -> element << " " << endl;
    printTree(T -> right);
}