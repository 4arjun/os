#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5 

int buffer[SIZE]; 
int in = 0, out = 0; 

sem_t empty;  
sem_t full;  
sem_t mutex;  

void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100; 
        sem_wait(&empty); 
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Produced: %d at index %d\n", item, in);
        in = (in + 1) % SIZE;

        sem_post(&mutex); 
        sem_post(&full);  

        sleep(1); 
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);  
        sem_wait(&mutex); 

        item = buffer[out];
        printf("Consumed: %d from index %d\n", item, out);
        out = (out + 1) % SIZE;

        sem_post(&mutex); 
        sem_post(&empty); 

        sleep(2); 
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}




// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <semaphore.h>
// #include <unistd.h>

// #define SIZE 5

// int buffer[SIZE];
// int in = 0, out = 0;

// sem_t empty;
// sem_t full;
// sem_t mutex;

// void* producer(void* arg) {
//     while (1) {
//         int item;
//         printf("Enter item to produce (or -1 to exit): ");
//         scanf("%d", &item);

//         if (item == -1) break;

//         sem_wait(&empty);
//         sem_wait(&mutex);

//         buffer[in] = item;
//         printf("Produced: %d at index %d\n", item, in);
//         in = (in + 1) % SIZE;

//         sem_post(&mutex);
//         sem_post(&full);
//     }
//     pthread_exit(NULL);
// }

// void* consumer(void* arg) {
//     while (1) {
//         char ch;
//         printf("Press 'c' to consume, 'q' to quit: ");
//         scanf(" %c", &ch);

//         if (ch == 'q') break;
//         if (ch == 'c') {
//             sem_wait(&full);
//             sem_wait(&mutex);

//             int item = buffer[out];
//             printf("Consumed: %d from index %d\n", item, out);
//             out = (out + 1) % SIZE;

//             sem_post(&mutex);
//             sem_post(&empty);
//         }
//     }
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t prodThread, consThread;

//     sem_init(&empty, 0, SIZE);
//     sem_init(&full, 0, 0);
//     sem_init(&mutex, 0, 1);

//     pthread_create(&prodThread, NULL, producer, NULL);
//     pthread_create(&consThread, NULL, consumer, NULL);

//     pthread_join(prodThread, NULL);
//     pthread_join(consThread, NULL);

//     sem_destroy(&empty);
//     sem_destroy(&full);
//     sem_destroy(&mutex);

//     return 0;
// }
