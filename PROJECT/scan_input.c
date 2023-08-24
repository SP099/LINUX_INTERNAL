#include "main.h"

pid_t pid; 
void scan_input(char *prompt, char *input_string)
{
    //variable declaration
    char *command = '\0';
    
    int command_type;
    
    int status;

    while(1)
    {
        /* Clear the input buffer. */
        memset(input_string, '\0', 25);
        
        //Display the prompt
        printf(ANSI_COLOR_RED"[%s]$:"ANSI_COLOR_RESET, prompt);
        
        //Clear the output buffer
        fflush(stdout);

        //Read the input from the user
        scanf("%[^\n]s", input_string);

        //clear the input buffer
        getchar();

        //customize the prompt
        if(!strncmp("PS1=", input_string, 4))
        {
            if(input_string[4] != ' ')
            {
                strcpy(prompt, &input_string[4]);

                //clear the input string
                memset(input_string, '\0', 25);
                continue;
            }

            printf("Command not found\n");
        }

        //to get the command
        command = get_command(input_string);

        //printf("command is %s\n", command);

        command_type = check_command_type(command);

        //printf("command_type %d\n", command_type);

        if(command_type == EXTERNAL)
        {
            /* Fork a new process. */
            pid = fork();

            /* If the child process, then execute the command. */
            if(pid == 0)
            {
                int ret = system(input_string);
                if(ret == 0)
                {
                    exit(0);
                }
                else
                {
                    exit(1);
                }
            }

            /* Otherwise, the parent process. */
            else if(pid > 0)
            {
                /* Wait for the child process to finish. */
                wait(&status);

                /* If the child process terminated normally, then print a message. */
                if(WIFEXITED(status))
                {
                     printf("child with pid %d terminated normally\n", pid);
                }
            }

            /* Otherwise, an error occurred. */
            else
            {
                /* Print an error message. */
                perror("Error : fork() called failed\n");
                exit(2);
            }
        }
        /* Echo the input string. */
        echo(input_string, status);

        /* Execute any internal commands. */
        execute_internal_commands(input_string);
    }

}