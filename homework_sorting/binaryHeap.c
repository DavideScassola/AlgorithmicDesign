#include<stdio.h>
#include<stdlib.h>
#include "limits.h"

typedef struct BinaryHeap
{
    int* H;
    size_t size;
    int (*compare)(int,int);
} BinaryHeap;

BinaryHeap newBinaryHeap(size_t size)
{
    BinaryHeap bh;
    short unsigned int multiplier = 1; //how many more space it allocates
    bh.H = (int *) malloc(sizeof(int) * size * multiplier);
    bh.size = size;
    return bh;
}

void freeBinaryHeap(BinaryHeap bh)
{
    free(bh.H);
}

int left_child(int i)
{
    return 2*(i+1)-1;
}

int right_child(int i)
{
    return 2*(i+1);
}

int parent(int i)
{
    return (i-1)/2;
}

int root()
{
    return 0;
}

int is_root(int i)
{
    return i == root();
}

int last(BinaryHeap h)
{
    return h.size-1;
}

int is_valid_node(BinaryHeap h, int i)
{
    return h.size>i;
}

int heap_minimum(BinaryHeap h)
{
    return(h.H[root()]);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(BinaryHeap h, int i)
{
    int m = i;
    int j;

    j = left_child(i);
    if(is_valid_node(h, j) && h.compare(h.H[j],h.H[m]))
        m=j;

    j = right_child(i);
    if(is_valid_node(h, j) && h.compare(h.H[j],h.H[m]))
        m=j;

    if(i!=m)
    {
        swap(&(h.H[i]), &(h.H[m]));
        heapify(h,m);
    }
}

void remove_minimum(BinaryHeap *h)
{
    h->H[root()] = h->H[last(*h)];
    h->size--;
    heapify(*h,root());
}

BinaryHeap build_binary_heap(int* A, size_t n, int (*compare_function)(int,int))
{
    BinaryHeap h;
    h.size=n;
    h.H=A;
    h.compare=compare_function;
    for(int i=parent(last(h));i>=0;i--)
    {
        heapify(h, i);
    }
    return h;
}

void heap_decrease_key(BinaryHeap h, int i, int value)
{
    if(h.H[i]<=value)
        printf("%d is not smaller than the selected element", value);

    h.H[i]=value;

    while( !is_root(i) && h.compare(h.H[i],h.H[parent(i)]) )
    {
        swap(&(h.H[i]),&(h.H[parent(i)]));
        i = parent(i);
    }
        
}

void heap_insert(BinaryHeap* h, int value)
{
    (h->size)++;
    h->H[last(*h)] = INT_MAX;
    heap_decrease_key(*h, last(*h), value);
}

void show_heap(BinaryHeap h)
{
    printf("\nheap: %d", h.H[0]);
    for(int i=1;i<h.size;i++)
        printf(", %d", h.H[i]);
    printf("\n");
}

/*
int main()
{
    size_t n = 10;
    int* A = (int *) malloc(sizeof(int) * n * 2);
    for(int i=0;i<n;i++)
       {
           A[i]=n-i;
           printf("%d, ",A[i]);
       }

    printf("\n");
    
    for(int i=0;i<n;i++)
        A[i]=n-i;

    BinaryHeap h = build_binary_heap(A,n);

    show_heap(h);
    heap_insert(&h, -1);
    show_heap(h);
    remove_minimum(&h);
    show_heap(h);
    freeBinaryHeap(h);
}
*/
