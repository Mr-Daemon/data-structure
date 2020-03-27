//
// Created by cyb12 on 2020/3/23.
//

#ifndef DATA_STRUCTURE_QUEUE_H
#define DATA_STRUCTURE_QUEUE_H

#include <cstdlib>
#include <stdexcept>

template<typename T>
class Queue {
    struct Node {
        T t;
        Node *next;
    };
    Node *head;
    Node *rear;
    int length;

    static Node *newNode(T t) {
        auto node = (Node *) malloc(sizeof(Node));
        *node = {t, nullptr};
        return node;
    }

public:
    Queue() {
        rear = head = newNode((T) 0);
        length = 0;
    };

    ~Queue() {
        Node *current;
        while (head != rear) {
            current = head;
            head = head->next;
            free(current);
        }
        free(head);
    }

    void enQueue(T t) {
        auto node = newNode(t);
        rear->next = node;
        rear = node;
        length++;
    }

    T deQueue() {
        if (length > 1) {
            auto node = head->next;
            auto t = node->t;
            head->next = node->next;
            free(node);
            length--;
            return t;
        } else if (length == 1) {
            auto t = head->next->t;
            free(rear);
            rear = head;
            return t;
        } else {
            throw std::length_error("no elements in Queue");
        }
    }

    T front() {
        return head->next->t;
    }

    bool empty() {
        return length == 0;
    }
};


#endif //DATA_STRUCTURE_QUEUE_H
