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
void counting_s(int* A, size_t n) {counting_sort(A, MAX_VALUE, n);}
void radix_s(int* A, size_t n) {radix_sort(A, MAX_VALUE, 10, n);}
///////////////////////////////////////////////

void print_performance(void (*sorting_algorithm)(int*,size_t), int* v, size_t n)
{
	struct timespec b_time, e_time;
        clock_gettime(CLOCK_REALTIME, &b_time);
        sorting_algorithm(v,n);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("\t%lf", get_execution_time(b_time, e_time));
}

void print_performance_bucket_sort(float* v, size_t n)
{
	struct timespec b_time, e_time;
        clock_gettime(CLOCK_REALTIME, &b_time);
        bucket_sort(v,n);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("\t%lf", get_execution_time(b_time, e_time));
}

int main()
{

    size_t max_n_of_test = 8;
    size_t max_size = 1E7;
    size_t n;

    int **M4 = allocate_int_matrix(max_n_of_test, max_size); // counting
    int **M5 = allocate_int_matrix(max_n_of_test, max_size); // radix
    float **M6 = allocate_matrix(max_n_of_test, max_size); // bucket

    randomly_fill_positive_int_matrix(M4, max_n_of_test, max_size, max_size);
    matrix_copy(M5, M4, max_n_of_test, max_size);
    randomly_fill_uniform_matrix(M6, max_n_of_test, max_size); 

	
    ///// counting, radix, bucket /////
    size_t size = 1E7;
    size_t n_of_test = 8;

    printf("\t\tcounting_sort");
    printf("\tradix_sort");
    printf("\tbucket_sort\n");

    for(int i=0;i<n_of_test;i++)
    {    
	n = size/(1<<(n_of_test-i-1));
	printf("size:%ld",n);

	print_performance(counting_s, M4[i], n);
	print_performance(radix_s, M5[i], n);
	print_performance_bucket_sort(M6[i], n);

	printf("\n");
    }

   deallocate_int_matrix(M4, max_n_of_test);
   deallocate_int_matrix(M5, max_n_of_test);
   deallocate_matrix(M6, max_n_of_test);

}
