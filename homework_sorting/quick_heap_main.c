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
void quick_s(int* A, size_t n) {quick_sort(A, n);}
void quick_s_central_pivot(int* A, size_t n) {quick_sort_central_pivot(A, n);}
void heap_s(int* A, size_t n) {heap_sort(A, n);}
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
    
    size_t max_n_of_test = 8;
    size_t max_size = 1E7;
    size_t n;

    int **M2 = allocate_int_matrix(max_n_of_test, max_size); // quick
    int **M3 = allocate_int_matrix(max_n_of_test, max_size); // heap

    randomly_fill_positive_int_matrix(M2, max_n_of_test, max_size, max_size);
    matrix_copy(M3, M2, max_n_of_test, max_size);
	
    ///// quick & heap (random case) /////
    size_t size = 1E7;
    size_t n_of_test = 8;

    printf("\t\tquick_sort");
    printf("\theap_sort (random case)\n");

    for(int i=0;i<n_of_test;i++)
    {    
	n = size/(1<<(n_of_test-i-1));
	printf("size:%ld",n);

 	print_performance(quick_s, M2[i], n);
	print_performance(heap_s, M3[i], n);

	printf("\n");
    }

    ///// quick (worst case) /////
    size = 1E7/4;
    n_of_test = 6;
    printf("\n\t\tquick_sort (worst case)\n");

    for(int i=0;i<n_of_test;i++)
    {    
	n = size/(1<<(n_of_test-i-1));
	printf("size:%ld",n);

 	print_performance(quick_s, M2[i], n);

	printf("\n");
    }

    ///// quick (best case) /////
    size = 1E7;
    n_of_test = 8;
    printf("\n\t\tquick_sort (best case)\n");

    for(int i=0;i<n_of_test;i++)
    {    
	n = size/(1<<(n_of_test-i-1));
	printf("size:%ld",n);

 	print_performance(quick_s_central_pivot, M2[i], n);

	printf("\n");
    }
		

   deallocate_int_matrix(M2, max_n_of_test);
   deallocate_int_matrix(M3, max_n_of_test);
   
}
