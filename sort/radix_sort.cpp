#include "random_array.h"

//
// Created by cyb12 on 2020/5/5.
//
struct Node {
    int val;
    Node *next;

    Node() {
        next = nullptr;
    }

    Node(int val) {
        this->val = val;
        next = nullptr;
    }
};

Node *arrayToLinked(int *array, int len) {
    Node *head = new Node();
    Node *current = head;
    for (int i = 0; i < len; ++i) {
        current->next = new Node(array[i]);
        current = current->next;
    }
    return head;
}

void linkedToArray(Node *head, int *array) {
    Node *node = head->next;
    for (int i = 0; node; ++i) {
        array[i] = node->val;
        Node *temp = node;
        node = node->next;
        delete temp;
    }
}

void radixSort(Node *const head, const int radix) {
    int divisor = radix;
    Node *distributeList[radix];
    for (int i = 0; i < radix; ++i) {
        distributeList[i] = new Node();
    }
    while (true) {
        Node *current = head->next;
        while (current) {
            Node *node = distributeList[(current->val % divisor) / (divisor / radix)];
            while (node->next) { node = node->next; }
            node->next = current;
            current = current->next;
            node->next->next = nullptr;
        }
        Node *node = head;
        bool time_to_exit = true;
        for (int i = 0; i < radix; ++i) {
            Node *cur = distributeList[i]->next;
            if (i > 0 && cur) { time_to_exit = false; }
            distributeList[i]->next = nullptr;
            while (cur) {
                node->next = cur;
                node = node->next;
                cur = cur->next;
            }
        }
        node->next = nullptr;
        divisor = divisor * radix;
        if (time_to_exit) { break; }
    }
    for (int i = 0; i < radix; ++i) {
        delete distributeList[i];
    }
}


int main(int argc, char const *argv[]) {
    int flag = true;
    for (int i = 0; i < 20; ++i) {
        auto wrapper = RandomArray::getInstance()->randArray();
        std::cout << "origin: ";
        for (int j = 0; j < wrapper.len; ++j) {
            std::cout << wrapper.array[j] << ",";
        }
        Node *head = arrayToLinked(wrapper.array, wrapper.len);
        radixSort(head, 10);
        linkedToArray(head, wrapper.array);
        std::cout << "\n" << "sorted: ";
        int e = wrapper.array[0];
        bool sorted = true;
        for (int j = 0; j < wrapper.len; ++j) {
            sorted = sorted && e <= wrapper.array[j];
            e = wrapper.array[j];
            std::cout << wrapper.array[j] << ",";
        }
        if (!sorted) {
            std::cout << "error!";
            flag = false;
        }
        printf("\n");
        for (int k = 0; k < 100; ++k) {
            printf("-");
        }
        printf("\n");
    }
    if (!flag) {
        std::cout << "somewhere occurred error";
    }
    return 0;
}
