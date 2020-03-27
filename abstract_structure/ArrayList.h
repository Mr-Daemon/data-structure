//
// Created by cyb12 on 2020/2/14.
//
#include "List.h"
#include <cstdlib>
#include <cstring>

#ifndef DATA_STRUCTURE_ARRAYLIST_H
#define DATA_STRUCTURE_ARRAYLIST_H

template<typename T>
class ArrayList : List<T> {
    int length, capacity;
    T *array;
    const static int INIT_SIZE = 16;
    const static int INCREMENT = 16;
public:
    ArrayList();
    ArrayList(int);
    ~ArrayList();
    bool empty() override;
    void clear() override;
    int size() override;
    int search(T t) override;
    T get(int i) override;
    void add(T t) override;
    void add(T t, int i) override;
    void erase(int i) override;
    void output() override;

};

template<typename T>
ArrayList<T>::ArrayList():length(0), capacity(INIT_SIZE) {
    array = (T *) malloc(capacity * sizeof(T));
}


template<typename T>
ArrayList<T>::ArrayList(int capacity):length(0), capacity(capacity) {
    array = (T *) malloc(capacity * sizeof(T));
}

template<typename T>
ArrayList<T>::~ArrayList() {
    free(array);
}

template<typename T>
bool ArrayList<T>::empty() {
    return length;
}

template<typename T>
void ArrayList<T>::clear() {
    length = 0;
}

template<typename T>
int ArrayList<T>::size() {
    return length;
}

template<typename T>
int ArrayList<T>::search(T t) {
    for (int i = 0; i < length; ++i) {
        if (array[i] == t)
            return i;
    }
    return -1;
}

template<typename T>
T ArrayList<T>::get(int i) {
    if (i >= length)
        throw std::invalid_argument("out of bound");
    return array[i];
}

template<typename T>
void ArrayList<T>::add(T t) {
    add(t, length);
}

template<typename T>
void ArrayList<T>::add(T t, int i) {
    if (length + 1 >= capacity) {
        capacity += INCREMENT;
        array = (T *) realloc(array, capacity * sizeof(T));
    }
    T temp[length - i];
    memcpy(temp, array + i, sizeof(temp));
    array[i] = t;
    memcpy(array + i + 1, temp, sizeof(temp));
}

template<typename T>
void ArrayList<T>::erase(int i) {

}

template<typename T>
void ArrayList<T>::output() {

}


#endif //DATA_STRUCTURE_ARRAYLIST_H
