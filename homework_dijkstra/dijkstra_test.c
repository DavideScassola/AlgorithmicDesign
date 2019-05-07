
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "Dijkstra.h"

double get_execution_time(const struct timespec b_time, const struct timespec e_time)
{
    return (e_time.tv_sec-b_time.tv_sec) + (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}

int abs(int x)
{
    return x>0 ? x : -x;
}

void print_performance(void (*algorithm)(Graph*, int), Graph* g)
{
	struct timespec b_time, e_time;
        clock_gettime(CLOCK_REALTIME, &b_time);
        algorithm(g, g->size/2);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("\t%lf", get_execution_time(b_time, e_time));
}

int main()
{
    int size = 20000;
    int n_of_test = 5;
    struct timespec b_time, e_time;
    

    ////////// Graph initialization //////////
    printf("initialization  . . .");

    int* adj_matrix = (int*) malloc(sizeof(int)*size*size);
    Graph g;
    g.weights_m = adj_matrix;
    g.v = (Node*) malloc(sizeof(Node)*size);
  

    ////////// Dijkstra shortest path search in a dense graph//////////

    /// building dense adjacency matrix
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            adj_matrix[i*size + j] = (abs(j-i-1)*2+1 + 80*((i+j)%3==0))/(1+5*((i+j)%(9)==0));


    printf("\n\nDijkstra shortest path search in a dense graph:\n");
   
    printf("\t\t\theap");
    printf("\t\tarray\n");

    for(int i=0;i<n_of_test;i++)
    {    
	g.size = size/(1<<(n_of_test-i-1));
	printf("n of nodes:%d ",g.size);

 	print_performance(Dijkstra_heap, &g);
	print_performance(Dijkstra_array, &g);

	printf("\n");
    }



    ////////// Dijkstra shortest path search in a sparse graph //////////

    printf("\n\nDijkstra shortest path search in a sparse graph:\n");
   
    printf("\t\t\theap");
    printf("\t\tarray\n");

    for(int i=0;i<n_of_test;i++)
    {    
	g.size = size/(1<<(n_of_test-i-1));

        /// building sparse adjacency matrix
        for(int i=0; i<g.size*g.size; i++)
            adj_matrix[i] = INF;

        for(int i=0; i<g.size-1; i++)
	    adj_matrix[i*g.size + i + 1] = 2;
	adj_matrix[(g.size-1)*g.size] = 2;
            
	printf("n of nodes:%d ", g.size);

 	print_performance(Dijkstra_heap, &g);
	print_performance(Dijkstra_array, &g);

	printf("\n");
    }


    free(adj_matrix);
    free(g.v);

    return 0;
}
