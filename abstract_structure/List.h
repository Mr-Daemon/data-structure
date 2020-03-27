//
// Created by cyb12 on 2020/2/14.
//

#ifndef DATA_STRUCTURE_LIST_H
#define DATA_STRUCTURE_LIST_H

template<typename T>
class List {
protected:
    virtual bool empty() = 0;
    virtual void clear() = 0;
    virtual int size() = 0;
    virtual int search(T) = 0;
    virtual T get(int) = 0;
    virtual void add(T) = 0;
    virtual void add(T, int) = 0;
    virtual void erase(int) = 0;
    virtual void output() = 0;
};

#endif //DATA_STRUCTURE_LIST_H
