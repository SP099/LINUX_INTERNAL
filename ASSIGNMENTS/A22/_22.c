/*Doc
Name            : Sushant Patil
Date            : 09-8-2023
Description     : WAP to multiply two matrices using multiple threads
Sample execution: 

 1. ./matrix_mul 
Enter M1 rows and columns 3  3 
Enter M2 rows and columns 3  3
Enter M1 values 1  2  3  1  1  1  2  2  2
Enter M2 values 1  1  1  2  2  2  3  3  3
Result is 
14 14 14 
6 6 6 
12 12 12
Doc*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#include<string.h>

// Define a structure to store thread data
typedef struct {
  short m1_row;
  short m1_col;
  short m2_col;
  int **matrix1;
  int **matrix2;
  int **result;
  short cur_row;
} Thread_data_t;

// Function to create a matrix
void create_matrix(int ***matrix, int rows, int cols)
{
  // Allocate memory for matrix array
  *matrix = (int **)malloc(rows * sizeof(int *));

  // Loop through rows
  for (int i = 0; i < rows; i++)
  {
    // Allocate memory for each row
    (*matrix)[i] = (int *)malloc(cols * sizeof(int));
  }
}

// Function to read matrix elements
void read_elements(int **matrix, int rows, int cols)
{
  // Loop through rows
  for (int i = 0; i < rows; i++)
  {
    // Loop through columns
    for (int j = 0; j < cols; j++)
    {
      scanf("%d", &matrix[i][j]);
    }
  }
}

// Function to perform matrix multiplication
void *matrix_mul(void *arg)
{
  // Get thread data
  Thread_data_t *data = (Thread_data_t *)arg;

  // Get the current row
  int row = data->cur_row;

  // Loop through columns
  for (int j = 0; j < data->m2_col; j++)
  {
    // Initialize the element in the result matrix
    data->result[row][j] = 0;

    // Loop through rows of the first matrix
    for (int k = 0; k < data->m1_col; k++)
    {
      // Calculate the dot product of the current row of the first matrix and the current column of the second matrix
      data->result[row][j] += data->matrix1[row][k] * data->matrix2[k][j];
    }
  }

  // Return from the thread
  pthread_exit(NULL);
}

// Function to deallocate memory for a matrix
void deallocate_matrix(int **matrix, int rows)
{
  // Loop through rows
  for (int i = 0; i < rows; i++)
  {
    free(matrix[i]);
  }
  free(matrix);
}

int main()
{
  // Variable declarations
  int m1_rows, m1_cols, m2_rows, m2_cols;

  // Take input from the user
  printf("Enter M1 rows and columns: ");
  scanf("%d %d", &m1_rows, &m1_cols);

  printf("Enter M2 rows and columns: ");
  scanf("%d %d", &m2_rows, &m2_cols);

  // Check if matrix multiplication is possible or not
  if (m1_cols != m2_rows)
  {
    printf("Error: M1 columns must be equal to M2 rows.\n");
    return 1;
  }

  // Declare matrices
  int **matrix1;
  int **matrix2;
  int **result;

  // Create matrices
  create_matrix(&matrix1, m1_rows, m1_cols);
  create_matrix(&matrix2, m2_rows, m2_cols);
  create_matrix(&result, m1_rows, m2_cols);

  // Take the input from the user
  printf("Enter M1 values:\n");
  read_elements(matrix1, m1_rows, m1_cols);

  printf("Enter M2 values:\n");
  read_elements(matrix2, m2_rows, m2_cols);

  // Create threads
  pthread_t threads[m1_rows];
  Thread_data_t thread_data[m1_rows];

  // Initialize thread data
  for (int i = 0; i < m1_rows; i++)
  {
    thread_data[i].m1_row = m1_rows;
    thread_data[i].m1_col = m1_cols;
    thread_data[i].m2_col = m2_cols;
    thread_data[i].matrix1 = matrix1;
    thread_data[i].matrix2 = matrix2;
    thread_data[i].result = result;
    thread_data[i].cur_row = i;
  }

  // Start threads
  for (int i = 0; i < m1_rows; i++)
  {
    pthread_create(&threads[i], NULL, matrix_mul, &thread_data[i]);
  }

  // Join threads
  for (int i = 0; i < m1_rows; i++)
  {
    pthread_join(threads[i], NULL);
  }

  // Print the result
  printf("Result is:\n");
  for (int i = 0; i < m1_rows; i++)
  {
    for (int j = 0; j < m2_cols; j++)
    {
      printf("%d ", result[i][j]);
    }
    printf("\n");
  }

  // Deallocate memory for matrices
  deallocate_matrix(matrix1, m1_rows);
  deallocate_matrix(matrix2, m2_rows);
  deallocate_matrix(result, m1_rows);

  return 0;
}
