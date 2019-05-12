#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "binaryHeap.h"
#include "matrix.h"

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}

int less_or_equal(int a, int b)
{
	return a<=b;
}

int main()
{
    printf("initialization ... \n");
    const size_t n_of_test = 3;
    const size_t size = 1E8;
    int **M1 = allocate_int_matrix(n_of_test, size);

    randomly_fill_int_matrix(M1, n_of_test, size, size);


    struct timespec b_time, e_time;

    printf("\tbuild_heap_time: (size = %ld)\n", size);

	
    for(int i=0;i<n_of_test;i++)
    {
        clock_gettime(CLOCK_REALTIME, &b_time);
        BinaryHeap h = build_binary_heap(M1[i], size, less_or_equal);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("test %d \t%lf\n", i+1, get_execution_time(b_time, e_time));
    }

    
    
   deallocate_int_matrix(M1, n_of_test);
}
