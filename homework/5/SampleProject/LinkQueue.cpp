#include "LinkQueue.h"
#include <stdio.h>
#include <stdlib.h>

LinkQueue::LinkQueue()
{
    rear = head = (node *)malloc(sizeof(node));
}

LinkQueue::~LinkQueue()
{
    node *temp;
    while (head != rear)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    free(head);
}

void LinkQueue::push_back(int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = data;
    rear->next = newNode;
    rear = newNode;
}

void LinkQueue::pop_front()
{
    node *temp = head->next->next;
    if (head->next == rear)
        rear = head;
    free(head->next);
    head->next = temp;
}

int LinkQueue::front() const
{
    return head->next->data;
}