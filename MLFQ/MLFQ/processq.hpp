//
//  processq.h
//  MLFQ
//
//  Created by luciano scarpaci on 9/24/22.
//

#ifndef processq_hpp
#define processq_hpp

#include <string>
#include <vector>
#include <stdlib>
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

#define ARRIVAL_TIME_UNSIG - 1

class Process {
    
    
public:
    Process();
    Process(string name, vector<int)> values);
    void setAT(int time);
    int getAT();
    void setPSstate(int state);
    int getPSstate();
    void calcTotalBurst();
    void setFirstAT(int time);
    void setLastTime(int time);
    string getName();
    int getData(int i);
    void set(int i, int value);
    void print();
    void popFirstItem();
    int processSize();
    int getTotalBurst();
    int getFirstAT();
    int getLastTime();
    int setPriorityQueue(int queue);
    
private:
    string name;
    int AT = 0;
    vector<int> data;
    int PSstate = 0;
    int totalBurst;
    int firstAT;
    int lastTime = 0;
    int priorityQueue = 1;
    
    
    
};


#endif /* processq_h */
