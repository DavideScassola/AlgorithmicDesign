#ifndef __AH__

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int d;
    int id;
    int position;
    struct Node* pred;
} Node;

typedef struct Array
{
    Node** A;
    size_t size;
} Array;

int array_empty(Array* a);
Array build_Array(Node* nodes, size_t n);

Node* extract_array_minimum(Array* a);
void freeArray(Array bh);

///////////////////////////////////////////////////////////////////

typedef struct Heap
{
    Node** H;
    size_t size;
    int (*compare)(int,int);
} Heap;

int empty(Heap* h);
Heap build_heap(Node* A, size_t n, int (*compare_function)(int,int));
int less(int a, int b);
void pns(Node** nodes, int n);
void pn(Node* n);
void update_distance(Heap* h, Node* v, int w);
Node* extract_minimum(Heap* h);
void freeHeap(Heap bh);

#endif // __AH__
