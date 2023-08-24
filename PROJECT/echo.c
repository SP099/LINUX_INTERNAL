#include "main.h"

void echo(char *input_string, int status)
{
    //exit status of last command
    if(strncmp("echo $?", input_string, 7) == 0)
    {
        printf("%d\n", status);
    }

    //PID of minishell
    if(strncmp("echo $$", input_string, 7) == 0)
    {
        printf("%d\n", getpid());
    }
    
    //to print executable path
    if(strncmp("echo $SHELL", input_string, 11) == 0)
    {
        system("pwd");
    }
} 