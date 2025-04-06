#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  

int main() {
    key_t key = ftok("shmfile", 65);  

    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); 

    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    char *str = (char *) shmat(shmid, NULL, 0);

    if (str == (char *) -1) {
        perror("shmat failed");
        exit(1);
    }

    printf("Enter a message to write: ");
    fgets(str, SHM_SIZE, stdin);

    printf("Data written to shared memory: %s\n", str);

    shmdt(str);

    return 0;
}

// Sample output 
// gcc ipcWriter.c
// ./a.out
// Enter a message to write: hello
// Data written to shared memory: hello

// gcc ipcReader.c
// ./a.out
// Data read from shared memory: hello