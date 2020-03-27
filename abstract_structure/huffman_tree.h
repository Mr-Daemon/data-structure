//
// Created by cyb12 on 2020/2/15.
//

#ifndef DATA_STRUCTURE_HUFFMAN_TREE_H
#define DATA_STRUCTURE_HUFFMAN_TREE_H

#include <cstdio>
#include <cstdlib>

struct Node {
    int weight;
    int left, right, parent;
};

void initNode(int weight, Node *node) {
    *node = {weight, -1, -1, -1};
}

Node *create(int *wList, int num_of_leaf) {
    auto tree = (Node *) malloc((2 * num_of_leaf - 1) * sizeof(Node));
    for (int i = 0; i < num_of_leaf; ++i) {
        initNode(wList[i], tree + i);
    }
    int current = num_of_leaf;
    while (current < num_of_leaf * 2 - 1) {
        int a = -1, b = -1;//index
        for (int i = 0; i < current; ++i) {
            if (tree[i].parent == -1 && tree[i].weight != 0) {
                if (a == -1) a = i;
                else if (b == -1) b = i;
                else if (tree[i].weight < tree[a].weight && tree[i].weight >= tree[b].weight)
                    a = i;
                else if (tree[i].weight < tree[b].weight && tree[i].weight >= tree[a].weight)
                    b = i;
                else if (tree[i].weight < tree[a].weight && tree[i].weight < tree[b].weight) {
                    if (tree[a].weight > tree[b].weight) a = i;
                    else b = i;
                }
            }
        }
        tree[a].parent = current;
        tree[b].parent = current;
        printf("%d %d %d\n", a, b, current);
        tree[current] = {tree[a].weight + tree[b].weight, a, b, -1};
        current++;
    }
    return tree;
}


#endif //DATA_STRUCTURE_HUFFMAN_TREE_H
