//
// Created by cyb12 on 2020-01-26.
//
#include <c++/cstdio>
#include <c++/cstring>

int main(int argc, char const *argv[]) {
    char test[] = "2345";
    int length = strlen(test);
    int multi = 1;
    int result = 0;
    while (length) {
        result += (test[--length] - '0') * multi;
        multi *= 10;
    }
    printf("%d", result);
    return 0;
}