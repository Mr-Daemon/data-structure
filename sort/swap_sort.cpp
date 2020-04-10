//
// Created by cyb12 on 2020/4/8.
//
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include "random_array.h"

void bubbleSort(int *array, int len) {
    for (int i = len - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

//unstable
void quickSort(int *array, int low, int high) {
    if (low + 1 < high) {
        int pivot = low;
        int pivotKey = array[low];
        int index = low;
        for (int i = low + 1; i < high; ++i) {
            if (array[i] < pivotKey) {
                index++;
                std::swap(array[index], array[i]);
            }
        }
        std::swap(array[pivot], array[index]);
        quickSort(array, low, index);
        quickSort(array, index + 1, high);
    }
}


int main(int argc, char const *argv[]) {
    for (int i = 0; i < 5; ++i) {
        auto wrapper = RandomArray::getInstance()->randArray();
        std::cout << "origin: ";
        for (int j = 0; j < wrapper.len; ++j) {
            std::cout << wrapper.array[j] << ",";
        }
        std::cout << "\n" << "sorted: ";
        quickSort(wrapper.array, 0, wrapper.len);
        for (int j = 0; j < wrapper.len; ++j) {
            std::cout << wrapper.array[j] << ",";
        }
        printf("\n");
        for (int k = 0; k < 100; ++k) {
            printf("-");
        }
        printf("\n");
    }
    return 0;
}
