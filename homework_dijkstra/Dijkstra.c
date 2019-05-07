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

int weight(Graph* g, Node* from, Node* to)
{
    return g->weights_m[from->id*g->size + to->id];
}

Node* getNode(Graph* g, int id)
{
    Node* v = g->v;
    for(int i=0; i<g->size; i++)
        if(v[i].id == id) return &v[i];
    return NULL;
}

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

Node** adjacents(Graph* g, Node* u)
{
    int n = adjacents_len(g, u);
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
        update_distance(q, v->id, u->d + w);
        v->pred = u;
    }
}

void relax_array(Array* q, Node* u, Node* v, int w)
{
    if(u->d + w < v->d)
    {
        array_update_distance(q, v->id, u->d + w);
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

        Node** u_adj = adjacents(g, u);
        int n =  adjacents_len(g, u);

        for(int i=0; i<n; i++)
            relax(q, u, u_adj[i], weight(g, u, u_adj[i]));
        free(u_adj);
    }
    freeHeap(Q);
}

void printArray(Array* a)
{
    for(int i=0; i<a->size; i++)
    {
        pn(a->A[i]);
    }
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
        Node** u_adj = adjacents(g, u);
        int n =  adjacents_len(g, u);

        for(int i=0; i<n; i++)
                relax_array(q, u, u_adj[i], weight(g, u, u_adj[i]));

        free(u_adj);
        
    }
    freeArray(Q);
}

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

/*
int main()
{
    int size = 5;
    int* adj_matrix = (int*) malloc(sizeof(int)*size*size);

    for(int i=0; i<size*size; i++)
        adj_matrix[i]=INF;

    adj_matrix[size*0 + 1] = 5; adj_matrix[size*0 + 4] = 10;
    adj_matrix[size*1 + 4] = 3; adj_matrix[size*1 + 3] = 9; adj_matrix[size*1 + 2] = 2;
    adj_matrix[size*2 + 0] = 7; adj_matrix[size*2 + 3] = 6;
    adj_matrix[size*3 + 2] = 4;
    adj_matrix[size*4 + 1] = 2; adj_matrix[size*4 + 3] = 1;

    Graph g;
    g.size=size;
    g.weights_m = adj_matrix;
    g.v = (Node*) malloc(sizeof(Node)*size);

    printf("starting graph\n"); 
    show_graph(&g);

    printf("\n\n\n");

    printf("array solution\n"); 
    Dijkstra_array(&g, 0);
    show_graph(&g);

    printf("\n\n\n");

    printf("heap solution\n");
    Dijkstra_heap(&g, 0);
    show_graph(&g);

    free(adj_matrix);
    free(g.v);

    return 0;
}
*/
