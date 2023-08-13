/*
Name             : Sushant H patil
Date             : 12/08/2023
Description      : Implement communication between three related processes using two pipe
Sample Execution :
                   ./three_pipes (No arguments)
		           Error: No arguments passed Usage: ./three_pipes  <command1 > '|'   <command2> '|'  <command3 >       

		           2. ./pipe ls ­l '|' grep 
		           Error: Insufficient arguments passed Usage: ./pipe  <command1 > '|'   <command2> '|'  <command3 >

		           3. ./pipe ls -­l '|' grep “pattern” '|' wc -­l 
		           5 5 25
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int pipe_fd[2];
    int pipe_fd1[2];
    pid_t pid_child1, pid_child2, pid_child3;
    int i = 1, argc_1 = 0, argc_2 = 0, argc_3 = 0, j = 0;

    if (argc < 6) {
        printf("Insufficient arguments passed!\n");
        printf("Usage : ./pipe <command 1> '|' <command 2> '|' <command 3>\n");
        return 1;
    }

    while (strcmp(argv[i++], "|") != 0)
        argc_1++;
    char *arg_1[argc_1 + 1];
    for (i = 1; i < argc_1 + 1; i++) {
        arg_1[i - 1] = argv[i];
    }
    arg_1[i - 1] = NULL;

    i = argc_1 + 2;
    while (strcmp(argv[i++], "|") != 0)
        argc_2++;
    char *arg_2[argc_2 + 1];
    for (i = argc_1 + 2; strcmp(argv[i], "|") != 0; i++) {
        arg_2[j] = argv[i];
        j++;
    }
    arg_2[j] = NULL;

    i = argc_1 + argc_2 + 3;
    while (argv[i++] != NULL)
        argc_3++;
    char *arg_3[argc_3 + 1];
    j = 0;
    for (i = argc_1 + argc_2 + 3; i < argc; i++) {
        arg_3[j] = argv[i];
        j++;
    }
    arg_3[j] = NULL;

    pipe(pipe_fd);
    pipe(pipe_fd1);

    pid_child1 = fork();
    if (pid_child1 == -1) {
        perror("FORK");
        exit(1);
    } else if (pid_child1 == 0) {
        // Child 1 (Command 1)
        close(pipe_fd1[0]);
        close(pipe_fd1[1]);
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        execvp(arg_1[0], arg_1);
        perror("exec fail");
        return 1;
    } else {
        pid_child2 = fork();
        if (pid_child2 == -1) {
            perror("FORK");
            exit(1);
        } else if (pid_child2 == 0) {
            // Child 2 (Command 2)
            close(pipe_fd[1]);
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);
            close(pipe_fd1[0]);
            dup2(pipe_fd1[1], STDOUT_FILENO);
            close(pipe_fd1[1]);
            execvp(arg_2[0], arg_2);
            perror("exec fail");
            return 1;
        } else {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            pid_child3 = fork();
            if (pid_child3 == -1) {
                perror("FORK");
                exit(1);
            } else if (pid_child3 == 0) {
                // Child 3 (Command 3)
                close(pipe_fd1[1]);
                dup2(pipe_fd1[0], STDIN_FILENO);
                close(pipe_fd1[0]);
                execvp(arg_3[0], arg_3);
                perror("exec fail");
                return 1;
            } else {
                close(pipe_fd1[0]);
                close(pipe_fd1[1]);
                wait(NULL);
                wait(NULL);
                wait(NULL);
            }
        }
    }
    return 0;
}
