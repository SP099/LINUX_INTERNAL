#include "main.h"

char *get_command(char *input_string)
{
    //example : input_string = "ls -l"
    //extract the command until new line or space is encountered : ls

    //Declare an array to store the command
    static char command[25] = {'\0'};

    int i = 0;

    while(1)
    {
        if(*input_string == ' ' || *input_string == '\0')
        {
            break;
        }
        command[i++] = (*input_string);
        input_string++;
    }
    command[i] = '\0';
    return command;
}