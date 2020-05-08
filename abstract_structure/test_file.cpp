//
// Created by cyb12 on 2020/2/14.
//

#include <iostream>
#include "ArrayList.h"
#include "Compressor.h"
#include "huffman_tree.h"
#include "AdjacencyWDigraph.h"


int main(int argc, char const *argv[]) {
//    int wList[5] = {2, 9, 7, 4, 1};
//    //5 9 12 21
//    Node *tree = create(wList, 5);
//    for (int k = 0; k < 9; ++k) {
//        printf("%d ", tree[k].weight);
//    }
    const char *path = "/home/cyb/test.txt";
//    std::ifstream in;
//    in.open(path, std::ios::in);
//    char c;
//    while ((c = in.get()) != EOF) {
//        printf("%c,", c);
//    }
    Compressor::compress(path);
}