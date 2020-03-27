//
// Created by cyb12 on 2020/3/23.
//

#ifndef DATA_STRUCTURE_JOB_H
#define DATA_STRUCTURE_JOB_H

#include "Queue.h"

class Job {
    struct task {
        int machine, time;
    };
    Queue<task> taskQueue;
    int tTime;

public:
    int arrivalTime;

    Job() {
        taskQueue = Queue<task>();
        arrivalTime = tTime = 0;
    }

    void addTask(int machine, int time) {
        taskQueue.enQueue({machine, time});
    }

    int rmTask(int time) {
        taskQueue.deQueue();
        tTime += (time - arrivalTime);
        return time - arrivalTime;
    }

    task currentTask() {
        return taskQueue.front();
    }

};


#endif //DATA_STRUCTURE_JOB_H
