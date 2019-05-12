#include<stdio.h>
#include<stdlib.h>

#include"binaryHeap.h"
#include"floatLinkedList.h"

int max(int a, int b)
{
	return a>b ? a : b;
}

int min(int a, int b)
{
	return a>b ? b : a;
}

void copy(int* A,int* B, size_t n)
{
	for(int i=0; i<n; i++)
		A[i]=B[i];
}

void s(int* v, size_t n)
{
	printf("\n");
	for(int i=0;i<n;i++)
		printf("%d ", v[i]);
}

void f(float* v, size_t n)
{
	printf("\n");
	for(int i=0;i<n;i++)
		printf("%f ", v[i]);
}

void swap(int *a, int *b);

void swap_float(float* a, float *b)
{
	float t = *a;
	*a = *b;
	*b = t;
}

int power(int basis, int exponent)
{
	int m = 1;
	for(int i=0; i<exponent; i++)
		m*=basis;
	return m;
}

int logarithm(int basis, int n)
{
	int m = 1;
	int exp = 0;
	for(exp=0;m<=n; exp++)
		m*=basis;
	return exp;
}

int partition(int *A, int left, int right, int pivot)
{
    int pivot_value = A[pivot];
    swap(&A[pivot], &A[left]);
    
    int j = right-1;
    int i = left+1;

    while(i<=j)
    {
        if(A[i]>pivot_value)
        {
            swap(&A[i],&A[j]);
            j--;
        }
        else
        {
            i++;
        } 
    }
    swap(&A[left],&A[j]);
    return j;
}

void insertion_sort(int* v, size_t n)
{
    int j;

    for(int i=1;i<n;i++)
    {
        j=i;
        while(j>0 && v[j]<v[j-1])
        {
            swap(&v[j],&v[j-1]);
            j=j-1;
        }
    }
}

void quick_sort_aux(int* v, int l, int r)
{
    while(l<r)
    {
        int p = partition(v,l,r,l);
        quick_sort_aux(v,l,p);
        l = p + 1;
    }
}

void quick_sort_aux_central_pivot(int* v, int l, int r)
{
    while(l<r)
    {
        int p = partition(v,l,r,(l+r)/2);
        quick_sort_aux_central_pivot(v,l,p);
        l = p + 1;
    }
}

void quick_sort_central_pivot(int* v, size_t n)
{     
    quick_sort_aux_central_pivot(v, 0, n);
}

void quick_sort(int* v, size_t n)
{     
    quick_sort_aux(v, 0, n);
}

int greater_or_equal(int a, int b)
{
    return a>=b;
}

int less_or_equal(int a, int b)
{
    return a<=b;
}

void heap_sort(int* v, size_t n)
{	
    BinaryHeap h = build_binary_heap(v, n, greater_or_equal);
	
    for(int i = n-1;i>=1;i--)
    {
        swap(&(h.H[0]),&(h.H[i]));
        h.size--;
        heapify(h,0);
    }
}

void counting_sort(int* A, size_t k, size_t n)
{
	int* C = (int*)calloc(k, sizeof(int));
	int* B = (int*)malloc(sizeof(int) * n);

	for(int i=0; i<n; i++)
		C[A[i]]++;

	for(int j=1; j<k; j++)
		C[j]+=C[j-1];

	for(int i=n-1; i>=0; i--)
	{
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;
	}

	free(C);
	copy(A,B,n);
	free(B);	
}

// it's an insertion sort
void sort(float* v, int start, int end)
{
    int j;

    for(int i=start+1;i<end;i++)
    {
        j=i;
        while(j>start && v[j]<v[j-1])
        {
            swap_float(&v[j],&v[j-1]);
            j=j-1;
        }
    }
}

// it's an insertion sort
void sort_int(int* v, int start, int end)
{
    int j;

    for(int i=start+1;i<end;i++)
    {
        j=i;
        while(j>start && v[j]<v[j-1])
        {
            swap(&v[j],&v[j-1]);
            j=j-1;
        }
    }
}

void bucket_sort(float* A, size_t n)
{
	List* B = allocate_lists_array(n);

	for(int i=0;i<n;i++)
	{
		push(&B[(int)(A[i]*n)], A[i]);
	}

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			for(int k=B[j].length-1;k>=0;k--)
			{
				A[i]=get(B[j],k);
				i++;
			}

		sort(A, i-B[j].length, B[j].length);
		}
	}

	free_lists_array(B, n);
}

// it returns the digit of the number n in the selected position (with respect to the selected basis)
unsigned int digit(unsigned int n, unsigned int position, const unsigned int basis)
{
	int m = power(basis, position);
	return ((n%(m*basis)) - (n%m))/(m);
}

//for radix sort
void counting_sort_aux(int* A, int digit_pos, int basis, size_t n)
{
	int* C = (int*)calloc(basis, sizeof(int));
	int* B = (int*)malloc(sizeof(int) * n);

	int* Adigits = (unsigned int*)malloc(sizeof(unsigned int) * n);

	for(int i=0; i<n; i++)
	{
		Adigits[i] = digit(A[i], digit_pos, basis);
	}
		

	for(int i=0; i<n; i++)
		C[Adigits[i]]++;

	for(int j=1; j<basis; j++)
		C[j]+=C[j-1];

	for(int i=n-1; i>=0; i--)
	{
		B[C[Adigits[i]]-1] = A[i];
		C[Adigits[i]]--;
	}

	free(C);
	free(Adigits);
	copy(A,B,n);
	free(B);
}


void radix_sort(int* v, unsigned int max, int basis, size_t n)
{
	unsigned n_of_digits = logarithm(basis, max);
	for(int i=0; i<n_of_digits; i++)
	{
		counting_sort_aux(v, i, basis, n);
	}
}


/*
This new partition algorithm deals with repeated values in the array: 
the problem is that values that are equal to the pivot are put all in the same side,
creating in this way an unbalancing.
I resolved this issue distributing in an equal way the equal values (half are treated like smaller values, half are treated like bigger values).
*/
int smart_partition(int *A, int left, int right, int pivot)
{
    int pivot_value = A[pivot];
    swap(&A[pivot], &A[left]);
    short skip = 1; // left or right
    
    int j = right-1;
    int i = left+1;

    while(i<=j)
    {
        if(A[i]==pivot_value)
            skip = !skip;   // I change it at each time

        if(A[i]>pivot_value || (A[i]==pivot_value && !skip))
        {
            swap(&A[i],&A[j]);
            j--;
        }
        else
        {
            i++;
        } 
    }
    swap(&A[left],&A[j]);
    return j;
}

int select_pivot(int* A, size_t l, size_t r)
{
	if(r-l<5)
	{
		sort_int(A,l,r);
		return (l+r)/2;
	}	

	int m_size = ((r-l-1)/5)+1;

	for(int i=0;i<m_size;i++)
		sort_int(A, 5*i + l, min(5*i + l + 4 + 1, r));

	for(int i=0;i<m_size;i++)
		swap(&A[l+i], &A[min(5*i + l + 2, r-1)]);

	int m = select_pivot(A, l, l+m_size);

	return m;
}

int select_aux(int* A, size_t i, size_t l, size_t r)
{
	if(l==r-1)
		return A[l];

	int p = select_pivot(A, l, r);
	int k = smart_partition(A, l, r, p);

	if(i==k)
		return A[k];

	if(i<k)
		return select_aux(A, i, l, k);
	
	else
		return select_aux(A, i, k+1, r);
}

int selection(int* A, int i, size_t n)
{
	return select_aux(A,i,0,n);
}









// this code was just for debugging purposes
/*
int main()
{	
	/*
	size_t n = 20;
	float* A = (float*)malloc(sizeof(float)*n);
	for(int i=0;i<n;i++)
		A[i]=((float)((n-i)%12))/1000;
	
	f(A,n);
	bucket_sort(A, n);
	f(A,n);
	printf("\n");

	free(A);
	*/  

	/*
	size_t n = 10000;
	int* A = (int*)malloc(sizeof(int)*n);
	for(int i=0;i<n;i++)
		A[i]=(n-1-i)%2;
	
	//f(A,n);
	//s(A,n);
	printf("\n");
	//counting_sort_aux(int** v, size_t n, int digit_pos, int basis, int n_of_digits)
	//counting_sort_aux(&A, 20, 1, 10, 2);
	//printf("%d",digit(178, 0, 10));
	//counting_sort(&A, 13000, n);
	//radix_sort(&A, 20, 20, n);
	//for(int i=0;i<n;i++)
	//int i = 13;
		//printf("\nA[%d]=%d",i,select2(A, i, n));
	//printf("\n%d",partition(A, 0, n, 0));
	//s(A,n);
	
	//printf("\nthe pivot is:%d\n", select_pivot(A, 0, n));
	//counting_sort(&A, n*100, n);
	//counting_sort(A,10000,n);

	for(int p=0; p<n; p++)
        selection(A, p, n);
        //if(p%1000 == 0)
		    //printf("\n A[%d]=%d ", p, selection(A, p, n));
	//heap_sort(A,n);
	//s(A,n);
	free(A);

}
*/
