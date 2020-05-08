#include <iostream>
#include <algorithm>
#include <cstring>
#include "random_array.h"


void mergeSort(int *array, int begin, int end) {
    if (end - begin > 1) {
        mergeSort(array, begin, (begin + end) / 2);
        mergeSort(array, (begin + end) / 2, end);
        int *temp = (int *) malloc((end - begin) * sizeof(int));
        std::merge(array + begin, array + (begin + end) / 2, array + (begin + end) / 2, array + end, temp);
        memcpy(array + begin, temp, (end - begin) * sizeof(int));
        free(temp);
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
        mergeSort(wrapper.array, 0, wrapper.len);
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