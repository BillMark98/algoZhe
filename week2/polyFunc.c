#include <stdio.h>
#include <stdlib.h>

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
typedef struct polyTerm {
    int expo;
    int coeff;
}polyTerm;

typedef struct nodePoly {
    int expo;
    int coeff;
    struct nodePoly * prevNode;
    struct nodePoly * nextNode;
}nodePoly;

typedef nodePoly * ptNode;
// polyTerm * readPoly();
ptNode readPolyList();
// polyTerm * AddPoly(polyTerm * p1, polyTerm * p2);
ptNode addPoly(ptNode p1, ptNode p2);
ptNode multPoly(ptNode p1, ptNode p2);
// polyTerm * MultPoly(polyTerm * p1, polyTerm * p2);
// void printPoly(polyTerm * p1);
void printPolyList(ptNode p);
void initializeList(ptNode * pNode) {
    *pNode = NULL;
}
// void AttachLen(int exp, int cof, ptNode *, int *);
void Attach(int exp, int cof, ptNode *);
void DeleteAll(ptNode *);
// polyTerm popFirst(ptNode *);
_Bool isEmpty(ptNode *);

int main() {
    // polyTerm * p1 = readPoly();
    // polyTerm * p2 = readPoly();
    // polyTerm * p3 = AddPoly(p1,p2);
    // polyTerm * p4 = MultPoly(p1,p2);
    // printPoly(p4);

    ptNode p1 = readPolyList();
    ptNode p2 = readPolyList();
    ptNode p3 = addPoly(p1, p2);
    ptNode p4 = multPoly(p1,p2);
    // printPolyList(p1);
    // printPolyList(p2);
    printPolyList(p4);
    printPolyList(p3);
    DeleteAll(&p1);
    DeleteAll(&p2);
    DeleteAll(&p3);
    DeleteAll(&p4);
    // free(p1);
    // free(p2);
    // free(p3);
    // free(p4);
    return 0;
}

// polyTerm * readPoly() {
//     int N;
//     int exp,cof;
//     scanf("%d", &N);
//     polyTerm * arrPoly = (polyTerm *)malloc(N * sizeof(polyTerm));
//     while(N--) {
//         scanf("%d %d", &cof, &exp);
//         arrPoly[N].coeff = cof;
//         arrPoly[N].expo = exp;
//     }
//     return arrPoly;
// }

// polyTerm * AddPoly(polyTerm * p1, polyTerm * p2) {
//     int n1 = NELEMS(p1);
//     int n2 = NELEMS(p2);
//     polyTerm arr[n1 + n2];
//     int count = 0;
//     int i1 = 0, i2 = 0;
//     while (i1 < n1 && i2 < n2) {
//         if(p1[i1].expo > p2[i2].expo) {
//             arr[count].expo = p1[i1].expo;
//             arr[count].coeff = p1[i1].coeff;
//             i1++;
//         }
//         else if (p1[i1].expo < p2[i2].expo) {
//             arr[count].expo = p2[i2].expo;
//             arr[count].coeff = p2[i2].coeff;
//             i2++;
//         }
//         else {
//             arr[count].expo = p2[i1].expo;
//             arr[count].coeff = p1[i1].coeff + p2[i2].coeff;
//             i1++;
//             i2++;
//         }
//         count++;
//     }
//     for(;i1 < n1; i1++) {
//         arr[count].expo = p1[i1].expo;
//         arr[count].coeff = p1[i1].coeff;
//         count++;
//     }
//     for(;i2 < n2;i2++) {
//         arr[count].expo = p2[i2].expo;
//         arr[count].coeff = p2[i2].coeff;
//         count++;
//     }
//     polyTerm * newArray = (polyTerm *) malloc(count * sizeof(polyTerm));
//     for(int i = 0; i < count; i++) {
//         newArray[i].expo = arr[i].expo;
//         newArray[i].coeff = arr[i].coeff;
//     }
//     return newArray;
// }

// polyTerm * MultPoly(polyTerm * p1, polyTerm * p2) {
//     int n1 = NELEMS(p1);
//     int n2 = NELEMS(p2);
//     // int count = 0;
//     // int i1 = 0, i2 = 0;
//     ptNode * pList;
//     int listLen = 0;
//     initializeList(pList);
//     for(int jp2 = 0; jp2 < n2; jp2++) {
//         for(int jp1 = 0; jp1 < n1; jp1++) {
//             int exp = p1[jp1].expo + p2[jp2].expo;
//             int cof = p1[jp1].coeff * p2[jp2].coeff;
//             AttachLen(exp, cof, pList, &listLen);
//         }
//     }
//     polyTerm * arr = (polyTerm *) malloc(listLen * sizeof(polyTerm));
//     for (int index = 0; index < listLen; index++) {
//         arr[index] = popFirst(pList);
//     }
//     return arr;
// }

// void printPoly(polyTerm * p1) {
//     int len = NELEMS(p1);
//     if (len == 0) {
//         return;
//     }
//     printf("%d %d", p1[0].coeff, p1[0].expo);
//     for(int i = 1; i < len; i++) {
//         printf(" %d %d", p1[i].coeff, p1[i].expo);
//     }
//     printf("\n");
// }

void printPolyList(ptNode p) {
    ptNode scan = p;
    if(scan) {
        printf("%d %d", scan -> coeff, scan -> expo);
        scan = scan -> nextNode;
    }
    else {
        // zero polynomial
        printf("0 0\n");
        return;
    }
    while(scan) {
        printf(" %d %d", scan -> coeff, scan -> expo);
        scan = scan -> nextNode;
    }
    printf("\n");
    return;
}
void Attach(int exp, int cof, ptNode * pNode) {
    if(cof == 0) {
        return;
    }
    if(isEmpty(pNode)) {
        *pNode = (ptNode) malloc(sizeof(nodePoly));
        (*pNode) -> coeff = cof;
        (*pNode) -> expo = exp;
        (*pNode) -> nextNode = NULL;
        (*pNode) -> prevNode = NULL;
        return;
    }
    ptNode scan = * pNode;
    _Bool equalFlag = 0;
    if(scan -> expo < exp) {
        ptNode newNode = (ptNode) malloc(sizeof(nodePoly));
        newNode -> expo = exp;
        newNode -> coeff = cof;
        newNode -> prevNode = NULL;
        newNode -> nextNode = scan;
        scan -> prevNode = newNode;
        *pNode = newNode;
        return;
    }
    else if(scan -> expo == exp) {
        int cofSum = scan -> coeff + cof;
        if(cofSum == 0) {
            ptNode temp = scan;
            scan = scan -> nextNode;
            if(scan) {
                scan -> prevNode = NULL;
            }
            (*pNode) = scan;
            free(temp);
        }
        else {
            scan -> coeff += cof;
            return;
        }
    }
    while ((scan -> nextNode != NULL) && scan -> nextNode -> expo >= exp) {
        if(scan -> nextNode -> expo == exp) {
            equalFlag = 1;
            break;
        }
        scan = scan -> nextNode;
    }
    if (equalFlag) {
        int sumCoeff = scan -> nextNode -> coeff + cof;
        if(sumCoeff == 0) {
            ptNode temp = scan -> nextNode;
            scan -> nextNode = temp -> nextNode;
            if(temp -> nextNode) {
                temp -> nextNode -> prevNode = scan;
            }
            free(temp);
        }
        else {
            scan -> nextNode -> coeff += cof;
        }
        return;
    }
    else {
        ptNode newNode = (ptNode) malloc(sizeof(nodePoly));
        newNode -> expo = exp;
        newNode -> coeff = cof;
        newNode -> prevNode = scan;
        newNode -> nextNode = scan -> nextNode;
        if (scan -> nextNode) {
            scan -> nextNode -> prevNode = newNode;
        }
        scan -> nextNode = newNode;
        return;
    }
}
void AttachLen(int exp, int cof, ptNode * pNode, int * len) {
    if(isEmpty(pNode)) {
        *pNode = (ptNode) malloc(sizeof(nodePoly));
        (*pNode) -> coeff = cof;
        (*pNode) -> expo = exp;
        (*pNode) -> nextNode = NULL;
        (*pNode) -> prevNode = NULL;
        len++;
        return;
    }
    ptNode scan = * pNode;
    _Bool equalFlag = 0;
    if(scan -> expo < exp) {
        ptNode newNode = (ptNode) malloc(sizeof(nodePoly));
        newNode -> expo = exp;
        newNode -> coeff = cof;
        newNode -> prevNode = NULL;
        newNode -> nextNode = scan;
        scan -> prevNode = newNode;
        *pNode = newNode;
        len++;
        return;
    }
    while ((scan -> nextNode != NULL) && scan -> nextNode -> expo >= exp) {
        if(scan -> nextNode -> expo == exp) {
            equalFlag = 1;
            break;
        }
        scan = scan -> nextNode;
    }
    if (equalFlag) {
        scan -> nextNode -> coeff += cof;
        return;
    }
    else {
        ptNode newNode = (ptNode) malloc(sizeof(nodePoly));
        newNode -> expo = exp;
        newNode -> coeff = cof;
        newNode -> prevNode = scan;
        newNode -> nextNode = scan -> nextNode;
        scan -> nextNode = newNode;
        len++;
        return;
    }
}
void DeleteAll(ptNode * pNode) {
    if(isEmpty(pNode)) {
        return;
    }
    ptNode scan = *pNode;
    while (scan) {
        ptNode temp = scan;
        scan = scan -> nextNode;
        free(temp);
    }
}

_Bool isEmpty(ptNode * pt) {
    return *pt == NULL;
}

polyTerm popFirst(ptNode * pNode) {
    if (isEmpty(pNode)) {
        printf("list is empty cant pop\n");
        exit(1);
    }
    polyTerm p1;
    ptNode scan = (*pNode);
    p1.coeff = scan ->coeff;
    p1.expo = scan -> expo;
    (*pNode) = scan -> nextNode;
    free(scan);
    return p1;
}

ptNode readPolyList() {
    int N;
    int exp,cof;
    if(!scanf("%d", &N)) {
        printf("error");
    }
    ptNode Node;
    initializeList(&Node);
    while(N--) {
        if(!scanf("%d %d", &cof, &exp)) {
            printf("error");
        }
        Attach(exp,cof,&Node);
    }
    return Node;
}

ptNode addPoly(ptNode p1, ptNode p2) {
    ptNode pAdd;
    initializeList(&pAdd);
    ptNode s1 = p1;
    ptNode s2 = p2;
    while(s1 && s2) {
        if((s1) -> expo > (s2) -> expo) {
            Attach((s1) -> expo, (s1) -> coeff, &pAdd);
            s1 = s1 -> nextNode;
        }
        else if((s2) -> expo > (s1) -> expo) {
            Attach((s2) -> expo, (s2) -> coeff, &pAdd);
            s2 = s2 -> nextNode;
        }
        else {
            Attach((s2) -> expo, (s1) -> coeff + (s2) -> coeff, &pAdd);
            s1 = s1 -> nextNode;
            s2 = s2 -> nextNode;
        }
    }
    while(s1) {
        Attach(s1 -> expo, s1 -> coeff, &pAdd);
        s1 = s1 -> nextNode;
    }
    while(s2) {
        Attach(s2 -> expo, s2 -> coeff, &pAdd);
        s2 = s2 -> nextNode;
    }
    return pAdd;
}

ptNode multPoly(ptNode p1, ptNode p2) {
    ptNode pMult;
    initializeList(&pMult);
    ptNode s1 = p1;
    while(s1) {
        ptNode s2 = p2;
        while(s2) {
            int cof = s1 -> coeff * s2 -> coeff;
            int exp = s1 -> expo + s2 -> expo;
            Attach(exp, cof, &pMult);
            s2 = s2 -> nextNode;
        }
        s1 = s1 -> nextNode;
    }
    return pMult;
}