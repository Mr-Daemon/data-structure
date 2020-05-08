/*******************************************************************************
* FileName:         LinkList.cpp
* Author:           Your_Name
* Student Number:   3019244xxx
* Date:             2020/02/26 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #2
*                   作业在这个文件中完成，需要补全LinkList类的实现，
*                   写明必要的注释
*******************************************************************************/

#include "LinkList.h"
#include "stdlib.h"
#include <stdio.h>

LinkList::LinkList()
{
    head = (node *)malloc(sizeof(node));
    head->next = nullptr;
    len = 0;
}

LinkList::~LinkList()
{
    node *cur = head;
    while (cur->next)
    {
        node *temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(cur);
}

int LinkList::length()
{
    return len;
}

int LinkList::getData(const int &location)
{
    node *cur = head->next;
    for (int i = 0; i < location; i++)
    {
        cur = cur->next;
    }
    return cur->value;
}

void LinkList::insert(const int &data, const int &location)
{
    node *cur = head;
    for (int i = 0; i < location; i++)
    {
        cur = cur->next;
    }
    node *target = (node *)malloc(sizeof(node));
    target->value = data;
    target->next = cur->next;
    cur->next = target;
    len++;
}

bool LinkList::remove(const int &location)
{
    if (location < len)
    {
        node *cur = head;
        for (int i = 0; i < location; i++)
        {
            cur = cur->next;
        }
        node *target = cur->next;
        cur->next = target->next;
        free(target);
        len--;
        return true;
    }
    return false;
}

void LinkList::converse()
{
    node *list[len];
    node *cur = head;
    for (int i = 0; i < len; i++)
    {
        cur = cur->next;
        list[i] = cur;
    }
    list[0]->next = nullptr;
    head->next = list[len - 1];
    for (int i = 1; i < len; i++)
    {
        list[i]->next = list[i - 1];
    }
}

void LinkList::append(const LinkList &append_list)
{
    node *cur = head;
    while (cur->next)
    {
        cur = cur->next;
    }
    cur->next = append_list.head->next;
    len += append_list.len;
}