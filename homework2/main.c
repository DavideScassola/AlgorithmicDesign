#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"
#include "chain_matrix_multiplication.h"

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}

int main(int argc, char *argv[]) {

 // correctness test ///////////////////////

  printf("correctness test:\n");
  int n = 5;
  int p[5] = {3,5,10,2,3};
  printf("input vector: ");
  for(int i=0;i<n-1;i++)
	printf("%d ",p[i]);

  show_parenthesization(p, n);

 //////////////////////////////////////////



  // performance test ///////////////////////

  printf("\n\nperformance test:\n");

  struct timespec b_time, e_time;


  const int test_size = 5;
  const int dimensions = 51;

  int **P = allocate_int_matrix(test_size,dimensions);
  randomly_fill_int_matrix(P, test_size, dimensions, 500);

  printf("testing multiplication of chains of %d matrices\n", dimensions-1);

  printf(" ");
  printf("\tnaive");
  printf("\t        improved\n");
  
  for(int i=0;i<test_size;i++)
  {     

	float ***M = (float ***)malloc(sizeof(float **)*(dimensions-1));

  	for(int j=0;j<dimensions-1;j++)
  	{
      		M[j] = allocate_matrix(P[i][j],P[i][j+1]);
  		randomly_fill_matrix(M[j], P[i][j], P[i][j+1], 3);
  	}

  	float **R1 = allocate_matrix(P[i][0],P[i][dimensions-1]);
  	float **R2 = allocate_matrix(P[i][0],P[i][dimensions-1]);
  	

    	clock_gettime(CLOCK_REALTIME, &b_time);
	multiply_chain_naive(R2, M, P[i], dimensions);
    	clock_gettime(CLOCK_REALTIME, &e_time);

    	printf("\t%lf", get_execution_time(b_time, e_time));


    	clock_gettime(CLOCK_REALTIME, &b_time);
	multiply_chain(R1, M, P[i], dimensions);
    	clock_gettime(CLOCK_REALTIME, &e_time);

    	printf("\t%lf\n", get_execution_time(b_time, e_time));
  

  	for(int j=0;j<dimensions-1;j++)
  	{
   	     deallocate_matrix(M[j],P[i][j]);
  	}

  	free(M);
  	deallocate_matrix(R1,P[i][0]);
  	deallocate_matrix(R2,P[i][0]);
  }

  deallocate_int_matrix(P,test_size);

  return 0;
}
