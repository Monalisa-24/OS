#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int waitingTime;
    int turnAroundTime;
    bool isCompleted;
};

void calculate(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime) {
                if (processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    idx = i;
                } else if (processes[i].priority == highestPriority) {
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

    double totalWaitingTime = 0;
    double totalTurnAroundTime = 0;

    printf("\nProcess\tArrival Time\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid, processes[i].arrivalTime, processes[i].priority,
               processes[i].burstTime, processes[i].waitingTime, processes[i].turnAroundTime);
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWaitingTime / n);
    printf("Average Turn Around Time = %.2f\n", totalTurnAroundTime / n);
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
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].isCompleted = false;
    }

    calculate(processes, n);

    return 0;
}


/*
Enter the number of processes: 5
Enter the details for Process 1:
Arrival Time: 0
Burst Time: 5
Priority: 3
Enter the details for Process 2:
Arrival Time: 4
Burst Time: 3
Priority: 2
Enter the details for Process 3:
Arrival Time: 5
Burst Time: 2
Priority: 4
Enter the details for Process 4:
Arrival Time: 9
Burst Time: 7
Priority: 1
Enter the details for Process 5:
Arrival Time: 12
Burst Time: 6
Priority: 5

Process     ArrivalTime     Priority        Burst Time      Waiting Time    Turnaround Time
P1              0               3               5               0               5
P2              4               2               3               1               4
P3              5               4               2               3               5
P4              9               1               7               1               8
P5              12              5               6               5               11

Average Waiting Time = 2.00
Average Turn Around Time = 6.60
*/