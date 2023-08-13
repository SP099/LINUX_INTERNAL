/*Doc
Name            : Sushant H Patil
Date            : 13-08-2023
Description     : WAP to implement alarm with snooze for given time and date using SIGALRM
Sample input    : pass arguments through command line
Sample execution: 

                  1. ./alarm (No arguments) 
                  Error: No arguments passed
                  Usage: ./alarm  [dd/mm/yy] 

                  2. ./alarm 30:15 
                  Error: Invalid time 

                  3. ./alarm 22:10 
                  set alarm for 10:10 PM for today 

                  4. ./alarm 22:10 02/03/16
                  set alarm for 10:10 PM for today 

                  5. When alarm occurs 
                Wake­up...Alarm..!! 
                1. Snooze     2. Exit 
                if user select 
                1 Enter snooze time :
                2  

                ( After 2 mins above process will repeat until user gives exit)
Doc*/

#include <stdio.h>
#include <signal.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define _XOPEN_SOURCE 

// global variable to check whether alarm has occurred or not
int flag = 0;

// signal handler function for SIGALRM
void handler(int signum) {
    flag = 1;
    printf("Wake up ...Alarm..!!\n");
}

int main(int argc, char* argv[]) {
    // check command line arguments
    if (argc <= 1) {
        printf("Error: No arguments passed. Usage: ./alarm [H:M:S] [dd-mm-yy]\n");
        return 1;
    }

    // initialize tm with zeros
    struct tm tm = {0};
    struct tm cur_tm;

    // variable declaration
    int sec, user_time;

    // read current time from epoch time
    time_t cur_time = time(NULL);

    // convert seconds to H:M:S dd-mm-yy format
    localtime_r(&cur_time, &cur_tm);

    // check command line arguments passed or not
    if (argc == 2) {
        // string format time converted to time format
        strptime(argv[1], "%H:%M:%S", &tm);
        // store today's date in the tm structure
        tm.tm_mday = cur_tm.tm_mday;
        tm.tm_mon = cur_tm.tm_mon;
        tm.tm_year = cur_tm.tm_year;
    } else {
        // if date and time both passed, strings converted to time and date format
        strptime(argv[1], "%H:%M:%S", &tm);
        strptime(argv[2], "%d-%m-%Y", &tm);
    }
    
    // convert to seconds
    user_time = mktime(&tm);
    
    // if user time is less than current time, show error
    if (user_time < cur_time) {
        printf("Error: Invalid time\n");
        return 1;
    }
    
    // calculate alarm time in seconds
    int alarm_time = user_time - cur_time;
    printf("Set alarm for %s for today\n", argv[1]);

    // register signal handler
    signal(SIGALRM, &handler);

    // set the alarm
    alarm(alarm_time);

    while (1) {
        // after the first alarm, provide options for snooze or exit
        if (flag) {
            flag = 0;
            printf("1. snooze\n2. exit\noption : ");
            int option;
            scanf("%d", &option);

            switch (option) {
                case 1:
                    // check for valid snooze time
                    sec = atoi(argv[1]);
                    if (sec <= 0) {
                        printf("Error: Invalid snooze time\n");
                        continue;
                    }

                    // set new alarm for snooze time
                    alarm(sec);
                    break;
                case 2:
                    exit(0);
            }
        }
    }
    
    return 0;
}
