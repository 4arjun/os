#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10  // Maximum number of processes
#define MAX_R 10  // Maximum number of resources

int allocation[MAX_P][MAX_R];
int maximum[MAX_P][MAX_R];
int need[MAX_P][MAX_R];
int available[MAX_R];

int n, m; // n = number of processes, m = number of resources

// Calculate the need matrix
void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
}

// Check if system is in a safe state and print the safe sequence
bool isSafe() {
    int work[MAX_R];
    bool finish[MAX_P] = {false};
    int safeSeq[MAX_P];
    int count = 0;

    // Initialize work = available
    for (int i = 0; i < m; i++)
        work[i] = available[i];

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            return false; // No safe sequence found
        }
    }

    // Print safe sequence
    printf("\nSystem is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return true;
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Maximum Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("\nEnter Available Resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    calculateNeed();

    if (!isSafe()) {
        printf("\nSystem is NOT in a safe state (deadlock may occur).\n");
    }

    return 0;
}


// Sample output 
// Enter number of processes: 5
// Enter number of resource types: 3

// Enter Allocation Matrix:
// P0: 0 1 0
// P1: 2 0 0
// P2: 3 0 2
// P3: 2 1 1
// P4: 0 0 2

// Enter Maximum Matrix:
// P0: 7 5 3
// P1: 3 2 2
// P2: 9 0 2
// P3: 2 2 2
// P4: 4 3 3

// Enter Available Resources: 3 3 2

// System is in a safe state.
// Safe sequence: P1 P3 P4 P0 P2 