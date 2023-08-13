/*
Name             : Sushant H Patil
Date             : 13/08/2023
Description      : A09 - Implement communication between two related processes using one pipe
Sample Execution :
                  1 ./pipe (No arguments)
		          Error: No arguments passed Usage: ./pipe   <command1 > '|'   <command2>   

	              2. ./pipe ls  
		          Error: Insufficient arguments passed Usage: ./pipe  <command1 > '|'   <command2>  
				   
	              3. ./pipe ls '|' wc
   		          5 25 4. 
		          4. ./pipe ls -l ­a '|' wc ­l -w 
  		          10 15
*/

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    int pipe_fd[2];
    int newfd, fd;
    pid_t c1, c2;
    int i = 1, argc_1 = 0, argc_2 = 0, j = 0;

    if (argc < 4) 
    {
        printf("Error: Insufficient arguments passed. Usage: ./pipe <command1> '|' <command2>\n");
        return 1;
    }

    while (strcmp(argv[i++], "|") != 0) 
    {
        argc_1++;
    }

    char *arg_1[argc_1 + 1];

    for (i = 1; i < argc_1 + 1; i++) 
    {
        arg_1[i - 1] = argv[i];
    }
    arg_1[i - 1] = NULL;

    i = argc_1 + 2;

    while (argv[i++] != NULL) 
    {
        argc_2++;
    }

    char *arg_2[argc_2 + 1];

    j = 0;

    for (i = argc_1 + 2; i < argc; i++) 
    {
        arg_2[j] = argv[i];
        j++;
    }
    arg_2[j] = NULL;

    pipe(pipe_fd);

    c1 = fork();
    if (c1 == -1) 
    {
        perror("FORK");
        exit(1);
    } 
    else if (c1 == 0) 
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipe_fd[1]);
        execvp(arg_1[0], arg_1);
        perror("exec fail");
        exit(1);
    } 
    else 
    {
        c2 = fork();
        if (c2 == -1) 
        {
            perror("FORK");
            exit(1);
        } 
        else if (c2 == 0) 
        {
            close(pipe_fd[1]);
            dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe
            close(pipe_fd[0]);
            execvp(arg_2[0], arg_2);
            perror("exec fail");
            exit(1);
        } 
        else 
        {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            wait(NULL);
            wait(NULL);
            exit(0);
        }
    }
    return 0;
}

