/*Doc
Name            : Sushant H Patil
Date            : 12/08/2023
Description     : WAP to print the address which is causing Segmentation fault
Sample Execution:
                  ./sigsegv 
                  Segmentation fault ..!! 

                  Address 0x123456 caused error
Doc*/


#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

//signal handler function to handle segmentation fault
void handler(int signum, siginfo_t *sig, void *arg)
{
	//check if the signsl is SIGSEGV
    if (signum == SIGSEGV)
    {
        printf("Segmentation fault ..!!\n");
		//print the address that cause the segmentation fault
        printf("Address %p caused error\n", sig->si_addr);
        exit(1); //exit the program after handling the signal
    }
}

int main()
{
    //declare a struct to configure signal action
	struct sigaction sig_act;
    char *str = "scientist";
    
	//configure the signal action
    sig_act.sa_sigaction = handler;
    sig_act.sa_flags = SA_SIGINFO;
    //register signal handler for SIGSEGV using sigaction 
    sigaction(SIGSEGV, &sig_act, NULL);

    //trying to modify read only memory which will cause segmentation fault
    *str = 'T'; 

    return 0;
}


