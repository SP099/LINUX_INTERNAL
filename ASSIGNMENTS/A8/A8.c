/*
Name            : Sushant Patil
Date            : 20/07/2023
Description     : WAP to create three child from the same parent
Sample execution:
                  ./three_child
                  Child 1 with pid 2020 created
                  Child 2 with pid 2021 created
                  Child 3 with pid 2022 created
                  Child 2020 is terminated with code 0
                  Child 2021 is terminated with code 0
                  Child 2022 is terminated with code 0
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    // Create a new process
    int child1 = fork();

    // Conditions for parents
    if (child1 > 0)
    {
        int child2 = fork();
        if (child2 > 0)
        {
            int child3 = fork();
            if (child3 > 0)
            {
                // Child created a message
                sleep(2);
                printf("child 1 with pid %d created\n", child1);
                printf("child 2 with pid %d created\n", child2);
                printf("child 3 with pid %d created\n", child3);
                sleep(2);
            }
            // Child process for child3
            else
            {
                sleep(4);
                printf("child %d is terminated with code %d\n", getpid(), child3);
            }
        }
        // Child process for child2
        else
        {
            sleep(3);
            printf("child %d is terminated with code %d\n", getpid(), child2);

        }
    }
    // Child process for child1
    else
    {
        sleep(2);
        printf("child %d is terminated with code %d\n", getpid(), child1);
    }
    return 0;
}

