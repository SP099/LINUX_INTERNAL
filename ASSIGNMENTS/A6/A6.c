/*
Name            : Sushant Patil
Date            :
Description     : WAP to avoid child becoming zombie without blocking parent
Sample execution:
                  ./nonblock_wait
                  A child created with pid 1234
                  parent is running
                  parent is running
                  parent is running . .
                  ............................
                  Child 1234 terminated normally with exit status 0 parent terminating
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    //variable declaration
    int status;

    //to create a new process
    int pid = fork();

    //Parent part
    if (pid > 0)
    {
        printf("A child created with pid %d\n", pid);
     
        while (waitpid(pid, &status, WNOHANG) == 0)
        {
            printf("Parent is running\n");
            sleep(2);
        }

        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            printf("Child %d terminated normally with exit status %d parent terminating\n", pid, exit_status);
        }
        else
        {
            printf("Child %d terminated abnormally.\n", pid);
        }
    }
    //child part
    else if (pid == 0)
    {
        //sleep for 5 seconds, then the child will terminate
        sleep(5);
    }
    else
    {
        //fork error checking
        perror("fork");
        exit(0);
    }
    return 0;
}

