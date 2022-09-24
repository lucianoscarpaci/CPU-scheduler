//
//  processq.cpp
//  MLFQ
//
//  Created by luciano scarpaci on 9/24/22.
//

#include "processq.hpp"

Process::Process() :
    totalBurst(0),
    firstAT(ARRIVAL_TIME_UNSIG)
{
    
}

Process::Process(string name, vector<int> values):
    totalBurst(0),
    firstAT(ARRIVAL_TIME_UNSIG)
{
    this->name = name;
    this->data = values;
    calcTotalBurst();
}

//shows the arrival time at the moment the process is at ready
int Process::getAT()
{
    return AT;
}
//setting arrival
void Process::setAT(int time)
{
    AT = time;
}
//shows the process state
int Process::getPSstate()
{
    return PSstate;
}
//setting process state to different state
void Process::setPSstate(int state)
{
    PSstate = state;
}
//calculate all the bursts together, both CPU and I/O bursts
void Process::calcTotalBurst()
{
    totalBurst = 0;
    for(int i = 0; i < data.size(); i++) //looping through the input data vector and incrementing
    {
        totalBurst += data[i]
    }
}
//first CPU arrival time while its running
void Process:setFirstAT(int time)
{
    firstAT = time;
}
//last arrival time while its running
void Process::setLastAT(int time)
{
    lastAT = time;
}
//returns the process name
string Process::getName()
{
    return name;
}
//return the input data
int Process::getdata(int i)
{
    return data[i];
}

void Process::set(int i, int value)
{
    data[i] = value;
}

//print all the process
void Process::print()
{
    for (int i=0; i < data.size(); i++)
    {
        cout << data[i] << ", ";
    }
    cout << endl;
}
//pop the first from the queue
void Process::popFirstItem()
{
    data.erase(data.begin());
}

int Process::processSize()
{
    return int(data.size());
}

int Process::getTotalBurst()
{
    return totalBurst;
}

int Process::getFirstAT()
{
    return firstAT;
}

int Process::getLastAT()
{
    return lastAT;
}

int Process::getPriorityQueue()
{
    return priorityQueue;
}

void Process::setPriorityQueue(int queue)
{
    priorityQueue = queue;
}


