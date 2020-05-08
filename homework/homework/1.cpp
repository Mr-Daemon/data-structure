#include <iostream>

//
// Created by cyb12 on 2020/5/2.
//
struct Node {
    int val;
    Node *left, *right;
    bool lTag, rTag;//false for child, true for thread
    Node() {}

    explicit Node(int val) {
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
        this->lTag = false;
        this->rTag = false;
    }
};

Node *createTree(int *array, int len) {
    Node *tree[len];
    tree[0] = new Node(array[0]);
    for (unsigned i = 1; i < len; ++i) {
        if (array[i]) {
            tree[i] = new Node(array[i]);
            if (array[(i - 1) / 2]) {
                if (i & 1u) {
                    tree[(i - 1) / 2]->left = tree[i];
                } else {
                    tree[(i - 1) / 2]->right = tree[i];
                }
            }
        }
    }
    return tree[0];
}

void preOrderThread(Node *node, Node *&prev) {
    if (prev) {
        if (!prev->right) {
            prev->rTag = true;
            prev->right = node;
        }
        if (!node->left) {
            node->lTag = true;
            node->left = prev;
        }
    }
    prev = node;
    if (node->left && !node->lTag) {
        preOrderThread(node->left, prev);
    }
    if (node->right && !node->rTag) {
        preOrderThread(node->right, prev);
    }
}

void preOrderThread(Node *root) {
    Node *prev = nullptr;
    preOrderThread(root, prev);
}

void printPreOrder(Node *node) {
    while (true) {
        std::cout << node->val << ",";
        if (node->left && !node->lTag) {
            node = node->left;
        } else if (node->right) {
            node = node->right;
        } else {
            break;
        }
    }
}

void inOrderThread(Node *node, Node *&prev) {
    if (node->left && !node->lTag) {
        inOrderThread(node->left, prev);
    }
    if (prev) {
        if (!prev->right) {
            prev->rTag = true;
            prev->right = node;
        }
        if (!node->left) {
            node->lTag = true;
            node->left = prev;
        }
    }
    prev = node;
    if (node->right && !node->rTag) {
        inOrderThread(node->right, prev);
    }
}

void inOrderThread(Node *root) {
    Node *prev = nullptr;
    inOrderThread(root, prev);
}

void printInOrder(Node *node) {
}

void postOrderThread(Node *node, Node *&prev) {
    if (node->left && !node->lTag) {
        postOrderThread(node->left, prev);
    }
    if (node->right && !node->rTag) {
        postOrderThread(node->right, prev);
    }
    if (prev) {
        if (!prev->right) {
            prev->rTag = true;
            prev->right = node;
        }
        if (!node->left) {
            node->lTag = true;
            node->left = prev;
        }
    }
    prev = node;
}

void postOrderThread(Node *root) {
    Node *prev = nullptr;
    postOrderThread(root, prev);
}

void printPostOrder(Node *node) {

}

int main(int argc, char const *argv[]) {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    Node *root = createTree(array, sizeof(array) / sizeof(int));
    postOrderThread(root);
    return 0;
}
