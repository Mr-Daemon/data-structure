/*******************************************************************************
* FileName:         SeqList.cpp
* Author:           田原
* Student Number:   3015218126
* Date:             2020/02/18 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #1
*                   作业在这个文件中完成，需要补全SeqList类的实现，
*                   给出了构造函数与析构函数的例子.
*                   写明必要的注释
*******************************************************************************/

#include "SeqList.h"
#include <string.h>

/*
    使用初始化列表来初始化const变量LIST_SIZE，
    并动态分配LIST_SIZE长度的数组。
*/
SeqList::SeqList(const int &listSize) : LIST_SIZE(listSize)
{
    seq = new int[LIST_SIZE];
    // equal to:  seq = (int*) malloc(sizeof(int) * LIST_SIZE);
    len = 0;
}

SeqList::~SeqList()
{
    delete[] seq;
}

bool SeqList::isIn(const int &data)
{
    for (int i = 0; i < len; i++)
    {
        if (seq[i] == data)
            return true;
    }
    return false;
}

int SeqList::length()
{
    return len;
}

int SeqList::getData(const int &location)
{
    return seq[location];
}

bool SeqList::insert(const int &data, const int &location)
{
    if (len < LIST_SIZE)
    {
        for (int i = len; i > location; i--)
        {
            seq[i] = seq[i - 1];
        }
        seq[location] = data;
        len++;
        return true;
    }
    return false;
}

bool SeqList::remove(const int &location)
{
    if (location < len)
    {
        len--;
        for (int i = location; i < len; i++)
        {
            seq[i] = seq[i + 1];
        }
        return true;
    }
    return false;
}