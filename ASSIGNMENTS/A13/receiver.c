#include "main.h"

#define SMSIZE 100
int main()
{
    //variable declaration
    int shmid, len, i, j, fd;
    char str[100];
    void *shm;
    key_t key;
    char temp;

    // SHARED MEMORY
    // key can be read/write
    key = 'A';

    // Create a shared memory segment
    shmid = shmget(key, SMSIZE, 0666);

    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the current process
    shm = shmat(shmid, NULL, 0);

    if (shm == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // Read the string from the shared memory segment
    strcpy(str, shm);
    printf("String is received successfully: %s\n", str);

    // Reverse the string
    len = strlen(str);
    for (i = 0, j = len - 1; i < j; i++, j--)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }

    // Write the reversed string to the FIFO file
    mkfifo(FIFO_NAME, 0666);

    fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0)
    {
        perror("open\n");
        exit(1);
    }

    write(fd, str, sizeof(str));
    printf("Write operation to FIFO is completed: %s\n", str);
    close(fd);

    // Detach the shared memory segment from the current process
    shmdt(shm);

    // Destroy the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}