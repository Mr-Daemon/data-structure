//
// Created by cyb12 on 2020/3/23.
//

#ifndef DATA_STRUCTURE_FACTORY_H
#define DATA_STRUCTURE_FACTORY_H

#include "LinkedList.h"
#include "Job.h"
#include "Machine.h"

class Factory {
    LinkedList<Machine *> mList;
    LinkedList<Job *> jList;
    int clock;


public:
    Factory() : clock(0) {
        mList = LinkedList<Machine *>();
        jList = LinkedList<Job *>();
    }

    void addMachine(Machine *machine) {
        mList.add(machine);
    }

    void addJob(Job *job) {
        jList.add(job);
    }
};


#endif //DATA_STRUCTURE_FACTORY_H
