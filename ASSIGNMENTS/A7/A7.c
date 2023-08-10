/*
Name            : Sushant Patil
Date            : 20/07/2023
Description     : WAP to create child process to execute command passed through command line
sample execution:
                  1. No args passed (Print usage info)
                  ./exe_child Usage: ./exe_child args...
                  2. Valid arg. passed
                  ./exe_child date
                  This is the CHILD process, with id 11612
                  Wed Apr  4 13:27:19 IST 2012
                  Child exited with status 0
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Checking if the command and arguments are provided
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Forking a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("This is the child process, with id %d\n", getpid());
        sleep(5);

        // Executing the command with provided arguments
        if (execvp(argv[1], &argv[1]) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        pid_t wpid = wait(&status);

        if (wpid == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}

