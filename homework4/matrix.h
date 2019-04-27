#ifndef __MATRIX__

#include <stdlib.h>
#include <stdio.h>

int naive_matrix_mult(float **C,
                        float **A,
                        float **B,
                        const size_t A_rows,
                        const size_t A_cols,
                        const size_t B_rows,
                        const size_t B_cols);

float **allocate_matrix(const size_t rows,
                        const size_t cols);

void deallocate_matrix(float **A, const size_t rows);

int same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		float **B, const size_t B_rows, const size_t B_cols);

int **allocate_int_matrix(const size_t rows, const size_t cols);

void deallocate_int_matrix(int **A, const size_t rows);

void show_matrix(int **M, const size_t rows, const size_t cols);

void matrix_copy(int** Out, int **In, const size_t rows, const size_t cols);

void randomly_fill_matrix(float **A, const size_t A_rows, const size_t A_cols, const size_t max_value);

void randomly_fill_int_matrix(int **A, const size_t A_rows, const size_t A_cols, const size_t max_value);

int almost_same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		float **B, const size_t B_rows, const size_t B_cols, float precision);

void show_float_matrix(float **M, const size_t rows, const size_t cols);

#endif // __MATRIX__
