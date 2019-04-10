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

  printf(" ");
  printf("\tnaive");
  printf("\t        improved\n");

  const int test_size = 10;
  const int dimensions = 20;
  //int dim[5] = {5,10,10,15,20};

  int **P = allocate_int_matrix(test_size,dimensions);
  randomly_fill_int_matrix(P, test_size, dimensions, 500);
   
  
  for(int i=0;i<test_size;i++)
  {     /*
        printf("\ninput=(%d", P[i][0]);
  	for(int j=1;j<dimensions;j++)
        {
		printf(",%d", P[i][j]);
	}
        printf(")\n");
        */

	float ***M = (float ***)malloc(sizeof(float **)*(dimensions-1));

  	for(int j=0;j<dimensions-1;j++)
  	{
      		M[j] = allocate_matrix(P[i][j],P[i][j+1]);
  		randomly_fill_matrix(M[j], P[i][j], P[i][j+1], 3);

		//printf("\nmatrix:\n");
		//show_float_matrix(M[j], P[i][j],P[i][j+1]);
		//printf("\n");
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

  	//int equal = same_matrix(R1, P[i][0], P[i][dimensions-1], R2, P[i][0], P[i][dimensions-1]);
  	//printf("      %d\n",equal);

	//printf("%f, %f", R1[0][1], R2[0][1]);
	//show_float_matrix(R1, P[i][dimensions-1], P[i][dimensions-1]);
  


  	for(int j=0;j<dimensions-1;j++)
  	{
   	     deallocate_matrix(M[j],P[i][j]);
  	}

  	free(M);
  	deallocate_matrix(R1,P[i][0]);
  	deallocate_matrix(R2,P[i][0]);
  }

   	deallocate_int_matrix(P,test_size);



  /*
  int P[[dim[0]]] = {3,5,10,2,3};
  int P[[dim[1]]] = {1,2,3,4,5,6,7,8,9,10};
  int P[[dim[2]]] = {10,9,8,7,6,5,4,3,2,1};
  int P[[dim[3]]] = {2,10,2,20,2,40,40,13,22,65,6,5,12,3,11};
  int P[[dim[4]]] = {1,12,3,2,6,6,7,2,1,10,2,8,7,5,4,8,1,2,3,2};
  */
  



  

  /*
  printf("input vector: ");
  for(int i=0;i<DIM;i++)
	printf("%d ",P[i]);

  show_parenthesization(P, DIM);
  */

  /*

  float ***M = (float ***)malloc(sizeof(float **)*(DIM-1));

  for(int i=0;i<DIM-1;i++)
  {
        M[i] = allocate_matrix(P[i],P[i+1]);
  	randomly_fill_matrix(M[i], P[i], P[i+1]);
  }

  float **R1 = allocate_matrix(P[0],P[DIM-1]);
  float **R2 = allocate_matrix(P[0],P[DIM-1]);
  multiply_chain(R1, M, P, DIM);
  multiply_chain_naive(R2, M, P, DIM);
  

  int equal = same_matrix(R1, P[0], P[DIM-1], R2, P[0], P[DIM-1]);
  printf("%d\n",equal);
  


  for(int i=0;i<DIM-1;i++)
  {
        deallocate_matrix(M[i],P[i]);
  }

  free(M);
  deallocate_matrix(R1,P[0]);
  deallocate_matrix(R2,P[0]);

  */

  return 0;
}
