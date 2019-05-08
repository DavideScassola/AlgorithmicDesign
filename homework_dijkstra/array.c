#include<stdio.h>
#include<stdlib.h>
//#include "limits.A"

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

int array_empty(Array* a)
{
    return a->size==0;
}

void freeArray(Array a)
{
    free(a.A);
}


void array_swap(Node** a, Node** b)
{
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void array_remove(Array *a, int i)
{
    array_swap(&a->A[i], &a->A[a->size-1]);
    a->size--;
}

Node* extract_array_minimum(Array* a)
{
    int min = a->A[0]->d;
    int min_index = 0;
    for(int i=1; i<a->size; i++)
        { 
            if(a->A[i]->d<min)
                {
                    min = a->A[i]->d;
                    min_index = i;
                }
        }

    Node* n = a->A[min_index];
    array_remove(a,min_index);
    return n;
}

Array build_Array(Node* nodes, size_t n)
{
    Node** node_pointers = (Node**) malloc(sizeof(Node*)*n);
    for(int i=0; i<n; i++)
        node_pointers[i]=&(nodes[i]);

    Array a;
    a.size=n;
    a.A=node_pointers;

    return a;
}


int array_findNode(Array* a, int node_id)
{
    for(int i=0; i<a->size; i++)
        if(node_id == a->A[i]->id) return i;
    return -1;
}

void show_Array(Array a)
{
    printf("\nArray: id:%d-d:%d", a.A[0]->id, a.A[0]->d);
    for(int i=1;i<a.size;i++)
        printf(", id:%d-d:%d", a.A[i]->id, a.A[i]->d);
    printf("\n");
}
