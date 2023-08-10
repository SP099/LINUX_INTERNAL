/*
Name              : Sushant Patil
Date              : 23/07/2023
Description       : WAP to understand usage of dup and dup2 system calls
Sample Execution  : ./dup_dup2 f1.txt
                    Print this message into STDOUT
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    int option;

    // Validation
    if (argc < 2 || argc > 2) 
    {
        printf("Please pass a valid command line argument.\n");
        return -1;
    }

    // Display the menu
    printf("Menu:\n1.dup\n2.dup2\n");

    // Read option from user
    printf("Choose the option: ");
    scanf("%d", &option);

    // File descriptor for standard output (STDOUT)
    int std_out = dup(1);

    // Conditions for dup
    if (option == 1) 
    {
        // File operation in write-only mode to redirect message into the specified file
        int fd1 = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd1 == -1) 
        {
            perror("open");
            return -1;
        }

        // Redirect STDOUT to the specified file
        if (dup2(fd1, 1) == -1) 
        {
            perror("dup2");
            close(fd1);
            return -1;
        }

        // Print message to the file
        printf("Print this message into FILE\n");

        // Restore STDOUT to the original descriptor
        if (dup2(std_out, 1) == -1) 
        {
            perror("dup2");
            close(fd1);
            return -1;
        }

        // Print the message to STDOUT
        printf("Print this message into STDOUT\n");

        // Close the file descriptor for the specified file
        close(fd1);
    }
    // Conditions for dup2
    else if (option == 2) 
    {
        // File operation in write-only mode to redirect message into the specified file
        int fd2 = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd2 == -1) 
        {
            perror("open");
            return -1;
        }

        // Redirect STDOUT to the specified file
        if (dup2(fd2, 1) == -1) 
        {
            perror("dup2");
            close(fd2);
            return -1;
        }

        // Print message to the file
        printf("Print this message into FILE\n");

        // Restore STDOUT to the original descriptor
        if (dup2(std_out, 1) == -1) 
        {
            perror("dup2");
            close(fd2);
            return -1;
        }

        // Print the message to STDOUT
        printf("Print this message into STDOUT\n");

        // Close the file descriptor for the specified file
        close(fd2);
    } 
    else 
    {
        printf("Invalid option selected.\n");
    }

    return 0;
}

