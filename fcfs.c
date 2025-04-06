#include <stdio.h>

struct Process {
    int pid;
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
};

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].arrivalTime > p[j].arrivalTime) {
                swap(&p[i], &p[j]);
            }
        }
    }
}

void calculateTimes(struct Process p[], int n) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrivalTime) {
            currentTime = p[i].arrivalTime; 
        }

        p[i].waitingTime = currentTime - p[i].arrivalTime;
        p[i].completionTime = currentTime + p[i].burstTime;
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        currentTime = p[i].completionTime;
    }
}

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

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process P%d: ", p[i].pid);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
    }

    sortByArrival(p, n);
    calculateTimes(p, n);
    printResult(p, n);
    printGanttChart(p, n);

    return 0;
}


// Sample Output
// Enter number of processes: 5
// Enter Arrival Time and Burst Time for Process P1: 2 2
// Enter Arrival Time and Burst Time for Process P2: 0 1
// Enter Arrival Time and Burst Time for Process P3: 2 3
// Enter Arrival Time and Burst Time for Process P4: 3 5
// Enter Arrival Time and Burst Time for Process P5: 4 4

// PID     Arrival Burst   Waiting Turnaround      Completion
// P2              0               1               0               1                       1
// P1              2               2               0               2                       4
// P3              2               3               2               5                       7
// P4              3               5               4               9                       12
// P5              4               4               8               12                      16

// Average Waiting Time = 2.80
// Average Turnaround Time = 5.80

// Gantt Chart:
//  -----------------------------------
// |  P2  |  P1  |  P3  |  P4  |  P5  |
//  -----------------------------------
// 0      1      4      7      12      16
