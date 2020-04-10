//
// Created by cyb12 on 2020/3/29.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>

struct Node {
    int elem;
    Node *left, *right;
};

Node *optimalBST(const int *list, int low, int high, const int *swList) {
    if (low < high) {
        int index = low;
        int sum = swList[high - 1] + swList[low];
        int min = sum;
        for (int i = low; i < high; ++i) {
            if (std::abs(sum - 2 * swList[i]) < min) {
                index = i;
                min = std::abs(sum - 2 * swList[i]);
            }
        }
        auto node = (Node *) malloc(sizeof(Node));
        *node = {list[index], nullptr, nullptr};
        node->left = optimalBST(list, low, index, swList);
        node->right = optimalBST(list, index + 1, high, swList);
        return node;
    }
    return nullptr;
}

Node *createOBST(const int *list, int len1, const int *wList, int len2) {
    auto swList = (int *) malloc(len2 * sizeof(int));
    int cur = 0;
    for (int i = 0; i < len2; ++i) {
        cur += wList[i];
        swList[i] = cur;
    }
    Node *root = optimalBST(list, 0, len1, swList);
    return root;
}


int main(int argc, char const *argv[]) {

    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int wList[] = {1, 1, 2, 5, 3, 4, 4, 3, 5};
    int test[] = {1, 3, 5, 7, 12, 45, 55, 79, 100, -1, 10, 50, 130};
    auto root = createOBST(list, sizeof(list) / sizeof(int), wList, sizeof(wList) / sizeof(int));
    for (int i = 0; i < sizeof(test) / sizeof(int); ++i) {
    }
    return 0;
}
