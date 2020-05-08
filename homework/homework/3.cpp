#include <iostream>

//
// Created by cyb12 on 2020/5/5.
//
struct Node {
    int val;
    Node *left, *right;

    explicit Node(int val) {
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }
};

void insert(Node *root, int val) {
    Node *node = new Node(val);
    while (true) {
        if (root->val > val) {
            if (root->left) {
                root = root->left;
                continue;
            } else {
                root->left = node;
                break;
            }
        } else {
            if (root->right) {
                root = root->right;
                continue;
            } else {
                root->right = node;
                break;
            }
        }
    }
}


Node *createTree(int *array, int len) {
    Node *root = new Node(array[0]);
    for (unsigned i = 1; i < len; ++i) {
        insert(root, array[i]);
    }
    return root;
}

Node *search(Node *root, int key) {
    while (root) {
        if (root->val > key) {
            root = root->left;
        } else if (root->val < key) {
            root = root->right;
        } else {
            return root;
        }
    }
    return nullptr;
}

void erase(Node *&root, int key) {
    Node *target = nullptr;
    Node *parent = nullptr;
    bool flag = true;
    while (root) {
        parent = root;
        if (root->val > key) {
            root = root->left;
            flag = true;
        } else if (root->val < key) {
            root = root->right;
            flag = false;
        } else {
            target = root;
            break;
        }
    }
    if (target) {
        if (root == target) {
            if (!root->left && !root->right) {
                delete root;
                root = nullptr;
            } else if (!root->left && root->right) {
                *root = *(root->right);
                delete root->right;
            } else if (root->left && !root->right) {
                *root = *(root->left);
                delete root->left;
            } else {
                Node *right = root->right;
                *root = *(root->left);
                delete root->left;
                Node *node = root;
                while (node->right) {
                    node = node->right;
                }
                node->right = right;
            }
        } else {
            Node **a = nullptr;
            if (flag) {
                a = &parent->left;
            } else {
                a = &parent->right;
            }
            if (!target->left && !target->right) {
                *a = nullptr;
            } else if (!target->left && target->right) {
                *a = target->right;
            } else if (target->left && !target->right) {
                *a = target->left;
            } else {
                *a = target->left;
                Node *node = target->left;
                while (node->right) {
                    node = node->right;
                }
                node->right = target->right;
            }
            delete target;
        }
    }

}

int main(int argc, char const *argv[]) {
    int array[] = {53};
    Node *root = createTree(array, sizeof(array) / sizeof(int));
    erase(root, 53);
    if (root) {
        std::cout << "not null";
    } else {
        std::cout << "current BST is null";
    }
    return 0;
}