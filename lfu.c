#include <stdio.h>

#define MAX 100

void lfuPageReplacement(int pages[], int n, int frames) {
    int memory[frames];
    int freq[frames];
    int time[frames]; // To break ties when frequency is same
    int count = 0, pageFaults = 0, currentTime = 0;

    // Initialize memory
    for (int i = 0; i < frames; i++) {
        memory[i] = -1;
        freq[i] = 0;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in memory
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                freq[j]++;
                time[j] = currentTime++;
                found = 1;
                break;
            }
        }

        // Page not found – page fault
        if (!found) {
            int replaceIndex = -1;

            // If there's space, use next empty frame
            if (count < frames) {
                replaceIndex = count;
                count++;
            } else {
                // Find LFU page (break tie using LRU logic)
                int minFreq = MAX;
                int oldestTime = MAX;
                for (int j = 0; j < frames; j++) {
                    if (freq[j] < minFreq || (freq[j] == minFreq && time[j] < oldestTime)) {
                        minFreq = freq[j];
                        oldestTime = time[j];
                        replaceIndex = j;
                    }
                }
            }

            memory[replaceIndex] = page;
            freq[replaceIndex] = 1;
            time[replaceIndex] = currentTime++;
            pageFaults++;
        }

        // Print current memory state
        printf("Step %d: ", i + 1);
        for (int j = 0; j < count; j++) {
            printf("%d ", memory[j]);
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

    lfuPageReplacement(pages, n, frames);

    return 0;
}

// Sample Output
// Enter the number of pages: 7
// Enter page reference string: 1 3 0 3 5 6 3
// Enter the number of frames: 3
// Step 1: 1 
// Step 2: 1 3 
// Step 3: 1 3 0 
// Step 4: 1 3 0 
// Step 5: 5 3 0 
// Step 6: 5 3 6 
// Step 7: 5 3 6 

// Total Page Faults: 5