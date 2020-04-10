//
// Created by cyb12 on 2020/3/28.
//

#include <cstdio>
#include <algorithm>

int binary_search(const int *list, int len, int target) {
    int low = 0;
    int high = len;
    int mid;
    while (low < high) {
        mid = (low + high) / 2;
        if (list[mid] == target)return mid;
        else if (list[mid] > target)high = mid;
        else low = mid + 1;
    }
    return -1;
}

//guarantee len>2
int fibonacci_search(const int *list, int len, int target) {
    int a = 0;
    int b = 1;
    int c = 1;
    int base = 0;
    while (c < len) {
        int temp = b + c;
        a = b;
        b = c;
        c = temp;
    }
    while (a > 0 && base < len) {
        int cur = std::min(base + a, len);
        if (list[cur - 1] == target)return cur - 1;
        else if (list[cur - 1] > target) {
            c = a;
            b = b - a;
            a = c - b;
        } else {
            base += a;
            c = b;
            b = a;
            a = c - b;
        }
    }
    return -1;
}


int main(int argc, char const *argv[]) {
    int list[] = {1, 3, 5, 7, 12, 45, 55, 79, 100};
    int test[] = {1, 3, 5, 7, 12, 45, 55, 79, 100, -1, 10, 50, 130};
    for (int i = 0; i < sizeof(test) / sizeof(int); ++i) {
        printf("%d ", fibonacci_search(list, sizeof(list) / sizeof(int), test[i]));
    }
    return 0;
}