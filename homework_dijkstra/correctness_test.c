#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "Dijkstra.h"

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
