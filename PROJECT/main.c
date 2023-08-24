/*
Name    : Sushant Patil
Project : Minishell
*/

#include "main.h"

int main()
{
    //clear the output screen
    system("clear");

    //Declare an array to store the input
    char input_string[25];

    //Declare an array to store the prompt
    char prompt[25] = "msh";

    //read the string
    scan_input(prompt, input_string);

    return 0;
}