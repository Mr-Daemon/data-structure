/*******************************************************************************
* FileName:         SeqStack.cpp
* Author:           Your_Name
* Student Number:   3019244xxx
* Date:             2020/03/04 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #4
*******************************************************************************/
#include "SeqStack.h"
#include <stdlib.h>

SeqStack::SeqStack()
{
    SeqList = (int *)malloc(MAX_ELEMENTS * sizeof(int));
    data_top = 0;
}
SeqStack::~SeqStack()
{
    free(SeqList);
}
void SeqStack::push_back(int data)
{
    SeqList[data_top++] = data;
}
int SeqStack::top() const
{
    return SeqList[data_top - 1];
}
void SeqStack::pop()
{
    data_top--;
}