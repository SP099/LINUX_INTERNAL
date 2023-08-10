/*
Name             : Sushant Patil
Date             : 31/7/2023
Description      : Implement communication between two different processes using SHM
Sample Execution :
                   1 /Process1 
		           Enter the string: Hello
		           Writing to shared memory ......
		           Reading from shared memory:  OLLEH

		           2 ./Process 2
		           Reading from shared memory :olleh
		           Writing to Shared memory ...
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ctype.h>
#include <unistd.h>

// Define shared memory size
#define SMSIZE 100

int main() {
    int shmid, i, j, len;
    char str[20];
    char *shm;
    char temp;

    // Key value
    key_t key = 'B';

    // Get the shared memory
    shmid = shmget(key, SMSIZE, 0664);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach to shared memory
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1) {
        perror("shmat");
        exit(1);
    } else {
        // Read string from SHM
        strcpy(str, shm);

        // Reverse string
        len = strlen(str);
        for (i = 0, j = len - 1; i < j; i++, j--) {
            temp = str[i];
            str[i] = str[j];
            str[j] = temp;
        }
        // Write reversed string into SHM
        strcpy(shm, str);
        printf("Writing to shared memory...\n");

        // Detach from SHM
        shmdt(shm);
    }
    return 0;
}
