//
// Created by cyb12 on 2020/4/30.
//
#include <cstdlib>
#include <iostream>


void test(int *p) {
    *(&p) = nullptr;
}

int main(int argc, char const *argv[]) {
    int a = 5;
    int *b = &a;
    test(b);
    if (b) {
        std::cout << "hi";
    } else {
        std::cout << "hello";
    }
    return 0;
}
