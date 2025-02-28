# 🎉 Shortest Job First (SJF) Scheduling 🎉

Welcome to the world of CPU scheduling! The Shortest Job First (SJF) algorithm is a classic approach that selects the process with the smallest burst time. It's a non-preemptive algorithm, meaning once a process starts, it runs to completion. Let's dive into the results! 🚀

## 📊 Results Overview

```bash
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Completed Processes: P0 P1 P2 P3 P4 P5 P6 P7 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

### ⏱️ Total Time & CPU Utilization

- **Total Time to Complete All Processes:** 677
- **CPU Utilization:** 81.68% 💪

### ⏳ Waiting Time

```bash
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
P1, Waiting Time: 34
P2, Waiting Time: 118
P3, Waiting Time: 285
P4, Waiting Time: 39
P5, Waiting Time: 240
P6, Waiting Time: 150
P7, Waiting Time: 134
P8, Waiting Time: 112
Average Waiting Time: 139.00
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
```

### 🔄 Turnaround Time

```bash
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
P1, Turnaround Time: 259
P2, Turnaround Time: 545
P3, Turnaround Time: 677
P4, Turnaround Time: 523
P5, Turnaround Time: 549
P6, Turnaround Time: 365
P7, Turnaround Time: 462
P8, Turnaround Time: 421
Average Turnaround Time: 475.12
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
```

### 🔁 Response Time

```bash
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
P1, Response Time: 11
P2, Response Time: 3
P3, Response Time: 16
P4, Response Time: 0
P5, Response Time: 103
P6, Response Time: 24
P7, Response Time: 47
P8, Response Time: 7
Average Response Time: 26.38
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
```