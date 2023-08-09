/*
Name		     : Sushant Patil
Date		     : 08/08/2023
Description	     : WAP to sum and maximum of a given array using multiple threads.Synchronize threads using mutex.
Sample Execution :
                   1. ./sum_max
                   Enter the size of array : 100
                   max = 100 Sum = 5050
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int sum = 0, max = 0;
int array[100];
typedef struct 
{
    int start;
    int end;
} st;

pthread_mutex_t lock;

void *sum_max(void *param) 
{
    pthread_mutex_lock(&lock);
    st *info = param;
    int i;
    for (i = info->start; i <= info->end; i++) 
    {
        sum += array[i];
        if (max < array[i])
            max = array[i];
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() 
{
    int size, i;
    static int j = 0;
    
    printf("Enter Size : ");
    scanf("%d", &size);
    
    if (size < 1) 
    {
        printf("Error: please enter a valid size\n");
        exit(1);
    }
    
    for (i = 0; i < size; i++) 
    {
        array[i] = i + 1;
    }

    pthread_t td[5];
    st thread_data[5];
    int div = size / 5;
    
    for (i = 0; i < 5; i++) 
    {
        thread_data[i].start = j;
        thread_data[i].end = (i == 4) ? size - 1 : j + div - 1;
        j += div;
        pthread_create(&td[i], NULL, sum_max, &thread_data[i]);
    }
    
    for (i = 0; i < 5; i++) 
    {
        pthread_join(td[i], NULL);
    }
    
    printf("Max = %d Sum = %d\n", max, sum);
    return 0;
}
