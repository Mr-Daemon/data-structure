//
// Created by cyb12 on 2020/5/5.
//
#include <iostream>
#include <cstring>

#define MAX_L 10

struct Node {
    char str[MAX_L];
    Node *next;

    Node() {
        next = nullptr;
    }

    Node(char *str) {
        strcpy(this->str, str);
        next = nullptr;
    }
};

Node *arrayToLinked(char **array, int len) {
    Node *head = new Node();
    Node *current = head;
    for (int i = 0; i < len; ++i) {
        current->next = new Node(array[i]);
        current = current->next;
    }
    return head;
}

void radixSort(Node *const head) {
    Node *distributeList[27];
    for (int i = 0; i < 27; ++i) {
        distributeList[i] = new Node();
    }
    Node *temp_node = head->next;
    while (temp_node) {
        memset(temp_node->str + strlen(temp_node->str), '\0', (MAX_L - strlen(temp_node->str) + 1) * sizeof(char));
        temp_node = temp_node->next;
    }
    for (int i = MAX_L - 1; i >= 0; i--) {
        Node *current = head->next;
        while (current) {
            int index = (current->str[i] == '\0') ? 0 : current->str[i] - 'a' + 1;
            Node *node = distributeList[index];
            while (node->next) { node = node->next; }
            node->next = current;
            current = current->next;
            node->next->next = nullptr;
        }
        Node *node = head;
        for (int j = 0; j < 27; ++j) {
            Node *cur = distributeList[j]->next;
            distributeList[j]->next = nullptr;
            while (cur) {
                node->next = cur;
                node = node->next;
                cur = cur->next;
            }
        }
        node->next = nullptr;
    }
    for (int i = 0; i < 27; ++i) {
        delete distributeList[i];
    }
}

int main(int argc, char const *argv[]) {
    char *list[] = {"graph", "list", "array", "linked", "stack", "queue", "huffman"};
    Node *head = arrayToLinked(list, 7);
    radixSort(head);
    Node *node = head->next;
    while (node) {
        std::cout << node->str << ",";
        node = node->next;
    }
    return 0;
}