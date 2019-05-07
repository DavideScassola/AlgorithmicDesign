#ifndef __DJ__

#include <stdio.h>
#include <stdlib.h>
#include "array_heap.h"
#define INF 2147483647

typedef struct Graph
{
    Node* v;
    int* weights_m;
    int size;
} Graph;

int weight(Graph* g, Node* from, Node* to);

Node* getNode(Graph* g, int id);

int adjacents_len(Graph* g, Node* u);

Node** adjacents(Graph* g, Node* u);

void initialize(Graph* g);

void relax(Heap* q, Node* u, Node* v, int w);

void relax_array(Array* q, Node* u, Node* v, int w);

void Dijkstra_heap(Graph* g, int start_id);

void Dijkstra_array(Graph* g, int start_id);

void show_graph(Graph* g);


#endif // __DJ__
