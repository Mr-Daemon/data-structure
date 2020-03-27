//
// Created by cyb12 on 2020-02-05.
//

#include <cstdlib>
#include "signal_booster.h"

SignalBiTree::SignalBiTree(int *array, int len, int torrance) : torrance(torrance) {
    arrayToLinked(root, array, len, 1);
    calculateBooster();
}

SignalBiTree::Node *SignalBiTree::initNode(int degrade) {
    auto node = (Node *) malloc(sizeof(Node));
    *node = {{degrade, 0, false}, 0,
             nullptr,
             nullptr};
    return node;
}

void SignalBiTree::arrayToLinked(Node *&node, int *array, int len, int serialNum) {
    if (array[serialNum - 1] >= 0) {
        node = initNode(array[serialNum - 1]);
        node->serialNum = serialNum;
//        std::cout << serialNum << ": " << array[serialNum - 1] << "\n";
        if (serialNum * 2 <= len)
            arrayToLinked(node->left, array, len, serialNum * 2);
        if (serialNum * 2 + 1 <= len)
            arrayToLinked(node->right, array, len, serialNum * 2 + 1);
    }
}

void SignalBiTree::calculateBooster() {
    calculateBooster(root, torrance);
}

int SignalBiTree::calculateBooster(SignalBiTree::Node *node, int torrance) {
    int degrade_to_leaf = 0;
    Node *list[2] = {node->left, node->right};
    for (int i = 0; i < 2; ++i) {
        if (list[i]) {
            int degrade = calculateBooster(list[i], torrance) + list[i]->elem.degrade_from_parent;
            if (degrade > torrance) {
                list[i]->elem.boosterHere = true;
//                std::cout << "booster on " << list[i]->serialNum << "\n";
                degrade_to_leaf = degrade_to_leaf > list[i]->elem.degrade_from_parent
                                  ? degrade_to_leaf
                                  : list[i]->elem.degrade_from_parent;
            } else {
                degrade_to_leaf = degrade_to_leaf > degrade
                                  ? degrade_to_leaf
                                  : degrade;
            }
        }
    }
    node->elem.degrade_to_leaf = degrade_to_leaf;
    return degrade_to_leaf;
}

int main(int argc, char const *argv[]) {
    int test[] = {0, 1, 3, 2, 2, 1, 2, 3, 1, -1, -1, 2, -1, 2, -1};
    SignalBiTree signalBiTree(test, sizeof(test) / sizeof(int), 3);
    return 0;
}