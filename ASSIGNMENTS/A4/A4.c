/*
Name            : Sushant Patil
Date            : 22/07/2023
Description     : WAP to understand advanced file control system calls
Sample Execution:
                  1.When no arguments are passed
                  ./a.out 
                  Insufficient arguments
                  Usage:- ./a.out filename

                  2. ./a.out f1.txt
                  PARENT PROCESS: locked file
                  PARENT PROCESS: writing to file f1.txt
                  PARENT PROCESS: unlocked file
                  CHILD PROCESS: locked file
                  CHILD PROCESS: writing to file f1.txt
                  CHILD PROCESS: unlocked file

Note : Parent will perform some task Ex: Print prime numbers upto 15
Child may perform another task Ex : Print Fibonacci series upto 10
These things should be present in the file
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Validation
    if (argc < 2)
    {
        printf("Please pass the valid command-line arguments\n");
        printf("Insufficient arguments\n");
        exit(1);
    }
    int fd = open(argv[1], O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    pid_t pid;
    struct flock file;

    memset(&file, 0, sizeof(file));

    pid = fork();
    if (pid > 0)
    {
        sleep(2);
        printf("PARENT PROCESS: locked the file\n");
        file.l_type = F_WRLCK;
        fcntl(fd, F_SETLKW, &file);
        printf("PARENT PROCESS: writing to file %s\n", argv[1]);
        printf("PARENT PROCESS: unlocked the file\n");

        // Store the standard output descriptor (stdout) to restore it later
        int std_cpy = dup(1);
        close(1);
        int new_fd = dup2(fd, 1);

        int num = 15, i, fact, j;
        printf("\nPrime Numbers are: \n");
        for (i = 1; i <= num; i++)
        {
            fact = 0;
            for (j = 1; j <= i; j++)
            {
                if (i % j == 0)
                {
                    fact++;
                }
            }
            if (fact == 2)
            {
                printf("%d ", i);
            }
        }
        printf("\n");

        // Close the duplicated file descriptor and restore the standard output
        close(fd);
        dup2(std_cpy, 1);

        file.l_type = F_UNLCK;
        fcntl(fd, F_SETLKW, &file);
    }
    else if (pid == 0)
    {
        printf("CHILD PROCESS: locked the file\n");
        file.l_type = F_WRLCK;
        fcntl(fd, F_SETLKW, &file);
        printf("CHILD PROCESS: writing to file %s\n", argv[1]);
        printf("CHILD PROCESS: unlocked the file\n");

        // Store the standard output descriptor (stdout) to restore it later
        int std_cpy = dup(1);
        close(1);
        int new_fd = dup2(fd, 1);

        int num = 15, f1 = 0, f2 = 1, i;
        if (num >= 0)
        {
            printf("Fibonacci series are: \n");
            printf("%d %d", f1, f2);
            i = f1 + f2;
        }
        while (i <= num)
        {
            printf(" %d", i);
            f1 = f2;
            f2 = i;
            i = f1 + f2;
        }
        printf("\n");

        // Close the duplicated file descriptor and restore the standard output
        close(fd);
        dup2(std_cpy, 1);

        file.l_type = F_UNLCK;
        fcntl(fd, F_SETLKW, &file);
    }
    else
    {
        perror("fork");
        exit(1);
    }
}

