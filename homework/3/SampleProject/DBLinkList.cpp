/*******************************************************************************
* FileName:         DBLinkList.cpp
* Author:           Your_Name
* Student Number:   3019244xxx
* Date:             2020/03/04 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #3
*******************************************************************************/

#include "DBLinkList.h"
#include <stdlib.h>

DBLinkList::DBLinkList()
{
    head = (DBNode *)malloc(sizeof(DBNode));
    *head = {nullptr, nullptr, 0};
    len = 0;
}

DBLinkList::~DBLinkList()
{
    DBNode *cur = head;
    while (cur->nxt)
    {
        cur = cur->nxt;
        free(cur->pre);
    }
    free(cur);
}

void DBLinkList::insert(int data, int location)
{
    DBNode *newNode = (DBNode *)malloc(sizeof(DBNode));
    DBNode *cur = head;
    for (int i = 0; i < location; i++)
    {
        cur = cur->nxt;
    }
    *newNode = {cur, cur->nxt, data};
    if (cur->nxt)
        cur->nxt->pre = newNode;
    cur->nxt = newNode;
    len++;
}

void DBLinkList::remove(int location)
{
    DBNode *cur = head;
    for (int i = 0; i < location; i++)
    {
        cur = cur->nxt;
    }
    DBNode *nxt = cur->nxt->nxt;
    nxt->pre = cur;
    free(cur->nxt);
    cur->nxt = nxt;
    len--;
}

int DBLinkList::length()
{
    return len;
}

int DBLinkList::getData(int location)
{
    DBNode *cur = head->nxt;
    for (int i = 0; i < location; i++)
    {
        cur = cur->nxt;
    }
    return cur->value;
}

void DBLinkList::bubbleSort()
{
    DBNode *cur = head;
    for (int i = len - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            cur = cur->nxt;
            if (cur->value > cur->nxt->value)
            {
                DBNode *nxt = cur->nxt;
                nxt->pre = cur->pre;
                nxt->pre->nxt = nxt;
                cur->pre = nxt;
                cur->nxt = nxt->nxt;
                if (cur->nxt)
                    cur->nxt->pre = cur;
                nxt->nxt = cur;
                cur = nxt;
            }
        }
        cur = head;
    }
}