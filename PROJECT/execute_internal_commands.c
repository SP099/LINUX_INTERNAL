#include "main.h"

void execute_internal_commands(char *input_string)
{
 
    int i, j;

    /*execute exit command*/
    if(strncmp("exit", input_string, 4) == 0)
    {
        exit(1);
    }

    if(strncmp("pwd", input_string, 4) == 0)
    {
        system("pwd");
    }

    if(strncmp("cd", input_string, 2) == 0)
    {
        //input_string[] = cd abc
        chdir(&input_string[3]);
        
        for(i = 0 ; input_string[i] ; i++)
        {
            
            if(input_string[i] == ' ' && input_string[i+1] == ' ')
            {
                for(j = i ; input_string[j]; j++)
                {
                    input_string[j] = input_string[j + 1];
                }
                i--;
            }
        }
        chdir(&input_string[3]);
    }
}
