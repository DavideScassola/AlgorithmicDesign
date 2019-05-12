#include<stdio.h>
#include<stdlib.h>
#include "limits.h"

typedef struct Node
{
    int d; // distance from source (dijkstra)
    int id;
    int position; // when I have a node I need to know its position in the heap
    struct Node* pred; // predecessor node i the shortest path (dijkstra)
} Node;

typedef struct Heap
{
    Node** H;
    size_t size;
    int (*compare)(int,int);
} Heap;

int empty(Heap* h)
{
    return h->size==0;
}

void freeHeap(Heap bh)
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
    return i == 0;
}

int last(Heap h)
{
    return h.size-1;
}

int is_valid_node(Heap h, int i)
{
    return h.size>i;
}

Node* heap_minimum(Heap h)
{
    return(h.H[0]);
}

void swap(Node** a, Node** b)
{
    int t = (**a).position;
    (**a).position = (**b).position;
    (**b).position = t;

    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap h, int i)
{
    int m = i;
    int j;

    j = 2*(i+1)-1;
    if(is_valid_node(h, j) && (h.H[j]->d < h.H[m]->d))
        m=j;

    j = 2*(i+1);
    if(is_valid_node(h, j) && (h.H[j]->d < h.H[m]->d))
        m=j;

    if(i!=m)
    {
        swap(&(h.H[i]), &(h.H[m]));
        heapify(h,m);
    }
}

Node* extract_minimum(Heap* h)
{
    Node* m = (h->H[0]);
    h->H[0] = h->H[last(*h)];
    h->size--;
    heapify(*h,0);
    return m;
}

Heap build_heap(Node* A, size_t n, int (*compare_function)(int,int))
{
    Node** node_pointers = (Node**) malloc(sizeof(Node*)*n);

    for(int i=0; i<n; i++)
    {
        A[i].position = i;
        node_pointers[i]=&(A[i]);
    }

    Heap h;
    h.size=n;
    h.H=node_pointers;
    h.compare=compare_function;
    for(int i=parent(last(h));i>=0;i--)
    {
        heapify(h, i);
    }
    return h;
}


void heap_decrease_key(Heap* h, int i, int value)
{
    //if(h->compare(h->H[i]->d,value))
        //printf("%d is not smaller than the selected element", value);

    h->H[i]->d=value;

    while( !is_root(i) && (h->H[i]->d < h->H[(i-1)/2]->d) )
    {
        swap(&(h->H[i]),&(h->H[(i-1)/2]));
        i = (i-1)/2;
    }
        
}

void update_distance(Heap* h, Node* v, int w)
{
    int pos = v->position;
    heap_decrease_key(h, pos, w);
}

void show_heap(Heap h)
{
    printf("\nheap: id:%d-d:%d", h.H[0]->id, h.H[0]->d);
    for(int i=1;i<h.size;i++)
        printf(", id:%d-d:%d", h.H[i]->id, h.H[i]->d);
    printf("\n");
}

void pn(Node* n)
{
    int id = n->pred == NULL ? -1:n->pred->id;
    printf("\n id:%d d:%d pred:%d", n->id, n->d, id);
}

void pns(Node** nodes, int n)
{
    for(int i=0; i<n; i++)
        pn(nodes[i]);
}

int less(int a, int b)
{
    return a<b;
}
