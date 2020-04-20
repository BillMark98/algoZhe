#include <stdio.h>
#define MaxTree 10
#define Element char
#define Tree int
// #define NodeIndex int
#define Null -1
#define DEBUG
typedef struct node {
    Element element;
    Tree left;
    Tree right;
}Node;

Node T1[MaxTree];
Node T2[MaxTree];

Tree BuildTree(Node * T);
int Isomorphic(Tree r1, Tree r2);


int main() {
    Tree R1, R2;
// #ifdef DEBUG
//     printf("the address of T1[0] is %d\n", &T1[0].element);
// #endif
    R1 = BuildTree(T1);
#ifdef DEBUG
    printf("R1 is : %d", R1);
#endif    
    R2 = BuildTree(T2);
#ifdef DEBUG
    printf("R2 is : %d", R2);
#endif    
#ifdef DEBUG
    printf("R1, R2 calculated successfully\n");
#endif
    if(Isomorphic(R1,R2)) printf("Yes\n");
    else {
        printf("No\n");
    }

    // int N;
    // scanf("%d", &N);
    // int check[N];
    // check[0] = 1;
    // check[1] = 2;
    // printf("%d %d\n",check[0],check[1]);
}

Tree BuildTree(Node * T) 
{
    int N;
    scanf("%d\n",&N);
#ifdef DEBUG
    printf("scanned N successfully\n");
#endif
    if(N) {
        int check[N];
        for(int i = 0; i < N; i++) {
            check[i] = 0;
        }
#ifdef DEBUG
        printf("check initialized successfully\n");
#endif
        char cl,cr;
        for(int i = 0; i < N; i++) {
#ifdef DEBUG
    printf("loop i: %d begins, \n", i);
#endif
            scanf("%c %c %c\n", &T[i].element, &cl, &cr);
#ifdef DEBUG
    printf("scanned successfully \n");
#endif
            if(cl != '-') {
#ifdef DEBUG
    printf("in the left if, yes, \n");
#endif
                T[i].left = cl - '0';
                check[T[i].left] = 1;

            }
            else {
#ifdef DEBUG
    printf("in the left if, no, \n");
#endif
                T[i].left = Null;
            }
            if(cr != '-') {
#ifdef DEBUG
    printf("in the right if, yes, \n");
#endif
                T[i].right = cr - '0';
                check[T[i].right] = 1;
            }
            else {
#ifdef DEBUG
    printf("in the right if, no, \n");
#endif
                T[i].right = Null;
            }
#ifdef DEBUG
    printf("loop i: %d ends, \n", i);
#endif
        }
#ifdef DEBUG
        printf("reading N lines successfully\n");
        printf("begins the check loop for finding root\n\n");
#endif
        for (int i = 0; i < N; i++) {
#ifdef DEBUG
        printf("loop i: \n");
        printf("check[i] ok? :\n");
        check[i];
        printf("ok\n");
#endif
            if(!check[i]) {
                return i;
            }
        }
    }
    else {
        return Null;
    }
}
int Isomorphic(Tree r1, Tree r2) {
    if((r1 == Null) && (r2 == Null)) {
        return 1;
    }
    if(((r1 == Null) && (r2 != Null)) || 
        ((r1 != Null) && (r2 == Null))) {
        return 0;
    }
    if (T1[r1].element != T2[r2].element) {
        return 0;
    }
    if ((T1[r1].left == Null) && (T2[r2].left == Null)) {
        return Isomorphic(T1[r1].right, T2[r2].right);
    }
    if(((T1[r1].left != Null) && (T2[r2].left != Null)) &&
        (T1[T1[r1].left].element == T2[T2[r2].left].element)) {
        return Isomorphic(T1[r1].left,T2[r2].left) && Isomorphic(T1[r1].right, T2[r2].right);
    }
    else {
        return Isomorphic(T1[r1].left, T2[r2].right) && Isomorphic(T1[r1].right,T2[r2].left);
    }
}