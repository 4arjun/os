#include <stdio.h>

void fifoPageReplacement(int pages[], int n, int frames){
    int count = 0;
    int pageFault = 0;
    int front = 0;
    int queue[frames];
    for (int i=0;i<frames;i++){
        queue[i]=-1;
    }
    
    for(int i=0;i<n;i++){
        int found = 0;
        
        for(int j=0;j<frames;j++){
            if (pages[i]==queue[j]){
                found = 1;
                break;
            }
        }
        if (!found){
            pageFault++;
            queue[front] = pages[i];
            front = (front+1)%frames;

        }
        if (count<frames){
            count++;
        }
    printf("Step %d :", i+1);
    for (int j=0;j<count;j++){
        printf("%d ",queue[j]);
    }
    printf("\n");
    }
printf("\nTotal Page Faults: %d\n", pageFault);
}

int main(){
    int n,frames;
    printf("Enter the number of pages: ");
    scanf("%d",&n);
    int pages[n];
    
    printf("enter page reference string: ");
    for (int i=0;i<n;i++){
        scanf("%d",&pages[i]);
    }
    printf("Enter the number of frames: ");
    scanf("%d",&frames);
    
    fifoPageReplacement(pages, n, frames);
}


// Sample Output
// Enter the number of pages: 12
// enter page reference string: 1 3 0 3 5 6 3 0 7 8 6 3
// Enter the number of frames: 3
// Step 1 :1 
// Step 2 :1 3 
// Step 3 :1 3 0 
// Step 4 :1 3 0 
// Step 5 :5 3 0 
// Step 6 :5 6 0 
// Step 7 :5 6 3 
// Step 8 :0 6 3 
// Step 9 :0 7 3 
// Step 10 :0 7 8 
// Step 11 :6 7 8 
// Step 12 :6 3 8 

// Total Page Faults: 11
