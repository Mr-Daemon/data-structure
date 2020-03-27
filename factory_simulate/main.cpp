//
// Created by cyb12 on 2020/3/23.
//

#include <cstdio>
#include "Queue.h"
#include "LinkedList.h"

int main(int argc, char const *argv[]) {

    LinkedList<int> list;
    list.add(1);
    list.add(2);
    printf("%d %d", list[0], list.size());
    return 0;
}