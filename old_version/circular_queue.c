#include <stdlib.h>
#include <stdio.h>

#define LENGTH 10
typedef struct {
    char *array;
    int front;
    int rear;
} queue;

queue *initQueue() {
    queue *myQueue = (queue *) malloc(sizeof(queue));
    myQueue->array = (char *) malloc(sizeof(char) * LENGTH);
    myQueue->front = myQueue->rear = 0;
    return myQueue;
}

char enQueue(queue *queue, char c) {
    if ((queue->rear + 1) % LENGTH == queue->front)
        return 0;
    queue->array[queue->rear] = c;
    queue->rear = (queue->rear + 1) % LENGTH;
    return 1;
}

char deQueue(queue *queue) {
    if ((queue->front + 1) % LENGTH == queue->rear)
        return 0;
    queue->front = (queue->front + 1) % LENGTH;
    return 1;
}

int len(queue *queue) {
    int len = queue->rear - queue->front;
    if (len < 0)
        len = LENGTH + len;
    return len;
}

int main(int argc, char const *argv[]) {
    queue *queue = initQueue();
    enQueue(queue, '+');
    enQueue(queue, '-');
    enQueue(queue, '*');
    printf("%d", len(queue));
    printf("%d", queue->front == queue->rear);
    printf("%c", queue->array[queue->front]);
    printf("%c", queue->array[queue->rear - 1]);
    return 0;
}
