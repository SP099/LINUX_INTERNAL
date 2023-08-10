/*Doc
Name            : Sushant Patil
Date            : 02-08-2023
Description     : WAP to block certain signals from being received from command line.
Sample execution:
1. ./block_signal
      Process 2345 waiting for signal.. press ctrl + c from terminal.
      SIGINT received
Inside handler
Inside handler
. .
.....

2. Now open another terminal and send signal to process using kill command.
Bash$ kill ­SIGUSR1 2345
Bash$ kill ­SIGTERM 2345
Bash$ kill ­SIGABRT 2345

3. After exiting from handler will respond to blocked signal.
Doc*/


#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

// Signal handler function called when the signal is received
void handler(int signum, siginfo_t *siginfo, void *arg)
{
  // Variable declaration
  int i = 10;

  // Print the received signal number
  printf("SIGINT %d received\n", signum);

  // Loop runs until the i value reaches zero
  while (i--)
  {
    // Print the message in each iteration
    printf("Inside handler\n");

    // Wait for 1 second after each iteration
    sleep(1);
  }
}

int main()
{
  // Declare a structure to handle signals
  struct sigaction sig_act;

  // Assign the handler function to the sa_sigaction member of the structure
  sig_act.sa_sigaction = handler;

  // Set the sa_flags member of the structure to SA_SIGINFO, indicating that the signal handler takes three arguments
  sig_act.sa_flags = SA_SIGINFO;

  // Signals will be blocked while signal handler is running
  sigaddset(&sig_act.sa_mask, SIGINT);
  sigaddset(&sig_act.sa_mask, SIGTSTP);
  sigaddset(&sig_act.sa_mask, SIGUSR1);
  sigaddset(&sig_act.sa_mask, SIGUSR2);

  // Register the signal handler for SIGINT signal
  sigaction(SIGINT, &sig_act, NULL);
  sigaction(SIGTSTP, &sig_act, NULL);
  sigaction(SIGUSR1, &sig_act, NULL);
  sigaction(SIGUSR2, &sig_act, NULL);

  // Print a message indicating that the process is waiting for a signal
  printf("Process %d waiting for signal.. press ctr+c from terminal\n", getpid());

  // Infinite loop to keep the process waiting and running for signals
  while(1);

  return 0;
}