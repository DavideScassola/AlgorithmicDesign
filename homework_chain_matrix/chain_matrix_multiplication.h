#ifndef __CHAIN__

#include <stdlib.h>

void matrix_chain(int **S, int **M, int *dimensions, int n);
void show_parenthesization(int *P, int n);
void multiply_chain(float **O, float ***M, int *P, size_t n);
void multiply_chain_naive(float **O, float ***M, int *P, size_t n);

#endif // __CHAIN__
