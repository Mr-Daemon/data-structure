//
// Created by cyb12 on 2020/4/5.
//

#ifndef DATA_STRUCTURE_RANDOM_ARRAY_H
#define DATA_STRUCTURE_RANDOM_ARRAY_H

#include <random>
#include <iostream>

class RandomArray {
    static RandomArray *instance;
    struct wrapper {
        int array[30];
        int len;
    };

    RandomArray() {
        srand(time(nullptr));
    }

    ~RandomArray() {
        std::cout << "destroy\n";
    }

public:
    static RandomArray *getInstance() {
        if (!instance) {
            instance = new RandomArray();
        }
        return instance;
    }

    wrapper randArray() {
        wrapper a;
        a.len = rand() % 20 + 10;
        for (int i = 0; i < a.len; ++i) {
            a.array[i] = rand() % 100;
        }
        return a;
    }
};

RandomArray *RandomArray::instance = nullptr;
#endif //DATA_STRUCTURE_RANDOM_ARRAY_H
