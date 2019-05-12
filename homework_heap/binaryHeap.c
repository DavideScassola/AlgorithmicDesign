#include<stdio.h>
#include<stdlib.h>
#include "limits.h"

typedef struct BinaryHeap
{
    int* H;
    size_t size;
    int (*compare)(int,int);
} BinaryHeap;


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


void freeBinaryHeap(BinaryHeap bh)
{
    free(bh.H);
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
    int lc, rc;
    int old = m;
    int finished = 0;

    while(!finished)
    {
        rc = right_child(m);
        lc = left_child(m);
	m = (is_valid_node(h, rc) && h.compare(h.H[rc],h.H[m])) ? rc : m;
        m = (is_valid_node(h, lc) && h.compare(h.H[lc],h.H[m])) ? lc : m;

        if(old!=m)
        {
            swap(&(h.H[m]), &(h.H[old]));
            old = m;
        }
        else 
            finished = 1;
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
        heapify(h, i);

    return h;
}


void heap_decrease_key(BinaryHeap h, int i, int value)
{
    if(h.compare(h.H[i],value))
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
