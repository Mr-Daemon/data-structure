//
// Created by cyb12 on 2020/3/23.
//

#ifndef DATA_STRUCTURE_LINKEDLIST_H
#define DATA_STRUCTURE_LINKEDLIST_H

#include <cstdlib>
#include <stdexcept>

template<typename T>
class LinkedList {
    struct Node {
        T t;
        Node *next;
    };
    int length;
    Node *head;

    static Node *newNode(T t) {
        auto node = (Node *) malloc(sizeof(Node));
        *node = {t, nullptr};
        return node;
    }

public:
    LinkedList() : length(0) {
        head = newNode((T) 0);
    }

    void insert(T t, int pos) {
        if (pos > length)
            throw std::out_of_range("change another pos");
        auto current = head;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        auto node = newNode(t);
        node->next = current->next;
        current->next = node;
        length++;
    }

    void add(T t) {
        insert(t, length);
    }

    int size() {
        return length;
    }

    T &operator[](int index) {
        if (index < length) {
            auto current = head->next;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->t;
        } else {
            throw std::out_of_range("index out of bound");
        }
    }
};


#endif //DATA_STRUCTURE_LINKEDLIST_H
