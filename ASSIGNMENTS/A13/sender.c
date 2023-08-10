/*
NAME             : Sushant Patil
Date             : 01/08/2023
Description      : Implement communication between three processes using PIPE, FIFO and SHM
*/

#include "main.h"

int main()
{
    char str[100];
    int shmid, i, fd;
    void *shm;
    key_t key;
    int p[2];

    // Create a new pipe
    if (pipe(p) == -1)
    {
        perror("pipe");
        exit(1);
    }

    // Create child
    int pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    // Parent process
    if (pid > 0)
    {
        // Pipe process
        close(p[0]); // Close read end
        printf("Enter the string: ");
        scanf("%99[^\n]", str);

        // Write into pipe
        write(p[1], str, sizeof(str));
        close(p[1]);
        // Close the pipe
        close(p[0]);
        return 0;
    }
    // Child process
    else if (pid == 0)
    {
        // PIPE PROCESS
        sleep(5);
        close(p[1]); // Close write end
        read(p[0], str, sizeof(str));
        close(p[0]);

        // Convert string to uppercase
        for (i = 0; str[i] != '\0'; i++)
        {
            str[i] = toupper(str[i]);
        }
        str[i] = '\0';

        // SHARED MEMORY
        key = 'A';
        shmid = shmget(key, SMSIZE, IPC_CREAT | 0666);

        if (shmid < 0)
        {
            perror("shmget");
            exit(1);
        }

        shm = shmat(shmid, NULL, 0);
        if (shm == (void *)-1)
        {
            perror("shmat");
            exit(1);
        }
        else
        {
            // Write into shared memory
            strcpy(shm, str);
            printf("String is sent successfully: %s\n", str);


            // Close the pipe
            close(p[0]);
            return 0;
        }
    }
    // Error checking
    else
    {
        perror("Fork");
        exit(1);
    }
}