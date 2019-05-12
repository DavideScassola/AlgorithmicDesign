#include <stdio.h>
#include <stdlib.h>
#include "array_heap.h"
#define INF 2147483647

typedef struct Graph
{
    Node* v; // list of nodes
    int* weights_m; // adjacency matrix
    int size; // n of nodes
} Graph;


void show_graph(Graph* g)
{
    int size = g->size;
    printf("\nsize: %d\nweights:\n", g->size);

    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(g->weights_m[size*i+j]==INF)
                printf("// ");
            else 
                printf("%2d ", g->weights_m[size*i+j]);
        }
        printf("\n");
    }

    for(int i=0; i<size; i++)
    {
        Node x = g->v[i];
        
        printf("\n node %d, dist=%d", x.id, x.d);
        if((x.pred)!=NULL)
            printf(", pred=%d", x.pred->id);
        else
            printf(", /");

    }

    printf("\n");
}


// it returns the weight of the edge connecting the two given nodes
int weight(Graph* g, Node* from, Node* to)
{
    return g->weights_m[from->id*g->size + to->id];
}


// returns a node from a graph given its id
Node* getNode(Graph* g, int id)
{
    Node* v = g->v;
    for(int i=0; i<g->size; i++)
        if(v[i].id == id) return &v[i];
    return NULL;
}


// returns the number of nodes adjacent to a given node
int adjacents_len(Graph* g, Node* u)
{
    int n = 0;
    for(int i=0; i<g->size; i++)
    {
        if((g->v)[i].id == u->id) continue;
        n+=(weight(g,u,&(g->v)[i]))< INF;
    }
        
    return n;
}


// returns nodes adjacent to a given node
Node** adjacents(Graph* g, Node* u, int n)
{
    Node** adj = (Node**) malloc(sizeof(Node*)*n);
    int a = 0;
    for(int i=0; i<g->size; i++)
    {
        int w = weight(g,u,&(g->v)[i]);
        if(w<INF && (g->v)[i].id != u->id)
                adj[a++] = &(g->v)[i];
    }
         
    return adj;
}


// initializes the nodes of the graph for a Dijkstra search
void initialize(Graph* g) 
{
    int n = g->size;
    for(int i=0; i<n; i++)
    {
        (g->v[i]).id = i;
        (g->v[i]).d = INF;
        (g->v[i]).pred = NULL;
    }
}


void relax(Heap* q, Node* u, Node* v, int w)
{
    if(u->d + w < v->d)
    {
        update_distance(q, v, u->d + w);
        v->pred = u;
    }
}


void relax_array(Array* q, Node* u, Node* v, int w)
{
    if(u->d + w < v->d)
    {
        v->d = u->d + w; // the update is simpler in the array implementation
        v->pred = u;
    }
}


void Dijkstra_heap(Graph* g, int start_id)
{
    initialize(g);
    Node* s = getNode(g, start_id);
    s -> d = 0;

    Heap Q = build_heap(g->v,  g->size, less);
    Heap* q = &Q;

    while(!empty(q))
    {
        Node* u = extract_minimum(q);
	int n =  adjacents_len(g, u);
        Node** u_adj = adjacents(g, u, n);
        
        for(int i=0; i<n; i++)
            relax(q, u, u_adj[i], weight(g, u, u_adj[i]));
        free(u_adj);
    }
    freeHeap(Q);
}


void Dijkstra_array(Graph* g, int start_id)
{
    initialize(g);
    Node* s = getNode(g, start_id);
    s -> d = 0;

    Array Q = build_Array(g->v,  g->size);
    Array* q = &Q;

    while(!array_empty(q))
    {
        Node* u = extract_array_minimum(q);
	int n =  adjacents_len(g, u);
        Node** u_adj = adjacents(g, u, n);

        for(int i=0; i<n; i++)
                relax_array(q, u, u_adj[i], weight(g, u, u_adj[i]));

        free(u_adj);
        
    }
    freeArray(Q);
}
