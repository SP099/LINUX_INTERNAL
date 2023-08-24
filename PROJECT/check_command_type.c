#include "main.h"

int check_command_type(char *command)
{
    //list of builtin commands
    char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval","set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source","exit", "exec","shopt", "caller", "true", "type", "hash", "bind", "help", NULL};
    
    //check whether the user has pressed enter key
    if(strcmp(command, "\0") == 0)
    {
        return NO_COMMAND;
    }
    
    //check for builtin command
    for(int i = 0; builtins[i] != NULL; i++)
    {
        if(strcmp(command, builtins[i]) == 0)
        {
            return BUILTIN;
        }
    }

    //to extract the external_commands
    char *external_commands[155] = {NULL};
    extract_external_commands(external_commands);

    //check for the external command
    for(int i = 0; external_commands[i] != NULL; i++)
    {
        if(strcmp(command, external_commands[i]) == 0)
        {
            return EXTERNAL;
        }
    }
}