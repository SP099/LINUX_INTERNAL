/*
Name             : Sushant Patil
Date             : 31/7/2023
Description      : Implement communication between two different processes using SHM
Sample Execution :
                   1 ./Process1 
		           Enter the string: Hello
		           Writing to shared memory ......
		           Reading from shared memory:  OLLEH

		           2. ./Process 2
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
    int shmid, i;
    char str[20];
    char *shm;
    key_t key = 'B';

    // Create shared memory
    shmid = shmget(key, SMSIZE, IPC_CREAT | 0664);
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
        // Read string
        printf("Enter string: ");
        scanf("%19[^\n]", str); // Limit input to 19 characters to avoid buffer overflow

        // Convert string to uppercase
        for (i = 0; str[i] != '\0'; i++) {
            str[i] = toupper(str[i]);
        }
        str[i] = '\0';

        // Write into SHM
        strcpy(shm, str);
        printf("Writing to shared memory...\n");

        sleep(8);

        // Read string from SHM
        printf("Reading from shared memory: %s\n", shm);

        // Detach from SHM
        shmdt(shm);

        // Remove shared memory
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}
