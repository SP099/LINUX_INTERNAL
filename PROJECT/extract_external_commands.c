#include "main.h"

void extract_external_commands(char **external_commands)
{
    //variable declaration
    char ch;
    char buffer[25] = {'\0'};
    int i = 0;
    int j = 0;

    //open the file 
    int fd = open("external_commands.txt", O_RDONLY);
    if(fd == -1)
    {
        perror("Error : Failed to open external_commands.txt\n");
        exit(1);
    }

    //Read the commands from the file
    while(read(fd, &ch, 1) > 0)
    {
        if(ch != '\n')
        {
            buffer[i++] = ch;
        }
        else
        {
            //allocate sufficient memory
            external_commands[j] = calloc(strlen(buffer) + 1, sizeof(char));

            //copy the contents
            strcpy(external_commands[j++], buffer);

            //append the null character at the end
            external_commands[j] = '\0';

            //clear the buffer
            memset(buffer, '\0', 25);
            i = 0;
        }
    }
}