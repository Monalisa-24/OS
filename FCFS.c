#include <stdio.h> 
struct Process { 
    int pid; 
    int burstTime; 
    int arrivalTime; 
    int waitingTime; 
    int turnaroundTime; 
}; 
void findWaitingTime(struct Process proc[], int n) { 
    int serviceTime[n]; 
    serviceTime[0] = proc[0].arrivalTime; 
    proc[0].waitingTime = 0; 
    
    for (int i = 1; i < n ; i++) { 
    serviceTime[i] = serviceTime[i-1] + proc[i-1].burstTime; 
    proc[i].waitingTime = serviceTime[i] - proc[i].arrivalTime; 
    if (proc[i].waitingTime < 0) 
    proc[i].waitingTime = 0; 
    } 
} 
void findTurnaroundTime(struct Process proc[], int n) { 
    for (int i = 0; i < n ; i++) { 
    proc[i].turnaroundTime = proc[i].burstTime + proc[i].waitingTime; 
    } 
} 
void findAvgTime(struct Process proc[], int n) { 
    findWaitingTime(proc, n); 
    findTurnaroundTime(proc, n); 
    int totalWaitingTime = 0, totalTurnaroundTime = 0; 
    printf("Processes Burst Time Arrival Time Waiting Time Turnaround Time\n"); 
    for (int i = 0; i < n; i++) { 
    totalWaitingTime += proc[i].waitingTime; 
    totalTurnaroundTime += proc[i].turnaroundTime; 
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, 
    proc[i].burstTime, proc[i].arrivalTime, proc[i].waitingTime, 
    proc[i].turnaroundTime); 
    } 
    printf("Average waiting time = %.2f\n", (float)totalWaitingTime / 
    (float)n); 
    printf("Average turnaround time = %.2f\n", (float)totalTurnaroundTime / 
    (float)n); 
}

int main() { 
    int n; 
    printf("Enter the number of processes: "); 
    scanf("%d", &n); 
    struct Process proc[n]; 
    for (int i = 0; i < n; i++) { 
        proc[i].pid = i + 1; 
        printf("Enter arrival time for process %d: ", i + 1); 
        scanf("%d", &proc[i].arrivalTime); 
        printf("Enter burst time for process %d: ", i + 1); 
        scanf("%d", &proc[i].burstTime); 
    } 
    findAvgTime(proc, n); 
    return 0; 
}



/*
Enter the number of processes: 4
Enter arrival time for process 1: 0
Enter burst time for process 1: 10
Enter arrival time for process 2: 2
Enter burst time for process 2: 15
Enter arrival time for process 3: 4
Enter burst time for process 3: 3
Enter arrival time for process 4: 6
Enter burst time for process 4: 9
Processes Burst Time Arrival Time Waiting Time Turnaround Time
1               10              0               0               10
2               15              2               8               23
3               3               4               21              24
4               9               6               22              31
Average waiting time = 12.75
Average turnaround time = 22.00
*/