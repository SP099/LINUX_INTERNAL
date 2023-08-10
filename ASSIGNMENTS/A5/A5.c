
/*Doc
Name            : Sushant Patil
Date            : 24-07-2023
Description     : WAP to make zombie process become orphan, print status of each state
Sample execution:
                 1. ./zomb_orph
                 A child created with pid 1234
                 Name:  ./zomb_orph
                 State: S (sleeping)
                 Name:  /zomb_orph   (After some time)
                 State: Z (zombie)
                 Process 1234 cleared by init  (After some time)
Doc*/






#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    //variable declaration
    pid_t pid;

    //to create a new process
    pid = fork();

    //checking parent
    if (pid > 0)
    {
        sleep(6);
        //variable declaration
        char path[50];

        //get parent zombie child status and print the status
        sprintf(path, "cat /proc/%d/status | head -2", pid);
        printf("%s\n", path);
        //system call
        system(path);

        //to create a new process
        int pid1 = fork();

        if (pid1 > 0)
        {
            //print the init cleared message
            printf("Process %d cleared by init (After some time)\n", pid);
            sleep(6);
            exit(1);
        }
        else if (pid1 == 0)
        {
            sleep(6);
            exit(1);
        }
    }
    //checking child
    else if (pid == 0)
    {
        //variable declaration
        char path[50];
        int ret = getpid();

        //print the child creating message with pid
        printf("Child created with pid %d\n", ret);

        //get child status and print the details
        sprintf(path, "cat /proc/%d/status | head -3", ret);
        printf("%s\n", path);
        //system call
        system(path);
        exit(1);
    }
    //error checking
    else
    {
        //fork error checking
        perror("fork");
        exit(1);
    }
    return 0;
}

