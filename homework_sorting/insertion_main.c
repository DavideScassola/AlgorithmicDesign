#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "sorting.h"
#include "matrix.h"

#define MAX_VALUE 10000000

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}

////////////// UNIFORM INTERFACE //////////////
void insertion_s(int* A, size_t n) {insertion_sort(A, n);}
///////////////////////////////////////////////

void print_performance(void (*sorting_algorithm)(int*,size_t), int* v, size_t n)
{
	struct timespec b_time, e_time;
        clock_gettime(CLOCK_REALTIME, &b_time);
        sorting_algorithm(v,n);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("\t%lf", get_execution_time(b_time, e_time));
}



int main()
{

    const size_t max_n_of_test = 10;
    const size_t max_size = 1E5;
    size_t n;

    int **M1 = allocate_int_matrix(max_n_of_test, max_size); // insertion


    randomly_fill_positive_int_matrix(M1, max_n_of_test, max_size, max_size);

	
    ///// insertion sort, random case /////
    size_t size = 1E5;
    size_t n_of_test = 8;

    printf("\t\tinsertion_sort (random case)\n");

    for(int i=0;i<n_of_test;i++)
    {    
	n = size/(1<<(n_of_test-i-1));
	printf("size:%ld",n);
	print_performance(insertion_s, M1[i], n);
	printf("\n");
    }
		

    ////// insertion sort, best case ///////
    printf("\n\t\tinsertion_sort (best case)\n");
    // now arrays are already ordered
    for(int i=0;i<n_of_test;i++)
    {    
	n = size/(1<<(n_of_test-i-1));
	printf("size:%ld",n);
	print_performance(insertion_s, M1[i], n);
	printf("\n");
    }

        
    ////// insertion sort, worst case ///////
    for(int j=0; j<max_n_of_test; j++)
        for(int i=0; i<max_size; i++)
            M1[j][i]=max_size-i-1;

    printf("\n\t\tinsertion_sort (worst case)\n");
    // now arrays are in inverse order
    for(int i=0;i<n_of_test;i++)
    {    
	n = size/(1<<(n_of_test-i-1));
	printf("size:%ld",n);
	print_performance(insertion_s, M1[i], n);
	printf("\n");
    }
	

   deallocate_int_matrix(M1, max_n_of_test);

   return 0;
   
}
