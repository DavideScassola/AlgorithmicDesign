#include <stdlib.h>
#include <stdio.h>
#define MAX_ELEM_VALUE 25

int naive_matrix_mult(float **C,
                        float **A,
                        float **B,
                        const size_t A_rows,
                        const size_t A_cols,
                        const size_t B_rows,
                        const size_t B_cols)
{
  if (A_cols != B_rows) {
     return -1;
  }

  // for all rows in A
  for (size_t i=0; i<A_rows; i++) {

     // for all cols in B
     for (size_t j=0; j<B_cols; j++) {

       // reset C[i][j]
       C[i][j] = 0.0;

       // sum all the element mults
       for (size_t k=0; k<A_cols; k++) {
        C[i][j] += (A[i][k]*B[k][j]);
       }
     }
  }

  return 0;
}

float **allocate_matrix(const size_t rows,
                        const size_t cols)
{
   float **A=(float **)malloc(sizeof(float *)*rows);

   for (size_t i=0; i<rows; i++) {
     A[i]=(float *)malloc(sizeof(float)*cols);
   }

   return A;
}

int **allocate_int_matrix(const size_t rows,
                        const size_t cols)
{
   int **A=(int **)malloc(sizeof(int *)*rows);

   for (size_t i=0; i<rows; i++) {
     A[i]=(int *)malloc(sizeof(int)*cols);
   }

   return A;
}

void deallocate_int_matrix(int **A, const size_t rows)
{
  for (size_t i=0; i<rows; i++) {
    free(A[i]);
  }

  free(A);
}

void deallocate_matrix(float **A, const size_t rows)
{
  for (size_t i=0; i<rows; i++) {
    free(A[i]);
  }

  free(A);
}

int same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		float **B, const size_t B_rows, const size_t B_cols)
{
   if ((A_rows != B_rows) || (A_cols != B_cols)) {
     return 0;
   }

   for (size_t i=0; i<A_rows; i++) {
     for (size_t j=0; j<A_cols; j++) {
        if (A[i][j] != B[i][j]) {
	         return 0;
        }
     }
   }

   return 1;
}

void show_matrix(int **M, const size_t rows, const size_t cols)
{
  for(int i = 0;i<rows;i++)
  {
    for(int j = 0;j<cols;j++)
    {
        printf("%d, ", M[i][j]);
    }
        printf("\n");
  }
};

void show_float_matrix(float **M, const size_t rows, const size_t cols)
{
  for(int i = 0;i<rows;i++)
  {
    for(int j = 0;j<cols;j++)
    {
        printf("%f, ", M[i][j]);
    }
        printf("\n");
  }
};


void matrix_copy(int** Out, int **In, const size_t rows, const size_t cols)
{
  for (size_t i=0; i<rows; i++)
     for (size_t j=0; j<cols; j++)
       Out[i][j] = In[i][j];
}

void randomly_fill_matrix(float **A, const size_t A_rows, const size_t A_cols, const int max_value)
{
   for (size_t i=0; i< A_rows; i++) {
     for (size_t j=0; j< A_cols; j++) {
   	   A[i][j]=(float)(rand()%(2*max_value)-max_value);
     }
   }
}

void randomly_fill_int_matrix(int **A, const size_t A_rows, const size_t A_cols, const size_t max_value)
{
   for (size_t i=0; i< A_rows; i++) {
     for (size_t j=0; j< A_cols; j++) {
   	   A[i][j]=(int)(rand()%(2*max_value)-max_value);
     }
   }
}

int almost_same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		float **B, const size_t B_rows, const size_t B_cols, float precision)
{
   if ((A_rows != B_rows) || (A_cols != B_cols)) {
     return 0;
   }

   for (size_t i=0; i<A_rows; i++) {
     for (size_t j=0; j<A_cols; j++) {
	float ratio = A[i][j] / B[i][j];
	float relative_error = 1-ratio>0 ? 1-ratio : ratio-1;
        if (relative_error > precision) {
	         return 0;
        }
     }
   }
return 1;
}

