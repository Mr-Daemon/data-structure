//
// Created by cyb12 on 2020-01-30.
//

#include <cstdlib>
#include <c++/cstdio>
#include <c++/iostream>

template<typename T>
class Matrix {
public:
    struct Node {
        int i, j;
        T e;
        Node *right, *down;
    };
    int row, column, num;
    Node **rHead, **cHead;

    //all node must use this function to generate
    static Node *generateNode(int i, int j, T e) {
        auto node = (Node *) malloc(sizeof(Node));
        *node = {i, j, e, nullptr, nullptr};
        return node;
    }

    void insert(Node *node) {
        //insert node in row list
        auto ptr = rHead[node->i];
        if (!ptr)
            rHead[node->i] = node;
        else {
            auto pre = ptr;
            while (ptr && ptr->j < node->j) {
                pre = ptr;
                ptr = ptr->right;
            }
            if (!ptr || ptr->j > node->j) {
                pre->right = node;
                node->right = ptr;
            } else {//ptr->j==node->j case
                ptr->e += node->e;
                free(node);
                if (!ptr->e) {//if e is 0 after add node->e
                    pre->right = ptr->right;
                    pre = cHead[ptr->j];
                    if (pre == ptr) {
                        cHead[ptr->j] = nullptr;
                        free(ptr);
                    } else {
                        while (pre->down != ptr)
                            pre = pre->down;
                        pre->down = ptr->down;
                        free(ptr);
                    }
                }
                return;
            }
        }
        ptr = cHead[node->j];
        if (!ptr)
            cHead[node->j] = node;
        else {
            auto pre = ptr;
            while (ptr && ptr->i < node->i) {
                pre = ptr;
                ptr = ptr->down;
            }
            pre->down = node;
            node->down = ptr;
        }
    }

    Matrix(int row, int column, Node *list, int num) : row(row), column(column), num(num) {
        rHead = (Node **) calloc(row, sizeof(Node *));
        cHead = (Node **) calloc(column, sizeof(Node *));
        for (int i = 0; i < num; ++i)
            insert(generateNode(list[i].i, list[i].j, list[i].e));
    }

    void print() {
        for (int i = 0; i < row; ++i) {
            auto node = rHead[i];
            for (int j = 0; j < column; ++j) {
                if (node && node->j == j) {
                    std::cout << node->e << " ";
                    node = node->right;
                } else printf("0 ");
            }
            printf("\n");
        }
    }

    Matrix *operator+(const Matrix &matrix) {

    }
};

int main(int argc, char const *argv[]) {

    Matrix<int> matrix(3, 2, nullptr, 0);
    matrix.insert(Matrix<int>::generateNode(0, 1, 3));
    matrix.insert(Matrix<int>::generateNode(1, 1, 5));
    matrix.print();
    return 0;
}