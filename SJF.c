#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
    bool isCompleted;
};

void SJF(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;
    
    while (completed < n) {
        int idx = -1;
        int lowestBurstTime = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted) {
                if (processes[i].burstTime < lowestBurstTime) {
                    lowestBurstTime = processes[i].burstTime;
                    idx = i;
                } else if (processes[i].burstTime == lowestBurstTime) {
                    if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            processes[idx].waitingTime = currentTime - processes[idx].arrivalTime;
            processes[idx].turnAroundTime = processes[idx].waitingTime + processes[idx].burstTime;
            currentTime += processes[idx].burstTime;
            processes[idx].isCompleted = true;
            completed++;
        } else {
            currentTime++;
        }
    }

    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
            processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, 
            processes[i].waitingTime, processes[i].turnAroundTime);
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
    }

    printf("\nAverage Waiting Time = %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turn Around Time = %.2f\n", (float)totalTurnAroundTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the details for Process %d:\n", i + 1);
        processes[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        processes[i].waitingTime = 0;
        processes[i].turnAroundTime = 0;
        processes[i].isCompleted = false;
    }

    SJF(processes, n);

    return 0;
}


/*
Enter the number of processes: 5
Enter the details for Process 1:
Arrival Time: 2
Burst Time: 6
Enter the details for Process 2:
Arrival Time: 5
Burst Time: 2
Enter the details for Process 3:
Arrival Time: 1
Burst Time: 8
Enter the details for Process 4:
Arrival Time: 0
Burst Time: 3
Enter the details for Process 5:
Arrival Time: 4
Burst Time: 4

Process Arrival Time    Burst Time      Waiting Time    Turnaround Time
P1              2               6               1               7
P2              5               2               4               6
P3              1               8               14              22
P4              0               3               0               3
P5              4               4               7               11

Average Waiting Time = 5.20
Average Turn Around Time = 9.80
*/
