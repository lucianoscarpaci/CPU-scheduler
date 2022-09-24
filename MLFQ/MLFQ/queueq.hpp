//
//  queueq.hpp
//  MLFQ
//
//  Created by luciano scarpaci on 9/24/22.
//

#ifndef queueq_hpp
#define queueq_hpp

#include "processq.hpp"

class Queue
{
public:
    Queue();
    Queue(string name);
    Queue(vector<Process> processes, string name);
    void printReadyQueue();
    void printIOQueue(int time);
    int runPS(int CPUTime, Queue& IOQueue, Queue& completed);
    void printData();
    void addNewProcess(Process process);
    void popFirstItem();
    void checkIOstate(int time, Queue& readyQueue);
    void sortIOqueue();
    int getIdle();
    int getArrivalOfFirstItem();
    int checkEmpty();
    
private:
    vector<Process> process;
    string name;
    int idle = 0;
};

#endif /* queueq_hpp */
