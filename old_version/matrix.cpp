#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>

//
// Created by cyb12 on 2020-01-26.
//

template<typename T>
class SparseMatrix {
public:
    int row, column, length;
    struct triple {
        int i, j;
        T e;
    };
    //in row-major order
    triple *list;
    //list[pos[i]] is the first entry in i-th row
    int *pos;

    SparseMatrix(triple *list, int row, int column, int length) : row(row), column(column), length(length) {
        this->list = (triple *) malloc(sizeof(triple) * length);
        memcpy(this->list, list, length * sizeof(triple));
        pos = (int *) malloc(row * sizeof(int));
        int num[row];
        for (int j = 0; j < row; ++j)
            num[j] = 0;
        for (int i = 0; i < length; ++i)
            num[list[i].i]++;
        pos[0] = 0;
        for (int k = 1; k < row; ++k)
            pos[k] = pos[k - 1] + num[k - 1];
        pos[row] = length;
    }

    ~SparseMatrix() {
        free(list);
        free(pos);
    }

    //time complexity O(length*column)
    //space complexity O(length)
    void transpose1() {
        if (length) {
            int cur = 0;
            auto *newList = (triple *) malloc(sizeof(triple) * length);
            for (int i = 0; i < column; ++i)
                for (int j = 0; j < length; ++j)
                    if (i == list[j].j) {
                        newList[cur].i = list[j].j;
                        newList[cur].j = list[j].i;
                        //Doesn't matter if T is a pointer
                        newList[cur].e = list[j].e;
                        cur++;
                    }
            free(list);
            list = newList;
        }
        int temp = column;
        column = row;
        row = temp;
    }

    //time complexity O(length+column)
    //space complexity O(length+column)
    //fast transpose, better than transpose1 in any cases
    void transpose2() {
        if (length) {
            int num[column];
            for (int j = 0; j < column; ++j) {
                num[j] = 0;
            }
            for (int i = 0; i < length; ++i) {
                int temp = list[i].j;
                list[i].j = list[i].i;
                list[i].i = temp;
                num[temp]++;
            }
            int *newPos = (int *) malloc(column * sizeof(int));
            newPos[0] = 0;
            for (int k = 1; k < column; ++k) {
                newPos[k] = num[k - 1] + newPos[k - 1];
            }
            free(pos);
            pos = newPos;
            auto *newList = (triple *) malloc(sizeof(triple) * length);
            for (int l = 0; l < length; ++l) {
                newList[newPos[list[l].i]++] = list[l];
            }
            free(list);
            list = newList;
        }
        int temp = column;
        column = row;
        row = temp;
    }

    void print() {
        int cur = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                if (list[cur].i == i && list[cur].j == j) {
                    std::cout << list[cur].e << " ";
                    cur++;
                } else {
                    printf("0 ");
                }
            }
            printf("\n");
        }
    }
};

//time complexity O(A.row*B*column+A.length*B.length/B.row)
//space complexity O(A.row*B.column)
template<typename T>
SparseMatrix<T> *multiple(SparseMatrix<T> *A, SparseMatrix<T> *B) {
    if (A->length * B->length) {
        T raw[A->row][B->column];
        //init raw with 0
        for (int i = 0; i < A->row * B->column * sizeof(T); ++i)
            ((char *) raw)[i] = 0;
        //time O(A.length*B.length/B.row)
        for (int j = 0; j < A->length; ++j) {
            auto a = A->list[j];
            for (int i = B->pos[a.j]; i < B->pos[a.j + 1]; ++i) {
                auto b = B->list[i];
                raw[a.i][b.j] += a.e * b.e;
//                printf("raw[%d][%d] += %d * %d\n", a.i, b.j, a.e, b.e);
            }
        }
        typename SparseMatrix<T>::triple buffer[A->row * B->column];
        int cur = 0;
        for (int i = 0; i < A->row; ++i)
            for (int j = 0; j < B->column; ++j)
                if (raw[i][j]) {
                    buffer[cur++] = {i, j, raw[i][j]};
                    printf("buffer[%d]={%d,%d,%d}\n", cur - 1, buffer[cur - 1].i,
                           buffer[cur - 1].j, buffer[cur - 1].e);
                }
        auto result = (typename SparseMatrix<T>::triple *) malloc
                (sizeof(typename SparseMatrix<T>::triple) * cur);
        memcpy(result, buffer,
               sizeof(typename SparseMatrix<T>::triple) * cur);
        auto sparseMatrix = new SparseMatrix<T>(result, A->row, B->column, cur);
        return sparseMatrix;
    }
}

int main(int argc, char const *argv[]) {
    SparseMatrix<int>::triple list[] = {{0, 0, 4},
                                        {1, 1, 5}};
    SparseMatrix<int> sparseMatrix(list, 2, 2, 2);
//    sparseMatrix.print();
//    sparseMatrix.transpose2();
//    sparseMatrix.print();
    auto test = multiple(&sparseMatrix, &sparseMatrix);
    test->print();
    return 0;
}
