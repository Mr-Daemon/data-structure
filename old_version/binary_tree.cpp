//
// Created by cyb12 on 2020-01-31.
//

#include <iostream>

template<typename T>
class BinaryTree {
public:
    struct Node {
        T e;
        Node *leftChild, *rightChild;
    };
    Node *root;
    int size;

    BinaryTree() {
        root = nullptr;
        size = 0;
    }

    void copy(Node **newNode, Node *oldNode) {
        if (oldNode) {
            *newNode = generateNode(oldNode->e);
            copy(&((*newNode)->leftChild), oldNode->leftChild);
            copy(&((*newNode)->rightChild), oldNode->rightChild);
        }
    }

    explicit BinaryTree(BinaryTree *binaryTree) : size(binaryTree->size) {
        copy(&root, binaryTree->root);
    }

    bool equal(BinaryTree *binaryTree) {
        return equal(root, binaryTree->root);
    }

    bool equal(Node *internal, Node *external) {
        if (!internal && !external)
            return true;
        return internal && external && internal->e == external->e &&
               equal(internal->leftChild, external->leftChild) &&
               equal(internal->rightChild, external->rightChild);
    }

    void levelOrder(void (*visitFun)(Node *)) {
        Node *queue[size];
        int front = 0, rear = 1;
        queue[0] = root;
        while (front != rear) {
            auto current = queue[front++];
            visitFun(current);
            if (current->leftChild)
                queue[rear++] = current->leftChild;
            if (current->rightChild)
                queue[rear++] = current->rightChild;
        }
    }

    void preOrder(void (*visitFun)(Node *)) {
        visit = visitFun;
        preOrder(root);
    }

    void preOrderIt(void(*visitFun)(Node *)) {
        Node *stack[size / 2];
        int cur = 0;
        Node *current = root;
        for (int i = 0; i < size; ++i) {
            visitFun(current);
            if (current->leftChild) {
                if (current->rightChild)
                    stack[cur++] = current->rightChild;
                current = current->leftChild;
            } else if (current->rightChild)
                current = current->rightChild;
            else
                current = stack[--cur];
        }
    }

    void inOrder(void (*visitFun)(Node *)) {
        visit = visitFun;
        inOrder(root);
    }

    void inOrderIt(void (*visitFun)(Node *)) {
        Node *stack[size];
        int cur = 0;
        Node *current = root;
        do {
            stack[cur++] = current;
            if (current->leftChild)
                current = current->leftChild;
            else
                while (true) {
                    visitFun(current);
                    cur--;
                    if (current->rightChild) {
                        current = current->rightChild;
                        break;
                    }
                    current = stack[cur - 1];
                }
        } while (cur > 0);
    }

    void postOrder(void (*visitFun)(Node *)) {
        visit = visitFun;
        postOrder(root);
    }

    void postOrderIt(void (*visitFun)(Node *)) {
        Node *stack[size];
        int cur = 0;
        auto current = root;
//        do {
//            stack[cur++] = current;
//            if (current->leftChild)
//                current = current->leftChild;
//            else if (current->rightChild)
//                current = current->rightChild;
//            else
//                while (true) {
//                    if (current->rightChild) {
//                        current = current->rightChild;
//                        break;
//                    }
//                    visitFun(current);
//                    --cur;
//                    current = stack[cur - 1];
//                }
//        } while (cur > 0);
    }

    void erase() {
        postOrder(dispose);
        root = nullptr;
        size = 0;
    }

    int height() { return height(root); }

    void randomInit() {
        preOrder(random);
    }

    static Node *generateNode(T e) {
        auto node = (Node *) malloc(sizeof(Node));
        *node = {e, nullptr, nullptr};
        return node;
    }

private:
    static void (*visit)(Node *);

    static void preOrder(Node *node) {
        if (node) {
            visit(node);
            preOrder(node->leftChild);
            preOrder(node->rightChild);
        }
    }

    static void inOrder(Node *node) {
        if (node) {
            inOrder(node->leftChild);
            visit(node);
            inOrder(node->rightChild);
        }
    }

    static void postOrder(Node *node) {
        if (node) {
            postOrder(node->leftChild);
            postOrder(node->rightChild);
            visit(node);
        }
    }


    static void dispose(Node *node) {
        free(node);
    }

    static int height(Node *node) {
        if (!node)
            return 0;
        int hl = height(node->leftChild);
        int hr = height(node->rightChild);
        return hl > hr ? ++hl : ++hr;
    }

    static void random(Node *node) {
        static int count = 0;
        static int left = 1;
        static int right = -1;
        if (count < 25) {
            node->leftChild = generateNode(left);
            node->rightChild = generateNode(right);
            count++;
            left++;
            right--;
        }
    }
};

template<typename T>
void (*BinaryTree<T>::visit)(Node *) = nullptr;

template<typename T>
void print(typename BinaryTree<T>::Node *node) {
    std::cout << node->e << ",";
}

int main(int argc, char const *argv[]) {
    BinaryTree<int> binaryTree;
    binaryTree.root = BinaryTree<int>::generateNode(10);
    binaryTree.size = 51;
    binaryTree.randomInit();
    binaryTree.postOrderIt(print<int>);
//    BinaryTree<int> test(&binaryTree);
//    test.root->leftChild->rightChild = nullptr;
//    test.preOrder(print<int>);
//    std::cout << binaryTree.equal(&test);
    return 0;
}