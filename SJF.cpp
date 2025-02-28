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

typedef pair<int, int> om;
void start_sjf(vector<vector<int>> process_p, priority_queue<om, vector<om>, 
greater<om>> ready_queue, vector<int> process_burst_index);
void print_all_completed_process(vector<int> completed_p);
void print_all_queue(priority_queue<om, vector<om>, greater<om>> que, vector<vector<int>> process_p, vector<int> process_burst_index);
void print_all_context_switch(vector<vector<int>> process_p, int process_index, priority_queue<om, vector<om>, greater<om>> ready_queue, 
vector<int> process_burst_index, int time);

int main(int argc, char const* argv[]){

    int num_p = 8;
    vector<vector<int>> process_p(num_p);
    priority_queue<om, vector<om>, greater<om>> ready_queue_SJF;
    vector <int> process_burst_index(num_p, 0);
    process_p[0] = {5, 27, 3, 31, 5, 43, 4, 18, 6, 22, 4, 26, 3, 24, 4};
    process_p[1] = {4, 48, 5, 44, 7, 42, 12, 37, 9, 76, 4, 41, 9, 31, 7, 43, 8};
    process_p[2] = {8, 33, 12, 41, 18, 65, 14, 21, 4, 61, 15, 18, 14, 26, 5, 31, 6};
    process_p[3] = {3, 35, 4, 41, 5, 45, 3, 51, 4, 61, 5, 54, 6, 82, 5, 77, 3};
    process_p[4] = {16, 24, 17, 21, 5, 36, 16, 26, 7, 31, 13, 28, 11, 21, 6, 13, 3, 11, 4};
    process_p[5] = {11, 22, 4, 8, 5, 10, 6, 12, 7, 14, 9, 18, 12, 24, 15, 30, 8};
    process_p[6] = {14, 46, 17, 41, 11, 42, 15, 21, 4, 32, 7, 19, 16, 33, 10};
    process_p[7] = {4, 14, 5, 33, 6, 51, 14, 73, 16, 87, 6};
    
    /* loop through process_p, construct a pair object with process_p index, and process burst index,
    push index into top of stack ready queue */
    for(int i=0; i < process_p.size(); i++){
        ready_queue_SJF.push(make_pair(process_p[i][process_burst_index[i]],i));
    }
    /* sjf takes in each process, the ready queue, and process burst index */
    start_sjf(process_p, ready_queue_SJF, process_burst_index);
    
    return 0;
}

void start_sjf(vector<vector<int>> process_p, priority_queue<om, vector<om>, greater<om>> ready_queue, vector<int> process_burst_index){

    vector<pair<int, int>> io_return;
    vector<int> arrival_time(process_p.size(), 0);
    vector<int> waiting_time(process_p.size(), 0);
    vector<int> turn_around_time(process_p.size(), 0);
    vector<int> response_time(process_p.size(), -1);
    vector<int> completed_p(process_p.size(), 0);

    for(int i=0; i < process_p.size(); i++){
        io_return.push_back(make_pair(INT_MAX, i));
    }
    int time = 0;
    int idle_cpu_time = 0;

    while(!ready_queue.empty()){

        int process_index = ready_queue.top().second;
        ready_queue.pop();

        /* calculate waiting time */
        waiting_time[process_index] += time - arrival_time[process_index];

        if(response_time[process_index] == -1){
            /* calculate response time */
            response_time[process_index] = time - arrival_time[process_index];
        }
        /* print the context switch */
        print_all_context_switch(process_p, process_index, ready_queue, process_burst_index, time);
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
        else {
            completed_p[process_index] = 1;
        }
        print_all_completed_process(completed_p);
        process_burst_index[process_index] += 2;

        sort(io_return.begin(), io_return.end());

        /* while ready queue is empty, ioreturn first is not equal to ioreturn first
        and greater than time. Count time and idle cpu time */

        if(ready_queue.empty()){
            while(io_return[0].first != INT_MAX && io_return[0].first > time)
            {
                time++;
                idle_cpu_time++;
            }
        }

            for(int i=0; i < process_p.size(); i++){
                if(io_return[i].first <= time){
                    /* fixed error, member .push was accidently overloading twice */ 
                    ready_queue.push(make_pair(process_p[io_return[i].second]
                    [process_burst_index[io_return[i].second]],io_return[i].second));
                    arrival_time[io_return[i].second] = io_return[i].first;
                    io_return[i].first = INT_MAX;
                }
            }
        }
       /* the burst time, total burst time, and turn around time */
        int burst_time = time - idle_cpu_time;

        for(int i=0; i < process_p.size(); i++){
            int total_burst_time=0;
            for(int j=0; j<process_p[i].size(); j++){
                total_burst_time += process_p[i][j];
            }
            turn_around_time[i] += total_burst_time + waiting_time[i];
        }


        cout << BLUE << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
        cout << BLUE << "total time to complete all processes: "<<time<<endl;
        cout << BLUE << "CPU Utilization: "<<fixed<<setprecision(2)<<(double)burst_time/time*100 << "%"<<endl<<endl;
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

/* print the queue such as process id, burst index of process id */
void print_all_queue(priority_queue<om, vector<om>, greater<om>> que, vector<vector<int>> process_p, vector<int> process_burst_index)
{
    cout<<setfill(' ')<<setw(10)<<"Process"<<setw(10)<<"Burst"<<endl;
    if (!que.empty()){
        while (!que.empty()){
            /* indicates where pid is */
            int pid = que.top().second;
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
/* fixed error here, needed priority queue */
void print_all_context_switch(vector<vector<int>> process_p, int process_index, priority_queue <om, vector<om>, greater<om>> ready_queue, 
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

