//
// Created by cyb12 on 2020/4/10.
//
#include <iostream>
#include "random_array.h"

//unstable
void naiveSelectionSort(int *array, int len) {
    for (int i = 0; i < len - 1; ++i) {
        int index = i;
        for (int j = i + 1; j < len; ++j) {
            if (array[j] < array[index]) {
                index = j;
            }
        }
        std::swap(array[i], array[index]);
    }
}

//unstable
void heapSort(int *array, int len) {
    int LIL_NUM = -1000000;
    for (int i = 1; i < len; ++i) {
        int child = i;
        int parent = (child - 1) / 2;
        while (child > 0 && array[child] > array[parent]) {
            std::swap(array[child], array[parent]);
            child = parent;
            parent = (child - 1) / 2;
        }
    }
    for (int i = len - 1; i > 0; --i) {
        int elem = array[i];
        array[i] = array[0];
        int index = 0;
        while (index * 2 + 1 < i) {
            int left = array[index * 2 + 1];
            int right = index * 2 + 2 < i ? array[index * 2 + 2] : LIL_NUM;
            if (elem > left && elem > right) {
                break;
            } else if (left < right) {
                array[index] = right;
                index = index * 2 + 2;
            } else {
                array[index] = left;
                index = index * 2 + 1;
            }
        }
        array[index] = elem;
    }
}

int main(int argc, char const *argv[]) {
    int flag = true;
    for (int i = 0; i < 20; ++i) {
        auto wrapper = RandomArray::getInstance()->randArray();
        std::cout << "origin: ";
        for (int j = 0; j < wrapper.len; ++j) {
            std::cout << wrapper.array[j] << ",";
        }
        heapSort(wrapper.array, wrapper.len);
        std::cout << "\n" << "sorted: ";
        int e = wrapper.array[0];
        bool sorted = true;
        for (int j = 0; j < wrapper.len; ++j) {
            sorted = sorted && e <= wrapper.array[j];
            e = wrapper.array[j];
            std::cout << wrapper.array[j] << ",";
        }
        if (!sorted) {
            std::cout << "error!";
            flag = false;
        }
        printf("\n");
        for (int k = 0; k < 100; ++k) {
            printf("-");
        }
        printf("\n");
    }
    if (!flag) {
        std::cout << "somewhere occurred error";
    }
    return 0;
}