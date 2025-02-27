/* Luciano Scarpaci
Created Oct 1st, 2022
*/
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<queue>
#include<functional>

#define GREEN "\033[32m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"
#define YELLOW "\033[33m"
#define BLUE "\033[1m\033[34m"
#define RED "\033[1m\033[31m"

using namespace std;

void start_mlfq(vector<vector<int>> process_p, queue<int> rr_ready_queue, vector<int> process_burst_index);
void print_all_completed_process(vector<int> completed_p);
void print_all_queue(queue<int> que, vector<vector<int>> process_p, vector<int> process_burst_index);
void print_all_context_switch(vector<vector<int>> process_p, int process_index, queue<int> ready_queue, 
vector<int> process_burst_index, int time);

int main(int argc, char const* argv[]){

    int num_p = 8;
    vector<vector<int>> process_p(num_p);
    queue<int> rr_ready_queue;
    vector <int> process_burst_index(num_p, 0);
    process_p[0] = {5, 27, 3, 31, 5, 43, 4, 18, 6, 22, 4, 26, 3, 24, 4};
    process_p[1] = {4, 48, 5, 44, 7, 42, 12, 37, 9, 76, 4, 41, 9, 31, 7, 43, 8};
    process_p[2] = {8, 33, 12, 41, 18, 65, 14, 21, 4, 61, 15, 18, 14, 26, 5, 31, 6};
    process_p[3] = {3, 35, 4, 41, 5, 45, 3, 51, 4, 61, 5, 54, 6, 82, 5, 77, 3};
    process_p[4] = {16, 24, 17, 21, 5, 36, 16, 26, 7, 31, 13, 28, 11, 21, 6, 13, 3, 11, 4};
    process_p[5] = {11, 22, 4, 8, 5, 10, 6, 12, 7, 14, 9, 18, 12, 24, 15, 30, 8};
    process_p[6] = {14, 46, 17, 41, 11, 42, 15, 21, 4, 32, 7, 19, 16, 33, 10};
    process_p[7] = {4, 14, 5, 33, 6, 51, 14, 73, 16, 87, 6};

    for(int i=0; i < process_p.size(); i++){
        rr_ready_queue.push(i); //enqueue the processes
    }

    start_mlfq(process_p, rr_ready_queue, process_burst_index);

    return 0;

}

void start_mlfq(vector<vector<int>> process_p, queue<int> rr_ready_queue, vector<int> process_burst_index)
{
    int num_p = process_p.size();
    vector<int> in_queue (num_p, 1);
    vector<int> arrival_time(process_p.size(), 0);
    vector<int> waiting_time(process_p.size(), 0);
    vector<int> turn_around_time(process_p.size(), 0);
    vector<int> response_time(process_p.size(), -1);
    vector<int> completed_p(process_p.size(), 0);
    vector<pair<int, int>> io_return;
    queue<int> rr2_ready_queue;
    queue<int> ready_queue_FCFS;

    for(int i=0; i < process_p.size(); i++){
        io_return.push_back(make_pair(INT_MAX, i));
    }
    int time = 0;
    int idle_cpu_time = 0;
    int tq1 = 5, tq2 = 10;

    while(!rr_ready_queue.empty() || !rr2_ready_queue.empty() || !ready_queue_FCFS.empty()){
    
        if(!rr_ready_queue.empty()){
            
            int process_index = rr_ready_queue.front(); //process index = 0
            rr_ready_queue.pop(); //process 1

            /* calculate waiting time */
            waiting_time[process_index] += time - arrival_time[process_index];

            if(response_time[process_index] == -1){
                /* calculate response time */
                response_time[process_index] = time - arrival_time[process_index]; //set response time to 0
            }
            /* get cpu bust time*/
            int getBurstTime = process_p[process_index][process_burst_index[process_index]]; // set burst time to 5
            /* print the context switch */
            print_all_context_switch(process_p, process_index, rr_ready_queue, process_burst_index, time);

            if(getBurstTime > tq1){ //5 > 5
                time += tq1;
                process_p[process_index][process_burst_index[process_index]] = getBurstTime - tq1;

                rr2_ready_queue.push(process_index);
                in_queue[process_index] = 2;
                arrival_time[process_index] = time + tq1;
            }
            else {
                time += getBurstTime; //5
                if(process_burst_index[process_index] <= process_p[process_index].size()-3){
                    for(int i=0; i<process_p.size(); i++){
                        if(io_return[i].second == process_index){
                            io_return[i].first = process_p[process_index][process_burst_index[process_index]+1] + time; //ioreturn first is 32
                            break;
                        }
                    }
                }
                else {
                    completed_p[process_index] = 1;
                }
                print_all_completed_process(completed_p); //completed process = 0
                process_burst_index[process_index] += 2;
            }

        }
        else if(!rr2_ready_queue.empty()){
            int process_index = rr2_ready_queue.front();
            rr2_ready_queue.pop();

            /* calculate waiting time */
            waiting_time[process_index] += time - arrival_time[process_index];
            /* get cpu bust time*/
            int getBurstTime = process_p[process_index][process_burst_index[process_index]];
            /* print the context switch */
            print_all_context_switch(process_p, process_index, rr2_ready_queue, process_burst_index, time);

            if(getBurstTime > tq2){
                time += tq2;
                process_p[process_index][process_burst_index[process_index]] = getBurstTime - tq2;

                ready_queue_FCFS.push(process_index);
                in_queue[process_index] = 3;
                arrival_time[process_index] = time + tq2;
            }
            else {
                time += getBurstTime;
                if(process_burst_index[process_index] <= process_p[process_index].size()-3){
                    for(int i=0; i<process_p.size(); i++){
                        if(io_return[i].second == process_index){
                            io_return[i].first = process_p[process_index][process_burst_index[process_index]+1] + time;
                            break;
                        }
                    }
                }
                else {
                    completed_p[process_index] = 1;
                }
                print_all_completed_process(completed_p);
                process_burst_index[process_index] += 2;
            }
        }
        else if(!ready_queue_FCFS.empty()){
            int process_index = ready_queue_FCFS.front();
            ready_queue_FCFS.pop();

            /* calculate waiting time */
            waiting_time[process_index] += time - arrival_time[process_index];
            /* print the context switch */
            print_all_context_switch(process_p, process_index, ready_queue_FCFS, process_burst_index, time);
            /* current execution time */
            time += process_p[process_index][process_burst_index[process_index]];

            if(process_burst_index[process_index] <= process_p[process_index].size()-3){
                for(int i=0; i < process_p.size(); i++){
                    if(io_return[i].second == process_index){
                        io_return[i].first = process_p[process_index][process_burst_index[process_index]+1] + time;
                        break;
                    }
                }
            } 
            /* while ready queue is not empty, set completed processes to final state 
            and print completed process. Sort the io_return inorder */
            else{
                completed_p[process_index] = 1;
            }
            print_all_completed_process(completed_p);
            process_burst_index[process_index] += 2; //set to 2

            sort(io_return.begin(), io_return.end());

            if(rr_ready_queue.empty() && rr2_ready_queue.empty() && ready_queue_FCFS.empty()){
                while(io_return[0].first != INT_MAX && io_return[0].first > time)
                {
                    time++;
                    idle_cpu_time++;
                }
            }
    

            for(int i=0; i < process_p.size(); i++){
                if(io_return[i].first <= time){
                    if(in_queue[io_return[i].second]==1) rr_ready_queue.push(io_return[i].second);

                    else if(in_queue[io_return[i].second]==2) rr2_ready_queue.push(io_return[i].second);

                    else ready_queue_FCFS.push(io_return[i].second);
                    arrival_time[io_return[i].second] = io_return[i].first;
                    io_return[i].first = INT_MAX;
                }
            }
        
        }
        /* the burst time, total burst time, and turn around time */
        int burst_time = time - idle_cpu_time; //total burst time = 5

        for(int i=0; i < process_p.size(); i++){
            int total_burst_time=0;
            for(int j=0; j<process_p[i].size(); j++){
                total_burst_time += process_p[i][j]; // 5, 32, 35, 66, 71, 114, 118, 136, 142, 164, 168, 194, 197, 221, 225
            }
            turn_around_time[i] = total_burst_time + waiting_time[i]; //225, 427, 392, 484, 309, 215, 328, 309
        }

        cout << BLUE << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
        cout << BLUE << "total time to complete all processes: "<<time<<endl; 
        cout << BLUE << "CPU Utilization: "<<fixed<<setprecision(2)<<(double)burst_time/time*100 << "%"<<endl<<endl; // 100% CPU utilization
        cout << CYAN << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
        cout << CYAN << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

        cout << GREEN << "Waiting Time:"<<endl;

        /* the waiting time, average waiting time */
        int total_waiting_time = 0;

        for(int i=0; i < process_p.size(); i++){
            cout << "P" + to_string(i) << ", Waiting Time: "<<waiting_time[i]<<endl;
            total_waiting_time += waiting_time[i];
        }

        cout << "Average Waiting Time: "<<fixed<<setprecision(2)<<(double)total_waiting_time/process_p.size()<<endl<<endl;
        cout << CYAN << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
        cout << CYAN << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
        cout << MAGENTA << "Turnaround Time: "<<endl;

        /* turnaround time, total turn around time, average turn around time */
        int total_turnaround_time = 0;
        for (int i=0; i < process_p.size(); i++) {
            cout << "P" + to_string(i) << ", Turnaround Time: "<<turn_around_time[i]<<endl;
            total_turnaround_time += turn_around_time[i];
        }
        cout << "Average Turnaround Time: "<<fixed<<setprecision(2)<<(double)total_turnaround_time/process_p.size()<<endl<<endl;
        cout << CYAN << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
        cout << CYAN << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

        /* response time, total response time, average response time */
        cout << YELLOW << "Response Time"<<endl;
        int total_response_time = 0;
        for(int i=0; i < process_p.size(); i++){
            cout << "P" + to_string(i) << ", Response Time: "<<response_time[i]<<endl;
            total_response_time += response_time[i];
        }
        cout<< YELLOW << "Average Response Time: "<<fixed<<setprecision(2)<<(double)total_response_time/process_p.size()<<endl;
    }
}


void print_all_queue(queue<int> que, vector<vector<int>> process_p, vector<int> process_burst_index)
{
    cout<<setfill(' ')<<setw(10)<<"Process"<<setw(10)<<"Burst"<<endl;
    if (!que.empty()){
        while (!que.empty()){
            /* indicates where pid is */
            int pid = que.front();
            cout<<setfill(' ')<<setw(10)<<"P"<<pid<<setw(10)<<process_p[pid][process_burst_index[pid]]<<endl;
            que.pop();
        }
    }
    /* process is empty, burst index is empty */
    else
    {
        cout<<setfill(' ')<<setw(10)<<"[empty]"<<setw(10)<<"N/A"<<endl;
    }
    cout << endl;
}

void print_all_completed_process(vector<int> completed_p)
{
    /*print completed processes */
    cout<<"Completed Processes: ";
    for(int i=0; i < completed_p.size(); i++){
        if(completed_p[i] == 1){
            cout<<"P"<<i<<" ";
        }
    }
    cout<<endl;
    cout<<setfill('~')<<setw(41)<<"~"<<endl;
}

void print_all_context_switch(vector<vector<int>> process_p, int process_index, queue<int> ready_queue, 
vector<int> process_burst_index, int time)
{
    /* print current execution time, next process on cpu, and ready queue */
    cout<<setfill('~')<<setw(42)<<"~"<<endl;
    cout<< RED << "Current Execution Time: "<<time<<endl<<endl;
    cout<< RED << "Next process on the CPU: P"<<process_index<<endl;
    cout<<setfill('~')<<setw(41)<<"~"<<endl<<endl;
    cout<< RED << "Ready queue:"<<endl;
    print_all_queue(ready_queue, process_p, process_burst_index);
    cout<<setfill('~')<<setw(42)<<"~"<<endl;
}
