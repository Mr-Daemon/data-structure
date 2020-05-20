#include<iostream>

using namespace std;


typedef char ElemType;
typedef struct node {
    ElemType data;
    int ltag, rtag;
    struct node *lchild;
    struct node *rchild;
} TBTNode;

void CreateTBTree(TBTNode *&b, char *str) {
    TBTNode *St[50], *p;
    int top = -1, k, j = 0;
    char ch;
    b = NULL;
    ch = str[j];
    while (ch != '\0') {
        switch (ch) {
            case '(':
                top++;
                St[top] = p;
                k = 1;
                break;
            case ')':
                top--;
                break;
            case ',':
                k = 2;
                break;
            default:
                p = new TBTNode;
                p->data = ch;
                p->lchild = p->rchild = NULL;
                if (b == NULL)
                    b = p;
                else {
                    switch (k) {
                        case 1:
                            St[top]->lchild = p;
                            break;
                        case 2:
                            St[top]->rchild = p;
                            break;
                    }
                }
        }
        j++;
        ch = str[j];
    }
}


TBTNode *pre;

void Thread(TBTNode *&p) {
    if (p != NULL) {
        if (pre->rtag == 1)
            pre->rchild = p;


        if ((p->lchild == NULL) && (p->rchild == NULL)) {
            p->lchild = pre;
            p->ltag = 1;
            p->rtag = 1;
            cout << "data:" << p->data << "ltag:" << p->ltag << "rtag:" << p->rtag;
            pre = p;
        }

        if (p->lchild != NULL && p->rchild != NULL) {
            p->ltag = 0;
            p->rtag = 0;
            cout << "data:" << p->data << "ltag:" << p->ltag << "rtag:" << p->rtag;
            pre = p;
            TBTNode *t = p;
            p = p->lchild;
            Thread(p);
            pre = p;
            p = t->rchild;
            Thread(p);

        }


        if (p->lchild != NULL && p->rchild == NULL) {
            p->ltag = 0;
            p->rtag = 1;
            cout << "data:" << p->data << "ltag:" << p->ltag << "rtag:" << p->rtag;
            pre = p;
            p = p->lchild;
            Thread(p);
        }


        if (p->lchild == NULL && p->rchild != NULL) {
            p->ltag = 1;
            p->rtag = 0;
            p->lchild = pre;
            cout << "data:" << p->data << "ltag:" << p->ltag << "rtag:" << p->rtag;
            pre = p;
            p = p->rchild;
            Thread(p);
        }
    }
}


TBTNode *CreateThread(TBTNode *b) {
    TBTNode *root = new TBTNode;
    root->ltag = 0;
    root->rtag = 1;
    root->rchild = b;
    if (b == NULL)
        root->lchild = root;
    else {
        root->lchild = b;
        pre = root;
        Thread(b);
        pre->rchild = root;
        pre->rtag = 1;
        root->rchild = pre;
    }
    return root;
}


int main() {
    char string[] = "A(B(D(,G)),C(E,F))";
    TBTNode *p;
    CreateTBTree(p, string);
    CreateThread(p);
    return 0;
}