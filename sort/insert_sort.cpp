//
// Created by cyb12 on 2020/4/5.
//
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include "random_array.h"

//naive insertion mergeSort
void insertionSort1(int *array, int len) {
    for (int i = 1; i < len; ++i) {
        int temp = array[i];
        int j;
        for (j = i; j > 0 && temp < array[j - 1]; --j) {
            array[j] = array[j - 1];
        }
        array[j] = temp;
    }
}

//binary insertion mergeSort
void insertionSort2(int *array, int len) {
    for (int i = 1; i < len; ++i) {
        int current = array[i];
        int low = 0, high = i, middle;
        while (low < high) {
            middle = (low + high) / 2;
            if (array[middle] > current) {
                high = middle;
            } else {
                low = middle + 1;
            }
        }
        for (int k = i; k > low; --k) {
            array[k] = array[k - 1];
        }
        array[low] = current;
    }
}

//unstable
void shellSort(int *array, int len) {
    for (int gap = len / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < len; ++i) {
            int temp = array[i];
            int j;
            for (j = i; j >= gap && temp < array[j - gap]; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
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
        insertionSort1(wrapper.array, wrapper.len);
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