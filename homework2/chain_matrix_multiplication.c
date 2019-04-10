#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "limits.h"


void matrix_chain_aux(int *P, int **M, int **S, int i, int j)
{
	M[i][j] = INT_MAX;

	for(int k=i+1; k<=j; k++)
	{
		int q = M[i][k-1] + M[k][j] + P[i]*P[k]*P[j+1];
		if(q < M[i][j])
		{
			M[i][j]= q;
			S[i][j-1] = k;
		}
	}
}

void matrix_chain(int **S, int **M, int *P, int n)
{

	for(int i=0; i<n; i++)
	{
		M[i][i]=0;
	}

	for(int l=2; l<=n; l++)
	{
		for(int i=0; i<(n-l+1); i++)
		{
			int j = i + l - 1;
			matrix_chain_aux(P,M,S,i,j);
		}
	}
}

void show_parenthesization(int *P, int n)
{
	unsigned int dim = n-1;
 	int **M=allocate_int_matrix(dim,dim);
	int **S=allocate_int_matrix(dim-1,dim-1);
	
	// I clean the matrix M
	for(int i=0;i<dim;i++)
		for(int j=0;j<dim;j++)
			M[i][j]=0;

  	matrix_chain(S, M, P, dim);

	printf("\n\nMatrix M:\n");
  	show_matrix(M, dim, dim);

	printf("\nMatrix S:\n");
  	show_matrix(S, dim-1, dim-1);

  	deallocate_int_matrix(M,dim);
  	deallocate_int_matrix(S,dim-1);

}

void multiply_chain_aux(float **O, float ***M, int **S, int *P, size_t left, size_t right)
{
	if(left==right-1)
	{
		//printf("caso base (left=%ld)\n",left);
		matrix_copy(O,M[left], P[left], P[left+1]);
		return;
	}

	size_t parenthesis = S[left][right-2];//controlla indice (forse devi fare +1 a right)
	//printf("left=%ld, right=%ld, parenthesis =%ld\n",left,right,parenthesis);

	size_t A_rows = P[left];
	size_t A_cols = P[parenthesis];
	size_t B_rows = P[parenthesis];
	size_t B_cols = P[right];
	float **A = allocate_matrix(A_rows, A_cols);
	float **B = allocate_matrix(B_rows, B_cols);

        multiply_chain_aux(A,M,S,P, left, parenthesis);
        multiply_chain_aux(B,M,S,P, parenthesis, right);	

	naive_matrix_mult(O, A, B, A_rows, A_cols, B_rows, B_cols);
	//printf("sto moltiplicando, left=%ld, right=%ld, par=%ld\n",left,right,parenthesis);

	deallocate_matrix(A, A_rows);
	deallocate_matrix(B, B_rows);
	//printf("qui ci sono arrivato\n");
}

void multiply_chain(float **O, float ***M, int *P, size_t n)
{
	unsigned int dim = n-1;
	int **S = allocate_int_matrix(dim-1, dim-1);
	int **cost=allocate_int_matrix(dim,dim);

	matrix_chain(S, cost, P, dim);
	multiply_chain_aux(O,M,S,P,0,dim);

  	deallocate_int_matrix(cost,dim);
  	deallocate_int_matrix(S,dim-1);
}

void multiply_chain_naive_aux(float **O, float ***M, int *P, size_t left, size_t right)
{
	if(left==right-1)
	{
		//printf("caso base (left=%ld)\n",left);
		matrix_copy(O,M[left], P[left], P[left+1]);
		return;
	}

	size_t parenthesis = (left+right)/2;
	//printf("left=%ld, right=%ld, parenthesis =%ld\n",left,right,parenthesis);

	size_t A_rows = P[left];
	size_t A_cols = P[parenthesis];
	size_t B_rows = P[parenthesis];
	size_t B_cols = P[right];
	float **A = allocate_matrix(A_rows, A_cols);
	float **B = allocate_matrix(B_rows, B_cols);

        multiply_chain_naive_aux(A,M,P, left, parenthesis);
        multiply_chain_naive_aux(B,M,P, parenthesis, right);	

	naive_matrix_mult(O, A, B, A_rows, A_cols, B_rows, B_cols);
	//printf("sto moltiplicando, left=%ld, right=%ld, par=%ld\n",left,right,parenthesis);

	deallocate_matrix(A, A_rows);
	deallocate_matrix(B, B_rows);
	//printf("qui ci sono arrivato\n");
}

void multiply_chain_naive(float **O, float ***M, int *P, size_t n)
{
	unsigned int dim = n-1;

	multiply_chain_naive_aux(O,M,P,0,dim);
}


