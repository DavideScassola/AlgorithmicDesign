#ifndef __SORTING__

#include<stdio.h>
#include<stdlib.h>
#include"binaryHeap.h"

void insertion_sort(int* v, size_t n);
void quick_sort(int* v, size_t n);
void heap_sort(int* v, size_t n);

void quick_sort_central_pivot(int* v, size_t n);

void counting_sort(int* A, size_t k, size_t n);
void bucket_sort(float* A, size_t n);
void radix_sort(int* v, unsigned int max, int basis, size_t n);

int selection(int* A, int i, size_t n);

#endif // __SORTING__
