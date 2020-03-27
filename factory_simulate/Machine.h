//
// Created by cyb12 on 2020/3/23.
//

#ifndef DATA_STRUCTURE_MACHINE_H
#define DATA_STRUCTURE_MACHINE_H

#include "Queue.h"
#include "Job.h"

class Machine {
    static const int LARGE_TIME = 100000;
    enum State {
        Idle,
        Working,
        Change
    };
    int id;
    int changeTime;
    int waitTime;
    int taskNum;
    int finishTime;
    Queue<Job *> jobQueue;
    Job *activeJob;
    State state;
public:
    Machine(int id, int changeTime) : id(id), changeTime(changeTime), finishTime(LARGE_TIME) {
        jobQueue = Queue<Job *>();
        activeJob = nullptr;
        taskNum = waitTime = 0;
        state = Idle;
    }

    Job *changeState(int &clock) {
        auto lastJob = activeJob;
        if (state == Working) {
            clock = finishTime;
            taskNum++;
            waitTime += activeJob->rmTask(clock);
            activeJob = nullptr;
            state = Change;
            finishTime += changeTime;
        } else if (state == Change) {
            clock = finishTime;
            if (jobQueue.empty()) {
                finishTime = LARGE_TIME;
                state = Idle;
            } else {
                activeJob = jobQueue.deQueue();
                activeJob->arrivalTime = clock;
                finishTime += activeJob->currentTask().time;
                state = Working;
            }
        }
        return lastJob;
    }

    void changeState(int &clock, Job *job) {
        if (state == Idle) {
            state = Working;
            activeJob = job;
            finishTime += activeJob->currentTask().time;
        } else {
            jobQueue.enQueue(job);
        }
    }

    int getFinishTime() {
        return finishTime;
    }
};


#endif //DATA_STRUCTURE_MACHINE_H
