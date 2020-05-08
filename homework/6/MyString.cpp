/*******************************************************************************
* FileName:         MyString.cpp
* Author:           Your_Name
* Student Number:   3018216xxx
* Date:             2020/03/18 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #3
*                   完成程度：
*                       简要说一下自己写了多少，完成了哪些函数
*******************************************************************************/
#include <cstdio>
#include <cstdlib>
#include "MyString.h"

MyString::MyString(const char *str)
{
    len = strlen(str);
    c_str = (char *)malloc((len + 1) * sizeof(char));
    strcpy(c_str, str);
}

MyString::~MyString()
{
    free(c_str);
}

int MyString::length() const
{
    return len;
}

void MyString::replace(const char *replace, int loc)
{
    if (strlen(replace) + loc > len)
    {
        len = strlen(replace) + loc;
        c_str = (char *)realloc(c_str, (len + 1) * sizeof(char));
        c_str[len] = '\0';
    }
    strcpy(c_str + loc, replace);
}

void preprocess(const char *str, int *list, int len)
{
    memset(list, 0, len * sizeof(int));
    int i = 0, j = 1;
    while (j < len)
    {
        if (str[i] == str[j])
        {
            i++;
            list[j] = i;
            j++;
        }
        else if (i > 0)
        {
            i = list[i - 1];
        }
    }
}

int MyString::find(const char *str) const
{
    int length = strlen(str);
    int list[length];
    preprocess(str, list, length);
    int i = 0, j = 0;
    while (i <= len)
    {
        if (j == length)
        {
            return i - j;
        }
        else if (c_str[i] == str[j])
        {
            i++;
            j++;
        }
        else if (!j)
        {
            i++;
        }
        else
        {
            j = list[j - 1];
        }
    }
    return -1;
}

const char *MyString::c_string() const
{
    char *ptr = (char *)malloc((len + 1) * sizeof(char));
    strcpy(ptr, c_str);
    return ptr;
}