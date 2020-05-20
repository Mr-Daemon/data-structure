#include <stdio.h>

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    int array[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", array + i);
    }
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (array[i] + array[j] > array[k] && array[i] + array[k] > array[j]) {
                    count++;
                }
            }
        }
    }
    printf("%d", count);
    return 0;
}