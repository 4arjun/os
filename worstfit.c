#include <stdio.h>
#include <stdlib.h>

struct Block {
    int size;
    int allocated;
    struct Block* next;
};

void allocateWorstFit(struct Block* head, int processSize) {
    struct Block* worst = NULL;
    struct Block* temp = head;
    while (temp != NULL) {
        if (!temp->allocated && temp->size >= processSize) {
            if (worst == NULL || temp->size > worst->size)
                worst = temp;
        }
        temp = temp->next;
    }
    if (worst != NULL) {
        worst->allocated = 1;
        printf("Process of size %d allocated to block of size %d\n", processSize, worst->size);
        worst->size= worst->size-processSize;
    } else {
        printf("No suitable block found for process size %d\n", processSize);
    }
}

void display(struct Block* head){
    struct Block* temp = head;
    printf("Free Block\n");
    while (temp!=NULL){
        printf("%d->",temp->size);
        temp = temp->next;
    }
}

struct Block* createMemory(int blocks[], int n) {
    struct Block* head = NULL;
    struct Block* temp = NULL;
    for (int i = 0; i < n; i++) {
        struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
        newBlock->size = blocks[i];
        newBlock->allocated = 0;
        newBlock->next = NULL;
        if (head == NULL)
            head = newBlock;
        else
            temp->next = newBlock;
        temp = newBlock;
    }
    return head;
}

int main() {
    int p;
    int memBlocks[] = {100, 500, 200, 300, 600, 500};
    int n = sizeof(memBlocks) / sizeof(memBlocks[0]);
    struct Block* memory = createMemory(memBlocks, n);
    printf("Enter number of processes: ");
    scanf("%d",&p);
    int processes[p];
    for (int i=0;i<p;i++){
        printf("enter process %d: ",i+1);
        scanf("%d",&processes[i]);
    }

    for (int i = 0; i < p; i++) {
        allocateWorstFit(memory, processes[i]);
    }
    
    display(memory);

    return 0;
}

// Sample Output Enter number of processes: 4
// enter process 1: 212
// Process of size 212 allocated to block of size 600
// enter process 2: 417
// Process of size 417 allocated to block of size 500
// enter process 3: 112
// Process of size 112 allocated to block of size 500
// enter process 4: 426
// No suitable block found for process size 426
// Free Block
// 100->83->200->300->388->388->

