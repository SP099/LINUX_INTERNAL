/*Doc
Name            : Sushant Patil
Date            : 04-08-2023
Description     : WAP to avoid child become zombie by using signal handlers

Sample execution:  

1. ./avoid_zombie 
child  terminated with exit code 0.
Doc*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

// Signal handler function to handle SIGCHILD signal
void handler(int signum, siginfo_t *info, void *data)
{
  // Print a message indicating that the child process has terminated
  printf("This is a parent process\n");
  printf("Child %d terminated with exit code %d \n", info->si_pid, info->si_status);
  exit(1);
}

int main()
{
  // Create a signal action struct
  struct sigaction act;

  // Set the signal handler function to `handler`
  act.sa_sigaction = handler;

  // Set the sa_flags member of the structure to SA_SIGINFO | SA_NOCLDWAIT,
  // indicating that the signal handler takes three arguments and that the child process should be reaped immediately.
  act.sa_flags = SA_SIGINFO | SA_NOCLDWAIT;

  // Register the signal handler for SIGCHLD signal
  sigaction(SIGCHLD, &act, NULL);

  // Create a child process
  pid_t pid;
  int status;

  pid = fork();
  if (pid < 0)
  {
    printf("Error: fork() failed");
    return 1;
  }

  // Child process
  else if (pid == 0)
  {
    sleep(1);
    exit(0);
  }

  // Parent process
  else
  {
    sleep(4);
    exit(0);
  }

  return 0;
}

