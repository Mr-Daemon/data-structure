/*******************************************************************************
* FileName:         LinkStack.cpp
* Author:           Your_Name
* Student Number:   3019244xxx
* Date:             2020/03/04 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #4
*******************************************************************************/

#include "LinkStack.h"
#include <stdlib.h>

LinkStack::LinkStack()
{
    head = (StackNode *)malloc(sizeof(StackNode));
    length = 0;
}
LinkStack::~LinkStack()
{
    StackNode *cur;
    for (int i = 0; i <= length; i++)
    {
        cur = head;
        head = head->next;
        free(cur);
    }
}

void LinkStack::push_back(int data)
{
    StackNode *cur = head;
    for (int i = 0; i < length; i++)
    {
        cur = cur->next;
    }
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->value = data;
    cur->next = node;
    length++;
}

int LinkStack::top() const
{
    StackNode *cur = head;
    for (int i = 0; i < length; i++)
    {
        cur = cur->next;
    }
    return cur->value;
}

void LinkStack::pop()
{
    StackNode *cur = head;
    for (int i = 0; i < length; i++)
    {
        cur = cur->next;
    }
    free(cur);
    length--;
}