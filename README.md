# 🚀 CPU-scheduler
An RTOS simulation of FCFS, and MLFQ scheduling.

The results of this experiment prove that MLFQ is better than FCFS in terms of CPU utilization, waiting time, turnaround time, and response time. MLFQ has significantly better performance than FCFS. 🎉

## 💻 Steps to run the code in the terminal
```bash
g++ -std=c++11 -o PROJ PROJ.cpp && ./PROJ
```

## 🐞 Debug in Visual Studio Code with gdb
To debug C++ code in Visual Studio Code, ensure you have the following prerequisites:
- Visual Studio Code installed
- C++ extension for Visual Studio Code
- `g++` and `gdb` installed on your system

### Setup Instructions

1. **Configure `tasks.json`:**
   - Define a task to compile your C++ code with `g++`. For example:
     ```json
     {
       "version": "2.0.0",
       "tasks": [
         {
           "label": "build",
           "type": "shell",
           "command": "g++",
           "args": "-std=c++11", //Add the -std=c++11 here
           "group": {
             "kind": "build",
             "isDefault": true
           }
         }
       ]
     }
     ```

2. **Configure `launch.json`:**
   - Set the `miDebuggerPath` to your installation path of `gdb`. For example:
     ```json
     {
       "version": "0.2.0",
       "configurations": [
         {
           "name": "(gdb) Launch",
           "type": "cppdbg",
           "request": "launch",
           "program": "${workspaceFolder}/your_program",
           "args": [],
           "stopAtEntry": false,
           "cwd": "${workspaceFolder}",
           "environment": [],
           "externalConsole": false,
           "MIMode": "gdb",
           "miDebuggerPath": "/usr/local/bin/gdb", // Update this path to gdb here
           "setupCommands": [
             {
               "description": "Enable pretty-printing for gdb",
               "text": "-enable-pretty-printing",
               "ignoreFailures": true
             }
           ],
           "preLaunchTask": "build"
         }
       ]
     }
     ```



## 📊 FCFS RESULTS
```bash
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Completed Processes: P0 P1 P2 P4 P5 P6 P7 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Current Execution Time: 645

Next process on the CPU: P3
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ready queue:
   Process     Burst
   [empty]       N/A

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Completed Processes: P0 P1 P2 P3 P4 P5 P6 P7 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
total time to complete all processes: 648
CPU Utilization: 85.34%

$$$$$$$$$$$$$$$$$$$$$$$$$$$$
$$$$$$$$$$$$$$$$$$$$$$$$$$$$
Waiting Time:
P0, Waiting Time: 170
P1, Waiting Time: 164
P2, Waiting Time: 165
P3, Waiting Time: 164
P4, Waiting Time: 221
P5, Waiting Time: 230
P6, Waiting Time: 184
P7, Waiting Time: 184
Average Waiting Time: 185.25

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
Turnaround Time: 
P0, Turnaround Time: 395
P1, Turnaround Time: 591
P2, Turnaround Time: 557
P3, Turnaround Time: 648
P4, Turnaround Time: 530
P5, Turnaround Time: 445
P6, Turnaround Time: 512
P7, Turnaround Time: 493
Average Turnaround Time: 521.38

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
Response Time
P0, Response Time: 0
P1, Response Time: 5
P2, Response Time: 9
P3, Response Time: 17
P4, Response Time: 20
P5, Response Time: 36
P6, Response Time: 47
P7, Response Time: 61
Average Response Time: 24.38
```

## 📈 MLFQ RESULTS
```bash
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Completed Processes: 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
total time to complete all processes: 82
CPU Utilization: 100.00%

$$$$$$$$$$$$$$$$$$$$$$$$$$$$
$$$$$$$$$$$$$$$$$$$$$$$$$$$$
Waiting Time:
P0, Waiting Time: 33
P1, Waiting Time: 25
P2, Waiting Time: 26
P3, Waiting Time: 35
P4, Waiting Time: 34
P5, Waiting Time: 39
P6, Waiting Time: 45
P7, Waiting Time: 50
Average Waiting Time: 35.88

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
Turnaround Time: 
P0, Turnaround Time: 258
P1, Turnaround Time: 452
P2, Turnaround Time: 413
P3, Turnaround Time: 519
P4, Turnaround Time: 328
P5, Turnaround Time: 249
P6, Turnaround Time: 368
P7, Turnaround Time: 359
Average Turnaround Time: 368.25

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
Response Time
P0, Response Time: 0
P1, Response Time: 5
P2, Response Time: 9
P3, Response Time: 14
P4, Response Time: 17
P5, Response Time: 22
P6, Response Time: 27
P7, Response Time: 32
Average Response Time: 15.75
