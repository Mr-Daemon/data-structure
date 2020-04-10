//
// Created by cyb12 on 2020/3/30.
//
#include <cstdlib>
#include <cstdio>

class AVLTree {
    struct Node {
        int data;
        Node *left, *right;
        int balance;
        int height;
    };
    int height;
    Node *root;

    static Node *newNode(int data) {
        auto node = (Node *) malloc(sizeof(Node));
        *node = {data, nullptr, nullptr, 0, 1};
        return node;
    }

public:
    explicit AVLTree(int data) : height(1) {
        root = newNode(data);
    }

    AVLTree(int *array, int len) {
        *this = AVLTree(array[0]);
        for (int i = 1; i < len; ++i) {
            insert(array[i]);
        }
    }

    Node *search(int data) {
        auto current = root;
        while (current) {
            if (current->data == data)return current;
            else if (current->data > data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr;
    }

    bool insert(int data) {
        Node *path[root->height];
        int cur = 0;
        auto current = root;
        while (current) {
            path[cur++] = current;
            if (current->data == data)return false;
            else if (current->data > data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (data < path[cur - 1]->data) {
            path[cur - 1]->left = newNode(data);
        } else {
            path[cur - 1]->right = newNode(data);
        }
        //左右都有节点说明height不变, 什么都不做
        if (!path[cur - 1]->left || !path[cur - 1]->right) {
            bool flag = false;
            for (int i = 0; i < cur; ++i) {
                if (flag || path[i]->height < cur - i + 1) {
                    path[i]->height++;
                    flag = true;
                    if (i > 0) {
                        path[i - 1]->balance = path[i - 1]->left->height - path[i - 1]->right->height;
                    }
                }
            }
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    int list[] = {1, 3, 5, 7, 12, 45, 55, 79, 100};
    int test[] = {1, 3, 5, 7, 12, 45, 55, 79, 100, -1, 10, 50, 130};
    auto avl = AVLTree(list, sizeof(list) / sizeof(int));

    return 0;
}