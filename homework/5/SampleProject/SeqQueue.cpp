#include "SeqQueue.h"
#include <stdlib.h>

const int SeqQueue::LENGTH = 10;

SeqQueue::SeqQueue()
{
    queue = (int *)malloc(SeqQueue::LENGTH * sizeof(int));
    front_idx = rear_idx = 0;
}
SeqQueue::~SeqQueue()
{
    free(queue);
}
void SeqQueue::pop_front()
{
    front_idx = (front_idx + 1) % LENGTH;
}
void SeqQueue::push_back(int data)
{
    queue[rear_idx] = data;
    rear_idx = (rear_idx + 1) % LENGTH;
}
int SeqQueue::front() const
{
    return queue[front_idx];
}