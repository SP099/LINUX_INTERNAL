/*Doc
Name            : Sushant Patil
Date            : 01-08-2023
Description     : WAP to print the factorial of a given number using multithreads
Sample input    : take the input from user
Sample execution: 
                  1. ./factorial 
                  Enter the number :10 
                  Factorial of 10 is 3628800
Doc*/

#include <stdio.h>
#include <pthread.h>

#define NO_OF_THREADS 3

// Define a structure to hold start and end values for each thread
struct td
{
  int start;
  int end;
};

// Thread function to calculate the factorial
void *thread(void *arg)
{
  struct td *td = (struct td *)arg;
  unsigned long int fact = 1;

  // Loop through the range specified by start and end
  for (int i = td->start; i <= td->end; i++)
  {
    fact *= i;
  }

  return (void *)fact;
}

int main()
{
  // Create a struct to hold thread data
  struct td td[NO_OF_THREADS];

  // Initialization of variables
  unsigned long int factorial = 1;
  int num;

  // Take the input from the user
  printf("Enter the number: ");
  scanf("%d", &num);

  // Check if the number is negative
  if (num < 0)
  {
    printf("Factorial is not defined for negative numbers.\n");
    return 1;
  }

  // Divide the number of threads and store it into div variable
  int div = num / NO_OF_THREADS;

  // Declare an array to hold thread IDs
  pthread_t threads[NO_OF_THREADS];

  // Share the work among threads
  for (int i = 0; i < NO_OF_THREADS; i++)
  {
    td[i].start = i * div + 1;
    td[i].end = (i == NO_OF_THREADS - 1) ? num : (i + 1) * div;
    pthread_create(&threads[i], NULL, thread, &td[i]);
  }

  // Wait for threads and collect return values
  for (int i = 0; i < NO_OF_THREADS; i++)
  {
    unsigned long int thread_result;
    pthread_join(threads[i], (void **)&thread_result);
    factorial *= thread_result;
  }

  // Print the factorial of the given number
  printf("Factorial of %d is %lu\n", num, factorial);
  return 0;
}