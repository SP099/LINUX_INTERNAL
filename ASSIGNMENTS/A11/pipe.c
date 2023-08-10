/*Doc
Name            : Sushant Patil
Date            : 04-08-2023
Description     : WAP to implement 'n' pipes to execute 'n+1' commands
Sample input    : pass arguments through command line
Sample execution: ./pipe (No arguments)
                  Error: No arguments passed,Provide atleast one pipe  or more
                  Usage: ./pipe <command1> '|' <command2>
                  Usage: ./pipe <command1> '|' <command2> '|' <command3> etc

                  2../pipe ls '|' wc
                  5 25 4

                  3. ./pipe ls -­l '|' grep “pattern” '|' wc -­l 
                  5 5 25
Doc*/


#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  // Variable declaration
  int i, pos = 0, count = 0, len = 0;
  char *const arg[10];
  const char* arg1[10];

  // Check if the required command is passed or not
  if (argc <= 1)
  {
    printf("Error: No arguments passed\n Usage: ./pipe <command1> '|' <command2>\n Usage: ./pipe <command1> '|' <command2> '|' <command3> etc\n");
    return 1;
  }

  // Check if pipe ("|") is passed or not
  for (i = 1; i < argc; i++)
  {
    // If pipe is passed, find the position
    if (strcmp(argv[i], "|") == 0 && pos == 0)
    {
      pos = i;
      count++;
      break;
    }
    else if (strcmp(argv[i], "|"))
    {
      count++;
    }
  }

  if (!pos)
  {
    printf("Error : Insufficient arguments passed Usage: ./pipe <command1> '|' <command2>\n");
    return 1;
  }

  // Declaring array for pipe read and write operation
  int p[2];

  // Creating child process
  pid_t pid = fork();

  // Parent part
  if (pid > 0)
  {
    wait(NULL);

    // Loop for 'n' number of pipes
    for (i = pos + 1; i < (count - 1); i++)
    {
      // Create new child process
      pid_t pid2 = fork();

      // Find the next pipe position
      if (strcmp(argv[i], "|") == 0)
      {
        pos = i;
      }

      // Store the position of the next command
      int j = pos + 1;

      // New child process
      if (!pid2)
      {
        // If it is not the last pipe, write the output of the command to the buffer
        if (i != count)
        {
          dup2(p[0], 0);
          dup2(p[1], 1);
          execlp(argv[j], argv[j], (char*)NULL);
          close(p[0]);
          close(p[1]);
        }

        // If it is the last pipe, the last command output is printed on stdout
        else
        {
          close(p[1]);
          dup2(p[0], 0);
          execlp(argv[j], argv[j], (char*)NULL);
          close(p[0]);
        }
      }
    }
  }
  else if (!pid)
  {
    int j = 0;

    // Store the commands till pipe to string array
    for (i = 1; i <= pos; i++)
    {
      strcpy(arg[j], argv[i]);
      j++;
    }

    strcpy(arg[j], "(char*)NULL");

    // Close the read end of the pipe
    close(p[0]);

    // Duplicate the write file descriptor at file descriptor 1, for that close stdout
    dup2(p[1], 1);

    // Execute the 1st command and the output will be stored in the pipe read write buffer
    execvp(argv[1], argv);

    // Close the write end of the pipe
    close(p[1]);

    // Close the file
    close(1);
  }

  return 0;
}