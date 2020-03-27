#include <iostream>
#include <algorithm>
#include <cstring>


void sort(int *array, int begin, int end) {
    if (end - begin > 1) {
        sort(array, begin, (begin + end) / 2);
        sort(array, (begin + end) / 2, end);
        auto temp = (int *) malloc((end - begin) * sizeof(int));
        std::merge(array + begin, array + (begin + end) / 2, array + (begin + end) / 2, array + end, temp);
        memcpy(array + begin, temp, (end - begin) * sizeof(int));
        free(temp);
    }
}

int main() {
    int test[] = {5, 3, 7, 1};
    sort(test, 0, 4);
    for (int i = 0; i < 4; ++i) {
        std::cout << test[i] << " ";
    }
    return 0;
}