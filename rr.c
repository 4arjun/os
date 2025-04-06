#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
};

int main() {
    int n, timeQuantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int queue[100], front = 0, rear = 0; 

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process P%d: ", p[i].pid);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
        p[i].waitingTime = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    int currentTime = 0, completed = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n) {
        int idx = queue[front++];
        if (p[idx].remainingTime > 0) {
            if (p[idx].remainingTime > timeQuantum) {
                currentTime += timeQuantum;
                p[idx].remainingTime -= timeQuantum;
            } else {
                currentTime += p[idx].remainingTime;
                p[idx].remainingTime = 0;
                p[idx].completionTime = currentTime;
                p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
                completed++;
            }

            for (int i = 0; i < n; i++) {
                if (!visited[i] && p[i].arrivalTime <= currentTime) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            if (p[idx].remainingTime > 0)
                queue[rear++] = idx;

            if (front == rear) {
                for (int i = 0; i < n; i++) {
                    if (!visited[i]) {
                        queue[rear++] = i;
                        visited[i] = 1;
                        break;
                    }
                }
            }
        }
    }

    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnaroundTime;
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime,
               p[i].waitingTime, p[i].turnaroundTime, p[i].completionTime);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}


// Sample output 
// Enter number of processes: 5
// Enter Arrival Time and Burst Time for Process P1: 0 8 
// Enter Arrival Time and Burst Time for Process P2: 5 2
// Enter Arrival Time and Burst Time for Process P3: 1 7
// Enter Arrival Time and Burst Time for Process P4: 6 3
// Enter Arrival Time and Burst Time for Process P5: 8 5
// Enter Time Quantum: 3

// PID     Arrival Burst   Waiting Turnaround      Completion
// P1              0               8               14              22                      22
// P2              5               2               4               6                       11
// P3              1               7               15              22                      23
// P4              6               3               5               8                       14
// P5              8               5               12              17                      25

// Average Waiting Time = 10.00
// Average Turnaround Time = 15.00