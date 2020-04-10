//
// Created by cyb12 on 2020/4/1.
//
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>

template<typename T>
class MaxHeap {
    T *array;
    int length;
    int capacity;
    const static int INIT_SIZE = 63;
public:
    MaxHeap() {
        capacity = INIT_SIZE;
        length = 0;
        array = (T *) malloc(capacity * sizeof(T));
    }

    MaxHeap(T *array, int len) {
        *this = MaxHeap();
        for (int i = 0; i < len; ++i) {
            push(array[i]);
        }
    }

    void push(T elem) {
        array[length++] = elem;
        int child = length - 1;
        int parent = (child - 1) / 2;
        while (child != 0 && array[child] > array[parent]) {
            std::swap(array[parent], array[child]);
            child = parent;
            parent = (parent - 1) / 2;
        }
    }

    T top() {
        return array[0];
    }

    void pop() {
        T elem = array[--length];
        int index = 0;
        while (true) {
            if (index * 2 + 1 > length - 1) {
                array[index] = elem;
                break;
            } else if (index * 2 + 2 > length - 1) {
                if (elem > array[index * 2 + 1]) {
                    array[index] = elem;
                } else {
                    array[index] = array[index * 2 + 1];
                    array[index * 2 + 1] = elem;
                }
                break;
            } else {
                if (elem > array[2 * index + 1] && elem > array[2 * index + 2]) {
                    array[index] = elem;
                    break;
                } else {
                    if (array[2 * index + 1] > array[2 * index + 2]) {
                        array[index] = array[2 * index + 1];
                        index = 2 * index + 1;
                    } else {
                        array[index] = array[2 * index + 2];
                        index = 2 * index + 2;
                    }
                }
            }
        }
    }

    void print() {
        int num = 0;
        for (int i = 0; i < length; ++i) {
            std::cout << array[i] << " ";
            if (i == num) {
                std::cout << "\n";
                num = num * 2 + 2;
            }
        }
    }
};

int main(int argc, char const *argv[]) {
    int test[] = {3, 4, 5, 1, 9, 7, 34, 35, 75, 63, 132};
    auto heap = MaxHeap<int>(test, sizeof(test) / sizeof(int));
    heap.print();
    for (int i = 0; i < 7; ++i) {
        printf("\n------------------------\n");
        heap.pop();
        heap.print();
    }
    return 0;
}