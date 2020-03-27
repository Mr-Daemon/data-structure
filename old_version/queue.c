#include <stdlib.h>
#include <stdio.h>

typedef struct linked_list {
    char data;
    struct linked_list *next;
} node;

typedef struct {
    node *front;
    node *rear;
} queue;

queue *initQueue() {
    node *headNode = (node *) malloc(sizeof(node));
    headNode->next = NULL;
    queue *myQueue = (queue *) malloc(sizeof(queue));
    myQueue->front = myQueue->rear = headNode;
    return myQueue;
}

void enQueue(queue *queue, char c) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->data = c;
    newNode->next = NULL;
    queue->rear = queue->rear->next = newNode;
}

char deQueue(queue *queue) {
    if (!queue->front->next)//this case queue is empty
        return 0;
    node *node = queue->front->next;
    if (!node->next)//this case deQueue the last element
        queue->rear = queue->front;
    queue->front->next = node->next;
    free(node);
    return 1;
}

int len(queue *queue) {
    int length = 0;
    node *node = queue->front;
    for (length = 0; node->next; length++)
        node = node->next;
    return length;
}

int main(int argc, char const *argv[]) {
    queue *queue = initQueue();
    enQueue(queue, '+');
    enQueue(queue, '-');
    enQueue(queue, '*');
    printf("%d", len(queue));
    printf("%d", queue->front == queue->rear);
    printf("%c", queue->front->next->data);
    printf("%c", queue->rear->data);
    return 0;
}
