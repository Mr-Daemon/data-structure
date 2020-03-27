#include <stdlib.h>
#include <stdio.h>

struct singly_node {
    int data;
    struct singly_node *next;
} hNode;

int length(struct singly_node *hNode) {
    int i = 0;
    while (hNode->next) {
        hNode = hNode->next;
        ++i;
    }
    return i;
}

int getNode(struct singly_node *hNode, int index) {
    //get the node before the index-th node
    for (int i = 0; i < index; i++)
        hNode = hNode->next;
    return hNode->next->data;
}

void insertNode(struct singly_node *hNode, int data, int index) {
    struct singly_node *newNode = (struct singly_node *) malloc(sizeof(struct singly_node));
    newNode->data = data;
    //get the node before the index-th node
    for (int i = 0; i < index; i++)
        hNode = hNode->next;
    newNode->next = hNode->next;
    hNode->next = newNode;
}

void deleteNode(struct singly_node *hNode, int index) {
    //get the node before the index-th node
    for (int i = 0; i < index; i++)
        hNode = hNode->next;
    struct singly_node *node = hNode->next;
    hNode->next = node->next;
    free(node);
}

void print(struct singly_node *hNode) {
    printf("[");
    if (!(hNode->next)) {
        printf("]");
        return;
    }
    hNode = hNode->next;
    printf("%d", hNode->data);
    while (hNode->next) {
        hNode = hNode->next;
        printf(",%d", hNode->data);
    }
    printf("]\n");
}

int search(struct singly_node *hNode, int target) {
    int i = 0;
    while (hNode->next) {
        hNode = hNode->next;
        if (hNode->data == target)
            return i;
        ++i;
    }
    return -1;
}

// store A∪B/A∩B in a linked list
void merge(struct singly_node *node_a, struct singly_node *node_b) {
    struct singly_node *node = node_b;
    while (node->next) {
        node = node->next;
        int index = search(node_a, node->data);
        if (index == -1)
            insertNode(node_a, node->data, 0);
        else
            deleteNode(node_a, index);
    }
}

int main(int argc, char const *argv[]) {
    // int test_list[] = {2, 0, 2, 0, 1, 1, 4};
    // struct singly_node hNode;
    // hNode.next = NULL;
    // for (int i = 0; i < 7; i++)
    //     insertNode(&hNode, test_list[i], i);
    // deleteNode(&hNode, 3);
    // printf("%d\n", length(&hNode));
    // print(&hNode);
    // printf("%d\n", search(&hNode, 4));
    int list_a[] = {1, 2, 3, 4, 5};
    int list_b[] = {4, 5, 6, 7, 8};
    struct singly_node node_a;
    struct singly_node node_b;
    node_a.next = NULL;
    node_b.next = NULL;
    for (int i = 0; i < 5; i++)
        insertNode(&node_a, list_a[i], i);
    for (int i = 0; i < 5; i++)
        insertNode(&node_b, list_b[i], i);
    merge(&node_a, &node_b);
    print(&node_a);
    return 0;
}
