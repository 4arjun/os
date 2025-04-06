#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int startTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int isCompleted;
};

int main() {
    int n, currentTime = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time, Burst Time and Priority for Process P%d: ", p[i].id);
        scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
        p[i].isCompleted = 0;
    }

    while (completed != n) {
        int idx = -1;
        int highestPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].isCompleted == 0) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == highestPriority) {
                    if (p[i].arrivalTime < p[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            p[idx].startTime = currentTime;
            p[idx].completionTime = p[idx].startTime + p[idx].burstTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;

            totalWT += p[idx].waitingTime;
            totalTAT += p[idx].turnaroundTime;

            p[idx].isCompleted = 1;
            completed++;
            currentTime = p[idx].completionTime;
        } else {
            currentTime++;
        }
    }

    printf("\nID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].arrivalTime,
               p[i].burstTime,
               p[i].priority,
               p[i].completionTime,
               p[i].turnaroundTime,
               p[i].waitingTime);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);
}


// Sample Output

// Enter number of processes: 5
// Enter Arrival Time, Burst Time and Priority for Process P1: 0 4 1
// Enter Arrival Time, Burst Time and Priority for Process P2: 0 2 2
// Enter Arrival Time, Burst Time and Priority for Process P3: 6 7 1
// Enter Arrival Time, Burst Time and Priority for Process P4: 11 2 2
// Enter Arrival Time, Burst Time and Priority for Process P5: 12 4 3

// ID      AT      BT      PR      CT      TAT     WT
// P1      0       4       1       4       4       0
// P2      0       2       2       6       6       4
// P3      6       7       1       13      7       0
// P4      11      2       2       15      4       2
// P5      12      4       3       19      7       3

// Average Waiting Time = 1.80
// Average Turnaround Time = 5.60