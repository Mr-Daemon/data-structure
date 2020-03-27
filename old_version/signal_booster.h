//
// Created by cyb12 on 2020-02-05.
//

#ifndef ALGORITHM_SIGNAL_BOOSTER_H
#define ALGORITHM_SIGNAL_BOOSTER_H

class SignalBiTree {
public:
    struct booster {
        int degrade_from_parent, degrade_to_leaf;
        bool boosterHere;
    };
    struct Node {
        booster elem;
        int serialNum;
        Node *left, *right;
    };
    Node *root;
    int size, torrance;
    SignalBiTree(int *array, int len, int torrance);
    void calculateBooster();
    static int calculateBooster(SignalBiTree::Node *node, int torrance);
    static Node *initNode(int degrade);
    static void arrayToLinked(Node *&node, int *array, int len, int serialNum);
};

#endif //ALGORITHM_SIGNAL_BOOSTER_H
