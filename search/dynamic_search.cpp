//
// Created by cyb12 on 2020/3/29.
//
#include <cstdlib>
#include <cstdio>

struct Node {
    int data;
    Node *left, *right;
};

Node *searchNode(Node *root, int data) {
    auto current = root;
    while (true) {
        if (current->data == data) return current;
        else if (current->data > data) {
            if (!current->left) {
                current->left = (Node *) malloc(sizeof(Node));
                *(current->left) = {data, nullptr, nullptr};
                return nullptr;
            } else {
                current = current->left;
            }
        } else {
            if (!current->right) {
                current->right = (Node *) malloc(sizeof(Node));
                *(current->right) = {data, nullptr, nullptr};
                return nullptr;
            } else {
                current = current->right;
            }
        }
    }
}

bool eraseNode(Node *root, int data) {
    auto parent = root;
    auto current = root;
    while (current) {
        if (current->data == data)break;
        else if (current->data > data) {
            parent = current;
            current = current->left;
        } else {
            parent = current;
            current = current->right;
        }
    }
    bool flag = (parent->left == current);
    Node *result;
    if (current) {
        if (!current->left) {
            result = current->right;
        } else if (!current->right) {
            result = current->left;
        } else {
            auto prev = current->left;
            while (prev->right) {
                prev = prev->right;
            }
            prev->right = current->right;
            result = current->left;
        }
        flag ? parent->left : parent->right = result;
        free(current);
        return true;
    } else return false;
}

Node *createBST(const int *list, int len) {
    auto root = (Node *) malloc(sizeof(Node));
    *root = {list[0], nullptr, nullptr};
    for (int i = 1; i < len; ++i) {
        searchNode(root, list[i]);
    }
    return root;
}

void inOrder(Node *node, int *array, int &cur) {
    if (node) {
        inOrder(node->left, array, cur);
        array[cur++] = node->data;
        printf("%d ", node->data);
        inOrder(node->right, array, cur);
    }
}

void sortedArray(Node *root, int *array) {
    int cur = 0;
    inOrder(root, array, cur);
}

int main(int argc, char const *argv[]) {
    int list[] = {6, 1, 4, 67, 43, 32, 93, 13};
    int test[] = {1, 3, 5, 7, 12, 45, 55, 79, 100, -1, 10, 50, 130};
    auto root = createBST(list, sizeof(list) / sizeof(int));
    eraseNode(root, 67);
    int array[20];
    sortedArray(root, array);
    return 0;
}
