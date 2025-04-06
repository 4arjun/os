#include <stdio.h>

struct Process {
    int pid;
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    int isCompleted;
};

void printGanttChart(struct Process p[], int n) {
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n|");
    for (int i = 0; i < n; i++) {
        printf("  P%d  |", p[i].pid);
    }
    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf("-------");
    }

    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("      %d", p[i].completionTime);
    }
    printf("\n");
}

void printResult(struct Process p[], int n) {
    float totalWaiting = 0, totalTurnaround = 0;

    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime, p[i].waitingTime, p[i].turnaroundTime, p[i].completionTime);
        totalWaiting += p[i].waitingTime;
        totalTurnaround += p[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time = %.2f", totalWaiting / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTurnaround / n);
}

void sjfScheduling(struct Process p[], int n) {
    int completed = 0, currentTime = 0;
    struct Process result[n];

    while (completed < n) {
        int idx = -1;
        int minBurst = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].isCompleted && p[i].arrivalTime <= currentTime) {
                if (p[i].burstTime < minBurst || (p[i].burstTime == minBurst && p[i].arrivalTime < p[idx].arrivalTime)) {
                    minBurst = p[i].burstTime;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].waitingTime = currentTime - p[idx].arrivalTime;
            if (p[idx].waitingTime < 0) p[idx].waitingTime = 0;

            currentTime += p[idx].burstTime;
            p[idx].completionTime = currentTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].isCompleted = 1;
            result[completed] = p[idx];
            completed++;
        } else {
            currentTime++;
        }
    }

    printResult(result, n);
    printGanttChart(result, n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process P%d: ", p[i].pid);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].isCompleted = 0;
    }

    sjfScheduling(p, n);
    return 0;
}

// Sample Output 

// Enter number of processes: 5
// Enter Arrival Time and Burst Time for Process P1: 2 1 
// Enter Arrival Time and Burst Time for Process P2: 1 5
// Enter Arrival Time and Burst Time for Process P3: 4 1
// Enter Arrival Time and Burst Time for Process P4: 0 6 
// Enter Arrival Time and Burst Time for Process P5: 2 3

// PID     Arrival Burst   Waiting Turnaround      Completion
// P4              0               6               0               6                       6
// P1              2               1               4               5                       7
// P3              4               1               3               4                       8
// P5              2               3               6               9                       11
// P2              1               5               10              15                      16

// Average Waiting Time = 4.60
// Average Turnaround Time = 7.80

// Gantt Chart:
//  -----------------------------------
// |  P4  |  P1  |  P3  |  P5  |  P2  |
//  -----------------------------------
// 0      6      7      8      11      16