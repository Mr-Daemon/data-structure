#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct {
    int index;
    unsigned long time;
    // 0-arrival 1-leave 2-the time spent
    char type;
} event;

// generate a arrival envent with index
event generateEvent(int *index) {
    event event = {*index, time(NULL), 0};
    index++;
    return event;
}

typedef struct linkedList {
    event event;
    struct linkedList *next;
} eventNode;

//init a event node that waits to be pushed into event list
eventNode *initEventNode() {
    eventNode *head = (eventNode *) malloc(sizeof(eventNode));
    head->next = NULL;
    return head;
}

//push a event into list(type 0 case)
//calculate time spent(type 1 case)
void manipulateEvent(eventNode *list, event event) {
    if (!event.type) {
        eventNode *node = initEventNode();
        node->event = event;
        while (list->next)
            list = list->next;
        list->next = node;
    } else {
        int index = event.index;
        do {
            list = list->next;
            if (list->event.index == index) {
                list->event.type = 2;
                list->event.time = event.time - list->event.time;
                break;
            }
        } while (list->next);
    }
}

typedef struct {
    struct node {
        int index;
        struct node *next;
    };
    struct node *front;
    struct node *rear;
} queue;
queue bank[4];

queue *initQueue() {
    queue *q = (queue *) malloc(sizeof(queue));
    q->rear = q->front = (struct node *) malloc(sizeof(struct node));
    q->front->next = NULL;
    return q;
}

int len(queue *queue) {
    int length = 0;
    struct node *node = queue->front;
    for (length = 0; node->next; length++)
        node = node->next;
    return length;
}


int main(int argc, char const *argv[]) {
    int index = 0;

    return 0;
}
