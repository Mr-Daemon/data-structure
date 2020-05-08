/*******************************************************************************
* FileName:         BinTree.cpp
* Author:           Your_name
* Student Number:   Student_Number
* Date:             2020/04/01 09:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #8
*******************************************************************************/

#include "BinTree.h"
#include <stdlib.h>
#include <algorithm>

BinTree::BinTree() {
    root = nullptr;
    h = 0;
    num = 0;
}

BinTree::~BinTree() {
}

void BinTree::insert(int val, int parent, int flg) {
    auto node = (Node *) malloc(sizeof(Node));
    *node = {val, nullptr, nullptr, parent, flg, num + 1};
    num++;
    if (root) {
        auto current = root;
        Node *list[num];
        int front = 0, rear = 1;
        list[0] = root;
        while (front < rear) {
            current = list[front++];
            if (current->sNum == parent) {
                flg > 0 ? current->right = node : current->left = node;
                break;
            }
            if (current->left && current->left->sNum <= parent) {
                list[rear++] = current->left;
            }
            if (current->right && current->right->sNum <= parent) {
                list[rear++] = current->right;
            }
        }
    } else {
        root = node;
        h = 1;
    }
}

void BinTree::preOrder(Node *node, int *list, int &cur) {
    if (node) {
        list[cur++] = node->data;
        preOrder(node->left, list, cur);
        preOrder(node->right, list, cur);
    }
}

int *BinTree::p_traversal() const {
    int *p = (int *) malloc(num * sizeof(int));
    int cur = 0;
    preOrder(root, p, cur);
    return p;
}

void BinTree::inOrder(Node *node, int *list, int &cur) {
    if (node) {
        inOrder(node->left, list, cur);
        list[cur++] = node->data;
        inOrder(node->right, list, cur);
    }
}

int *BinTree::m_traversal() const {
    int *p = (int *) malloc(num * sizeof(int));
    int cur = 0;
    inOrder(root, p, cur);
    return p;
}

int BinTree::countNode() const {
    return num;
}

int BinTree::h_recur(Node *node) {
    if (!node)
        return 0;
    return std::max(h_recur(node->left), h_recur(node->right)) + 1;
}

int BinTree::height() const {
    return h_recur(root);
}