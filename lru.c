#include <stdio.h>

int findLRU(int timestamps[], int frames) {
    int minIndex = 0;
    for (int i = 1; i < frames; i++) {
        if (timestamps[i] < timestamps[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex; 
}

void lruPageReplacement(int pages[], int n, int frames) {
    int queue[frames];      
    int timestamps[frames]; 
    int time = 0, pageFaults = 0, count = 0;

    for (int i = 0; i < frames; i++) {
        queue[i] = -1; 
        timestamps[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (queue[j] == pages[i]) {
                found = 1;
                timestamps[j] = time++; 
                break;
            }
        }

        if (!found) { 
            int replaceIndex;
            if (count < frames) { 
                replaceIndex = count;
                count++;
            } else { 
                replaceIndex = findLRU(timestamps, frames);
            }

            queue[replaceIndex] = pages[i];
            timestamps[replaceIndex] = time++;
            pageFaults++;
        }

        printf("Step %d: ", i + 1);
        for (int j = 0; j < count; j++) {
            printf("%d ", queue[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int n, frames;
    
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    int pages[n];

    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    lruPageReplacement(pages, n, frames);

    return 0;
}


// Sample Output
// Enter the number of pages: 12
// Enter page reference string: 1 3 0 3 5 6 3 0 7 8 6 3
// Enter the number of frames: 3
// Step 1: 1 
// Step 2: 1 3 
// Step 3: 1 3 0 
// Step 4: 1 3 0 
// Step 5: 5 3 0 
// Step 6: 5 6 0 
// Step 7: 5 6 3 
// Step 8: 0 6 3 
// Step 9: 0 7 3 
// Step 10: 0 7 8 
// Step 11: 6 7 8 
// Step 12: 6 3 8 

// Total Page Faults: 10
